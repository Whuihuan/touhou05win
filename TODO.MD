TODO LIST
======================

Enemy does not shoot bullet
============================
At the Stage 2 and 3, just one or two enemys does not shoot bullet. They also does not have player crash judgement but have player's bullet crash judgement. I recently found this problem is related to case 42 or 43 of CEnemy::StepEnemyScript(), but I couldn't figure out what is problem. Because assembly code of original one works same.

The way to calculate Slowdown
==============================
Slowdown is one variable in Skill Verdict. I couldn't find the routine of calculate this. So I guess (Slowdown)=(Passed Frame)*(Recommended fps)/(Real passed time). But I don't know the way to count well (Passed Frame) and (Real passed time).

Staff Roll
==============================
Could I make this in this life?

PMD Routine
================================
Because of this, Piano Effect can not work. Originally, Piano Routine access on PMD Variable. But in this, PMDWin libray makes problem. PMDWin output Sound Buffer first, and Sound Driver ouput this buffer. This make when we read PMD Variable, this value points future value. Also I tried many other ways, but no one have accuracy.

Piano Effect in Music Room
==============================
First, Related to PMD Routine Problem
Secound, if I draw all rectengle one by one, I makes Much lack.

Demo Always Dead
===============================
I implement Demo Play Routine, but demo die well. I guess this because inaccuracy of fps(Real PC98 is 26fps but Simulation runs on 56.0fps)

Complete SE Option
===============================
SE Use coverted wav file.

ETC
=================================
* Practice Play Character Select Design
* Midi Routine is spagetti
* Make RT5CUSTOM
