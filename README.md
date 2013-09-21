cs246FinalProject
=================

Overview
========
This is an implementation of Quadris in C++ written under the ubuntu gcc environment. <br>
The game of Quadris is simply Tetris but with letters as blocks.

Features
========
Support 7 types of blocks: I J L O S Z T <br>
Supports score, highscore.<br>
Have a text based and GUI component.<br>
Four levels to control block probability.<br>
Text commands.<br>
Command line flags.

Commands In Game
================
Note: All commands support a functionality that if you write enough of the command to distinguish it from other commands, entering that string is enough to trigger the command. Also each command can be repeated by adding an integer before or after the command or as a part of the command.<br>
Block movement:<br>
left<br>
right<br>
down<br><br>
clockwise<br>
counterclockwise<br>
drop      | this command will stop block movement and spawn next block<br>
levelup<br>
leveldown<br>
restart   | this command saves highscore<br>

Command-Line Flags
==================
-text <br>
runs the program without GUI<br>
-seed xxx<br>
sets the seed of the random number generator<br>
-scriptfile xxx<br>
uses a user created script for the manual sequence of blocks in level 0, the starting level<br>
-startlevel n<br>
manually specify the starting level
