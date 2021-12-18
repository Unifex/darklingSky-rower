# Darkling Sky - rower

I'm taking the Creative Engineering course on Monthly.com that is run by Mark Rober. This drives one of the IoT devices for my project for the third build.  The constraint on this build was Habits and I have decided to [gamify my exercise](https://monthly.com/p/c7RqRx).

## This device

I have a rowing machine, but  it's a fairly simple thing. No way to get data out of it.  The idea of this device is that it will sit on the top of the rower and measure the km/h of each stroke and push that value to a local server running on a Raspberry Pi.

Currently this is mostly working for the measurement part.  This is achieved with an ultrasonic sensor and a certain amound of selective processing of the reads from that.

## TODO

* Get a Raspberry Pi on the local network
* Set up a RESTful API that can be pinged
* Add the wifi shield to the arduino and have these values recieved by the Pi

