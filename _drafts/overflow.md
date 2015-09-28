layout: true
class: center, middle, inverse
---

# Your Stack Overfloweth
How She Gets to See Shells Because of Terrible C Code

???

SUMMARY: This talk will walk you through the basics of why buffer overflows are so damn dangerous in C

BACKGROUND:

 * layout of the stack
 * function calls
 * basic C memory layouts
 * basic strcpy overflow (overwrite check bit)
 * function pointer overflow
 * shellcode?

Hi, my name's Wesley and I'm an android developer on Sello. That's mostly unrelated to this talk though.

I've been learning some C by way of learning simple exploits.

I want to get really deep into exactly how a buffer overflow can result in pwnage

So first things first, how do computers even?

---

# How do computers even?

???

Deep inside your computer, everything that is happening, happens in assembly.

Specifically, x86 assembly (as opposed to ARM which is what all your phones are running)

It screams along and a pretty amazing clip when you think about it (2.3Ghz means ~2 instruction per nanosecond) executing INSTRUCTIONS written in ASSEMBLY

These instructions look something like this

---

# `ADD rax, 05`

x64 assembly to add 5 to rax

???

Or your CPUs preferred form of

---

# `8366 05c0`

???

Now these instructions are all stored in memory and accessed by a 64 bit _address_

So our instruction from before might be stored in

---

#  `0xffbfc3a0`

???

Now your CPU doesn't just start reading instructions from 0x0 and go up from there.

Our CPU can jump around, so obviously it needs to keep track of where it is going next.

It does this in a _register_ (don't worry about those for now) once called the Instruction Pointer (IP), then called EIP, now called

# RIP

???

Now as a Bad Person (tm) taking over this one thing lets me pwn your box because then I can make your computer execute any code I want

How do you do mess with RIP? Well sadly there is no instruction for directly setting this register, unlike most other registers.

There are many registers on your CPU, which are kind of like places to store information.

---
class: left

# Example registers

.left-column[
&nbsp;
 - RAX
 - RBX
 - RCX
 - RDX
 - RSI
 - RDI
 - RBP
 - RSP

]
.right-column[
&nbsp;
 - R8
 - R9
 - R10
 - R11
 - R12
 - R13
 - R14
 - R15
]

???

Some of them are general purpose registers, which can be used for whatever a program feels like.

Some of them are special and hold values like whether the addition your just performed resulted in an overflow, or where the current stack starts

The way RIP is manipulated happens with 3 instructions:

---

# jmp, call and ret

???

`jmp address` will go directly to the address, but I want to focus on call and ret for now

---

# Subroutines

Using `call` and `ret`

???

So, call and ret are ways that we can use _subroutines_ (aka functions)

Call will set RIP to an address, but when we call return we need to know where to return to!

So the other thing that call does is to push the current value RIP onto the _stack_

---

# The STACK

???

Now, as the talk is about stack overflows, you might guess that I'll be talking more about the stack now and you would be right.

The stack in assembly is a

---

# Last In, First Out

???

data structure. You can _push_ values onto the stack with

---

# `push val`


---

# `pop destination`

???

you can also `pop dest` to get the value you want back.

When you do this, a special register called the

---

# STACK POINTER

SP, then ESP, now RSP

???

is DECREMENTED.

Yes that's right, the stack

---

# The stack GROWS DOWN

More recent items on the stack have lower memory addresses, and olders ones have higher (larger) memory addresses

???

When you call a function in C, you have have variables that live only during that function call and they are sometimes referred to as

---

# Stack Variables

.left[
```
void example() {
  int a;
  char b[10];
}
```
]

???

because they live on the stack. They are pushed onto the stack in the order they are delcared

Yes, that's right

---

# They live alongside the <u>stored instruction pointer</u>
which will result in us being able to take over a computer

---

# Strings in C

???

A quick detour on strings in C.

---

# Strings in C are a LIE

Just arrays of characters

???

There's no such thing as a string in C. Just arrays of characters.

Normally, a string will will end with a null character ('\0')

---

# Null character = `'\0'`

???

You'll notice that one thing we don't have here: a length.

That means, as a programmer it's up to you to keep track of how long your string is, and how big the array you are storing it is.

If you make a mistake... you can easily access or overwrite further than you intened to in your char array / string.

Now, in C

---

# array access happens from low to high
That is if you have `char a[10]` then `a[0]` is a at a lower address than `a[10]`


???

---

# HERE'S THE PROBLEM


---

# Stack variables, like a char array live on the stack, and the return address for a subroutine ALSO LIVES ON THE STACK.


???

Combined with the fact that you can easily write past the end of a char array in C if you're not careful leads to the prevelance of the

---

# STACK OVER FLOW

---
class: left

# Example 1


.left[
```
#include <stdio.h>
#include <string.h>

void good()
{
        puts("Win.");
        execl("/bin/sh", "sh", NULL);
}
void bad()
{
        printf("I'm so sorry, you're at %p and you want to be at %p\n", bad, good);
}

int main(int argc, char **argv, char **envp)
{
        void (*functionpointer)(void) = bad;
        char buffer[50];

        if(argc != 2 || strlen(argv[1]) < 4)
                return 0;

        memcpy(buffer, argv[1], strlen(argv[1]));

        printf("This is exciting we're going to %p\n", functionpointer);
        functionpointer();

        return 0;
}
```
]

---

# Example 2

.left[
```
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

        char buf[128];

        if(argc < 2) return 1;

        strcpy(buf, argv[1]);

        printf("%s\n", buf);

        return 0;
}
```
]

???

which is basically just echoing the first argument I pass to it when I run from the command line

But what I'm *not* doing is making sure that the value at argv[1] is small enough to fit into buf.

Can you guess what happens if we call this program with a string larger than 128 characters?

(hint: it's why I'm here)

Yes, that's right a **STACK OVERFLOW**

---

# SHELLCODE

---

# Shellcode example


.left[
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
]
---

# How Compilers and Operating Systems Keep us Safe


---

# ASLR

Address Space Layout Randomization

---

# Non executable stack


---

# Stack smashing detection

Insert secure value between stack frames and check before calling ret

OR

Insert 0000000 because you can't have 0s in your shellcode

---

# Want to learn more?

.left[

Hacking: The art of Exploitation

Smashing the Stack for Fun and Profit: Phrack Magazine #49: http://www.phrack.org/archives/49/P49-14

Anatomy of a Stack Smashing Attack and How GCC Prevents It: http://www.drdobbs.com/security/anatomy-of-a-stack-smashing-attack-and-h/240001832?pgno=3
]
