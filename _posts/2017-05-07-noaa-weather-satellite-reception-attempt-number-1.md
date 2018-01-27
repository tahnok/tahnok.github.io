---
layout: post
title: "NOAA Weather Satellite Reception Attempt #1"
date: 2017-05-07 12:37:40 -0400
---

After my [last research post](post/plans-for-a-noaa-weather-satellite-antenna) I decided on making a Cross Dipole.
This may have been a bit ambitious and I have yet to find a good way to validate the resulting antenna, so it's possible you will have better luck attaching a few leads to a roll of tin foil.

Attempt #1 involved some solid copper rods that were too thick in diamater for me to solder to.
They now sit in a sad pile in my living room until I can figure out what to do with them.

Attempt #2 used from much thinner diamater brass rods.
They were bought at my local 'Metal Supermarket' (great name) and cost under $20.
They take solder really well

Now that I had the rods I needed to arrange them a cross pattern with support for a delay line.
Seeing an excuse to try and pretend like I know anything about CAD / 3D modeling, I busted out openscad and started "coding" with the hope of having something I could 3D print.

# image here

The intial design went ok, but using openscad got tedious quickly when I needed to tweak things.
After hearing some good things about Fusion 360 I decided to give it a go.
I'm not entirely pleased with the fact that it's closed source and seems to depend heavily on Autodesk continuing to run some servers forever, but I've learned a lot about the CAD process.
The ability to go back in time and tweak some shape or hole is really really really really really fantastic.
I have yet to find any really good tutorials or resources on learning the ins and outs of the software, but clicking around randomly has proved mildly successful.

# more images here

The final antenna holder piece can be downloaded for 3D printing below:

# link and thumbnail


## Material list

What's that? You want a materials list? Ok, here you go:

 1. 52cm lengths of XX diamater brass rods (x4)
  - Used for the antenna
 1. XXcm of coaxial cable
  - This is a "delay line" so that the 2 dipoles are out of phase and thus receive polarized signals
 1. 3D printed case halves (x2)
 1. 1" (yes I know that's not metric) screws + nuts
  - I used 6-32 but the holes in the design are bigger than that
 1. BNC Connector
  - I ordered this screw terminal style one from aliexpress
  -

## Assembly instructions

Cut your delay line to the appropriate length + a few extra centimeters for the parts that you will loose when stripped.
Carefully strip about 2cm the outer layer off the coax on one end.
Gather the strands from the outer braid and twist them together.
Next remove the plastic coating from the center of the wire a little bit above where the wires you twisted from the shield are.
You want to make sure the outer wires and the center don't touch.
I used some wire stripper to cut most of the way through and then just twisted.
Repeat the procedure for the other send of your delay line.

Next, solder 

