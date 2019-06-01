@echo off
:loop
gen.exe
game.exe
game1.exe
fc game.out game1.out
if not errorlevel 1 goto loop
pause