/**
 * @file main.c
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
#include "hal_i2c.h"
#include "hal_uart.h"

int main(void)
{
    i2c_msg_t msg[2];
    uint8_t buf[8] = {0};

    bflb_platform_init(0);

    i2c_register(I2C0_INDEX, "i2c", DEVICE_OFLAG_RDWR);
    struct device *i2c0 = device_find("i2c");

    if (i2c0)
    {
        MSG("device find success\r\n");
        device_open(i2c0, 0);
    }
    msg[0].buf = buf;
    msg[0].flags = SUB_ADDR_1BYTE | I2C_WR;
    msg[0].len = 8;
    msg[0].slaveaddr = 0x50;
    msg[0].subaddr = 0x00;

    msg[1].buf = buf;
    msg[1].flags = SUB_ADDR_1BYTE | I2C_RD;
    msg[1].len = 8;
    msg[1].slaveaddr = 0x50;
    msg[1].subaddr = 0x00;
    if (i2c_transfer(i2c0, &msg[0], 2) == 0)
        MSG("\r\n read:%0x\r\n", msg[1].buf[0] << 8 | msg[1].buf[1]);

    while (1)
    {
        MSG("\r\n i2c case\r\n");
        bflb_platform_delay_ms(1000);
    }
}