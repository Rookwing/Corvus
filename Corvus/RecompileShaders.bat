echo off

echo Deleting old shaders...
echo.

for /f %%f in ('dir /b "shaders/compiled"') do (
del shaders\compiled\%%f
echo %%f deleted.
)
echo.

echo Old Shaders Deleted!
echo.

pause

echo.
echo Compiling new shaders...
echo. 

for /f %%f in ('dir /b /a-d "shaders/"') do (
	echo Compiling %%f ...
	C:\Libraries\VulkanSDK\1.2.198.1\Bin\glslc.exe -c shaders/%%f
	move %%f.spv shaders\compiled
	echo %%f.spv created.
echo.
)

echo Recompilation complete!
echo. 

@echo on
pause
