---
layout: post
title: "toggling pins in rust"
date: 2018-07-08 12:07:44 -0400
---

My first goal after getting someone elses good compiling, was to toggle a pin on my own.
I think for my first attempt to generate a frequency, I will just turn a pin on and off at a given rate.

My target frequency is 2600Hz, and if I want to generate a square wave (which I get by turning things on and off) I need to toggle the pin at twice that frequency.
So with a target frequency of 5200Hz, I can now figure out the period which is 0.000192308 seconds or 192 microseconds.

Now that I knew how long a delay to use, I needed to figure out how to actually toggle a pin...
I struggled with the docs a fair amount here.
The example code uses an LED type so I looked at [the source code](https://docs.rs/f3/0.6.1/src/f3/led.rs.html#167-169).
I should have just tried that code directly, but I checked the docs first and got very confused.
The LED uses a [PEx type](https://docs.rs/stm32f30x-hal/0.2.0/stm32f30x_hal/gpio/gpioe/struct.PEx.html) which implements [OutputPin](https://docs.rs/embedded-hal/0.2.0/embedded_hal/digital/trait.OutputPin.html) but somehow I missed that.
Instead, I was looking at the [Output](https://docs.rs/stm32f30x-hal/0.2.0/stm32f30x_hal/gpio/struct.Output.html) type which didn't seem to have any methods associated with it...

Anyway, the end result is that if you have an `OutputPin` you can call `set_high` and `set_low`.
OutputPin comes from [embedded_hal](https://docs.rs/embedded-hal/0.2.1/embedded_hal/) which should theoretically work on all embedded rust targets!
