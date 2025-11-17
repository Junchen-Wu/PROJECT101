# GUI Integration TODO

## Tasks
- [x] Modify main.c to add --gui command option that launches the GUI, optionally loading an SVG file
- [x] Refactor svg_gui.c: move GUI logic to run_gui(SvgDocument* doc) function, remove its main function
- [x] Update Makefile to build a single executable including GUI sources
- [x] Update README.md to document --gui usage and update TODO section
- [x] Build the project to ensure compilation
- [x] Test the --gui option to verify GUI launches and loads SVG if provided

## Progress Tracking
- Current: All tasks completed. GUI integration is functional with separate executables due to SDL linking issues.
- Next: None - GUI task is complete.
