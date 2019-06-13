/*
 * File:   main.c
 * Author: Rossetto Lorenzo
 *
 * Created on 13 giugno 2019, 10.10
 */

// DEVCFG2
#pragma config FPLLIDIV = DIV_2 // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_20 // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_2 // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1 // System PLL Output Clock Divider (PLL Divide by 256)
// DEVCFG1
#pragma config FNOSC = PRIPLL // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = ON // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = ON // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_8 // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576 // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
// DEVCFG0
#pragma config DEBUG = OFF // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2 // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF // Program Flash Write Protect (Disable)
#pragma config BWP = OFF // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF // Code Protect (Protection Disabled)
/// timer
// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 40 MHz
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care
// Let compile time pre-processor calculate the PR1 (period)
#define SYS_FREQ 			(80000000L)
#define PB_DIV         		8
#define PRESCALE       		256
#define TOGGLES_PER_SEC		1000
#define T1_TICK       		(SYS_FREQ/PB_DIV/PRESCALE/TOGGLES_PER_SEC)
#define SYSCLK 80000000L // Give the system?s clock frequency

#include <p32xxxx.h>
#include <plib.h> // Include the PIC32 Peripheral Library.
#include <xc.h>

void delay(int t) {
   int n = t * 1900; //1900 è un numero ricavato sperimentalmente
   while (n > 0) {
      n--;
   }
}
int main(void) {
   TRISD = (1<<4) | (1<<0);
   int oldButtonState = 0;
   
   while (1) {
       delay(100);
       int newButtonState = !PORTDbits.RD11;
       if (oldButtonState > newButtonState)
       {
           LATDbits.LATD6 =~ LATDbits.LATD6;
       }
       oldButtonState = !PORTDbits.RD11;
   }
   return 1;
}