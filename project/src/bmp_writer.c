#include "../include/bmp_writer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BMPHeader;

typedef struct {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits;
    uint32_t compression;
    uint32_t imagesize;
    int32_t xresolution;
    int32_t yresolution;
    uint32_t ncolors;
    uint32_t importantcolors;
} BMPInfoHeader;
#pragma pack(pop)

static void draw_pixel(uint8_t *pixels, int width, int height, int x, int y, uint32_t color) {
    if (x < 0 || x >= width || y < 0 || y >= height) return;
    
    int index = (y * width + x) * 3;
    pixels[index + 0] = (color >> 16) & 0xFF; // R
    pixels[index + 1] = (color >> 8) & 0xFF;  // G
    pixels[index + 2] = color & 0xFF;         // B
}

static void draw_circle(uint8_t *pixels, int width, int height, SvgCircle *circle) {
    int cx = (int)circle->cx;
    int cy = (int)circle->cy;
    int r = (int)circle->r;

    // Parse color from string
    uint32_t color = 0xFFFFFF; // default white
    if (circle->fill && strlen(circle->fill) > 1) {
        sscanf(circle->fill + 1, "%6x", &color);
    }

    for (int y = cy - r; y <= cy + r; y++) {
        for (int x = cx - r; x <= cx + r; x++) {
            int dx = x - cx;
            int dy = y - cy;
            if (dx * dx + dy * dy <= r * r) {
                draw_pixel(pixels, width, height, x, y, color);
            }
        }
    }
}

static void draw_rect(uint8_t *pixels, int width, int height, SvgRect *rect) {
    int x1 = (int)rect->x;
    int y1 = (int)rect->y;
    int x2 = x1 + (int)rect->width;
    int y2 = y1 + (int)rect->height;

    // Parse color from string
    uint32_t color = 0xFFFFFF; // default white
    if (rect->fill && strlen(rect->fill) > 1) {
        sscanf(rect->fill + 1, "%6x", &color);
    }

    for (int y = y1; y < y2; y++) {
        for (int x = x1; x < x2; x++) {
            draw_pixel(pixels, width, height, x, y, color);
        }
    }
}

static void draw_line(uint8_t *pixels, int width, int height, SvgLine *line) {
    int x1 = (int)line->x1;
    int y1 = (int)line->y1;
    int x2 = (int)line->x2;
    int y2 = (int)line->y2;

    // Parse color from string
    uint32_t color = 0x000000; // default black
    if (line->stroke && strlen(line->stroke) > 1) {
        sscanf(line->stroke + 1, "%6x", &color);
    }

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (1) {
        draw_pixel(pixels, width, height, x1, y1, color);

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

int export_to_bmp(const char *filename, const SvgDocument *doc) {
    if (!doc || !filename) return -1;
    
    int width = (int)doc->width;
    int height = (int)doc->height;
    
    // Allocate pixel buffer
    uint8_t *pixels = (uint8_t *)calloc(width * height * 3, sizeof(uint8_t));
    if (!pixels) return -1;
    
    // Fill with white background
    memset(pixels, 255, width * height * 3);
    
    // Render all shapes
    SvgShape *current = doc->shapes;
    while (current) {
        switch (current->type) {
            case SVG_SHAPE_CIRCLE:
                draw_circle(pixels, width, height, &current->data.circle);
                break;
            case SVG_SHAPE_RECT:
                draw_rect(pixels, width, height, &current->data.rect);
                break;
            case SVG_SHAPE_LINE:
                draw_line(pixels, width, height, &current->data.line);
                break;
        }
        current = current->next;
    }
    
    // Write BMP file
    FILE *file = fopen(filename, "wb");
    if (!file) {
        free(pixels);
        return -1;
    }
    
    int row_size = ((width * 3 + 3) / 4) * 4;
    int image_size = row_size * height;
    
    BMPHeader header = {0};
    header.type = 0x4D42;
    header.size = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + image_size;
    header.offset = sizeof(BMPHeader) + sizeof(BMPInfoHeader);
    
    BMPInfoHeader info = {0};
    info.size = sizeof(BMPInfoHeader);
    info.width = width;
    info.height = height;
    info.planes = 1;
    info.bits = 24;
    info.imagesize = image_size;
    
    fwrite(&header, sizeof(BMPHeader), 1, file);
    fwrite(&info, sizeof(BMPInfoHeader), 1, file);
    
    // Write pixel data (bottom to top, BGR format)
    uint8_t *row = (uint8_t *)calloc(row_size, sizeof(uint8_t));
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            int src_idx = (y * width + x) * 3;
            int dst_idx = x * 3;
            row[dst_idx + 0] = pixels[src_idx + 2]; // B
            row[dst_idx + 1] = pixels[src_idx + 1]; // G
            row[dst_idx + 2] = pixels[src_idx + 0]; // R
        }
        fwrite(row, row_size, 1, file);
    }
    
    free(row);
    free(pixels);
    fclose(file);
    
    return 0;
}
