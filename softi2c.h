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

#ifndef SOFTI2C_H_
#define SOFTI2C_H_

#ifdef __AVR__
#include "softi2c_port_avr.h"
#else
#error no port for given architecture
#endif

#include "stdbool.h"
#include "stdint.h"

/**
* Initialize a software I2C bus using the given configuration
*/
void SoftI2C_Init(SoftI2C_Port_Config_t *config);

/**
* Start a data transfer using a given software I2C configuration
*/
bool SoftI2C_Start(SoftI2C_Port_Config_t *config, uint8_t address, bool reading);

/**
* Restart a data transfer using a given software I2C configuration
*/
bool SoftI2C_Restart(SoftI2C_Port_Config_t *config, uint8_t address, bool reading);

/**
* Send a byte using a given software I2C configuration
*/
bool SoftI2C_SendByte(SoftI2C_Port_Config_t *config, uint8_t data);

/**
* Receive a byte using a given software I2C configuration
*/
uint8_t SoftI2C_RecvByte(SoftI2C_Port_Config_t *config, bool cont);

/**
* Stop a data transfer using a given software I2C configuration
*/
void SoftI2C_Stop(SoftI2C_Port_Config_t *config);


#endif // SOFTI2C_H_
