Area Editor version 1.34
========================

Release notes
-------------

Monday, 20th March 2006


Author: Nick Gammon 

-----------------------------------------
If you are reading this file with NotePad,
enable "Word Wrap" under the Edit menu for
proper viewing of it.
-----------------------------------------

Area Editor is produced by Gammon Software Solutions:  

  http://www.gammon.com.au/


Introduction
------------

This program is designed to facilitate editing of the "area" files used by the SMAUG and ROM MUD program.


Installation
------------

1. Create a directory on your disk called "AreaEditor".

2. Use WinZip to unzip all of the files into the AreaEditor directory. Make sure that you have "Use folder names" checked. It is important that the following files are placed in a subdirectory called "spell", otherwise the spell checker will not work properly:

 accent.tlx
 correct.tlx
 Ssce.hlp
 ssceam.tlx
 ssceam2.clx
 userdic.tlx

3. Double-click on AreaEditor.exe to start the Area Editor.

4. Press <F1> for help on using the editor.


What is SMAUG and ROM?
----------------------

SMAUG stands for [S]imulated [M]edieval [A]dventure multi[U]ser [G]ame. 
SMAUG itself is copyright: SMAUG 1.0 (C) 1994, 1995, 1996 by Derek Snider
You can find the source code for SMAUG, and more about it at: http://www.game.org


ROM 2.4 beta is copyright 1993 - 1996 by Russ Taylor <rtaylor@efn.org>.
You can find the source code for ROM, and more about it at: http://www.cmc.net/~rtaylor/


Program features
----------------

Area Editor lets you edit area files "offline" using a GUI (graphical) interface.

You can:

1. Set attributes for rooms, mobiles etc. using checkboxes, rather than having to add up large numbers.
2. Add, delete or duplicate things in the area. Deleting an item (eg. a room) optionally deletes references to that item (eg. exits leading to the room). Duplicating an item (eg. an object) also duplicates sub-items (eg. programs, affects etc.)
3. Syntax-check MUD programs against your current commands/skills/socials files
4. Do an "area check" to check for missing, or unused, items
5. Renumber the vnums in an area, including references to vnums in MUD programs
6. Cross-reference most things against each other (eg. which mobs are loaded into a particular room)
7. Find things by summary, detail, program contents, or vnum.
8. View, edit, save commands/skills/socials in easy-to-view windows.
9. Print an area to give a hard-copy summary of what all rooms/mobs/objects are.
10. Specify flag names as used in your particular version of the MUD code-base.
11. Do an "area walkthrough" which simulates what you would see as you enter each room in the area.
12. Export an area as MUSH code.
13. Read SMAUG or ROM areas, and convert from one to the other if desired.
14. Keep lists of things (eg. classes, races, skills, gender) in a configuration file, so that they configured to suit a particular MUD implementation.
15. Spell check descriptions as they are entered, or check a whole area as a batch.
16. Work with multiple areas open at once. You can make exits from one area to another, find a string over all open areas, and do an Area Check over all open areas.
17. Open a batch of areas at once (by reading the area.lst file).

Instructions
------------

Press F1 in the program for an explanation of the various screens.


Enhancements in this version  
----------------------------

Fixed another problem with the "layers" field for objects.



Configuration file
------------------

Details about using the Area Editor configuration file are in the separate document: configuration.txt.


Warning regarding making backups
--------------------------------

Although this program has been tested and saved area files seem to work OK, you are strongly advised to back up (ie. make a copy under a different name) any existing area files you have before editing them with this program. This particularly applies if you are about to renumber your area, or convert from SMAUG to ROM, or ROM to SMAUG.


Example area
------------

An example area - manor.are - has been included, so you can play with the Area Editor immediately after downloading it (in case you don't have any area files of your own). This file is from the SMAUG distribution, from www.game.org.


Comments welcome
----------------

You are most welcome to make comments or suggestions. Send comments to our forum at:

	http://www.gammon.com.au/scripts/forum.php?bbsection_id=2


Freeware
--------

This version is released as Freeware. You are welcome to use it without making any payment.


Comments welcome
----------------

Please let me know if you have any problems. Check out the web pages mentioned above for details about later versions or known bugs.

Send comments to our forum at:

  http://www.gammon.com.au/scripts/forum.php?bbsection_id=2



Spell checker
-------------

The Sentry Spelling-Checker Engine Copyright © 1999 Wintertree Software Inc.


Copyright notice and credits
----------------------------

The world of MUDs is a co-operative effort by many people. For a very interesting history of MUDs (and the Internet in general) see the paper "Cultural Formations in Text-Based Virtual Realities" by Elizabeth M. Reid at: 

http://www.ee.mu.oz.au/papers/emr/cult-form.html 

The sequence of programs that preceded the creation of Area Editor was: 

1. Diku Mud 
2. Merc 
3. ROM
4. SMAUG 
5. Area Editor 

Credits for these programs are given below ... 

* Diku Mud is copyright (C) 1990, 1991 by Sebastian Hammer, Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe. 

* Merc Diku Mud is a derivative of the original Diku Mud. Merc Diku Mud contains substantial enhancements to Diku Mud. These enhancements are copyright 1992, 1993 by Michael Chastain, Michael Quan, and Mitchell Tse. 

* ROM 2.4 is copyright 1993-1998 Russ Taylor. ROM has been brought to you by the ROM consortium. Russ Taylor (rtaylor@hypercube.org), Gabrielle Taylor (gtaylor@hypercube.org) Brian Moore (zump@rom.org).
The full ROM licence agreement is in the file "license.rom" which is supplied as part of the Area Editor archive.

* SMAUG is a derivative of the version 2.1 distribution of Merc Diku Mud. SMAUG contains substantial enhancements to Merc Diku Mud, including some features of the original Diku Mud that were removed by the Merc team. 

* Area Editor does not use code from any of the above programs, however it is designed to edit area files used by the current version of the SMAUG server (1.04) and ROM Server (2.4). SMAUG Editor is copyright (C) 1998 by Nick Gammon of Gammon Software Solutions. 


Disclaimer
----------

The software is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and noninfringement. 

In no event shall the authors or copyright holders be liable for any claim, damages or other liability, whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software or the use or other dealings in the software. 
