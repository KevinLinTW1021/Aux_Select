
#include <xc.h>
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 4000000

#define HIGH 1
#define ON 1
#define INPUT 1

#define LOW 0
#define OFF 0
#define OUTPUT 0

#define TA0 TRISAbits.TRISA0
#define TA1 TRISAbits.TRISA1
#define TA2 TRISAbits.TRISA2
#define TA3 TRISAbits.TRISA3
#define TA4 TRISAbits.TRISA4
#define TA5 TRISAbits.TRISA5
#define TA6 TRISAbits.TRISA6
#define TA7 TRISAbits.TRISA7

#define TB0 TRISBbits.TRISB0
#define TB1 TRISBbits.TRISB1
#define TB2 TRISBbits.TRISB2
#define TB3 TRISBbits.TRISB3
#define TB4 TRISBbits.TRISB4
#define TB5 TRISBbits.TRISB5
#define TB6 TRISBbits.TRISB6
#define TB7 TRISBbits.TRISB7

#define CD4052_A PORTAbits.RA0
#define CD4052_B PORTAbits.RA1
#define PA2 PORTAbits.RA2
#define LED_A3 PORTAbits.RA3
#define LED_A4 PORTAbits.RA4
#define LED_A5 PORTAbits.RA5
#define PA6 PORTAbits.RA6
#define PA7 PORTAbits.RA7

#define SELECT_TRIGGER_B0 PORTBbits.RB0
#define SELECT_TRIGGER_B1 PORTBbits.RB1
#define SELECT_TRIGGER_B2 PORTBbits.RB2
#define PB3 PORTBbits.RB3
#define PB4 PORTBbits.RB4
#define PB5 PORTBbits.RB5
#define PB6 PORTBbits.RB6
#define PB7 PORTBbits.RB7

#define OPTION_REG_ALL OPTION_REGbits.nRBPU

#define WPUB_B0 WPUBbits.WPUB0
#define WPUB_B1 WPUBbits.WPUB1
#define WPUB_B2 WPUBbits.WPUB2
#define WPUB_B3 WPUBbits.WPUB3
#define WPUB_B4 WPUBbits.WPUB4
#define WPUB_B5 WPUBbits.WPUB5
#define WPUB_B6 WPUBbits.WPUB6
#define WPUB_B7 WPUBbits.WPUB7

void main() {
    ANSEL = OFF;
    
    TA0 = OUTPUT;
    TA1 = OUTPUT;
    TA2 = OUTPUT;
    TA3 = OUTPUT;
    TA4 = OUTPUT;
    TA5 = OUTPUT;
    TA6 = OUTPUT;
    TA7 = OUTPUT;
    
    CD4052_A = LOW;
    CD4052_B = LOW;
    PA2 = LOW;
    LED_A3 = LOW;
    LED_A4 = LOW;
    LED_A5 = LOW;
    PA6 = LOW;
    PA7 = LOW;
    
    
    ANSELH = OFF;
    OPTION_REG_ALL = OFF;
    
    WPUB_B0 = ON;
    WPUB_B1 = ON;
    WPUB_B2 = ON;
    WPUB_B3 = OFF;
    WPUB_B4 = OFF;
    WPUB_B5 = OFF;
    WPUB_B6 = OFF;
    WPUB_B7 = OFF;
    
    TB0 = INPUT;
    TB1 = INPUT;
    TB2 = INPUT;
    TB3 = OUTPUT;
    TB4 = OUTPUT;
    TB5 = OUTPUT;
    TB6 = OUTPUT;
    TB7 = OUTPUT;
    
    SELECT_TRIGGER_B0 = HIGH;
    SELECT_TRIGGER_B1 = HIGH;
    SELECT_TRIGGER_B2 = HIGH;
    PB3 = LOW;
    PB4 = LOW;
    PB5 = LOW;
    PB6 = LOW;
    PB7 = LOW;
    

   
    while(1) {
        LED_A3 = ON;
        CD4052_A = LOW;
        CD4052_B = LOW;

        if (SELECT_TRIGGER_B0 == LOW) {
            LED_A3 = ON;
            CD4052_A = LOW;
            CD4052_B = LOW;
        }
        
        if (SELECT_TRIGGER_B1 == LOW) {
            LED_A4 = ON;
            CD4052_A = HIGH;
            CD4052_B = LOW;
        }

        if (SELECT_TRIGGER_B2 == LOW) {
            LED_A5 = ON;
            CD4052_A = LOW;
            CD4052_B = HIGH;
        }
    }
}


