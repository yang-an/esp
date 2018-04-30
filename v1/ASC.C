//****************************************************************************
// @Module        Asynchronous / Synchronous Serial Interface (ASC)
// @Filename      ASC.C
// @Project       v1.dav
//----------------------------------------------------------------------------
// @Controller    Infineon C164CI-8E
//
// @Compiler      KEIL C166
//
// @Codegenerator DAvE 2-0-0
//
// @Description   This file contains all functions that use the
//                Asynchronous / Synchronous Serial Interface.
//
//----------------------------------------------------------------------------
// @Date          16.04.2018 09:39:21
//
//****************************************************************************


//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (ASC_General,1)

// USER CODE END


//***************************************************************************
// @Global Variables
//***************************************************************************

// USER CODE BEGIN (ASC_General,2)

// USER CODE END


//****************************************************************************
// @Function      void ASC_vInit(void)
//
//----------------------------------------------------------------------------
// @Description   This function initializes the ASC component. It effects all
//                necessary configurations of the SFR, depending on the selected
//                operating mode. The configuration determines whether the ASC
//                interrupts are to be released, and the priority of the 
//                released interrupt.
//
//----------------------------------------------------------------------------
// @Returnvalue   none
//
//----------------------------------------------------------------------------
// @Parameters    none
//
//----------------------------------------------------------------------------
// @Date          16.04.2018 09:39:21
//
//****************************************************************************

void ASC_vInit(void)
{
  ///  8-bit data asynchronous operation
  ///  one stop bit
  ///  divide clock by reload value + constant
  ///  receiver disabled
  S0CON  = 0x0001;

  //   ASC baudrate reload register
  ///  baudrate =  9615,38 Baud
  S0BG   = 0x0040;

  P3    |= 0x0400;    //  set P3.10 output latch (TXD0)
  DP3   |= 0x0400;    /// set P3.10 direction control (TXD0 output)


  // USER CODE BEGIN (ASC_Init,1)

  // USER CODE END

  S0R    = 1;         //  enable baudrate generator
}


//****************************************************************************
// @Function      void ASC_vSendData(uword Data)
//
//----------------------------------------------------------------------------
// @Description   This function writes a send data initialization word into
//                the S0TBUF register.
//                
//                Note:
//                In a multiprocessor system the master with this function
//                has the possibility to send data to the selected slave. To
//                achieve this, the 9th bit must set on zero.
//
//----------------------------------------------------------------------------
// @Returnvalue   none
//
//----------------------------------------------------------------------------
// @Parameters    data to be written into the S0TBUF register
//
//----------------------------------------------------------------------------
// @Date          16.04.2018 09:39:21
//
//****************************************************************************

void ASC_vSendData(uword Data)
{
  S0TBIR = 0;           // reset transmit buffer interrupt request flag
  S0TBUF = Data;        // load transmit buffer register
}




// USER CODE BEGIN (ASC_General,3)

// USER CODE END

