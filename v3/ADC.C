//****************************************************************************
// @Module        ADC
// @Filename      ADC.C
// @Project       v2.dav
//----------------------------------------------------------------------------
// @Controller    Infineon C164CI-8E
//
// @Compiler      KEIL C166
//
// @Codegenerator DAvE 2-0-0
//
// @Description   This file contains all functions that use the ADC peripheral
//                
//
//----------------------------------------------------------------------------
// @Date          30.04.2018 10:46:31
//
//****************************************************************************


//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (ADC_General,1)

// USER CODE END


//***************************************************************************
// @Global Variables
//***************************************************************************

// USER CODE BEGIN (ADC_General,2)

/* 0, 3, 6, ... : Ch0
	 1, 4, 7, ... : Ch1
	 2, 5, 8, ... : Ch2
*/
unsigned avgbuf[BUFSIZE];
// USER CODE END


//****************************************************************************
// @Function      void ADC_vInit(void)
//
//----------------------------------------------------------------------------
// @Description   This function initializes the ADC component. It effects all
//                necessary configurations of the SFR, depending on the selected
//                operating mode. The configuration determines whether the ADC
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
// @Date          30.04.2018 10:46:31
//
//****************************************************************************

void ADC_vInit(void)
{
  /// digital input stage is disconnected from port line P5.0
  /// digital input stage is disconnected from port line P5.1
  /// digital input stage is disconnected from port line P5.2
  /// digital input stage is disconnected from port line P5.3
  /// digital input stage is disconnected from port line P5.4
  /// digital input stage is disconnected from port line P5.5
  /// digital input stage is disconnected from port line P5.6
  /// digital input stage is disconnected from port line P5.7

  P5DIDIS = 0x00FF;

  ///  enable ADC interrupt
  ///  ADC interrupt priority level(ILVL) = 2
  ///  ADC interrupt group level (GLVL) = 1
  ADCIC = 0x0049;

  /// fixed channel single conversion
  /// converts channel 0
  /// ADC start bit is reset
  /// converter clock = fcpu / 24 (1,200 µs)
  /// sample time = 9,600 µs 
  ADCON   = 0x0000;

  //  USER CODE BEGIN (ADC_Init,1)

  //  USER CODE END

}


//****************************************************************************
// @Function      uword ADC_uwReadConv(void)
//
//----------------------------------------------------------------------------
// @Description   This function returns the result of a conversion.
//                This function must be called after each conversion.
//                The lower 10 bits contain the conversion result
//                while the upper 4 bits identify the converted
//                analog channel.
//
//----------------------------------------------------------------------------
// @Returnvalue   conversion result
//
//----------------------------------------------------------------------------
// @Parameters    none
//
//----------------------------------------------------------------------------
// @Date          30.04.2018 10:46:31
//
//****************************************************************************

uword ADC_uwReadConv(void)
{
  return(ADDAT);
}


//****************************************************************************
// @Function      void ADC_viIsrConv(void) interrupt ADCINT
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the ADC.
//                It is called at the end of each conversion. The user
//                obtains the conversion result by calling the function
//                ADC_uwReadConv.
//                
//                Please note that you have to add application specific
//                code to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   none
//
//----------------------------------------------------------------------------
// @Parameters    none
//
//----------------------------------------------------------------------------
// @Date          30.04.2018 10:46:31
//
//****************************************************************************

void ADC_viIsrConv(void) interrupt ADCINT
{
  // USER CODE BEGIN (ADC_IsrConv,1)
	isr_send_signal(4);
  // USER CODE END
}




// USER CODE BEGIN (ADC_General,3)
void adc_tsk() _task_ 4 {
	unsigned char avgbuf_idx = 0;
	
	for (;;) {
		
		ADC_vConfConv(FIXED, avgbuf_idx % 3);
		ADC_vStartConv();
		
		os_wait(K_SIG, 0, 0);
		
		avgbuf[avgbuf_idx] = ADC_uwReadConv() & 0x03FF;
		avgbuf_idx = ++avgbuf_idx % BUFSIZE;
		
		os_wait(K_IVL, 10, 0);
	}
}

float fGibADmittel(unsigned char ch) {
	int i;
	float ret = 0;
	
	if (ch > CHCNT - 1)
		return -1;
	
	for (i = ch; i < BUFSIZE; i+=CHCNT)
		ret += avgbuf[i];
	
	return ret / (BUFSIZE / CHCNT);
}

float fGibGewicht() {
	float ret = 0;
	int i;
	
	for (i=0; i<CHCNT; i++)
		ret += fGibADmittel(i);
	
	return ret;
}
// USER CODE END

