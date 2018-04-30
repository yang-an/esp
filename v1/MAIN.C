//****************************************************************************
// @Module        Main
// @Filename      MAIN.C
// @Project       v1.dav
//----------------------------------------------------------------------------
// @Controller    Infineon C164CI-8E
//
// @Compiler      KEIL C166
//
// @Codegenerator DAvE 2-0-0
//
// @Description   This file contains the Project initialization function.
//
//----------------------------------------------------------------------------
// @Date          16.04.2018 09:39:21
//
//****************************************************************************

/*
******************************************************************************
@Note




******************************************************************************
*/

//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (Main,0)

// USER CODE END


//***************************************************************************
// @Global Variables
//***************************************************************************

// USER CODE BEGIN (Main,3)
unsigned tsk1_cnt = 0;
char ch;
// USER CODE END


//****************************************************************************
// @Function      void Project_Init(void)
//
//----------------------------------------------------------------------------
// @Description   This function initializes the microcontroller.
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

void Project_Init(void)
{

  // USER CODE BEGIN (Project_Init,0)

  // USER CODE END

  /// the following initialization is made by the compiler EDE when you
  /// import the DAvE project

  /// --- initialization of the SYSCON Register ---
  ///- 256 words system stack
  ///- the internal ROM area is mapped to segment 1
  ///- the segmentation is enabled (CSP is saved/restored during interrupt entry/exit)
  ///- the internal ROM is disabled: accesses to the ROM area use the external bus
  ///- the pin #BHE (byte high enable) is enabled
  ///- the system clock output is disabled
  ///- the pin #WR acts as #WRL and pin #BHE acts as #WRH
  ///- the on-chip X-Peripherals are enabled and can be accessed
  ///- pin #RSTIN is an input only
  ///- the on-chip oscillator watchdog is disabled
  ///- latched CS mode; CS signals are latch internally


  /// --- initialization of the BUSCON 0-4 and ADRRSEL Registers 1-4 ---

  /// ---------- external bus 0 is enabled ----------
  ///- 16-bit multiplexed bus
  ///- memory cycle time control: 15 waitstates
  ///- read/write delay control: activate signal 1 TCL after falling edge of ALE  
  ///- chip select mode: address chip select 
  ///- memory tristate control: 1 waitstate
  ///- ALE lengthening control: lengthened ALE signal


  // initializes the IO ports
  IO_vInit();

  // initializes the Asynchronous/Synchronous Serial Interface (ASC)
  ASC_vInit();

  // USER CODE BEGIN (Project_Init,1)

  // USER CODE END

  /// globally enable interrupts
  IEN = 1;
}


//****************************************************************************
// @Function      void main(void)
//
//----------------------------------------------------------------------------
// @Description   This is the main function.
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


  // USER CODE BEGIN (Main,1)
void start_tsk(void) _task_ 0
{
  // USER CODE END

  Project_Init();

  // USER CODE BEGIN (Main,2)
  //printf("Hello World");
	
	os_create_task(1);
  os_create_task(2);
  os_delete_task(0);
}

void commando_tsk() _task_ 1 {
 	while (1) {
		tsk1_cnt++;
		
		if (KeyDown()) {
			ch = GetKey();
			ToggleLED(ch);
			switch (GetKey()) {
				case '1':
					ASC_vSendData('1');
					ASC_vSendData('\n');
					break;
				case '2':
					ASC_vSendData('2');
					ASC_vSendData('\n');
					break;
				case '3':
					ASC_vSendData('3');
					ASC_vSendData('\n');
					break;
				case '4':
					ASC_vSendData('4');
					ASC_vSendData('\n');
					break;
				default:
					//printf("Unbekannte Taste\r\n");
					;
			}
		}
		os_wait(K_IVL, 100, 0);
	}
}
  // USER CODE END

