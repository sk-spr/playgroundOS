#include "../../intf/print.h"
#include "../../intf/interrupt.h"
#include "../../intf/math.hpp"
//#include "threading.h"
extern "C"
void kernel_main(){
    //must be called to initialize the screen buffer
    init_screen();
    //welome message / console test
    prints("Welcome to playgroundOS \nfeel free to look around nya");
    prints("abcdef");
    int j = 0;
    for(int i = 0; i < 10; i++){
        //for(int i = 0; i < 9000000; i++)
        //    j++;
        prints_colour("i am green on black", BG);
        prints_colour("i am black on green", GB);
    }
    prints("\n");
    prints("printing int = ");
    //char* buf = tochars(123);
    //prints(tochars(123));
//    idt_init();
//    prints("initialised idt \n");
}