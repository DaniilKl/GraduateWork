#include <stdint.h>

// AHB1 definitions:
#define PERIPHERAL_BASE (0x40000000U)
#define AHB1_BASE (PERIPHERAL_BASE + 0x20000U)
#define AHB1_RCC_BASE (AHB1_BASE + 0x3800U)
#define AHB1_GPIOA_BASE (AHB1_BASE + 0x0U)

#define RCC_AHB1ENR ((volatile uint32_t*)(AHB1_RCC_BASE + 0x30U))

#define GPIOA_MODER ((volatile uint32_t*)(AHB1_GPIOA_BASE + 0x0U))
#define GPIO_MODER5 (0xaU)
#define GPIOA_ODR ((volatile uint32_t*)(AHB1_GPIOA_BASE + 0x14U))

#define LED_PIN (0x5U)

int main(void){
  *RCC_AHB1ENR |= (uint32_t)0x1;

  uint32_t dummy;
  dummy = *(RCC_AHB1ENR);
  dummy = *(RCC_AHB1ENR);
  
  *GPIOA_MODER |= (1 << GPIO_MODER5);

  while (1) {
      *GPIOA_ODR ^= (1 << LED_PIN);
      for (uint32_t i = 0; i < 1000000; i++);
  }
}
