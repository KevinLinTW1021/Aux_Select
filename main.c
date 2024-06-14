
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

#define TC0 TRISCbits.TRISC0
#define TC1 TRISCbits.TRISC1
#define TC2 TRISCbits.TRISC2
#define TC3 TRISCbits.TRISC3
#define TC4 TRISCbits.TRISC4
#define TC5 TRISCbits.TRISC5
#define TC6 TRISCbits.TRISC6
#define TC7 TRISCbits.TRISC7

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
#define CD4052_A PORTAbits.RA0
#define CD4052_B PORTAbits.RA1

#define OPTION_REG_ALL OPTION_REGbits.nRBPU

#define WPUB_B0 WPUBbits.WPUB0
#define WPUB_B1 WPUBbits.WPUB1
#define WPUB_B2 WPUBbits.WPUB2
#define WPUB_B3 WPUBbits.WPUB3
#define WPUB_B4 WPUBbits.WPUB4
#define WPUB_B5 WPUBbits.WPUB5
#define WPUB_B6 WPUBbits.WPUB6
#define WPUB_B7 WPUBbits.WPUB7

#define LCD_RS PORTCbits.RC0
#define LCD_EN PORTCbits.RC1
#define LCD_D4 PORTCbits.RC2
#define LCD_D5 PORTCbits.RC3
#define LCD_D6 PORTCbits.RC4
#define LCD_D7 PORTCbits.RC5

// Function declarations
void LCD_Command(unsigned char cmd);
void LCD_Char(unsigned char data);
void LCD_Init();
void LCD_String(const char *str);
void LCD_Nibble(unsigned char nibble);
void displayText(const char *str);


void LCD_Command(unsigned char cmd) {
    LCD_RS = 0;
    LCD_Nibble(cmd >> 4);
    LCD_Nibble(cmd & 0x0F);
    __delay_ms(2);
}

void LCD_Char(unsigned char data) {
    LCD_RS = 1;
    LCD_Nibble(data >> 4);
    LCD_Nibble(data & 0x0F);
    __delay_ms(2);
}

void LCD_Init() {
    __delay_ms(20);
    LCD_Command(0x02);
    LCD_Command(0x28);
    LCD_Command(0x0C);
    LCD_Command(0x06);
    LCD_Command(0x01);
    __delay_ms(2);
}

void LCD_String(const char *str) {
    while(*str) {
        LCD_Char(*str++);
    }
}

void LCD_Nibble(unsigned char nibble) {
    LCD_EN = 1;
    LCD_D4 = (nibble >> 0) & 0x01;
    LCD_D5 = (nibble >> 1) & 0x01;
    LCD_D6 = (nibble >> 2) & 0x01;
    LCD_D7 = (nibble >> 3) & 0x01;
    LCD_EN = 0;
    __delay_ms(2);
}

void displayText(const char *str) {
    TC0 = OUTPUT;
    TC1 = OUTPUT;
    TC2 = OUTPUT;
    TC3 = OUTPUT;
    TC4 = OUTPUT;
    TC5 = OUTPUT;
    
    LCD_RS = LOW;
    LCD_EN = LOW;
    LCD_D4 = LOW;
    LCD_D5 = LOW;
    LCD_D6 = LOW;
    LCD_D7 = LOW;
    
    LCD_Init();
    LCD_String(str);
    
}


void setFirstGroup() {
    TA0 = OUTPUT;
    TA1 = OUTPUT;
    TA2 = OUTPUT;
    
    WPUB_B0 = LOW;
    WPUB_B1 = HIGH;
    WPUB_B2 = HIGH;
    
    TA3 = OUTPUT;
    TA4 = OUTPUT;
    TA5 = OUTPUT;
    LED_A3 = ON;
    LED_A4 = OFF;
    LED_A5 = OFF;
    
    TB6 = OUTPUT;
    TB7 = OUTPUT;
    
    CD4052_B = LOW;
    CD4052_A = LOW;
    
    displayText("AUX1");
}

void setSecondGroup() {
    TA0 = OUTPUT;
    TA1 = OUTPUT;
    TA2 = OUTPUT;

    
    WPUB_B0 = HIGH;
    WPUB_B1 = LOW;
    WPUB_B2 = HIGH;
    
    TA3 = OUTPUT;
    TA4 = OUTPUT;
    TA5 = OUTPUT;
    
    LED_A3 = OFF;
    LED_A4 = ON;
    LED_A5 = OFF;
    
    TB6 = OUTPUT;
    TB7 = OUTPUT;

    CD4052_B = LOW;
    CD4052_A = HIGH;
    
    displayText("AUX2");
}

void setThirdGroup() {
    TA0 = OUTPUT;
    TA1 = OUTPUT;
    TA2 = OUTPUT;
    
    WPUB_B0 = HIGH;
    WPUB_B1 = HIGH;
    WPUB_B2 = LOW;
    
    TA3 = OUTPUT;
    TA4 = OUTPUT;
    TA5 = OUTPUT;
    
    LED_A3 = OFF;
    LED_A4 = OFF;
    LED_A5 = ON;
    
    TB6 = OUTPUT;
    TB7 = OUTPUT;
    CD4052_A = HIGH;
    CD4052_B = LOW;
    
    displayText("AUX3");
}

void delayDebounce() {
    __delay_ms(100);
}


void main() {
    ANSEL = OFF;
    
    ANSELH = OFF;
    OPTION_REG_ALL = OFF;
   
    
    TB0 = INPUT;
    TB1 = INPUT;
    TB2 = INPUT;
    TB3 = OUTPUT;
    TB4 = OUTPUT;
    TB5 = OUTPUT;
    TB6 = OUTPUT;
    TB7 = OUTPUT;
    

    PB3 = LOW;
    PB4 = LOW;
    PB5 = LOW;
    
    setFirstGroup();
    
    while(1) {
        
        if (SELECT_TRIGGER_B0 == LOW) {
            delayDebounce();
            if (SELECT_TRIGGER_B0 == LOW) {
            setFirstGroup();
           }
        }
        
        
       if (SELECT_TRIGGER_B1 == LOW) { 
           delayDebounce();
            if (SELECT_TRIGGER_B1 == LOW) {
            setSecondGroup();
           }
       }

        
       if (SELECT_TRIGGER_B2 == LOW) {
           delayDebounce();
        if (SELECT_TRIGGER_B2 == LOW) {
            setThirdGroup();
           }
       }
        
    }
        
}


