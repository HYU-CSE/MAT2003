@echo off

SET sTIME=""
SET eTIME=""
SET rTIME=""

IF NOT "%1"=="" (
	call :save %1.exe
) else (
	call :loop 
)
goto:End

:loop
	SET F=""
	FOR %%x IN (*.exe) DO call :save %%x
goto :eof

:save
	call :start
	SET FNAME=%1
	echo RUN %FNAME:~0,-4% save to %FNAME:~0,-4%.out
	"%FNAME:~0,-4%" > "%FNAME:~0,-4%.out"
	call :finish	
	echo execution time(ms): %rTIME%
goto :eof

:start
	SET STARTTIME=%TIME%
	SET /A sTIME=(1%STARTTIME:~0,2%-100)*360000 + (1%STARTTIME:~3,2%-100)*6000 + (1%STARTTIME:~6,2%-100)*100 + (1%STARTTIME:~9,2%-100)

goto :eof

:finish
	SET ENDTIME=%TIME%
	SET /A eTIME=(1%ENDTIME:~0,2%-100)*360000 + (1%ENDTIME:~3,2%-100)*6000 + (1%ENDTIME:~6,2%-100)*100 + (1%ENDTIME:~9,2%-100)
	SET /A rTIME=(%eTIME%-%sTIME%)*10
goto :eof

:End
	echo FINISHED!!