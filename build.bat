@echo off
REM Build script for MinGW / Windows
if exist output rmdir /s /q output
mkdir output 2>nul
REM generate lexer/parser if present
if exist usl.l (
    flex usl.l
) else (
    echo "usl.l not found"
)
if exist usl.y (
    bison -d usl.y
) else (
    echo "usl.y not found"
)
REM compile all .c files in the project folder
gcc -o usl_compiler *.c lex.yy.c usl.tab.c -lfl -ly -static
if errorlevel 1 (
    echo Build failed
) else (
    echo Build succeeded. Run: usl_compiler input\sample_input1.usl
)
