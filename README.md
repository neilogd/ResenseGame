Resense - 2012 7DFPS Game
=========================

Overview
--------

My 7DFPS entry from 2012 brought up to date and working with the latest version of Psybrus.

To build, setup a folder structure like so:

PsybrusDev/Psybrus 			- should be a clone of https://github.com/neilogd/Psybrus
PsybrusDev/ResenseGame	- should be a clone of https://github.com/neilogd/ResenseGame

Then to generate the VS project run make_vs2012_build. VS2012 is the earliest version supported due to some C++11 in Psybrus.

When the project has been built (goes to Build/vs2012), load up in VS and compile. Set the DevelopmentGame project working directory to "../../Dist" before running.

Basics
------

When you start up the game, you will be taken to the map editor screen. Controls are as follows:

0-9: Switch to a different level (will not save!)

Tab: Toggle in and out of game play.

X: Save and rebuild BSP.

B: Rebuild BSP.

E: Add an enemy where the cursor is.

S: Set start position to be where the cursor is.

Q: Set the quit location to be where the cursor is.

Left mouse click: Begin placing points for BSP hull. Note: Must be convex, there is no checking as this was a game jam game after all.

Right mouse click: Delete a point or edge.

Middle mouse click: Flip normal of edge.

