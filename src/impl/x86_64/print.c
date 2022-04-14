#include "print.h"

const static size_t COLS = 80;
const static size_t ROWS = 25;

struct Char {
    uint8_t c;
    uint8_t color;
};

struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void clear_row(size_t row)
{
    struct Char empty = (struct Char) {
        c: ' ',
        color: color,
    };

    for (size_t col = 0; col < COLS; col++) {
        buffer[col + COLS * row] = empty;
    }
}

void clear()
{
    for (size_t i = 0; i < ROWS; i++)
    {
        clear_row(i);
    }
}

void print_char(char c)
{
    if (c == '\n')
    {
        newline();
        return;
    }

    if (col > COLS)
    {
        newline();
    }

    buffer[col + COLS * row] = (struct Char) {
        c: (uint8_t) c,
        color: color,
    };

    col++;
}

void newline() {
    col = 0;

    if (row < ROWS - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < ROWS; row++) {
        for (size_t col = 0; col < COLS; col++) {
            struct Char c = buffer[col + COLS * row];
            buffer[col + COLS * (row - 1)] = c;
        }
    }

    clear_row(COLS - 1);
}

void print(char* str)
{
    for (size_t i = 0; 1; i++)
    {
        char c = (uint8_t) str[i];
        if (c == '\0')
        {
            return;
        }

        print_char(c);
    }
}

void set_text_color(uint8_t fg, uint8_t bg)
{
    color = fg + (bg << 4);
}

