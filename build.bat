@echo off
echo Building USL Compiler...

REM Create output directories if they don't exist
if not exist output mkdir output
if not exist output\optimizations mkdir output\optimizations

REM Compile the compiler with all necessary files
gcc -o usl_compiler.exe main.c ast.c tac_generator.c basic_blocks.c optimizer.c semantic_analysis.c symbol_table.c usl.tab.c lex.yy.c -I.

if %ERRORLEVEL% EQU 0 (
    echo Build successful!
    echo Executable created: usl_compiler.exe
) else (
    echo Build failed!
    exit /b 1
)