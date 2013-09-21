cs246FinalProject
=================

Overview
========
This is an implementation of Quadris in C++ written under the ubuntu gcc environment. <br>
The game of Quadris is simply Tetris but with letters as blocks.

Features
========
Support 7 types of blocks: I J L O S Z T
Supports score, highscore.
Have a text based and GUI component.
Four levels to control block probability.
Text commands.
Command line flags.

Commands In Game
================
Note: All commands support a functionality that if you write enough of the command to distinguish it from other commands, entering that string is enough to trigger the command. Also each command can be repeated by adding an integer before or after the command or as a part of the command.
Block movement:
left
right
down
clockwise
counterclockwise
drop      | this command will stop block movement and spawn next block
levelup
leveldown
restart   | this command saves highscore

Command-Line Flags
==================
-text 
runs the program without GUI
-seed xxx
sets the seed of the random number generator
-scriptfile xxx
uses a user created script for the manual sequence of blocks in level 0, the starting level
-startlevel n
manually specify the starting level

