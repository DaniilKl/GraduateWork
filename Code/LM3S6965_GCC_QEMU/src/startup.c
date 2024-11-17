#include <stdint.h>

// Memory definitions:
#define SRAM_START (0x20000000U)
#define SRAM_SIZE (64U * 1024U)
#define SRAM_END (SRAM_START + SRAM_SIZE)
#define STACK_POINTER_INIT_ADDRESS (SRAM_END)

#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

void ResetISR(void);
static void vDefaultHandler(void);
extern void vPortSVCHandler(void);
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);

uint32_t isr_vector[] __attribute__((section(".isr_vector"))) = {
    STACK_POINTER_INIT_ADDRESS,
    (uint32_t)&ResetISR,                             // The reset handler
    (uint32_t)&vDefaultHandler,                      // The NMI handler
    (uint32_t)&vDefaultHandler,                      // The hard fault handler
    (uint32_t)&vDefaultHandler,                      // The MPU fault handler
    (uint32_t)&vDefaultHandler,                      // The bus fault handler
    (uint32_t)&vDefaultHandler,                      // The usage fault handler
    0,                                               // Reserved
    0,                                               // Reserved
    0,                                               // Reserved
    0,                                               // Reserved
    (uint32_t)&vPortSVCHandler,			     // SVCall handler
    (uint32_t)&vDefaultHandler,                      // Debug monitor handler
    0,                                               // Reserved
    (uint32_t)&xPortPendSVHandler,                   // The PendSV handler
    (uint32_t)&xPortSysTickHandler,                  // The SysTick handler
    (uint32_t)&vDefaultHandler,                      // GPIO Port A
    (uint32_t)&vDefaultHandler,                      // GPIO Port B
    (uint32_t)&vDefaultHandler,                      // GPIO Port C
    (uint32_t)&vDefaultHandler,                      // GPIO Port D
    (uint32_t)&vDefaultHandler,                      // GPIO Port E
    (uint32_t)&vDefaultHandler,                      // UART0 Rx and Tx
    (uint32_t)&vDefaultHandler,                      // UART1 Rx and Tx
    (uint32_t)&vDefaultHandler,                      // SSI Rx and Tx
    (uint32_t)&vDefaultHandler,                      // I2C Master and Slave
    (uint32_t)&vDefaultHandler,                      // PWM Fault
    (uint32_t)&vDefaultHandler,                      // PWM Generator 0
    (uint32_t)&vDefaultHandler,                      // PWM Generator 1
    (uint32_t)&vDefaultHandler,                      // PWM Generator 2
    (uint32_t)&vDefaultHandler,                      // Quadrature Encoder
    (uint32_t)&vDefaultHandler,                      // ADC Sequence 0
    (uint32_t)&vDefaultHandler,                      // ADC Sequence 1
    (uint32_t)&vDefaultHandler,                      // ADC Sequence 2
    (uint32_t)&vDefaultHandler,                      // ADC Sequence 3
    (uint32_t)&vDefaultHandler,                      // Watchdog timer
    (uint32_t)&vDefaultHandler,                      // Timer 0 subtimer A
    (uint32_t)&vDefaultHandler,                      // Timer 0 subtimer B
    (uint32_t)&vDefaultHandler,                      // Timer 1 subtimer A
    (uint32_t)&vDefaultHandler,                      // Timer 1 subtimer B
    (uint32_t)&vDefaultHandler,                      // Timer 2 subtimer A
    (uint32_t)&vDefaultHandler,                      // Timer 2 subtimer B
    (uint32_t)&vDefaultHandler,                      // Analog Comparator 0
    (uint32_t)&vDefaultHandler,                      // Analog Comparator 1
    (uint32_t)&vDefaultHandler,                      // Analog Comparator 2
    (uint32_t)&vDefaultHandler,                      // System Control (PLL, OSC, BO)
    (uint32_t)&vDefaultHandler,                      // FLASH Control
    (uint32_t)&vDefaultHandler,                      // GPIO Port F
    (uint32_t)&vDefaultHandler,                      // GPIO Port G
    (uint32_t)&vDefaultHandler,                      // GPIO Port H
    (uint32_t)&vDefaultHandler,                      // UART2 Rx and Tx
    (uint32_t)&vDefaultHandler,                      // SSI1 Rx and Tx
    (uint32_t)&vDefaultHandler,                      // Timer 3 subtimer A
    (uint32_t)&vDefaultHandler,                      // Timer 3 subtimer B
    (uint32_t)&vDefaultHandler,                      // I2C1 Master and Slave
    (uint32_t)&vDefaultHandler,                      // Quadrature Encoder 1
    (uint32_t)&vDefaultHandler,                      // CAN0
    (uint32_t)&vDefaultHandler,                      // CAN1
    0,                                               // Reserved
    (uint32_t)&vDefaultHandler,                      // Ethernet
    (uint32_t)&vDefaultHandler                       // Hibernate
};

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;

int main(void);

void ResetISR(void){

  // Copy data from FLSH to SRAM
  uint32_t DataSize = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *FlashData = (uint8_t*) &_etext;
  uint8_t *SramData = (uint8_t*) &_sdata;

  for (uint32_t i = 0; i < DataSize; i++){
    SramData[i] = FlashData[i];
  }

  // Zero-fill .bss section in SRAM
  uint32_t BssSize = (uint32_t)&_ebss - (uint32_t)&_sbss;
  uint8_t *Bss = (uint8_t*) &_sbss;

  for (uint32_t i = 0; i < BssSize; i++){
    Bss[i] = 0;
  }

  main();
}

void vDefaultHandler(void){
    while (1) {
    }
}
