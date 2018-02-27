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

typedef struct {
    // TODO Implement
} SoftI2C_Port_Config_t;

#define SOFTWAREI2C_PORT_INIT_SDA(config) {(void)config;} // TODO Implement
#define SOFTWAREI2C_PORT_INIT_SCL(config) {(void)config;} // TODO Implement
#define SOFTWAREI2C_PORT_SET_SDA(config) {(void)config;} // TODO Implement
#define SOFTWAREI2C_PORT_SET_SCL(config) {(void)config;} // TODO Implement
#define SOFTWAREI2C_PORT_CLEAR_SDA(config) {(void)config;} // TODO Implement
#define SOFTWAREI2C_PORT_CLEAR_SCL(config) {(void)config;} // TODO Implement
#define SOFTWAREI2C_PORT_GET_SDA(config) (0) // TODO Implement
#define SOFTWAREI2C_PORT_GET_SCL(config) (0) // TODO Implement

#define SOFTWAREI2C_PORT_DELAY(config) \
{\
    volatile int SoftI2C_Port_DelayCount; \
    for(SoftI2C_Port_DelayCount = 0; \
        SoftI2C_Port_DelayCount < 10; \
        SoftI2C_Port_DelayCount++) \
    { \
        (void)SoftI2C_Port_DelayCount; \
    } \
} // TODO better implementation

#define SOFTWAREI2C_PORT_ERROR(config, msg) {} // TODO Implement

#endif // SOFTI2C_PORT_H_
