/*
 * This file is part of the Bus Pirate project (http://code.google.com/p/the-bus-pirate/).
 *
 * Written and maintained by the Bus Pirate project.
 *
 * To the extent possible under law, the project has
 * waived all copyright and related or neighboring rights to Bus Pirate. This
 * work is published from United States.
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
#ifndef BASE 
#define BASE
#include <p24Fxxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef unsigned char u8;
//typedef unsigned int u16;
//typedef unsigned long u32;
//typedef unsigned char BYTE;

#define FALSE   0
#define TRUE    (!FALSE)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// [ BUS PIRATE SETTINGS ] ////////////////////////////////////////////////////
/////////// NOTE:
///////////     Configuration and Settings for building the Bus Pirate firmware. For more information and support
///////////  On building your own firmware. Please visit the forums on DangerousPrototypes.com. Enjoy the BP :)
///////////
///////////                                                 Bus Pirate - Brought to you by DangerousPrototypes.com

///////////////////////////////////////
// HARDWARE VERSION
#if defined(__PIC24FJ256GB106__)        //v4 chip
        #define BUSPIRATEV4
#elif defined(__PIC24FJ64GA002__)       //v3/v2go/v1a chip
        // Uncomment the hardware version you are building for
        #define BUSPIRATEV3                             // V3 is also V2G0
        //#define BUSPIRATEV1A                  //probably no longer supported...
#endif

////////////////////////////////////////
// FIRMWARE VERSION STRING
// Build Firmware Version String
// used in 'i' and startup
#define BP_FIRMWARE_STRING "Firmware v6.3-beta1 r2088 "


////////////////////////////////////////
// FREQUENCY
// Frequency in hertz, used for bpDelayMS and bpDelayUS
#define FCY 8000000

////////////////////////////////////////
// LANGUAGE
// Select language (US AND DE Currently Supported)
// If you know anyone bi-le
#define LANGUAGE_EN_US
//#define LANGUAGE_DE_DE
//#define LANGUAGE_IT_IT //Not yet supported
//#define LANGUAGE_ES_ES //Not yet supported


////////////////////////////////////////
// MODE SELECTION
// Default Mode Selection
// BP_MAIN is the default mode setting; varys by hardware version
// BP_ADDONS is for special builds with special modes
// BP_CUSTOM is for selecting your own modes below (find: BP_CUSTOM) and uncomment wanted modes
#define BP_MAIN
//#define BP_ADDONS
//#define BP_CUSTOM


////////////////////////////////////////
// OTHER CONFIGS
// BP_ENABLE_HISTORY = Enable the 'h' command for whatever reason it was disabled this enables it. can be disabled again.
// These settings should be left within the BUSPIRATEV4 define due to lack of space on v3. Unless you disable a mode or two
// for a custom v3 build, only include the following options on a v4 build.
#if defined(BUSPIRATEV4)
// Enables the 'h' command to show history
#define BP_ENABLE_HISTORY

#endif

///////////////////////
///////////////////////////// [ END OF CONFIGURATION ]//////////////////
////////////////////////////////////////////////////////////
/////////////////////////////////////


// Buspirate version 3 and v2go use the same everything; so this just
// fixs if the user selected v2go.
#if defined(BUSPIRATEV2GO)
        #define BUSPIRATEV3
#endif


#ifdef BUSPIRATEV4
        #include "hardwarev4a.h"
#include "dp_usb/usb_stack_globals.h"
        #include "onboardEEPROM.h"
#endif

#if defined(BUSPIRATEV1A)
        #include "hardwarev1a.h"
#elif defined(BUSPIRATEV3)
        #define BUSPIRATEV2 //v25 (2go) and v3 are about the same, enable the same featue set for both
        #include "hardwarev3.h"
#elif defined(BUSPIRATEV4)

#else
#error "No hardware defined in base.h."
#endif

#include "baseIO.h"
#include "baseUI.h"

//include/exclude modules here
// standard protocols
//#define BP_USE_RAW2WIRE
//#define BP_USE_RAW3WIRE

//Debugging mode for BPv4, comment out for normal compiling
//Adds alternative communicaton to UART1 over AUX1 and AUX2 instead of USB.
//#define BPV4_DEBUG  


#if defined(BP_MAIN)

        #define BP_USE_1WIRE
        //#ifndef BUSPIRATEV4
        #define BP_USE_HWUART //hardware uart (now also MIDI)
        //#endif
        #define BP_USE_I2C
        //#define BP_USE_I2C_HW
        #define BP_USE_HWSPI //hardware spi
        #define BP_USE_RAW2WIRE
        #define BP_USE_RAW3WIRE
        #define BP_USE_LCD // include HD44780 LCD library       
        #define BP_USE_BASIC
        
        #if defined(BUSPIRATEV4)
                #define BP_USE_DIO //binary mode
                #define BP_USE_PCATKB
                #define BP_USE_PIC
        #endif
        
#elif defined(BP_ADDONS)
        // most used protos
        //#define BP_USE_1WIRE
        //#define BP_USE_HWUART //hardware uart (now also MIDI)
        //#define BP_USE_I2C
        //#define BP_USE_I2C_HW
        //#define BP_USE_HWSPI //hardware spi
        #define BP_USE_RAW2WIRE
        #define BP_USE_RAW3WIRE
        #define BP_USE_PCATKB
        #define BP_USE_LCD // include HD44780 LCD library
        #define BP_USE_PIC
        #define BP_USE_DIO //binary mode
        
#elif defined(BP_CUSTOM)
        // most used protos
        //#define BP_USE_1WIRE
        #define BP_USE_HWUART //hardware uart (now also MIDI)
        //#define BP_USE_I2C
        //#define BP_USE_I2C_HW
        //#define BP_USE_HWSPI //hardware spi
        //#define BP_USE_RAW2WIRE
        //#define BP_USE_RAW3WIRE
        //#define BP_USE_PCATKB
        //#define BP_USE_LCD // include HD44780 LCD library
        //#define BP_USE_PIC
        //#define BP_USE_DIO //binary mode

#else
#error "No Bus Pirate configuration defined."
#endif

//ENABLE BASIC SCRIPTING
#if defined(BUSPIRATEV4)
	#define BP_USE_BASIC   // basic subsystem
	//#define BP_USE_BASICI2C  // use an i2ceeprom for storing
#endif


// only 1 should be uncommented
//#define BASICTEST
//#define BASICTEST_I2C
//#define BASICTEST_UART
//#define BASICTEST_R3W
//#define BASICTEST_PIC10                       // program blink a led
//#define BASICTEST_PIC10_2                     // read whole pic

//sets the address in the bootloader to jump to on the bootloader command
//must be defined in asm
asm (".equ BLJUMPADDRESS, 0xABF8");

//
//
//
// END CONFIG AREA
//
//
//

//// left out for now
/*      my italian and spanish aint that good ;)
#elif defined(LANGUAGE_IT_IT)
        #include "translations/it-IT.h"
//      #include "translations/en-US.h"
#elif defined(LANGUAGE_ES_ES)
        #include "translations/es-ES.h"
 */
 
 
