#if defined(MIK32)

#pragma once

#include <stdint.h>

#include "mik32_hal_i2c.h"

/* PCC_GPIO_1_CLK must be enabled */
void SCCB_Init();

/* Write byte to OV7670 and return true on success. */
bool SCCB_WriteReg(uint8_t reg_addr, uint8_t reg_data);

/* Read byte from OV7670 and return true on success and write to reg_data. */
bool SCCB_ReadReg(uint8_t reg_addr, uint8_t* reg_data);

#endif