/*
   Copyright 2018 eeucalyptus <dev@eeucalyptus.net>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "softi2c.h"
#include "softi2c_port.h"

inline void SoftI2C_SendBit(SoftI2C_Port_Config_t config, bool bit) {
    if(bit) {
        SOFTWAREI2C_PORT_SET_SDA(config);
    }
    else {
        SOFTWAREI2C_PORT_CLEAR_SDA(config);
    }
    I2SOFTWAREI2C_PORT_DELAY(config);
    SOFTWAREI2C_PORT_SET_SCL(config);
    do {
        I2SOFTWAREI2C_PORT_DELAY(config);
    }
    Until clock is actually high (clock stretching)
    while(!SOFTWAREI2C_PORT_GET_SCL(config));
    SOFTWAREI2C_PORT_CLEAR_SCL(config);
}

inline bool SoftI2C_RecvBit(SoftI2C_Port_Config_t config) {
    SOFTWAREI2C_PORT_SET_SDA(config);
    I2SOFTWAREI2C_PORT_DELAY(config);
    SOFTWAREI2C_PORT_SET_SCL(config);
    do {
        I2SOFTWAREI2C_PORT_DELAY(config);
    }
    while(!SOFTWAREI2C_PORT_GET_SCL(config));
    Clock low
    SOFTWAREI2C_PORT_CLEAR_SCL(config);
}

void SoftI2C_Init(SoftI2C_Port_Config_t config) {
    SOFT_I2SOFTWAREI2C_PORT_INIT_SDA(config);
    SOFT_I2SOFTWAREI2C_PORT_INIT_SCL(config);
}

bool SoftI2C_Start(SoftI2C_Port_Config_t config, uint8_t address, bool reading) {
    if(!SOFTWAREI2C_PORT_GET_SCL(config) || !SOFTWAREI2C_PORT_GET_SCL(config)) {
        SOFTWAREI2C_PORT_ERROR(config, "SDA or SCL already low!");
    }

    SOFTWAREI2C_PORT_CLEAR_SDA(config);
    SOFTWAREI2C_PORT_DELAY(config);
    SOFTWAREI2C_PORT_CLEAR_SCL(config);
    SOFTWAREI2C_PORT_DELAY(config);

    for(int i = 0; i < 7; i++)
    {
        SoftI2C_SendBit(config, (address & 0x1) == 1);
        address = address >> 1;
    }
    SoftI2C_SendBit(config, reading);

    bool nack = SoftI2C_RecvBit(config);
    return !nack;
}

bool SoftI2C_Restart(SoftI2C_Port_Config_t config, uint8_t address, bool reading) {
    SOFTWAREI2C_PORT_SET_SDA(config);
    SOFTWAREI2C_PORT_DELAY(config);
    SOFTWAREI2C_PORT_SET_SCL(config);
    SOFTWAREI2C_PORT_DELAY(config);

    return SoftI2C_Start(config, address, reading);
}


bool SoftI2C_SendByte(SoftI2C_Port_Config_t config, uint8_t data) {
    for(int i = 0; i < 8; i++)
    {
        SoftI2C_SendBit(config, (data & 0x1) == 1);
        address = data >> 1;
    }

    bool nack = SoftI2C_RecvBit(config);
    return !nack;
}


uint8_t SoftI2C_RecvByte(SoftI2C_Port_Config_t config, bool cont) {
    uint8_t data = 0;
    for(int i = 0; i < 8; i++)
    {
        if(SoftI2C_RecvBit(config)) {
            data |= 1;
        }
        data = data << 1;
    }
    SoftI2C_SendBit(config, cont);

    return data;
}


void SoftI2C_Stop(SoftI2C_Port_Config_t config) {
    SOFTWAREI2C_PORT_CLEAR_SDA(config);
    SOFTWAREI2C_PORT_DELAY(config);
    SOFTWAREI2C_PORT_SET_SCL(config);
    SOFTWAREI2C_PORT_DELAY(config);
    SOFTWAREI2C_PORT_SET_SDA(config);
    SOFTWAREI2C_PORT_DELAY(config);
}
