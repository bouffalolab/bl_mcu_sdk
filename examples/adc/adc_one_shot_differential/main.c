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
#include "hal_adc.h"
#include "hal_gpio.h"

#define ADC_SCAN_NUM (50)

adc_channel_t posChList[] = {ADC_CHANNEL3};
adc_channel_t negChList[] = {ADC_CHANNEL4};

adc_channel_val_t result_val;

struct device* adc_test;

int main(void)
{
    bflb_platform_init(0);

    adc_channel_cfg_t adc_channel_cfg;

    adc_channel_cfg.pos_channel = posChList;
    adc_channel_cfg.neg_channel = negChList;
    adc_channel_cfg.num = 1;

    MSG("adc one-shot differential test case \r\n");
    adc_register(ADC0_INDEX, "adc_one_diff", DEVICE_OFLAG_STREAM_RX);

    adc_test = device_find("adc_one_diff");
    if(adc_test)
    {
        ADC_DEV(adc_test)->differential_mode = ENABLE;
        device_open(adc_test, DEVICE_OFLAG_STREAM_RX);
        device_control(adc_test,DEVICE_CTRL_ADC_CHANNEL_CONFIG,&adc_channel_cfg);
        MSG("adc device find success\r\n");
    }

    for(uint32_t i = 0; i < ADC_SCAN_NUM; i++ )
    {
        adc_channel_start(adc_test);
        device_read(adc_test, 0, (void *)&result_val,sizeof(result_val)/sizeof(adc_channel_val_t));
        if(result_val.volt <= 0)
        {
            result_val.volt = -result_val.volt;
            MSG("PosId = %d NegId = %d V= -%d mV \r\n",result_val.posChan,result_val.negChan,(uint32_t)(result_val.volt * 1000));
        }
        else
        {
            MSG("PosId = %d NegId = %d V= %d mV \r\n",result_val.posChan,result_val.negChan,(uint32_t)(result_val.volt * 1000));
        }
        bflb_platform_delay_ms(500);
    }

    while (1)
    {

    }

}