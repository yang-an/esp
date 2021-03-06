//****************************************************************************
// @Module        Ports
// @Filename      IO.H
// @Project       v2.dav
//----------------------------------------------------------------------------
// @Controller    Infineon C164CI-8E
//
// @Compiler      KEIL C166
//
// @Codegenerator DAvE 2-0-0
//
// @Description   This file contains all function prototypes and macros for
//                the Parallel Ports.
//
//----------------------------------------------------------------------------
// @Date          30.04.2018 08:35:48
//
//****************************************************************************

//****************************************************************************
// @Prototypes of global functions
//****************************************************************************

void IO_vInit(void);


// USER CODE BEGIN (IOHeader,1)

bit KeyDown();
char GetKey();
void ToggleLED(unsigned char);

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

//****************************************************************************
// @Macro         IO_bReadPin(PinNr)
//
//----------------------------------------------------------------------------
// @Description   This macro returns the status of the chosen port pin.
//                Warning:
//                All instructions that manipulate single bits or bit
//                groups internally, use a read-modify-write sequence
//                that accesses the whole word, which contains the
//                specified bit(s).
//                The read modify-write approach may be critical with
//                hardware-effected bits. In this cases the hardware
//                may change specific bits while the read-modify-write
//                operation is in progress, where the writeback would
//                overwrite the new bit value generated by the hardware.
//                The solution is either the implemented hardware 
//                protection or realized through special programming
//                (see "Particular Pipeline Effects" and "Protected
//                Bits" in the User's Manual). 
//                
//                Note:
//                See the "Declaration of bit addressable SFRs" 
//                section in the header file for the available 
//                definitions for the parameter PinNr.
//
//----------------------------------------------------------------------------
// @Returnvalue   status of the chosen port pin
//
//----------------------------------------------------------------------------
// @Parameters    pin to be read
//
//----------------------------------------------------------------------------
// @Date          30.04.2018 08:35:48
//
//****************************************************************************

#define IO_bReadPin(PinNr) PinNr


//****************************************************************************
// @Macro         IO_vSetPin(PinNr)
//
//----------------------------------------------------------------------------
// @Description   The chosen port pin is set to '1'.
//                Warning:
//                All instructions that manipulate single bits or bit
//                groups internally, use a read-modify-write sequence
//                that accesses the whole word, which contains the
//                specified bit(s).
//                The read modify-write approach may be critical with
//                hardware-effected bits. In this cases the hardware
//                may change specific bits while the read-modify-write
//                operation is in progress, where the writeback would
//                overwrite the new bit value generated by the hardware.
//                The solution is either the implemented hardware 
//                protection or realized through special programming
//                (see "Particular Pipeline Effects" and "Protected
//                Bits" in the User's Manual). 
//                
//                Note:
//                See the "Declaration of bit addressable SFRs" 
//                section in the header file for the available 
//                definitions for the parameter PinNr.
//
//----------------------------------------------------------------------------
// @Returnvalue   none
//
//----------------------------------------------------------------------------
// @Parameters    pin to be set to '1'
//
//----------------------------------------------------------------------------
// @Date          30.04.2018 08:35:48
//
//****************************************************************************

#define IO_vSetPin(PinNr) PinNr = 1


//****************************************************************************
// @Macro         IO_vResetPin(PinNr)
//
//----------------------------------------------------------------------------
// @Description   The chosen port pin is set to '0'.
//                Warning:
//                All instructions that manipulate single bits or bit
//                groups internally, use a read-modify-write sequence
//                that accesses the whole word, which contains the
//                specified bit(s).
//                The read modify-write approach may be critical with
//                hardware-effected bits. In this cases the hardware
//                may change specific bits while the read-modify-write
//                operation is in progress, where the writeback would
//                overwrite the new bit value generated by the hardware.
//                The solution is either the implemented hardware 
//                protection or realized through special programming
//                (see "Particular Pipeline Effects" and "Protected
//                Bits" in the User's Manual). 
//                
//                Note:
//                See the "Declaration of bit addressable SFRs" 
//                section in the header file for the available 
//                definitions for the parameter PinNr.
//
//----------------------------------------------------------------------------
// @Returnvalue   none
//
//----------------------------------------------------------------------------
// @Parameters    pin to be set to '0'
//
//----------------------------------------------------------------------------
// @Date          30.04.2018 08:35:48
//
//****************************************************************************

