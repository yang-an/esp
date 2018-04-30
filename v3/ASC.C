//****************************************************************************
// @Module        Asynchronous / Synchronous Serial Interface (ASC)
// @Filename      ASC.C
// @Project       v2.dav
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
// @Date          30.04.2018 10:46:31
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
static char linebuf[LINELENGTH];
bit lineComplete = 1;
int i;
int gTid[NBR_TSK];
int pidx = 0, cidx = 0;
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
// @Date          30.04.2018 10:46:31
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

  ///  enable transmit interrupt
  ///  transmit interrupt priority level(ILVL) = 9
  ///  transmit interrupt group level (GLVL) = 2
  S0TIC = 0x0066;

  P3    |= 0x0400;    //  set P3.10 output latch (TXD0)
  DP3   |= 0x0400;    /// set P3.10 direction control (TXD0 output)


  // USER CODE BEGIN (ASC_Init,1)
	for (i = 0; i < LINELENGTH; i++)
		linebuf[i] = ' ';
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
// @Date          30.04.2018 10:46:31
//
//****************************************************************************

void ASC_vSendData(uword Data)
{
  S0TBIR = 0;           // reset transmit buffer interrupt request flag
  S0TBUF = Data;        // load transmit buffer register
}


//****************************************************************************
// @Function      void ASC_viIsrTx(void) interrupt S0TINT
//
//----------------------------------------------------------------------------
// @Description   This is the transmit interrupt service routine for the ASC0.
//                It is called when the sending of data is terminated
//                (S0TIR is set).
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

void ASC_viIsrTx(void) interrupt S0TINT
{
  // USER CODE BEGIN (ASC_IsrTx,1)
	static int idx = 1;
	
	if (idx < LINELENGTH) {
		ASC_vSendData(linebuf[idx]);
		linebuf[idx] = ' ';
		idx++;
	}
	else {
		
		if (pidx != cidx) {
			isr_send_signal(gTid[cidx]);
			cidx = ++cidx % NBR_TSK;
		}
		
		lineComplete = 1;
		idx = 1;
	}

  // USER CODE END
}




// USER CODE BEGIN (ASC_General,3)

// Text in pBuf auf Zeile mit Nummer iZnr ausgeben
void DoPrintZ(unsigned char iZnr, char *pBuf) {
	int idx = 4;
	
	// return on invalid line number
	if (iZnr == 0 || iZnr > 4)
		return;
	
	// return if queue is full
	if (synchronize())
		return;
	
	lineComplete = 0;
	
	linebuf[0] = '\x1B';
	linebuf[1] = 'O';
	linebuf[2] = 1;
	linebuf[3] = iZnr;
	
	while (*pBuf && idx < LINELENGTH)
		linebuf[idx++] = *pBuf++;
	
	ASC_vSendData(linebuf[0]);
}
// Displayinhalt loeschen
void ClrScr() {
	DoPrintZ(1, "\xC");
}

int synchronize(void){  
  IEN = 0;
  
	if(!lineComplete) { // line is busy
		if ((pidx+1)%NBR_TSK == cidx) { // queue is full
      IEN = 1;
			return -1; 
		} 
		
		gTid[pidx] = os_running_task_id(); // get task id
		pidx = ++pidx % NBR_TSK; // set index for next task
		IEN = 1;
		os_wait(K_SIG,0,0); // self knock-out
    
		// AFTER WAKEUP
		return 0; 
	} 
	
	IEN = 1;
  return 0; 
} 

// USER CODE END

