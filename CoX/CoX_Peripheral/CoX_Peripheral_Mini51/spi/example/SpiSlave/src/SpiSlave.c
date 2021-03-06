//*****************************************************************************
//
//! \file SPI_loop.c
//! \brief Test SPI.
//! \version 1.0
//! \date 8/2/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xspi.h"
#include "xhw_spi.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xcore.h"

/*
unsigned long ulSourceData[] = {0x01020304, 0x11121314, 0x21212124, 0x31323334,
                                0x41424344, 0x51525354, 0x61626364, 0x71727374, 
                                0x81828384, 0x91929394, 0xA1A2A3A4, 0xB1B2B3B4, 
                                0xC1C2C3C4, 0xD1D2D3D4, 0xE1E2E3E4, 0xF1F2F3F4};
*/
unsigned char ulSourceData[] = {'1', '2', '3', '4','5', '6', '7', '8'};
unsigned char ulDestData[];
unsigned long i;

//*****************************************************************************
//
//! Ininite the SPI case which is needed
//!
//! \param None
//!
//! This function ininite the SPI including clock source and enable spi 
//!
//! \return none
//
//*****************************************************************************
void SpiReceiveTransferInit(void)
{
    //
    // Set SysClk 36MHz using Extern 12M oscillator
    //
    xSysCtlClockSet(12000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    //
    // Enable Peripheral SPI0
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);
    
    //
    // Configure Some GPIO pins as SPI Mode
    //
    xSPinTypeSPI(SPI0CLK, PA7);
    xSPinTypeSPI(SPI0MOSI, PA5);
    xSPinTypeSPI(SPI0MISO, PA6);
    xSPinTypeSPI(SPI0CS, PA4);

 //   xSPIConfigSet(SPI0_BASE, 10000, SPI_FORMAT_MODE_5 | SPI_DATA_WIDTH8 | 
 //                            SPI_MSB_FIRST | SPI_MODE_SLAVE);
    xHWREG(SPI0_BASE + SPI_CNTRL) |= SPI_FORMAT_MODE_5 | SPI_DATA_WIDTH8 | 
                             SPI_MSB_FIRST | SPI_MODE_SLAVE;
    SPISSConfig(SPI0_BASE, SPI_SS_LEVEL_TRIGGER, SPI_SS_ACTIVE_LOW_FALLING);

}
//*****************************************************************************
//
//! Spi Master Slave Mode Configure
//!
//! \param None
//!
//! This function configure the SPI as master and slave mode at the same time
//! transfer and receive data
//!
//! \return None
//
//*****************************************************************************
void SpiSlaveModeConfig(void)
{    
    for(i = 0; i < 8; i++)
    {
        ulDestData[i] = xSPISingleDataReadWrite(SPI0_BASE, ulSourceData[i]);
    }    
}