#define IO_vResetPin(PinNr) PinNr = 0


//****************************************************************************
// @Macro         IO_uwReadPort(PortNr)
//
//----------------------------------------------------------------------------
// @Description   This macro returns the value of the selected port. If a 
//                port has less than 16 pins, the unused bits are
//                set to 0 in the return value
//                
//                The following definitions for PortNr are available:
//                P0L,P0H,P1L,P1H,P3,P4,P5,P8
//
//----------------------------------------------------------------------------
// @Returnvalue   value of the port
//
//----------------------------------------------------------------------------
// @Parameters    port to be read
//
//----------------------------------------------------------------------------
// @Date          30.04.2018 08:35:48
//
//****************************************************************************

#define IO_uwReadPort(Port) Port



// USER CODE BEGIN (IOHeader,2)

// Keys on P1H[7..4]
//#define KEY_PORT ((IO_uwReadPort(P1H) >> 4) ^ 0x0F)
# define KEY_PORT (IO_uwReadPort(P1H) >> 4 ^ 0x0F)

// USER CODE END


//****************************************************************************
// Declaration of bit addressable SFRs (for parameter PinNr)
//****************************************************************************

sbit  P0L_0 = P0L^0;
sbit  P0L_1 = P0L^1;
sbit  P0L_2 = P0L^2;
sbit  P0L_3 = P0L^3;
sbit  P0L_4 = P0L^4;
sbit  P0L_5 = P0L^5;
sbit  P0L_6 = P0L^6;
sbit  P0L_7 = P0L^7;
sbit  P0H_0 = P0H^0;
sbit  P0H_1 = P0H^1;
sbit  P0H_2 = P0H^2;
sbit  P0H_3 = P0H^3;
sbit  P0H_4 = P0H^4;
sbit  P0H_5 = P0H^5;
sbit  P0H_6 = P0H^6;
sbit  P0H_7 = P0H^7;
sbit  P1L_0 = P1L^0;
sbit  P1L_1 = P1L^1;
sbit  P1L_2 = P1L^2;
sbit  P1L_3 = P1L^3;
sbit  P1L_4 = P1L^4;
sbit  P1L_5 = P1L^5;
sbit  P1L_6 = P1L^6;
sbit  P1L_7 = P1L^7;
sbit  P1H_0 = P1H^0;
sbit  P1H_1 = P1H^1;
sbit  P1H_2 = P1H^2;
sbit  P1H_3 = P1H^3;
sbit  P1H_4 = P1H^4;
sbit  P1H_5 = P1H^5;
sbit  P1H_6 = P1H^6;
sbit  P1H_7 = P1H^7;
sbit  P3_4 = P3^4;
sbit  P3_6 = P3^6;
sbit  P3_8 = P3^8;
sbit  P3_9 = P3^9;
sbit  P3_10 = P3^10;
sbit  P3_11 = P3^11;
sbit  P3_12 = P3^12;
sbit  P3_13 = P3^13;
sbit  P3_15 = P3^15;
sbit  P4_0 = P4^0;
sbit  P4_1 = P4^1;
sbit  P4_2 = P4^2;
sbit  P4_3 = P4^3;
sbit  P4_5 = P4^5;
sbit  P4_6 = P4^6;
sbit  P5_0 = P5^0;
sbit  P5_1 = P5^1;
sbit  P5_2 = P5^2;
sbit  P5_3 = P5^3;
sbit  P5_4 = P5^4;
sbit  P5_5 = P5^5;
sbit  P5_6 = P5^6;
sbit  P5_7 = P5^7;
sbit  P8_0 = P8^0;
sbit  P8_1 = P8^1;
sbit  P8_2 = P8^2;
sbit  P8_3 = P8^3;


// USER CODE BEGIN (IOHeader,3)
#define DEBOUNCE_THRESHOLD 3
// USER CODE END

