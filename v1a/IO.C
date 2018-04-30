//****************************************************************************
// @Module        Ports
// @Filename      IO.C
// @Project       v1.dav
//----------------------------------------------------------------------------
// @Controller    Infineon C164CI-8E
//
// @Compiler      KEIL C166
//
// @Codegenerator DAvE 2-0-0
//
// @Description   This file contains all functions that use the general IO ports.
//                
//
//----------------------------------------------------------------------------
// @Date          16.04.2018 09:39:21
//
//****************************************************************************







//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (IO_General,1)

// USER CODE END


//***************************************************************************
// @Global Variables
//***************************************************************************

// USER CODE BEGIN (IO_General,2)
volatile unsigned key_cnt = 0;
unsigned tsk2_cnt = 0;

unsigned char saved_key_port;

static volatile bit key_flag = 0;
// USER CODE END


//****************************************************************************
// @Function      void IO_vInit(void)
//
//----------------------------------------------------------------------------
// @Description   This function initializes the IO component. It effects all
//                necessary configurations of the SFR, depending on the selected
//                operating mode.
//                Note:
//                Only those pins that are initialized are used as general IO.
//                If the alternate function of a pin is used, this pin is
//                initialized in the initialization function of the peripheral.
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

void IO_vInit(void)
{
  /// P8.0 .. P8.7  switch on standard TTL input levels
  /// P3.8 .. P3.15 switch on standard TTL input levels
  /// P3.0 .. P3.7  switch on standard TTL input levels
  PICON = 0x0000;

  /// no pin of port 0 low is used as general IO

  /// no pin of port 0 high is used as general IO

  //  initializes port 1 low
  /// P1L.4 is used as general IO
  /// -  the pin is configured as output
  /// -  the pin status is low level
  /// P1L.5 is used as general IO
  /// -  the pin is configured as output
  /// -  the pin status is low level
  /// P1L.6 is used as general IO
  /// -  the pin is configured as output
  /// -  the pin status is low level
  /// P1L.7 is used as general IO
  /// -  the pin is configured as output
  /// -  the pin status is low level
  P1L   = 0x00;          // set port data register
  DP1L  = 0xF0;          // set port direction register

  //  initializes port 1 high
  /// P1H.4 is used as general IO
  /// -  the pin is configured as input
  /// P1H.5 is used as general IO
  /// -  the pin is configured as input
  /// P1H.6 is used as general IO
  /// -  the pin is configured as input
  /// P1H.7 is used as general IO
  /// -  the pin is configured as input
  P1H   = 0x00;          // set port data register
  DP1H  = 0x00;          // set port direction register

  /// no pin of port 3 is used as general IO

  /// no pin of port 4 is used as general IO

  /// no pin of port 5 is used as general input

  /// no pin of port 8 is used as general IO


  // USER CODE BEGIN (IO_Init,1)

  // USER CODE END

}


// USER CODE BEGIN (IO_General,3)
void tasten_tsk (void) _task_ 2 {
	while (1) {
		tsk2_cnt++;
		saved_key_port = KEY_PORT;
		if ((saved_key_port)) {
			key_cnt++;
			
			if (key_cnt == DEBOUNCE_THRESHOLD)
				os_send_signal(1);
		}
		else
			key_cnt = 0;
		
		os_wait(K_IVL, 20, 0);
	}
}

char GetKey() {
	switch (saved_key_port) {
		case 1:
			return '1';
		case 2:
			return '2';
		case 4:
			return '3';
		case 8:
			return '4';
		default:
			return -1;
	}
}


void ToggleLED(unsigned char ch) {
	switch (ch) {
		case '1':			
			if (IO_bReadPin(P1L_4))
				IO_vResetPin(P1L_4);
			else
				IO_vSetPin(P1L_4);
			break;
			
		case '2':			
			if (IO_bReadPin(P1L_5))
				IO_vResetPin(P1L_5);
			else
				IO_vSetPin(P1L_5);
			break;
			
		case '3':			
			if (IO_bReadPin(P1L_6))
				IO_vResetPin(P1L_6);
			else
				IO_vSetPin(P1L_6);
			break;
			
		case '4':			
			if (IO_bReadPin(P1L_7))
				IO_vResetPin(P1L_7);
			else
				IO_vSetPin(P1L_7);
			break;
		}
}
// USER CODE END

