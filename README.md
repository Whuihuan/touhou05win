Introduction
============
This is an unofficial port of the game Touhou Kaikidan: Mystic Square (the fifth game of the touhou series, referred to as th05 below) to windows. It faithfully reproduces almost all features of the original PC98 version. Check "Comparison" section for the details

Usage
=====
1. Extract all files into a folder.
2. Download glew from http://glew.sourceforge.net/ (download the binaries) and extract glew32.dll into the same folder.
3. Download PMDWin from http://c60.fmp.jp/ and extract PMDWin.dll into the same folder.
4. (Optional) Put anex86.bmp into the same foldeer. (google it to find out how to get this file)
5. Put 怪綺談1.dat, 怪綺談2.dat, MUSIC.dat and ZUN.com from the orignal PC98 version into the same folder (these files may have different names depending on you system's code page, for example, 夦鉟択1.dat in chinese code page)
  5.1 If you only have an .hdi file that contains the original game, you can:
    5.1.1 Download anex86 (google it to find the download link)
    5.1.2 Use anxdiet that is included in anex86 to open the .hdi file
    5.1.3 Drag the three need files to the destination folder
6. Rename 怪綺談1.dat to kaiki1.dat, 怪綺談2.dat to kaiki2.dat.
7. Run uth05win.exe.

Comparison
==========
New features in this ported version:
 * Replay support
 * Practice Mode support
 * Bullet point support
 * fixed a number of bugs in the PC98 version
 * uses float instead of int where necessary, increasing accuracy

Features not ported in this version:
 * Some MusicRoom's visual effect
 * Some options

Supposing features in this ported version:
 * Practice Mode's cheak routine (always able to use)
 * Player performance evaluation
 * MIDI Music support
 
Controls
========
Similar to other games of touhou series:
  Z      Shoot
  X      Bomb
  Shift  Slow move
  Ctrl   skip dialog
  ESC    Menu

To toggle fullscreen mode, press alt + enter.

Game pad is not supported yet.

Known bugs
==========
When you switch to/from full screen mode, the font texture may become corrupted.

Copyright
=========
1998 ZUN
2011 Pegasy
2018 WindowsTiger
This program is in the public domain.

The assets and libraries it uses belongs to their authors. Check their webpage for copyright information

This program uses:
* assets from th05 (http://www.kt.rim.or.jp/~aotaka/am/index.htm)
* The OpenGL Extension Wrangler Library (http://glew.sourceforge.net/)
* PMDWin (http://c60.fmp.jp/)


Misc
====
For bug report and feature request, please contact the one you received this program from:)
glew.lib requires 1.3.5, later version cause build fail.

This text is based on the original text author Pegasy
