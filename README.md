# arduino-shoutbox
A toy box that record and play voice by Arduino

The circuit is inside a box.
There is a button outside of the box.

After pushing the button, open the box and shout something. then close the box.
From now on, when opening the box, the message will be played.

Main components: ISD1820 voice recorder and player
https://www.elabpeers.com/isd1820-voice-recording-module.html
LDR (Light Dependent Resistor)

Partial wiring (Fritzing):
https://www.circuito.io/static/reply/index.html?solutionId=5a3d4c6bfb33e200225be712&solutionPath=storage.circuito.io

Wiring with Attiny85:
(fake component instead of the ISD1820, and the real batteries are AA)
![Fritzing for Attiny85](https://github.com/ShaiFisher/Arduino-Shoutbox/raw/master/shoutbox-attiny85_bb.jpg)
