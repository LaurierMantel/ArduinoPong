# ArduinoPong

A pong game I made using Arduino, a small proximity sensor, and Processing to allow users to control a pong game by moving their hand toward/away from the sensor.  

The Arduino program communicates with the Processing program via serial connection.  They exchange bytes to synchronize via a serial handshake and are then prepared to run the game.  Processing runs a loop which controls the ball in the pong game, and listens for position information from Arduino.  When Processing detects that a goal has been scored, it writes a 'G' byte to the Arduino, which keeps score of "lives" left in the game with lights.  

I attached a breadboard to the Arduino with a multiplexer wired to control buttons, allowing the game to be paused, stopped and started, by registering an input and sending a serial message to arduino, triggering the arduino to change its state.

The ball is a silly picture of my friend Claire's face.

![screen shot 2016-01-21 at 6 49 22 pm](https://cloud.githubusercontent.com/assets/9892964/12498366/fd7e6fa2-c06f-11e5-81ff-41b8ef16a138.png)


