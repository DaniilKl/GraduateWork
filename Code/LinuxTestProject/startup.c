#include <stdint.h>

// Memory definitions:
#define SRAM_START (0x20000000U)
#define SRAM_SIZE (96U * 1024U)
#define SRAM_END (SRAM_START + SRAM_SIZE)
#define STACK_POINTER_INIT_ADDRESS (SRAM_END)

void reset_handler(void);
void default_handler(void);
void nmi_handler(void) __attribute__((weak, alias("default_handler")));
void hard_fault_handler(void) __attribute__((weak, alias("default_handler")));
void mem_manage_handler(void) __attribute__((weak, alias("default_handler"))); 
void bus_fault_handler(void) __attribute__((weak, alias("default_handler")));
void usage_fault_handler(void) __attribute__((weak, alias("default_handler")));
void svcall_handler(void) __attribute__((weak, alias("default_handler")));
void debug_monitor_handler(void) __attribute__((weak, alias("default_handler")));
void pendsv_handler(void) __attribute__((weak, alias("default_handler")));
void systick_handler(void) __attribute__((weak, alias("default_handler")));
void wwdg_handler(void) __attribute__((weak, alias("default_handler")));
void pvd_handler(void) __attribute__((weak, alias("default_handler")));
void tamp_stamp_handler(void) __attribute__((weak, alias("default_handler")));
void rtc_wkup_handler(void) __attribute__((weak, alias("default_handler")));
void flash_handler(void) __attribute__((weak, alias("default_handler")));
void rcc_handler(void) __attribute__((weak, alias("default_handler")));
void exti0_handler(void) __attribute__((weak, alias("default_handler")));
void exti1_handler(void) __attribute__((weak, alias("default_handler")));
void exti2_handler(void) __attribute__((weak, alias("default_handler")));
void exti3_handler(void) __attribute__((weak, alias("default_handler")));
void exti4_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream1_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream2_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream3_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream4_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream5_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream6_handler(void) __attribute__((weak, alias("default_handler")));
void adc_handler(void) __attribute__((weak, alias("default_handler")));
void exti9_5_handler(void) __attribute__((weak, alias("default_handler")));
void tim1_brk_tim9_handler(void) __attribute__((weak, alias("default_handler")));
void tim1_up_tim10_handler(void) __attribute__((weak, alias("default_handler")));
void tim1_trg_com_tim11_handler(void) __attribute__((weak, alias("default_handler")));
void tim1_cc_handler(void) __attribute__((weak, alias("default_handler")));
void tim2_handler(void) __attribute__((weak, alias("default_handler")));
void tim3_handler(void) __attribute__((weak, alias("default_handler")));
void tim4_handler(void) __attribute__((weak, alias("default_handler")));
void i2c1_ev_handler(void) __attribute__((weak, alias("default_handler")));
void i2c1_er_handler(void) __attribute__((weak, alias("default_handler")));
void i2c2_ev_handler(void) __attribute__((weak, alias("default_handler")));
void i2c2_er_handler(void) __attribute__((weak, alias("default_handler")));
void spi1_handler(void) __attribute__((weak, alias("default_handler")));
void spi2_handler(void) __attribute__((weak, alias("default_handler")));
void usart1_handler(void) __attribute__((weak, alias("default_handler")));
void usart2_handler(void) __attribute__((weak, alias("default_handler")));
void exti15_10_handler(void) __attribute__((weak, alias("default_handler")));
void rtc_alarm_handler(void) __attribute__((weak, alias("default_handler")));
void otg_fs_wkup_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream7_handler(void) __attribute__((weak, alias("default_handler")));
void sdio_handler(void) __attribute__((weak, alias("default_handler")));
void tim5_handler(void) __attribute__((weak, alias("default_handler")));
void spi3_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream0_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream1_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream2_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream3_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream4_handler(void) __attribute__((weak, alias("default_handler")));
void otg_fs_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream5_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream6_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream7_handler(void) __attribute__((weak, alias("default_handler")));
void usart6_handler(void) __attribute__((weak, alias("default_handler")));
void i2c3_ev_handler(void) __attribute__((weak, alias("default_handler")));
void i2c3_er_handler(void) __attribute__((weak, alias("default_handler")));
void fpu_handler(void) __attribute__((weak, alias("default_handler")));
void spi4_handler(void) __attribute__((weak, alias("default_handler")));

