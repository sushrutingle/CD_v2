@echo off
REM Build script for MinGW / Windows
if exist output rmdir /s /q output
mkdir output 2>nul
REM generate lexer/parser if present
if exist usl.l (
    win_flex usl.l
) else (
    echo "usl.l not found"
)
if exist usl.y (
    win_bison -d usl.y
) else (
    echo "usl.y not found"
)
REM compile standalone parser
gcc -o usl_parser.exe -DSTANDALONE_PARSER usl.tab.c usl.lex.c ast.c symbol_table.c semantic_analysis.c -lm
if errorlevel 1 (
    echo Standalone parser build failed
) else (
    echo Standalone parser build succeeded.
)
REM compile main compiler with all components
gcc -o usl_compiler.exe main.c usl.tab.c usl.lex.c ast.c symbol_table.c semantic_analysis.c tac_generator.c basic_blocks.c optimizer.c -lm
if errorlevel 1 (
    echo Main compiler build failed
) else (
    echo Main compiler build succeeded. Run: usl_compiler.exe input.txt
)