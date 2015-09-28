---
layout: post
title: "your stack overfloweth"
date: 2015-07-31 11:34:08 -0400
---

*How She Gets to See Shells Because of Terrible C Code*

SUMMARY: This post will walk you through the basics of why buffer overflows are so damn dangerous in C.
I've been learning C for a while, and one of the ways I've found to keep myself engaged is to explore how exploits work.
I'm going to focus on the *STACK OVERFLOW* and get pretty deep into exactly how a buffer overflow can result in pwnage.

So first things first, how do computers even?

# How do computers even?

¯\\(°_o)/¯

Deep inside your computer, everything clever that is happening, happens on your CPU.
Your CPU is told what to do by INSTRUCTIONS, also known as assembly.
Specifically, x86 assembly (as opposed to ARM which is what all your phone is running)
These instructions look something like this

    ADD rax, 05

Which is x64 assembly to add 5 to rax.

Technically that isn't what your CPU sees though. It prefers something more like

    8366 05c0

Obviously the CPU needs to get these instructions from somewhere, and that somewhere is MEMORY.
Your computer has a lot of memory, and as with any thing that is numerous, we need a way to specify which memory spot we are talking about.
This is done using an ADDRESS that is 64 bits long.

So our instruction from before might be stored in a memory location with address:

    0xffbfc3a0

One important fact about computers is that they flexible.
They would be much less powerful if they could only follow instructions starting at the beginning of memory (address 0x00000000) and go up one memory spotafter every instruction.
Normally, that's what happen though. Once the CPU finishes an instruction it goes to the next instruction which is located at the "next" address.
But our CPU isn't dumb!
Our CPU can jump around!
It can go from `0xdeadbeef` to `0xabad1dea` and back again if it was told to.
What that implies is that somehow it needs to keep track of where it is going next.

