@echo off
echo Configuring and building Waf project...

REM Конфигурация
python -B sys/waf-ex configure
if %ERRORLEVEL% NEQ 0 (
    echo Configuration failed!
    pause
    exit /b %ERRORLEVEL%
)

echo Build completed successfully!
pause