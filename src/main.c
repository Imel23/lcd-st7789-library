#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "lcd_st7789_library.h"

#define PI 3.14159265358979323846

#define FLAG_RED create_color(255, 0, 0)   // Moroccan flag red
#define FLAG_GREEN create_color(0, 255, 0)   // Moroccan flag green
#define LINE_THICKNESS 3  // Thickness of the star's lines

// Function to draw a thick line
void lcd_draw_thick_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color, uint8_t thickness) {
    int16_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int16_t dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int16_t err = dx + dy, e2;

    while (1) {
        for (int16_t i = -(thickness / 2); i <= thickness / 2; i++) {
            for (int16_t j = -(thickness / 2); j <= thickness / 2; j++) {
                lcd_draw_pixel(x0 + i, y0 + j, color);
            }
        }
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

// Function to draw a thick line with any angle
void lcd_draw_thick_line_angle(int16_t x0, int16_t y0, float angle, int16_t length, uint16_t color, uint8_t thickness) {
    int16_t x1 = x0 + length * cos(angle);
    int16_t y1 = y0 + length * sin(angle);
    lcd_draw_thick_line(x0, y0, x1, y1, color, thickness);
}

// Function to draw an outlined pentagram (five-pointed star) with thick lines
void draw_outlined_pentagram(int16_t x, int16_t y, int16_t r, uint16_t color, uint8_t thickness) {
    for (int i = 0; i < 5; i++) {
        float angle1 = (float)i * 2 * PI / 5 - PI / 2;  // Start from top point
        float angle2 = (float)(i + 2) * 2 * PI / 5 - PI / 2;
        int16_t x1 = x + r * cos(angle1);
        int16_t y1 = y + r * sin(angle1);
        int16_t x2 = x + r * cos(angle2);
        int16_t y2 = y + r * sin(angle2);
        lcd_draw_thick_line(x1, y1, x2, y2, color, thickness);
    }
}

int main() {
    stdio_init_all();
    lcd_init();

    // Fill the screen with red (background of the Moroccan flag)
    lcd_fill_color(FLAG_RED);

    // Calculate the center and size of the pentagram
    int16_t center_x = WIDTH / 2;
    int16_t center_y = HEIGHT / 2;
    int16_t star_size = (WIDTH < HEIGHT ? WIDTH : HEIGHT) / 3;  // Star size is 1/3 of the smaller dimension

    // Draw the green outlined pentagram with thick lines
    draw_outlined_pentagram(center_x, center_y, star_size, FLAG_GREEN, LINE_THICKNESS);

    // Main loop (do nothing, just keep the display on)
    while (1) {
        tight_loop_contents();
    }

    return 0;
}