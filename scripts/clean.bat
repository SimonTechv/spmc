@echo off
echo Configuring and building Waf project...

REM Очистка
python -B sys/waf-ex distclean
if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    pause
    exit /b %ERRORLEVEL%
)

echo Build completed successfully!
pause