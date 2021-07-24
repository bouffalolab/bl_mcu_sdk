/**
 * @file touch.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "touch.h"

void touch_init(void)
{
#if defined(TOUCH_CONTROLLER_XPT2046)
    xpt2046_init();
#endif
}

uint8_t touch_read(int16_t *x, int16_t *y)
{
#if defined(TOUCH_CONTROLLER_XPT2046)
    return xpt2046_read(x, y);
#endif
}
