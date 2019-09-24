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

#include "MK22F51212.h"


typedef struct {
	PORT_Type *sda_port;
	int sda_pin;
	PORT_Type *scl_port;
	int scl_pin;
} SoftI2C_Port_Config_t;

/*
 * PORTBASE = 0x40049000u
 * PORTOFFSET = 0x1000
 *
 * GPIOBASE = 0x400FF000u
 * GPIOOFFSET = 0x40
 *
 * portpos = port - PORTBASE
 * portidx = portpos / PORTOFFSET
 * gpioidx = portidx
 * gpiopos = gpioidx * GPIOOFFSET
 * gpio = gpiopos + GPIOBASE
 *
 * => gpio = ((port - PORTBASE) / PORTOFFSET) * GPIOOFFSET + GPIOBASE
 */
#define SOFTWAREI2C_PORT_PORT_INDEX(port) (((uint32_t)port - PORTA_BASE) / (PORTB_BASE - PORTA_BASE))
#define SOFTWAREI2C_PORT_GPIO_REG(port) ((GPIO_Type *)((SOFTWAREI2C_PORT_PORT_INDEX(port) * (GPIOB_BASE - GPIOA_BASE) + GPIOA_BASE)))
#define SOFTWAREI2C_PORT_SCGC5_MASK(port) *((uint32_t *)(0x200U << SOFTWAREI2C_PORT_PORT_INDEX(port)))

#define SOFTWAREI2C_PORT_SDA_INIT(config) { \
	SIM->SCGC5 |= SOFTWAREI2C_PORT_SCGC5_MASK(config->sda_port); \
	config->sda_port->PCR[config->sda_pin] = PORT_PCR_MUX(1) | PORT_PCR_ODE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; \
	SOFTWAREI2C_PORT_GPIO_REG(config->sda_port)->PSOR = (1 << config->sda_pin); \
	SOFTWAREI2C_PORT_GPIO_REG(config->sda_port)->PDDR |= (1 << config->sda_pin); \
}

#define SOFTWAREI2C_PORT_SCL_INIT(config) { \
	SIM->SCGC5 |= SOFTWAREI2C_PORT_SCGC5_MASK(config->scl_port); \
	config->scl_port->PCR[config->scl_pin] = PORT_PCR_MUX(1) | PORT_PCR_ODE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; \
	SOFTWAREI2C_PORT_GPIO_REG(config->scl_port)->PSOR = (1 << config->scl_pin); \
	SOFTWAREI2C_PORT_GPIO_REG(config->scl_port)->PDDR |= (1 << config->scl_pin); \
}

#define SOFTWAREI2C_PORT_SDA_HIGH(config) {SOFTWAREI2C_PORT_GPIO_REG(config->sda_port)->PSOR = 1 << config->sda_pin;}
#define SOFTWAREI2C_PORT_SCL_HIGH(config) {SOFTWAREI2C_PORT_GPIO_REG(config->scl_port)->PSOR = 1 << config->scl_pin;}
#define SOFTWAREI2C_PORT_SDA_LOW(config) {SOFTWAREI2C_PORT_GPIO_REG(config->sda_port)->PCOR = 1 << config->sda_pin;}
#define SOFTWAREI2C_PORT_SCL_LOW(config) {SOFTWAREI2C_PORT_GPIO_REG(config->scl_port)->PCOR = 1 << config->scl_pin;}
#define SOFTWAREI2C_PORT_SDA_GET(config) ((SOFTWAREI2C_PORT_GPIO_REG(config->sda_port)->PDIR & (1 << config->sda_pin)) != 0)
#define SOFTWAREI2C_PORT_SCL_GET(config) ((SOFTWAREI2C_PORT_GPIO_REG(config->scl_port)->PDIR & (1 << config->scl_pin)) != 0)

#define SOFTWAREI2C_PORT_DELAY(config) \
{\
    volatile int SoftI2C_Port_DelayCount; \
    for(SoftI2C_Port_DelayCount = 0; \
        SoftI2C_Port_DelayCount < 100; \
        SoftI2C_Port_DelayCount++) \
    { \
        (void)SoftI2C_Port_DelayCount; \
    } \
} // TODO better implementation

#define SOFTWAREI2C_PORT_ERROR(config, msg) {} // TODO Implement

#endif // SOFTI2C_PORT_H_
