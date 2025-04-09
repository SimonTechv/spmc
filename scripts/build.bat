@echo off
echo Configuring and building Waf project...

REM Сборка
python -B sys/waf-ex build
if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    pause
    exit /b %ERRORLEVEL%
)

echo Build completed successfully!
pause