/*
 * Copyright (c) 2017, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    MineSweeper_LPC54608.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "LPC54608.h"
#include "board.h"
#include "clock_config.h"
#include "lcd_tft.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

static void LcdTask(void *pvParameters) {
  LCD_Setup();

  LCD_RunExample();
}

/*
 * @brief   Application entry point.
 */
int main(void) {
  BOARD_InitPins();
  BOARD_BootClockFROHF48M();

  /* UART output thread, simply counts seconds */
  xTaskCreate(LcdTask, "vLcdTask", configMINIMAL_STACK_SIZE, NULL,
              (tskIDLE_PRIORITY + 1UL), (xTaskHandle *)NULL);

  /* Start the scheduler */
  vTaskStartScheduler();

  while (1) {
    __WFI();
  }
  return 0;
}
