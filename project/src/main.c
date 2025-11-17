#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/svg_parser.h"
#include "../include/svg_render.h"
#include "../include/bmp_writer.h"
// #include "../include/svg_gui.h"

void print_usage(const char *program_name) {
    printf("Usage:\n");
    printf("  %s --parse <input.svg>\n", program_name);
    printf("  %s -p <input.svg>\n", program_name);
    printf("  %s --export_bmp <input.svg> <output.bmp>\n", program_name);
    printf("  %s -eb <input.svg> <output.bmp>\n", program_name);
    printf("  %s --gui [input.svg]\n", program_name);
    printf("  %s -g [input.svg]\n", program_name);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    // GUI mode
    if (strcmp(argv[1], "--gui") == 0 || strcmp(argv[1], "-g") == 0) {
        printf("GUI mode is not available in this build (SDL not linked).\n");
        printf("Please use the separate svg_gui.exe for GUI functionality.\n");
        return 1;
    }

    if (argc < 3) {
        print_usage(argv[0]);
        return 1;
    }

    // Parse command
    if (strcmp(argv[1], "--parse") == 0 || strcmp(argv[1], "-p") == 0) {
        SvgDocument *doc = NULL;
        if (svg_load_from_file(argv[2], &doc) != 0) {
            fprintf(stderr, "Failed to load SVG file: %s\n", argv[2]);
            return 1;
        }

        svg_print_summary(doc);
        svg_print_shapes(doc);

        svg_free_document(doc);
        return 0;
    }

    // Export to BMP
    if (strcmp(argv[1], "--export_bmp") == 0 || strcmp(argv[1], "-eb") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Error: Output filename required\n");
            print_usage(argv[0]);
            return 1;
        }

        SvgDocument *doc = NULL;
        if (svg_load_from_file(argv[2], &doc) != 0) {
            fprintf(stderr, "Failed to load SVG file: %s\n", argv[2]);
            return 1;
        }

        if (export_to_bmp(argv[3], doc) != 0) {
            fprintf(stderr, "Failed to export BMP file: %s\n", argv[3]);
            svg_free_document(doc);
            return 1;
        }

        printf("Successfully exported to BMP: %s\n", argv[3]);

        svg_free_document(doc);
        return 0;
    }

    fprintf(stderr, "Unknown command: %s\n", argv[1]);
    print_usage(argv[0]);
    return 1;
}
