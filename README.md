USL Compiler - Full Pipeline (Windows-ready)

This package integrates your original project files with a conservative optimization pipeline.

Build (Windows, using MinGW + msys tools):
1. Install MinGW and make sure gcc, flex (win_flex), and bison are available in PATH.
2. Open MSYS2/MinGW shell in the project directory.
3. Run: build.bat

Or use the included Makefile in a POSIX-like environment (MSYS2):
make
./usl_compiler input/sample_input1.usl

Outputs are written to the output/ directory:
- output/tac.txt
- output/basic_blocks.txt
- output/optimized_tac.txt
- output/optimization_log.txt
