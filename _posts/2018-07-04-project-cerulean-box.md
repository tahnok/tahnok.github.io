---
layout: post
title: "project CERULEAN BOX"
date: 2018-07-04 21:56:54 -0400
---

I found a way to combine a bunch of things I have wanted to learn together into one project!

For a while, I have been fascinated with phone phreaking, and specifically the mythical BLUE BOX.
Lots of myths and history surounding it.
I think I can probably still play with it on [Project MF](http://www.projectmf.org/), but we will see.

It seems like a great way to learn more electronics stuff, and some radio adjacent stuff too.
I'll need to figure out how to generate waves at specfic frequencies and how to combine them.

I happen to have bought an stm32 f3 discovery that seems like a good platform for this.
I think it's fast enough to bit bang out a wave at 2600Hz?
Guess I will find out!

I also want to do this in rust.
The f3 also seems to have decent rust support.
See the [f3 crate](https://docs.rs/f3/0.6.1/f3/) and [discovery](https://japaric.github.io/discovery/)

I wanted to write up some quick notes of things I learned getting [cerulean box](https://github.com/tahnok/cerulean_box) blinking.

Step 1 was to create a new rust project and add the f3 dependency. After that, I copied the [blinky.rs](https://docs.rs/f3/0.6.1/f3/examples/_03_blinky/index.html) to my project as `main.rs`

Next I had to add a few more dependencies, `cortex-m`, `cortex-m-rt` and `panic-semihosting`.
This was enough to get rust complaining about an `eh_personality`.
No idea what that was, but I made it go away by copy the contents of the f3 project's [.cargo/config](https://github.com/tahnok/cerulean_box/blob/de742b6a597fae6d8a96af6cb5bcddff1af15a99/.cargo/config).
As far as I can tell, this species the target architecture as being `thumbv7em-none-eabihf` which is ARM (thumbv7 specificall), with no OS and support for hard float.

That was enough to get things compiling, but then gdb would start...
In the f3 example, I was able to type continue but all gdb could do was disassemble main.
It turns out I also needed to copy [.gdbinit](https://github.com/tahnok/cerulean_box/blob/de742b6a597fae6d8a96af6cb5bcddff1af15a99/.gdbinit).
I believe this works because I have `set auto-load safe-path /` in `~/.gdbinit`.

After that, I get blinky leds!

![](https://media.giphy.com/media/3oz8xRF0v9WMAUVLNK/giphy.gif)


## Next steps

There's a few things I want to do next.
I need to actually twiddle a pin at a given frequency.
That means learning how timers work probably, maybe interupts if I want to be able to other things.

I also need to figure how this semihosting thing. I think that's so I can run the code from my laptop, and get error messages, strack traces and breakpoints which seem useful, but... I don't know how to turn it off.
How to I make a binary I can flash onto the f3 directly?

Adventures for next time!