// If BUSPIRATEv4 then use the en_US.h otherwise
// use the v3 one. The version3 one does not include
// the modes that the v3 cannot fit. This way we dont
// waste space on strings we wont see.
//
// Also note; the BPV4 project file uses the en_US.s file
// the buspurate v3 uses the other one...
#if defined(BUSPIRATEV4)
        #if defined(LANGUAGE_EN_US)
                #include "translations/BPv4_en_US.h"
        #elif defined(LANGUAGE_DE_DE)
                #include "translations/BPv4_de_DE.h"
        #else
                #error "No language defined in base.h."
        #endif
#else
        #if defined(LANGUAGE_EN_US)
                #include "translations/BPv3_en_US.h"
        #elif defined(LANGUAGE_DE_DE)
                #include "translations/BPv3_de_DE.h"
        #else
                #error "No language defined in base.h."
        #endif
#endif






//these settings are destroyed between modes.
//this is used to pass stuff from protocol libraries to BP
//for example, allowpullup determines if the P menu is available
//TO DO: add global scratch buffer to setting array for use in 
//	1-Wire enumeration, JTAG input buffer, etc...

struct _modeConfig {
    unsigned char speed;
    unsigned char numbits;
    unsigned char buf[16];
    unsigned char altAUX : 2; // there are 4 AUX on BUSPIRATEV4
    unsigned char periodicService : 1;
    unsigned char lsbEN : 1;
    unsigned char HiZ : 1;
    unsigned char int16 : 1; // 16 bits output?
    unsigned char wwr : 1; // write with read
};

struct _command {
    unsigned char cmd;
    unsigned int num;
    unsigned int repeat;
};

unsigned int bpRevByte(unsigned int c);

//reset all peripherals before configuring a new bus protocol
void bpInit(void);

//take an ADC measurement on channel c
unsigned int bpADC(unsigned char c);
//takes a measurement from the ADC probe and prints the result to the user terminal
void bpADCprobe(void);
void bpADCCprobe(void);

//print byte c to the user terminal in the format 
//  specified by the bpConfig.displayMode setting
void bpWbyte(unsigned int c);


#include <libpic30.h>
//delays used by many libraries
//void bpDelayMS(const unsigned char delay);
//void bpDelayUS(const unsigned char delay);
#define bpDelayMS __delay_ms
#define bpDelayUS __delay_us
#endif


