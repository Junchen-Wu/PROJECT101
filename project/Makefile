CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -Iinclude -Igui_libs/SDL2-2.30.6/include
LDFLAGS = -Lgui_libs/SDL2-2.30.6/lib/x64 -lSDL2 -lm
TARGET = build/svg_processor.exe

SRCS = src/main.c src/svg_parser.c src/svg_render.c src/bmp_writer.c src/svg_gui.c
OBJS = $(SRCS:.c=.o)
HEADERS = include/svg_types.h include/svg_parser.h include/svg_render.h include/bmp_writer.h include/svg_gui.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q $(OBJS) build\$(TARGET) 2>nul || echo Cleaned

run: $(TARGET)
	.\$(TARGET)

.PHONY: all clean run
