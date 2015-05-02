---
layout: post
title: "Building a Watch: Part 1"
date: "2015-05-01 20:35:30 -0400"
---

I want to build myself a watch.

One of my goals this year is to learn more electronics, and the best way I've found to learn is often to have a project. For example, the [heart box](http://blog.tahnok.me/post/how-to-propose-to-an-engineer) taught me a bunch about laser cutting and tolerances. I think a watch will be a good project because:

 - I currently don't have one, but I want one
 - It has interesting size constraints (imposing limits is fun!)
 - It'll be battery powered
 - Lots of room for improvements

Bonus: It looks like I will probably have to make a circuit board for this! I have 0 clue on how to go about doing that yet, but this should give me a pretty good excuse.

## Feature Wish List

I want the watch to have normal watch functions like keeping the time, having alarms and preferrably a stopwatch / timer mode.
It would also be really cool if I could make it silent, since beeping is pretty annoying. Instead, I think I should incorporate a vibration motor.

Eventually, I would like to have it connect to my phone / computer so it will need to have bluetooth at some point.

Finally, it needs to look good. That means, it can't be a 20cm tall monstrosity covered in electrical tape.

## Potential Parts

I'm not entirely sure which parts I will choose yet. I've been drawing heavily from [The open source watch](http://oswatch.org/) to see how such a thing *can* be made. They use a [microduino core+](https://www.microduino.cc/module/view?id=53d7037cb6c69d00003ede53) which is really cool and super tiny! I have the most experience with Arduino (and thus AVR) chips so I will probably stick with that, although now that I think about it, it might be cool to use a Propeller because it can multi-task. The other option is to use something like the Trinket Pro (since it has a nice battery board addon) but it may prove to be too big.

Next, I have to choose a display. After lots of googling I found the [Sharp Memory Display](https://www.adafruit.com/product/1393) which is a cool mix of e-ink and LCD. (fun fact: it's the [display in the pebble](https://www.ifixit.com/Teardown/Pebble+Teardown/13319)). I don't care much about color, so I think I will go with it despite the memory restrictions it will impose on the build.

I don't yet know what battery I will use, probably something from Adafruit. I'm trying to choose between a 150 mAh and a 500 mAh one.

I *think* I need an RTC module, but it's possible that I can get away with keeping track of time without it, and just relying on paired phone to deliver accurate time.

## Next Steps

I think I will order a bunch of parts to bread board this out. I need to test a bunch of things like power draw. Also probalby lots of yelling at my computer when I can't figure out how to build a bread board.