uint32_t isr_vector[] __attribute__((section(".isr_vector"))) = {
	STACK_POINTER_INIT_ADDRESS, //0x0
	(uint32_t)&reset_handler, //0x4
	(uint32_t)&nmi_handler, //0x8
	(uint32_t)&hard_fault_handler, //0xc
	(uint32_t)&mem_manage_handler, //0x10
	(uint32_t)&bus_fault_handler, //0x14
	(uint32_t)&usage_fault_handler, //0x18
  0, //0x1c RESERVED
  0, //0x20 RESERVED
  0, //0x24 RESERVED
  0, //0x28 RESERVED
  (uint32_t)&svcall_handler, //0x2c
  (uint32_t)&debug_monitor_handler, //0x30
  0, //0x34 RESERVED
  (uint32_t)&pendsv_handler, //0x38
  (uint32_t)&systick_handler, //0x3c
  (uint32_t)&wwdg_handler, //0x40
  (uint32_t)&pvd_handler, //0x44
  (uint32_t)&tamp_stamp_handler, //0x48
  (uint32_t)&rtc_wkup_handler, //0x4c
  (uint32_t)&flash_handler, //0x50
  (uint32_t)&rcc_handler, //0x54
  (uint32_t)&exti0_handler, //0x58
  (uint32_t)&exti1_handler, //0x5c
  (uint32_t)&exti2_handler, //0x60
  (uint32_t)&exti3_handler, //0x64
  (uint32_t)&exti4_handler, //0x68
  (uint32_t)&dma2_stream0_handler, //0x6c
  (uint32_t)&dma2_stream1_handler, //0x70
  (uint32_t)&dma2_stream2_handler, //0x74
  (uint32_t)&dma2_stream3_handler, //0x78
  (uint32_t)&dma2_stream4_handler, //0x7c
  (uint32_t)&dma2_stream5_handler, //0x80
  (uint32_t)&dma2_stream6_handler, //0x84
  (uint32_t)&adc_handler, //0x88
  0, //0x8c
  0, //0x90
  0, //0x94
  0, //0x98
  (uint32_t)&exti9_5_handler, //0x9c
  (uint32_t)&tim1_brk_tim9_handler, //0xa0
  (uint32_t)&tim1_up_tim10_handler, //0xa4
  (uint32_t)&tim1_trg_com_tim11_handler, //0xa8
  (uint32_t)&tim1_cc_handler, //0xac
  (uint32_t)&tim2_handler, //0xb0
  (uint32_t)&tim3_handler, //0xb4
  (uint32_t)&tim4_handler, //0xb8
  (uint32_t)&i2c1_ev_handler, //0xbc
  (uint32_t)&i2c1_er_handler, //0xc0
  (uint32_t)&i2c2_ev_handler, //0xc4
  (uint32_t)&i2c2_er_handler, //0xc8
  (uint32_t)&spi1_handler, //0xcc
  (uint32_t)&spi2_handler, //0xd0
  (uint32_t)&usart1_handler, //0xd4
  (uint32_t)&usart2_handler, //0xd8
  0, //0xdc
  (uint32_t)&exti15_10_handler, //0xe0
  (uint32_t)&rtc_alarm_handler, //0xe4
  (uint32_t)&otg_fs_wkup_handler, //0xe8
  0, //0xec
  0, //0xf0
  0, //0xf4
  0, //0xf8
  (uint32_t)&dma1_stream7_handler, //0xfc
  0, //0x100
  (uint32_t)&sdio_handler, //0x104
  (uint32_t)&tim5_handler, //0x108
  (uint32_t)&spi3_handler, //0x10c
  0, //0x110
  0, //0x114
  0, //0x118
  0, //0x11c
  (uint32_t)&dma2_stream0_handler, //0x120
  (uint32_t)&dma2_stream1_handler, //0x124
  (uint32_t)&dma2_stream2_handler, //0x128
  (uint32_t)&dma2_stream3_handler, //0x12c
  (uint32_t)&dma2_stream4_handler, //0x130
  0, //0x134
  0, //0x138
  0, //0x13c
  0, //0x140
  0, //0x144
  0, //0x148
  (uint32_t)&otg_fs_handler, //0x14c
  (uint32_t)&dma2_stream5_handler, //0x150
  (uint32_t)&dma2_stream6_handler, //0x154
  (uint32_t)&dma2_stream7_handler, //0x158
  (uint32_t)&usart6_handler, //0x15c
  (uint32_t)&i2c3_ev_handler, //0x160
  (uint32_t)&i2c3_er_handler, //0x164
  0, //0x168
  0, //0x16c
  0, //0x170
  0, //0x174
  0, //0x178
  0, //0x17c
  0, //0x180
  (uint32_t)&fpu_handler, //0x184
  0, //0x188
  0, //0x18c
  (uint32_t)&spi4_handler, //0x190
};

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;

int main(void);

void reset_handler(void){

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

void default_handler(void){
    while (1) {
    }
  }
