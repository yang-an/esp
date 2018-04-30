//****************************************************************************
// @Module        Asynchronous / Synchronous Serial Interface (ASC)
// @Filename      ASC.H
// @Project       v2.dav
//----------------------------------------------------------------------------
// @Controller    Infineon C164CI-8E
//
// @Compiler      KEIL C166
//
// @Codegenerator DAvE 2-0-0
//
// @Description   This file contains all function prototypes and macros for
//                the Asynchronous / Synchronous Serial Interface.
//
//----------------------------------------------------------------------------
// @Date          30.04.2018 08:35:48
//
//****************************************************************************

//****************************************************************************
// @Prototypes of global functions
//****************************************************************************

void ASC_vInit(void);
void ASC_vSendData(uword Data);


// USER CODE BEGIN (ASCHeader,1)
void DoPrintZ(unsigned char, char*);
void ClrScr();
int synchronize();

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************


// USER CODE BEGIN (ASCHeader,2)

// USER CODE END


//***************************************************************************
// @Defines
//***************************************************************************


// USER CODE BEGIN (ASCHeader,4)
#define LINELENGTH 24  // 4 Control Chars + 20 User Chars
#define NBR_TSK 10
// USER CODE END


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

#define S0TINT    0x2A


// USER CODE BEGIN (ASCHeader,3)

// USER CODE END


