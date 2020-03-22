@echo off
gcc %~1.c -o prog
prog.exe
del prog.exe
dot %~1.dot -Tpng -o %~1.png
rem del %~1.dot
start i_view64 %~1.png