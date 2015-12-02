@echo off
del /q problem1.out
del /q problem2.out
echo run Problem1 save to Problem1.out
Problem1.exe > Problem1.out
echo Problem1 Finished!
echo run Problem2 save to Problem2.out
Problem2.exe > Problem2.out
echo Problem2 Finished!
pause