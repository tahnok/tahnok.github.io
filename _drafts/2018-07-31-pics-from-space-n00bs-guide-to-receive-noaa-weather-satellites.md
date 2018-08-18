---
layout: post
title: "pics from space: n00b's guide to receive NOAA weather satellites"
date: 2018-07-31 23:47:25 +0000
---

It's been a dream of mine for a while to receive images from space.
Around 2 years ago, I finally succeeded in getting images from the NOAA APT weather satellites, but I hadn't gotten around writing up how I did that until now.

My initial research led to lots of confusing information on many different topics.
What kind of antenna did I absolutely need?
How did I get the software?
Which were the satellites and how did I figure out when they were overhead?

There are 2 things you need to acquire:

 1. A receiver
 2. An antenna

And 3 things you need to know:

 3. How to figure out when a satellite can be heard
 4. How to set up your receiver properly
 5. How to decode the image you receive


I'm gonna focus on the cheapest / easiest setup possible because that worked for me.

## Receiver: RTL-SDR

For the receiver I am using an RTL-SDR.
This is a device initially intended to receive European TV, but some clever hackers figured out how to turn it into a receiver across a huge range of frequencies.
Importantly for us it can receive ~137 MHz really well, and they are SUPER cheap.
You have a few choices for suppliers.

You can search ebay / amazon / aliexpress / adafruit.
This is your cheapest option, but the devices you will get here have 2 drawbacks.
First, they need to be frequency corrected.
I'll mention how to do this when we get to the software section, but it's pretty easy.
Second, you need an adapter / pigtail to connect these to an antenna.
These have a weird mini MCX connector that isn't standard.
Most antennas for commercial / ham use have an SMA, BNC or UHF connector.
The same sites above will also stock pigtails / adapters.

Your other option is one of the redesigned / upgraded models.
I bought one from rtl-sdr.com because it has an SMA connector.
rtl-sdr.com also offers a package that include an antenna that works.

rtl-sdr.com store (choose the one with the dipole antenna kit): https://www.rtl-sdr.com/buy-rtl-sdr-dvb-t-dongles/

## Antenna: Dipole

There are plenty of better antennas for receiving satellites.
If you have looked into this, you will hear mention of [the QFH or the double cross dipole](https://www.youtube.com/watch?v=cjClTnZ4Xh4).
These are better, but hard to make in terms of skill and in terms of gear required.

Instead, I have had great luck with the simplest antenna: the dipole.

Any dipole designed for 2m / 144 MHz should work, but if you are making your own you should tune it for 137MHz.

### Bunny ears

One way to make a dipole is to find a pair of old TV bunny ears, or buy one.
That's what I have done recently with the rtl-sdr.com package mentioned above.
If you can extend each side to be 52cm, you should be good to go.

### Homemade dipole

For my first attempt, I built my own antenna.
I did this by buying a length of the thinnest brass rod I could find that would support it's own weight.
I cut 2 lengths to 52cm.
I calculated this number using this [online dipole calculator](http://www.kwarc.org/ant-calc.html)

Next, I soldered a bit of wire to both pieces.
Then I got a T-joint made of PVC and tapped these pieces so they were parallel to each other.

Finally, I connected the bits of wire to one of these [screw terminal BNC connectors]() that I got from Aliexpress.
This is probably the most weird / hard to find part of this build.
I've been thinking of other ways to do this, but so far ordering this and waiting the 35-50 days requried to get something from China is the easiest and the cheapest.

#TODO section on a pole, or pointing

## Finding passes: ISS Tracker

My first attempts for figuring out when a satellite was hearable because it was overhead (a pass), I used [wxtoimg](https://web.archive.org/web/20171226033343/http://www.wxtoimg.com:80/downloads/).
We will need this software later, but if you configure your ground station location (options -> ground station location), you can see a list of passes by going to file -> satellite pass list...

That worked OK, but I have found something better, if less free: [ISS Detector]()

It's poorly named, and a bit clunky to set up but it works really well.
It buzzes when a pass is about to happen.
It shows you the frequency of the satellite and it shows you were it will be coming from.

Once you have the app installed on your phone, go to the overflow menu (the vertical ...) and hit extensions and buy the Amateur Radio Satellites package.
Next, go to filters and turn on amateur radio satellites and select the following 3 satellites:

 - NOAA-15
 - NOAA-18
 - NOAA-19

These are the only operational NOAA satellites that are transmitting images.

When you see a good pass (that is something with an elevation over 30 degress, but the higher the better) it's time to find a good spot.

I've found open parks are really good, but any spot with a clear view of the sky that's well away from any buildings will work.

## Receiving software: SDRSharp

Now that you have an antenna and a receiver, it's time to you know... receive.

I'm using windows, so I am using [SDRSharp](https://airspy.com/download/) (or SDR#).

Once you have that installed, it's time to set it up.

Each satellite has a different frequency

 - NOAA-15: 137.620 MHz
 - NOAA-18: 137.913 MHz
 - NOAA-19: 137.100 MHz

You can tune to that frequency at the top of SDRsharp

Once you have the frequency selected, it's time to choose the receiving mode.
You want to use the WFM (wide FM) mode and you want to have a have a bandwidth of 55,000 Hz (55 KHz)

#TODO picz maybe?


## Decoding: WXtoImg

The satellites transmit images using an encoding called APT (Automatic Picture Transmission).
If you listen to it, it sounds like repeating deet-deet deet-deet.

In order to decode it, I used a program called [WXtoImg](https://web.archive.org/web/20171226033343/http://www.wxtoimg.com:80/downloads/).
The original site that hosted the program is offline at the time of me writing this (July 2018), but it's still available from archive.org

Once you have it installed, set your ground station location (under options)

You need a way to connect the audio output of SDRSharp to WXtoImg.
If you are lucky, your sound card has some kind of monitor or loopback interface.
I was not lucky, so instead I used [VB-Cable Virtual Audio Device](https://www.vb-audio.com/Cable/).
Once installed, this virtual cable gives you a fake output device and a fake input device that are connected.

I changed SDRSharp to output to "[Windows Direct Sound] CABLE Input" but "[MME] Cable Input" also worked.
(I have no idea what the difference is)

In WXtoImg, I changed the soundcard to use "CABLE Output" by going to options -> recording options -> Common Recording Options

## Putting it together: receive PICTURES FROM SPACE

 1. Use ISS tracker or WXtoImg to find a good pass at a time that works for you
 2. Get your antenna out and connected to the RTL-SDR
 3. Launch SDRSharp and tune it to the right frequency for the satellite that will be overhead. Make sure the mode is set right (WFM with 50KHz bandwidth) and the output is set to the CABLE Input
 4. Launch WXtoImg and make sure the soundcard is set to CABLE Output
 5. Get WXtoImg to record by going to File -> Record ... -> Auto Record
 6. Watch for the APT signal in SDRSharp. You may have to zoom, but you should see a series of several spikes
 7. Point antenna! Try turning, tilting, or pointing the antenna so that the signal appears stronger
 8. wait...
 9. Stop WXtoImg (File -> Stop) and check out your space picture!

#TODO put a few pictures here of final output
