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

#ifndef SOFTI2C_PORT_H_
#define SOFTI2C_PORT_H_

#include "stdint.h"



typedef struct {
    uint8_t *port;
	uint8_t sda_pin;
	uint8_t scl_pin;
} SoftI2C_Port_Config_t;

#define SOFTWAREI2C_PORT_AVR_DDR(port) (port-1)
#define SOFTWAREI2C_PORT_AVR_PIN(port) (port-2)

#define SOFTWAREI2C_PORT_SDA_INIT(config) { \
	*(SOFTWAREI2C_PORT_AVR_DDR(config->port)) &= ~(1 << config->sda_pin); \
	*(config->port) |= (1 << config->sda_pin);\
}

#define SOFTWAREI2C_PORT_SCL_INIT(config) { \
	*(SOFTWAREI2C_PORT_AVR_DDR(config->port)) &= ~(1 << config->scl_pin); \
	*(config->port) |= (1 << config->scl_pin);\
}

#define SOFTWAREI2C_PORT_SDA_HIGH(config) { \
	*(SOFTWAREI2C_PORT_AVR_DDR(config->port)) &= ~(1 << config->sda_pin); \
	*(config->port) |= (1 << config->sda_pin);\
}

#define SOFTWAREI2C_PORT_SCL_HIGH(config) { \
	*(SOFTWAREI2C_PORT_AVR_DDR(config->port)) &= ~(1 << config->scl_pin); \
	*(config->port) |= (1 << config->scl_pin);\
}

#define SOFTWAREI2C_PORT_SDA_LOW(config) { \
	*(config->port) &= ~(1 << config->sda_pin);\
	*(SOFTWAREI2C_PORT_AVR_DDR(config->port)) |= (1 << config->sda_pin); \
}

#define SOFTWAREI2C_PORT_SCL_LOW(config) { \
	*(config->port) &= ~(1 << config->scl_pin);\
	*(SOFTWAREI2C_PORT_AVR_DDR(config->port)) |= (1 << config->scl_pin); \
}

#define SOFTWAREI2C_PORT_SDA_GET(config) ((*(SOFTWAREI2C_PORT_AVR_PIN(config->port)) >> config->sda_pin) & 0x01)
#define SOFTWAREI2C_PORT_SCL_GET(config) ((*(SOFTWAREI2C_PORT_AVR_PIN(config->port)) >> config->scl_pin) & 0x01)

#define SOFTWAREI2C_PORT_DELAY(config) {/*Ain't nobody got time for that...*/}

#define SOFTWAREI2C_PORT_ERROR(config, msg) {/*Houston, we have a problem*/}

#endif // SOFTI2C_PORT_H_