It does this in a _register_ (don't worry about those for now) once upon a time called the Instruction Pointer (IP), then called EIP, now called *RIP* which holds the address of the next instruciton the CPU will execute.

Now as a Bad Person (tm), what I really want to do is to take control of RIP.
If I can make RIP point at some location of my choosing, I can probably make your computer do whatever I want.

So, how do you do mess with RIP?

Well sadly there is no instruction (like `add` or `sub`) for directly setting this register, unlike most other registers.
But before we proceed any further I think we should explore this register thing a bit further.

# A brief detour into registers

There are many registers on your CPU, which are kind of like places to store / get information.
As your CPU executes instructions, it needs a place to read input from and write output to.
Sometimes, it uses memory (AKA RAM), but it's faster and easier to use a register.

Here's a list of the registers (probably) on your machine

 - RAX
 - RBX
 - RCX
 - RDX
 - RSI
 - RDI
 - RBP
 - RSP
 - R8
 - R9
 - R10
 - R11
 - R12
 - R13
 - R14
 - R15

Some of them are "general purpose" registers, which are used for whatever a program/programmer feels like.
Some of them are special and hold values like whether the `add` instruction your cpu just performed resulted in an carry, or where the current stack starts.
Many CPU instructions take a register as an argument and can load information from it, or put the result of the operation there.
But enough about those other register. What we want to know about is RIP.

The way RIP is manipulated happens with 3 instructions:

    jmp, call and ret

`jmp address` will make your CPU go directly to the address given to it.
But I want to focus on `call` and `ret` for now, which are used for: (drumroll please)

# Subroutines

So, `call` and `ret` (short for return) are ways that programs can use _subroutines_ (aka functions), one of the most important abstractions in programming.

`call 0x12341234` will set RIP to an address (just like `jmp`).
Once we've arrived at the address, the CPU does it's normal thing of executing the instruction located in the next address.
But when we're done with our subroutine, we execute `ret` and return to the memory location that comes after address where we ran `call`.
This means that we need to keep track of where we return to.
In order to do that, what `call` does (in addition to jumping) is to push the current value RIP onto the _stack_

# The STACK

Now, as this post is about stack overflows, you've probably come to conclusion that this next bit is important, given that it's one of the words in the title.
And you would be correct.

The stack is a *Last In, First Out* data structure.
Basically, it's a place to store stuff with some important properties.
When you "push" a stuff onto a a stack, it will stay there until you retrieve it.
When you "pop" the stack, you remove the last thing you pushed to the stack.
You're not allowed to get a stuff back from the stack unless it was the last thing you pushed there.

Now, in assembly you can push values onto the stack with

    push val

and you can also

    pop dest

to get the last value you pushed back.

When you do this, a special register called the *STACK POINTER* (known once as SP, then ESP, now RSP) GETS SMALLER.
The Stack Pointer holds the location in memory of the last item that was pushed to the stack.
It's important to note that because SP is decemented it means

### The stack GROWS DOWN

(This confused me for a long time, so I'm going to say it again)

### The stack GROWS DOWN

More recent items on the stack have lower memory addresses, and olders ones have higher (larger) memory addresses.
I know this seems a bit abitrary, but keep this in mind for now.

# Stack Variables

When you call a function in C, you have have variables that live only during that function call and they are sometimes referred to as Stack Variables.
As you might guess from the name, stack variables live on the stack. Here's an example:

    void example() {
      int a;
      char b[10];
    }

Both `a` and `b` are stored on the stack...

Yes, that's right

**They live alongside the <u>stored instruction pointer</u>**

This fact of the CPU will result in us being able to take over a computer in a little while.

But first, a small detour

# Strings in C

First things first,

**Strings in C are a LIE**

There's no such thing as a string in C.
They are just arrays of characters.
That is, some continuous sequence of memory addresses.
By convention, a "string"  will will end with a null character ('\0').

Sometimes as programmers, we don't know how long a string will end up being.
So we make a variable / reserve some memory of some size we decide when we're writing the program.
That's why a string ends with a null character, because we won't always fill the space we've set aside for our "string".

In C/Assembly, "strings" are passed around by giving methods a pointer to the starting memory address.
You'll notice that one thing we *don't* have here: a length.

That means, as a programmer it's up to you to keep track of how long your string is, and how big the array you are storing it is.
If you make a mistake... you can easily access or overwrite further than you intened to in your "string".

Now, in C array access happens from low to high.
That is if you have `char a[10]` then `a[0]` is a at a lower address than `a[10]`

*HERE'S THE PROBLEM*

(so pay attention)

*Stack variables, like a char array live on the stack, and the return address for a subroutine ALSO LIVES ON THE STACK.*

Combined with the fact that you can easily write past the end of a char array in C if you're not careful leads to the prevelance of the *STACK OVER FLOW*

Suppose I have the following C program

```
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

        char buf[128]; // allocate a "string" on the stack

        if(argc < 2) return 1; // do nothing if there's no argument

        strcpy(buf, argv[1]); //copy the argument passed to this program into buf

        printf("%s\n", buf); //print buf

        return 0;
}
```

This code is basically just echoing the first argument I pass to it when I run from the command line.
See?

```
$ ./example1 foobar
foobar
$ ./example1
$
```

But what I'm *not* doing is making sure that the value at `argv[1]` is small enough to fit into buf.
Can you guess what happens if we call this program with a string larger than 128 characters?

(hint: it's why I'm here)
Yes, that's right a **STACK OVERFLOW**

When you call run the program the `main` function is called using `call`, which means somewhere there's a return address that `ret` will use when we're done.

Now, when main was called, the stack pointer had some value.
Let's suppose it was 0x0000ff00.


# SHELLCODE

```
BITS 32

; execve(const char *filename, char *const argv [], char *const envp[])
  push BYTE 11      ; push 11 to the stack
  pop eax           ; pop dword of 11 into eax
  push ecx          ; push some nulls for string termination
  push 0x68732f2f   ; push "//sh" to the stack
  push 0x6e69622f   ; push "/bin" to the stack
  mov ebx, esp      ; put the address of "/bin//sh" into ebx, via esp
  push ecx          ; push 32-bit null terminator to stack
  mov edx, esp      ; this is an empty array for envp
  push ebx          ; push string addr to stack above null terminator
  mov ecx, esp      ; this is the argv array with string ptr
  int 0x80          ; execve("/bin//sh", ["/bin//sh", NULL], [NULL])
```

# How Compilers and Operating Systems Keep us Safe

 * ASLR: Address Space Layout Randomization
 * Non executable stack
 * Stack smashing detection: Insert secure value between stack frames and check before calling ret OR Insert 0000000 because you can't have 0s in your shellcode


# Want to learn more?

 * Hacking: The art of Exploitation
 * Smashing the Stack for Fun and Profit: Phrack Magazine #49: http://www.phrack.org/archives/49/P49-14
 * Anatomy of a Stack Smashing Attack and How GCC Prevents It: http://www.drdobbs.com/security/anatomy-of-a-stack-smashing-attack-and-h/240001832?pgno=3
