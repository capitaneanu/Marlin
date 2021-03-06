/**
 * Marlin 3D Printer Firmware
 *
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 * Copyright (c) 2016 Bob Cousins bobcousins42@googlemail.com
 * Copyright (c) 2015-2016 Nico Tonnhofer wurstnase.reprap@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#include "../../HAL.h"
#if (HAL_PLATFORM_ID == HAL_ID_STM32_F4_F7) && defined(STM32F4)

#include "../../../inc/MarlinConfig.h"

// ------------------------
// Local defines
// ------------------------

#define NUM_HARDWARE_TIMERS 2
#define STEP_TIMER_IRQ_ID TIM5_IRQn
#define TEMP_TIMER_IRQ_ID TIM8_IRQn

// ------------------------
// Private Variables
// ------------------------

stm32_timer_t TimerHandle[NUM_HARDWARE_TIMERS] = {0};
HAL_STEP_TIMER_ISR();
HAL_TEMP_TIMER_ISR();

uint32_t TimerRates[NUM_HARDWARE_TIMERS] = {0};

static uint32_t HAL_stepper_timer_prescaler(
  const uint8_t timer_num, const uint32_t desired_freq) {
  return (TimerHandle[timer_num]->getTimerClkFreq() + desired_freq / 2) / desired_freq;
}
// ------------------------
// Public functions
// ------------------------
void HAL_timer_start(const uint8_t timer_num, const uint32_t frequency) {
  if (!TimerHandle[timer_num]) {
    switch (timer_num) {
      case STEP_TIMER_NUM:
        // STEPPER TIMER TIM5 - use a 32bit timer
        TimerHandle[timer_num] = new HardwareTimer(TIM5);
        TimerHandle[timer_num]->setMode(1, TIMER_OUTPUT_COMPARE, NC);
        TimerHandle[timer_num]->setPrescaleFactor(
          HAL_stepper_timer_prescaler(STEP_TIMER_NUM, 2000000));
        TimerHandle[timer_num]->attachInterrupt(TC5_Handler);
        HAL_NVIC_SetPriority(STEP_TIMER_IRQ_ID, 1, 0);
        break;

      case TEMP_TIMER_NUM:
        // TEMP TIMER TIM8 - any available 16bit Timer (1 already used for PWM)
        TimerHandle[timer_num] = new HardwareTimer(TIM8);
        TimerHandle[timer_num]->setMode(1, TIMER_OUTPUT_COMPARE, NC);
        TimerHandle[timer_num]->setPrescaleFactor(
          HAL_stepper_timer_prescaler(TEMP_TIMER_NUM, 72000));
        TimerHandle[timer_num]->attachInterrupt(TC8_Handler);
        HAL_NVIC_SetPriority(TEMP_TIMER_IRQ_ID, 2, 0);
        break;
    }
    TimerRates[timer_num] = TimerHandle[timer_num]->getTimerClkFreq()
      / TimerHandle[timer_num]->getPrescaleFactor();
    TimerHandle[timer_num]->setOverflow(
      TimerRates[timer_num] / frequency - 1, TICK_FORMAT);
    TimerHandle[timer_num]->resume();
  }
}

void HAL_timer_enable_interrupt(const uint8_t timer_num) {
  if (TimerHandle[timer_num]) TimerHandle[timer_num]->resume();
  switch (timer_num) {
    case STEP_TIMER_NUM: HAL_NVIC_EnableIRQ(STEP_TIMER_IRQ_ID); break;
    case TEMP_TIMER_NUM: HAL_NVIC_EnableIRQ(TEMP_TIMER_IRQ_ID); break;
  }
}

void HAL_timer_disable_interrupt(const uint8_t timer_num) {
  if (TimerHandle[timer_num]) TimerHandle[timer_num]->pause();
  switch (timer_num) {
    case STEP_TIMER_NUM: 
      HAL_NVIC_DisableIRQ(STEP_TIMER_IRQ_ID);
      break;
    case TEMP_TIMER_NUM:
      HAL_NVIC_DisableIRQ(TEMP_TIMER_IRQ_ID);
      break;
  }

  // We NEED memory barriers to ensure Interrupts are actually disabled!
  // ( https://dzone.com/articles/nvic-disabling-interrupts-on-arm-cortex-m-and-the )
  __DSB();
  __ISB();
}

bool HAL_timer_interrupt_enabled(const uint8_t timer_num) {
  switch (timer_num) {
    case STEP_TIMER_NUM:
      return NVIC->ISER[(uint32_t)((int32_t)STEP_TIMER_IRQ_ID) >> 5]
        & (uint32_t)(1 << ((uint32_t)((int32_t)STEP_TIMER_IRQ_ID) & (uint32_t)0x1F));
    case TEMP_TIMER_NUM:
      return NVIC->ISER[(uint32_t)((int32_t)TEMP_TIMER_IRQ_ID) >> 5]
        & (uint32_t)(1 << ((uint32_t)((int32_t)TEMP_TIMER_IRQ_ID) & (uint32_t)0x1F));
  }
  return false;
}

#endif // (HAL_PLATFORM_ID == HAL_ID_STM32_F4_F7) && defined(STM32F4)
