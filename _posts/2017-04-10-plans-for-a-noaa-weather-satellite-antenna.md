---
layout: post
title: "plans for a NOAA weather satellite antenna"
date: 2017-04-10 19:26:24 -0500
---

One of the things I _really_ want to do with ham radio is listen to SPACE MACHINES (a.k.a satellites).
Technically you don't need a ham radio license to do this, but I only learned about it after getting mine.

Some of the most interesting looking satellites that anyone can receive are NOAA weather satelittes.
These satellites continuously transmit LIVE IMAGES OF THE EARTH.
As far as I can tell there are 3 in orbit: NOAA-15, NOAA-18 and NOAA-19.
All three of these broadcast black and white images of the globe using [Automatic Picture Transmission](https://en.wikipedia.org/wiki/Automatic_picture_transmission).
They transmit on frequencies around 137 MHz, which can be received using the dirt cheap RTL-SDR.
The transmissions can (apparently) be decoded with [wxtoimg](www.wxtoimg.com).

The only thing that I am currently missing is some kind of antenna.

I've done a bunch of research to determine what kind antennas are suitable and I've come up with a (not very) short list:

 - QFH (Quadrifilar helicoidal antenna) or Helical Quad
   - https://umarca.blogspot.ca/2013/05/project-8-turnstile-antenna-for-weather.html
   - http://jcoppens.com/ant/qfh/calc.en.php
   - http://www.housedillon.com/?p=1461
   - http://www.instructables.com/id/NOAA-Satellite-Signals-with-a-PVC-QFH-Antenna-and-/
 - Cross Dipole or Turnstile
   - http://www.thornett.net/Rosliston_Archive_2009-11/html/cross_dipole_antenna.html
   - https://imgur.com/a/qczZW
   - https://www.digitalham.co.uk/turnstile-antenna/
   - https://umarca.blogspot.ca/2013/05/project-8-turnstile-antenna-for-weather.html
 - IOio
   - http://www.ea4cax.com/paginaea4cyq/Antenaioio/ioioingles.pdf
   - http://www.kj6akq.com/blog/2010/02/building-an-ioio-satellite-antenna/
 - Yaggi-Uda
   - http://ve2zaz.net/Arrow_Ant/Arrow_Style_Ant.htm
   - http://www.fredspinner.com/W0FMS/CheapYagi/vjbcy.html
   - https://web.archive.org/web/20110102162129/http://www.amsat.org/amsat-new/information/faqs/crow/JulAug06AmsatJournal.pdf (444MHz)
   - https://web.archive.org/web/20110102161932/http://www.amsat.org/amsat-new/information/faqs/crow/SepOct06AmsatJournal.pdf (146MHz)
   - http://neodux.com/?view=story.php&post_id=451
   - http://makezine.com/projects/make-24/homemade-yagi-antenna/

I've been working on the cross dipole since it seems to be the simplest to construct and deploy.
Will probably end up building a Yaggi-uda at some point as well for dat sweet gain, but it's too directional if I want to set up a NOAA reception station permananently somewhere.
