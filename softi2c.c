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

void SoftI2C_SendBit(SoftI2C_Port_Config_t *config, bool bit) {
    if(bit) {
        // SDA high if bit is true
        SOFTWAREI2C_PORT_SDA_HIGH(config);
    }
    else {
        // SDA low if bit is false
        SOFTWAREI2C_PORT_SDA_LOW(config);
    }
    // Delay
    SOFTWAREI2C_PORT_DELAY(config);
    // Clock high
    SOFTWAREI2C_PORT_SCL_HIGH(config);
    do {
        // Delay
        SOFTWAREI2C_PORT_DELAY(config);
    }
    // TODO last delay may be needed (clock might have risen nanoseconds before check)

    // Until clock is actually high (clock stretching)
    while(!SOFTWAREI2C_PORT_SCL_GET(config));
    // Clock low
    SOFTWAREI2C_PORT_SCL_LOW(config);
}

bool SoftI2C_RecvBit(SoftI2C_Port_Config_t *config) {
    // SDA High
    SOFTWAREI2C_PORT_SDA_HIGH(config);
    // Delay
    SOFTWAREI2C_PORT_DELAY(config);
    // Clock high
    SOFTWAREI2C_PORT_SCL_HIGH(config);
    do {
        // Delay
        SOFTWAREI2C_PORT_DELAY(config);
    }
    // Until clock is actually high (clock stretching)
    while(!SOFTWAREI2C_PORT_SCL_GET(config));
    // TODO last delay may be needed (clock might have risen nanoseconds before check)

    bool bit = SOFTWAREI2C_PORT_SDA_GET(config);

    // Clock low
    SOFTWAREI2C_PORT_SCL_LOW(config);

    return bit;
}

void SoftI2C_Init(SoftI2C_Port_Config_t *config) {
    // Initialize SDA pin
    SOFTWAREI2C_PORT_SDA_INIT(config);
    // Initialize SCL pin
    SOFTWAREI2C_PORT_SCL_INIT(config);
}

bool SoftI2C_Start(SoftI2C_Port_Config_t *config, uint8_t address, bool reading) {
    // Check if already started or bus not ready
    if(!SOFTWAREI2C_PORT_SCL_GET(config) || !SOFTWAREI2C_PORT_SCL_GET(config)) {
        SOFTWAREI2C_PORT_ERROR(config, "SDA or SCL already low!");
    }

    // Start sequence
    SOFTWAREI2C_PORT_SDA_LOW(config);
    SOFTWAREI2C_PORT_DELAY(config);
    SOFTWAREI2C_PORT_SCL_LOW(config);
    SOFTWAREI2C_PORT_DELAY(config);

    // Send address bits
    for(int i = 0; i < 7; i++)
    {
        SoftI2C_SendBit(config, (address & 0x40) == 0x40);
        address = address << 1;
    }
    // Send read/!write bit
    SoftI2C_SendBit(config, reading);

    // Check for nack
    bool nack = SoftI2C_RecvBit(config);
    SOFTWAREI2C_PORT_DELAY(config);
    SOFTWAREI2C_PORT_DELAY(config);
    // Return true if nack has been received
    return !nack;
}

bool SoftI2C_Restart(SoftI2C_Port_Config_t *config, uint8_t address, bool reading) {
    // Reset bus to enable restart
    SOFTWAREI2C_PORT_SDA_HIGH(config);
    SOFTWAREI2C_PORT_DELAY(config);
    SOFTWAREI2C_PORT_SCL_HIGH(config);
    SOFTWAREI2C_PORT_DELAY(config);

    // Re-send start sequence, address and read/!write bit
    return SoftI2C_Start(config, address, reading);
}


bool SoftI2C_SendByte(SoftI2C_Port_Config_t *config, uint8_t data) {
    // Send bits from data byte
    for(int i = 0; i < 8; i++)
    {
        SoftI2C_SendBit(config, (data & 0x80) == 0x80);
        data = data << 1;
    }

        // Check for nack
    bool nack = SoftI2C_RecvBit(config);
    SOFTWAREI2C_PORT_DELAY(config);
    SOFTWAREI2C_PORT_DELAY(config);
    // Return true if nack has been received
    return !nack;
}


uint8_t SoftI2C_RecvByte(SoftI2C_Port_Config_t *config, bool cont) {
    uint8_t data = 0;
    // Receive bits from data byte
    for(int i = 0; i < 8; i++)
    {
        data = data << 1;
        if(SoftI2C_RecvBit(config)) {
            data |= 1;
        }
    }

    // Send ack bit if cont is true
    SoftI2C_SendBit(config, !cont);

    return data;
}


void SoftI2C_Stop(SoftI2C_Port_Config_t *config) {
    // Reset bus
    SOFTWAREI2C_PORT_SDA_LOW(config);
    SOFTWAREI2C_PORT_DELAY(config);

    // Stop sequence
    SOFTWAREI2C_PORT_SCL_HIGH(config);
    SOFTWAREI2C_PORT_DELAY(config);
    SOFTWAREI2C_PORT_SDA_HIGH(config);
    SOFTWAREI2C_PORT_DELAY(config);
}
