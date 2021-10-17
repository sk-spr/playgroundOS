#pragma once
#include <stdint.h>
#define GDT_OFFSET_KERNEL_CODE 0x08
#define IDT_MAX_DESCRIPTORS 256

typedef struct {
	uint16_t    base_low;      // The lower 16 bits of the ISR's address
	uint16_t    cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t	    ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    base_mid;      // The higher 16 bits of the lower 32 bits of the ISR's address
	uint32_t    base_high;     // The higher 32 bits of the ISR's address
	uint32_t    rsv0;     // Set to zero
} __attribute__((packed)) idt_entry_t;

//IDTR struct
typedef struct{
    uint16_t limit;
	uint64_t base;
} __attribute__ ((packed)) idtr_t;

//create IDT
__attribute__((aligned(0x10)))
static idt_entry_t idt[IDT_MAX_DESCRIPTORS];

static idtr_t idtr;

void idt_init(void);

static bool vectors[IDT_MAX_DESCRIPTORS];
