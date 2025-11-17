#ifndef SVG_TYPES_H
#define SVG_TYPES_H

typedef enum {
    SVG_SHAPE_CIRCLE,
    SVG_SHAPE_RECT,
    SVG_SHAPE_LINE
} SvgShapeType;

typedef struct {
    double cx, cy, r;
    char* fill; // e.g., "#RRGGBB"
} SvgCircle;

typedef struct {
    double x, y, width, height;
    char* fill; // e.g., "#RRGGBB"
} SvgRect;

typedef struct {
    double x1, y1, x2, y2;
    char* stroke; // e.g., "#RRGGBB"
} SvgLine;

typedef struct SvgShape {
    SvgShapeType type;
    union {
        SvgCircle circle;
        SvgRect rect;
        SvgLine line;
    } data;
    int id;
    struct SvgShape *next;
} SvgShape;

typedef struct {
    double width, height;
    SvgShape *shapes;
} SvgDocument;

#endif
