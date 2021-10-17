#include "../../intf/print.h"
#include "../../intf/math.hpp"
const Character empty = {' ', BG};
int currentX = 0;
int currentY = 0;
int screenX = 0;
int screenY = 0;

Character* buffer = (Character*) 0xb8000;

Character screen[NUMROWS][NUMCOLS];

//print a char array to the character buffer unchecked
void print_debug(char msg[], uint8_t col, int len){
    for(int i = 0; i < len - 1; i++)
        print_char(msg[i], col);
    return;
}
//print red text to the character buffer
void print_error(char msg[], int len){
    print_debug(msg, PRINT_COLOR_RED | PRINT_COLOR_BLACK << 4, len);
    return;
}
//print a string of characters to the character buffer
void print_str(char msg[], uint8_t col, int len){
    print_debug(msg, col, len);
    return;
    //TODO: escape sequences
};
//print a char array of colour col to the screen buffer
void prints(char msg[], uint8_t col, int len){
    for(int i = 0; i < len - 1; i++)
        prints_char((Character){msg[i], col});
    print_screen();
    return;
}
//print a char array to the screen buffer
void prints(char msg[], int len){
    prints(msg, BG, len);
}
void prints(char msg[]){
    prints(msg, BG, strlen(msg));
}
void prints_colour(char msg[], uint8_t col){
    prints(msg, col, strlen(msg));
}
//print a char with color col to the character buffer
void print_char(char character, uint8_t col){
    if(currentX >= NUMCOLS){
        print_newline();
        buffer[currentX + currentY * NUMCOLS] = (Character){
            character, col
        };    
        currentX++;
    }   
    else if(character == '\n')
        print_newline();
    else{
        buffer[currentX + currentY * NUMCOLS] = (Character){
            character, col
        };    
        currentX++;
    }
}
//print a char to the character buffer
void print_char(char character){
    print_char(character, BG);
}
//print a Character to the character buffer
void print_char(Character c){
    print_char(c.c, c.col);
}

//print a character to the screen buffer
void prints_char(Character c){
    if(screenX >= NUMCOLS){
        prints_newline();
        screen[screenY][screenX] = c;
        screenX++;
    }else if(c.c == '\n'){
        prints_newline();
    } else {
        screen[screenY][screenX] = c;
        screenX++;
    }
    return;
}
//print a newline to the character buffer
void print_newline(){
    int remaining = NUMCOLS - currentX;
    for(int i = 0; i < remaining; i++){
        print_char(' ', BG);
    }
    currentY++;
    currentX = 0;
    return;
}
//print a newline to the screen buffer
void prints_newline(){
    int remaining = NUMCOLS - screenX;
    for(int i = 0; i < remaining; i++){
        prints_char(empty);
    } 
    screenY++;
    if(screenY >= NUMROWS)
        displace_screen();
    screenX = 0;
}

//fill the screen buffer with spaces, then print it
void init_screen(){
    for(int i = 0; i < NUMROWS; i++){
        for(int j = 0; j < NUMCOLS; j++){
            screen[i][j] = empty;
        }
    }
    print_screen();
    currentX = 0;
    currentY = 0;
    screenX = 0;
    screenY = 0;
}

//print the screen buffer to the character buffer
void print_screen(){
    currentX = 0;
    currentY = 0;
    for(int i = 0; i < NUMROWS; i++){
        for(int j = 0; j < NUMCOLS; j++){
            print_char(screen[i][j]);
        }
        print_newline();
    }
    currentX = 0;
    currentY = 0;
    return;
}

//move all rows in the screen buffer up and insert empty row
void displace_screen(){
    for(int i = 0; i < NUMROWS - 1; i++){
        for(int j = 0; j < NUMCOLS; j++){
            screen[i][j] = screen[i+1][j];
        }
    }
    for(int i = 0; i < NUMCOLS; i++)
        screen[NUMROWS-1][i] = empty;
    screenY = NUMROWS-1;
    print_screen();
}

//HELPERS

//constructs a "colstring"(array of Characters) in buffer out
void construct_colstring(char* string, int len, uint8_t colour, Character* out){
    for(int i = 0; i < len; i++){
        out[i] = (Character){string[i], colour};
    }
    return;
}

//gets array length of null-terminated char arrays
//(including null termination)
int strlen(char msg[]){
    int len = 0;
    while(msg[len] != '\0')
        len++;
    return len+1;
}

const char digits[] = "0123456789";
