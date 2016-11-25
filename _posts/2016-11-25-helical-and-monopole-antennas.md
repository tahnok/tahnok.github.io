---
layout: post
title: "Helical and monopole antennas"
date: 2016-11-25 09:19:06 -0500
---

Today's reseach: helical and monopole antennas!

One of the things you can do with radios (and without needing a license) is receiving NOAA weather satelite images!
Yes, that's right, you can LISTEN TO SPACE MACHINES. Another way to look at it is free selfies!

Anyway I was reading this article ([Helical Quad Antenna for Weather Satellites](http://www.alternet.us.com/?p=1461)) which walks through the process of building a better antenna for receiving these satellites.
These NOAA satellites transmit in the VHF (~140MHz / 2m) range so the antenna is tuned for that.
From a quick skim through it seems a bit more involved than what I need in my exploratory phase but the author does mention that they started with "a 1/4 wave whip with a 4-wire ground plane" so I started looking into that.

This led me to the wikipedia article on [Whip antennas](https://en.wikipedia.org/wiki/Whip_antenna) which led me to the wikipedia article on [Monopole antennas](https://en.wikipedia.org/wiki/Monopole_antenna) which [ERR: WIKIPEDIA ARTICLE RECURSION LIMIT REACHED]

Reading through that article led quite a few things to click in my head.
One thing that I hadn't quite grokked properly was the relation between the 2 connection points on radio connectors like SMA and the parts of antenna.
A monopole antenna has one of the connectors attached to the thing that most people think of as the antenna.
That is, the long wirey sticky-outy bit.
The other connection is either attached to the ground of whatever the circuit is (as in a cellphone) OR earth ground via some spike or something OR to a "ground plane".
A ground plane can consist of some kind of solid metal or mesh sheet.
It can also consist of a another series of wires, which is what the "4-wire ground plane" was referring to earlier.

Next up I was reading about [Helical antennas](https://en.wikipedia.org/wiki/Helical_antenna).
These ones look much goofier. For example:

![](https://upload.wikimedia.org/wikipedia/commons/thumb/9/9f/Hammer_Ace_SATCOM_Antenna.jpg/640px-Hammer_Ace_SATCOM_Antenna.jpg)

Helical antennas have 2 modes.
If the circumference of the helix is a lot less than the wavelenght you want to tune to, it acts just like a monopole (sort of).
If the circumference is close to the wavelenth you can send/receive *polarized* waves.
I don't quite know exactly what that means, but I do know that satelittes transmit polarized signals and that you need a polarized antenna to pick them up properly.

Now, for my purposes I care less about getting a great signal and a lot more about just getting a signal.
I think I will spend some time looking into building myself a 2m/VHF/140MHz monopole.
