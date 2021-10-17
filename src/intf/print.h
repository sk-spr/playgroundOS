#ifndef PRINTH
#define PRINTH
#include "stdint.h"
#include "./math.hpp"
#define NUMCOLS 80
#define NUMROWS 25
#define BG (PRINT_COLOR_GREEN | PRINT_COLOR_BLACK << 4)
#define GB (PRINT_COLOR_BLACK | PRINT_COLOR_GREEN << 4)

//The standard Character struct for printing to the char buffer. Contains char and colour.
struct Character{
    uint8_t c;
    uint8_t col;
};

void print_str(char msg[], uint8_t col, int len);
void print_char(char c, uint8_t col);
void print_char(Character c);
void init_screen();
void print_screen();
void displace_screen();
void prints_char(Character c);
void prints_newline();
void prints(char msg[], uint8_t col, int len);
void prints(char msg[], int len);
void prints(char msg[]);
void prints_colour(char msg[], uint8_t col);
void construct_colstring(char* message, int len, uint8_t col, Character* out);
int strlen(char msg[]);
char* tochars(int i);
void print_newline();
void print_blankline();
//https://github.com/davidcallanan/os-series/blob/ep2/src/intf/print.h
enum {
    PRINT_COLOR_BLACK = 0,
	PRINT_COLOR_BLUE = 1,
	PRINT_COLOR_GREEN = 2,
	PRINT_COLOR_CYAN = 3,
	PRINT_COLOR_RED = 4,
	PRINT_COLOR_MAGENTA = 5,
	PRINT_COLOR_BROWN = 6,
	PRINT_COLOR_LIGHT_GRAY = 7,
	PRINT_COLOR_DARK_GRAY = 8,
	PRINT_COLOR_LIGHT_BLUE = 9,
	PRINT_COLOR_LIGHT_GREEN = 10,
	PRINT_COLOR_LIGHT_CYAN = 11,
	PRINT_COLOR_LIGHT_RED = 12,
	PRINT_COLOR_PINK = 13,
	PRINT_COLOR_YELLOW = 14,
	PRINT_COLOR_WHITE = 15,
};
#endif