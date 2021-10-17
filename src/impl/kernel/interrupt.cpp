#include "../../intf/interrupt.h"
#include "../../intf/print.h"
extern "C"
__attribute__ ((noreturn))
void exception_handler(void);
extern "C"
void exception_handler(){
    __asm__ volatile ("cli;hlt"); // completely hangs the computer
    //TODO: exception handling
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags){
    idt_entry_t* desc = &idt[vector];
    desc->base_low = (uint32_t)isr & 0xFFFF;
    desc->cs = GDT_OFFSET_KERNEL_CODE;
    desc->ist = 0;
    desc->attributes = flags;
    desc->base_mid       = ((uint64_t)isr >> 16) & 0xFFFF;
    desc->base_high      = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    desc->rsv0           = 0;
}
extern void *isr_stub_table[];
void idt_init(){
    prints("initialising idtr \n");
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS;
    prints("going into for loop \n");
    for(uint8_t vector = 0; vector < 32; vector++){
        prints("vector = ");
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }
    prints("\n going into asm \n");
    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    prints("asm 2 \n");
    __asm__ volatile ("sti"); // set the interrupt flag
    prints("initialised idtr");
}
