# SVG Processing System - ENGR1010J Project

## Overview
This project implements an SVG parser and image exporter in C that can read SVG files and convert them to BMP format.

## Features
- Parse SVG files with circle, rectangle, and line elements
- Display parsed SVG content in console
- Export SVG to BMP format
- Modular code structure for easy maintenance

## Build Instructions

### Windows
```cmd
cd project
make
```

Or compile manually:
```cmd
gcc -Iinclude -Wall -Wextra -std=c99 -O2 -o build/svg_processor.exe src/main.c src/svg_parser.c src/svg_render.c src/bmp_writer.c -lm
```

## Usage

### Parse and Display SVG
```cmd
build/svg_processor.exe --parse assets/test.svg
build/svg_processor.exe -p assets/test.svg
```

### Export to BMP
```cmd
build/svg_processor.exe --export_bmp assets/test.svg assets/output.bmp
build/svg_processor.exe -eb assets/test.svg assets/output.bmp
```

### Interactive GUI Editor
```cmd
build/svg_gui.exe [assets/test.svg]
```
Note: The GUI is a separate executable due to SDL dependencies. Use --gui option in svg_processor.exe for a message directing to the GUI executable.

### Launch GUI Editor
```cmd
build/svg_processor.exe --gui [assets/test.svg]
build/svg_processor.exe -g [assets/test.svg]
```
The GUI provides an interactive SVG editor with mouse-based shape manipulation, toolbar for adding shapes, and real-time preview.

## Project Structure
```
project/
├── src/
│   ├── main.c           # Main program entry point
│   ├── svg_parser.c     # SVG file parsing
│   ├── svg_render.c     # Console output rendering
│   └── bmp_writer.c     # BMP export functionality
├── include/
│   ├── svg_types.h      # Data structure definitions
│   ├── svg_parser.h
│   ├── svg_render.h
│   └── bmp_writer.h
├── assets/
│   ├── test.svg         # Sample SVG file
│   └── output.bmp       # Generated BMP output
├── build/
│   └── svg_processor.exe # Compiled executable
├── docs/
│   └── [documentation files]
├── Makefile             # Build configuration
└── README.md            # This file
```

## Supported SVG Elements
- `<circle>` - with cx, cy, r, fill attributes
- `<rect>` - with x, y, width, height, fill attributes
- `<line>` - with x1, y1, x2, y2, stroke attributes

## Implementation Notes
- Uses linked list for shape storage
- BMP export uses 24-bit RGB format
- Bresenham's algorithm for line drawing
- Simple scanline rendering for shapes

## TODO
- [ ] Add JPG export support
- [x] Implement interactive editing mode (GUI completed)
- [ ] Add more SVG element types
- [ ] Improve error handling

## Team Members
[Add your team member names here]

## License
Educational project for ENGR1010J
