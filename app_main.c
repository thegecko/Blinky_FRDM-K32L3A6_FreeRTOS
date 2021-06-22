/* -----------------------------------------------------------------------------
 * Copyright (c) 2020 Arm Limited (or its affiliates). All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * -------------------------------------------------------------------------- */

#include "main.h"

#include "cmsis_os2.h"
#include "cmsis_vio.h"

#define BLINKING_DELAY 500U

static const osThreadAttr_t app_main_attr = {.stack_size = 8192U};

/*-----------------------------------------------------------------------------
 * Application main thread
 *----------------------------------------------------------------------------*/
static void app_main(void *argument) {
  
  volatile int8_t led;
  led = 1;

  for (;;) {
    if (led == 1) {
      vioSetSignal(vioLED0, vioLEDon);  // Switch LED0 on
    } else {
      vioSetSignal(vioLED0, vioLEDoff); // Switch LED0 off
    }
    osDelay(BLINKING_DELAY);
    led *= -1;
  }
}

/*-----------------------------------------------------------------------------
 * Application initialization
 *----------------------------------------------------------------------------*/
void app_initialize(void) { osThreadNew(app_main, NULL, &app_main_attr); }
