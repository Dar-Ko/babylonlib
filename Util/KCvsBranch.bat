@echo off
REM $RCSfile: KCvsBranch.bat,v $: Batch command script file
REM $Revision: 1.1 $ $Date: 2008/09/15 13:50:02 $
REM $Author: ddarko $
REM
REM Replaces CVS revision tag with branch name.
REM Requires cvs.exe in working path
REM Note: Win32 specific
REM 2005-04-03 Darko Kolakovic

CLS

TITLE Remobe CVS Tag
COLOR 09

REM 1st argument is CVS tag to be removed
c:cvs tag -Fb  %1 *.a*
c:cvs tag -Fb  %1 *.b*
c:cvs tag -Fb  %1 *.c*
c:cvs tag -Fb  %1 *.d*
c:cvs tag -Fb  %1 *.e*
c:cvs tag -Fb  %1 *.f*
c:cvs tag -Fb  %1 *.g*
c:cvs tag -Fb  %1 *.h*
c:cvs tag -Fb  %1 *.i*
c:cvs tag -Fb  %1 *.j*
c:cvs tag -Fb  %1 *.k*
c:cvs tag -Fb  %1 *.l*
c:cvs tag -Fb  %1 *.m*
c:cvs tag -Fb  %1 *.n*
c:cvs tag -Fb  %1 *.o*
c:cvs tag -Fb  %1 *.p*
c:cvs tag -Fb  %1 *.r*
c:cvs tag -Fb  %1 *.s*
c:cvs tag -Fb  %1 *.t*
c:cvs tag -Fb  %1 *.v*

c:cvs status -v > _status.txt

c:cvs up -r%1

REM ---------------------------------------------------------------------------
REM $Log: KCvsBranch.bat,v $
REM Revision 1.1  2008/09/15 13:50:02  ddarko
REM Created
REM
