#include "../include/svg_render.h"
#include <stdio.h>

void svg_print_summary(const SvgDocument *doc) {
    if (!doc) return;
    
    int count = 0;
    SvgShape *current = doc->shapes;
    while (current) {
        count++;
        current = current->next;
    }
    
    printf("SVG Document: width=%.2f, height=%.2f\n", doc->width, doc->height);
    printf("Total shapes: %d\n", count);
}

void svg_print_shapes(const SvgDocument *doc) {
    if (!doc) return;
    
    SvgShape *current = doc->shapes;
    while (current) {
        switch (current->type) {
            case SVG_SHAPE_CIRCLE:
                printf("[%d] CIRCLE: cx=%.2f, cy=%.2f, r=%.2f, fill=%s\n",
                       current->id,
                       current->data.circle.cx,
                       current->data.circle.cy,
                       current->data.circle.r,
                       current->data.circle.fill ? current->data.circle.fill : "none");
                break;
            
            case SVG_SHAPE_RECT:
                printf("[%d] RECT: x=%.2f, y=%.2f, width=%.2f, height=%.2f, fill=%s\n",
                       current->id,
                       current->data.rect.x,
                       current->data.rect.y,
                       current->data.rect.width,
                       current->data.rect.height,
                       current->data.rect.fill ? current->data.rect.fill : "none");
                break;
            
            case SVG_SHAPE_LINE:
                printf("[%d] LINE: from (%.2f,%.2f) to (%.2f,%.2f), stroke=%s\n",
                       current->id,
                       current->data.line.x1,
                       current->data.line.y1,
                       current->data.line.x2,
                       current->data.line.y2,
                       current->data.line.stroke ? current->data.line.stroke : "none");
                break;
        }
        current = current->next;
    }
}
