/*
 * File:   main.c
 * Author: klawler
 *
 * Created on March 8, 2014, 3:17 PM
 */
/*
 * File:   main.c
 * Author: klawler
 *
 * Created on March 8, 2014, 3:11 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <delays.h>


/*************************
 configrue microcontroller
 ************************/
#include <p18F25K80.h>

// CONFIG1L
#pragma config RETEN = OFF      // VREG Sleep Enable bit (Ultra low-power regulator is Disabled (Controlled by REGSLP bit))
#pragma config INTOSCSEL = HIGH // LF-INTOSC Low-power Enable bit (LF-INTOSC in High-power mode during Sleep)
#pragma config SOSCSEL = DIG   // SOSC Power Selection and mode Configuration bits (DIGITAL selected)
#pragma config XINST = OFF       // Extended Instruction Set (Disabled)

// CONFIG1H
#pragma config FOSC = INTIO2    // Oscillator (Internal RC oscillator)
#pragma config PLLCFG = OFF     // PLL x4 Enable bit (Disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power Up Timer (Disabled)
#pragma config BOREN = SBORDIS  // Brown Out Detect (Enabled in hardware, SBOREN disabled)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (1.8V)
#pragma config BORPWR = ZPBORMV // BORMV Power level (ZPBORMV instead of BORMV is selected)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer (WDT disabled in hardware; SWDTEN bit disabled)
#pragma config WDTPS = 1048576  // Watchdog Postscaler (1:1048576)

// CONFIG3H
#pragma config CANMX = PORTC    // ECAN Mux bit (ECAN TX and RX pins are located on RC6 and RC7, respectively)
#pragma config MSSPMSK = MSK7   // MSSP address masking (7 Bit address masking mode)
#pragma config MCLRE = ON       // Master Clear Enable (MCLR Enabled, RE3 Disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Overflow Reset (Enabled)
#pragma config BBSIZ = BB2K     // Boot Block Size (2K word Boot Block size)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protect 00800-01FFF (Disabled)
#pragma config CP1 = OFF        // Code Protect 02000-03FFF (Disabled)
#pragma config CP2 = OFF        // Code Protect 04000-05FFF (Disabled)
#pragma config CP3 = OFF        // Code Protect 06000-07FFF (Disabled)

// CONFIG5H
#pragma config CPB = OFF        // Code Protect Boot (Disabled)
#pragma config CPD = OFF        // Data EE Read Protect (Disabled)

// CONFIG6L
#pragma config WRT0 = OFF       // Table Write Protect 00800-03FFF (Disabled)
#pragma config WRT1 = OFF       // Table Write Protect 04000-07FFF (Disabled)
#pragma config WRT2 = OFF       // Table Write Protect 08000-0BFFF (Disabled)
#pragma config WRT3 = OFF       // Table Write Protect 0C000-0FFFF (Disabled)

// CONFIG6H
#pragma config WRTC = OFF       // Config. Write Protect (Disabled)
#pragma config WRTB = OFF       // Table Write Protect Boot (Disabled)
#pragma config WRTD = OFF       // Data EE Write Protect (Disabled)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protect 00800-03FFF (Disabled)
#pragma config EBTR1 = OFF      // Table Read Protect 04000-07FFF (Disabled)
#pragma config EBTR2 = OFF      // Table Read Protect 08000-0BFFF (Disabled)
#pragma config EBTR3 = OFF      // Table Read Protect 0C000-0FFFF (Disabled)

// CONFIG7H
#pragma config EBTRB = OFF      // Table Read Protect Boot (Disabled)

/////// Main Test Variables ////
int readyToFire = 0;
int attack1 = 0;
int heal1 = 0;
volatile int hit = 0;
int time = 0;
int storage = 0x00;
int imDead = 0;
volatile int hapfront = 0;
volatile int hapleft = 0;
volatile int hapright = 0;
volatile int hapback = 0;
int blink = 0;
int a = 0;
int b = 0;
int c = 0;
int green_start; //conditional led
int blue_start;
int red_start;
////////////////////////////////

///// Main Test Functions //////
void irreceive(void);
void initialize(void);
void absorb(void);
//void haptic(void);
void visuals(void);
void userinput(void);
void irsend(void);
///////////////////////////////

///// Visuals Functions //////////
void addr_off(int);
void addr_on(int);
void all_off();
void all_on();
void addr_2thru8_off();
void addr_3thru8_off();
void addr_4thru8_off();
void addr_5thru8_off();
void addr_6thru8_off();
void addr_7thru8_off();
void addr_1thru2_on();
void addr_1thru3_on();
void addr_1thru4_on();
void addr_1thru5_on();
void addr_1thru6_on();
void addr_1thru7_on();
void powerBar(int);
void LED_init();

#define hSig PORTAbits.RA5 = 1;
#define lSig PORTAbits.RA5 = 0;
#define SPI_Data SSPBUF
#define SPI_Wait while(!SSPSTATbits.BF);
#define decode 0x09
#define intensity 0x0A
#define sLimit 0x0B
#define shutdown 0x0C
#define test 0x0F

#define delay Delay10KTCYx(200);
////////////////////////////////////////////////

////////// Vibration Functions and Defines ////////////////////////////////////
void haptic(void);


//#define Left_Shoulder PORTAbits.RA0 //Pin 2
//#define Right_Shoulder PORTAbits.RA1  //Pin 3
//#define Chest PORTAbits.RA2  //Pin 4
//#define Back PORTAbits.RA3  //Pin 5

#define Left_Shoulder PORTAbits.RA2 //Pin 2 //a2 left
#define Right_Shoulder PORTAbits.RA3
#define Chest PORTAbits.RA1  //Pin 4 pin 1 a1 right
#define Back PORTAbits.RA0  //Pin 5  //a0 back
///////////////////////////////////////////////////////////////////////////////




//////// IR Recieve Variables, Constants and functions ///////////////////////
unsigned int isValid = 0;
unsigned int start_on = 0;
unsigned int start_off = 0;
unsigned int data1_on = 0;
unsigned int data1_off = 0;
unsigned int data2_on = 0;
unsigned int data2_off = 0;
unsigned int stop_on = 0;
unsigned int stop_off = 0;
unsigned int i = 0;


/////////// 8MHz PIC18F25K80 w/ C18 Compiler ///////////
#define MIRP_TOLERANCE          5
#define START_COUNT             25
#define START_OFF_COUNT         300
#define DATA_COUNT              42
#define DATA_OFF_COUNT          278
#define STOP_COUNT              560


void irISR(void);

//////////////////////////////////////////////////////////////////



/////////// IR Send Fuctions //////////////////////////////////////
void main (void);
//void attack(void);
//void heal(void);
//void IR_Init(void);
void IR_Delay(int);
void heal(void);
void attack(void);
void signal_on(unsigned char);
void signal_off(unsigned char);

//#define IR_OFF TRISBbits.TRISB4
#define IRLED PORTAbits.RA6
//////////////////////////////////////////////////////////////////

/////////////////////////// CAN Variables and Functions ///////////////////////
void sendImDead(void);
void MCANinit(void);
unsigned char temp_EIDH;
unsigned char temp_EIDL;
unsigned char temp_SIDH;
unsigned char temp_SIDL;
unsigned char temp_DLC;
unsigned char temp_D0;
unsigned char temp_D1;
//////////////////////////////////////////////////////////////////



#pragma code HIGH_INTERRUPT_VECTOR = 0x8
void high_ISR (void)
{
    _asm
     //goto irreceive    //Main Test Function
     goto irISR
    _endasm
}
#pragma code


#pragma interrupt irISR
void irISR()
{
    INTCONbits.GIE = 0;
    INTCONbits.RBIE = 0;
    


if(INTCONbits.INT0IF)                                       ///Activates if Pin INT0 interrupts
{
                                 //Disable interrupt pin

        //PORTCbits.RC3 ^= 1;
        while(PORTBbits.RB0 == 0 && start_on < 200)                               //Count signal low (IR High)
                start_on = start_on + 1;
        while(PORTBbits.RB0 == 1 && start_off < 700)                               //Count signal high (IR Low)
                start_off = start_off +  1;
        while(PORTBbits.RB0 == 0 && data1_on < 200)                               //Count signal low (IR High)
                data1_on = data1_on + 1;
        while(PORTBbits.RB0 == 1 && data1_off < 700)                               //Count signal high (IR Low)
                data1_off = data1_off +  1;
        while(PORTBbits.RB0 == 0 && data2_on < 200)                               //Count signal low (IR High)
                data2_on = data2_on + 1;
        while(PORTBbits.RB0 == 1 && data2_off < 700)                               //Count signal high (IR Low)
                data2_off = data2_off +  1;

        if(start_on > START_COUNT - MIRP_TOLERANCE
        && start_on < START_COUNT + MIRP_TOLERANCE
        && start_off > START_OFF_COUNT - MIRP_TOLERANCE
        && start_off < START_OFF_COUNT + MIRP_TOLERANCE
        && data1_on > DATA_COUNT - MIRP_TOLERANCE
        && data1_on < DATA_COUNT + MIRP_TOLERANCE
        && data1_off > DATA_OFF_COUNT - MIRP_TOLERANCE
        && data1_off < DATA_OFF_COUNT + MIRP_TOLERANCE
        && data2_on > DATA_COUNT - MIRP_TOLERANCE
        && data2_on < DATA_COUNT + MIRP_TOLERANCE
        && data2_off > DATA_OFF_COUNT - MIRP_TOLERANCE
        && data2_off < DATA_OFF_COUNT + MIRP_TOLERANCE)             //Verify data packet
                isValid = 1;


        //////MARK AS HIT FROM RECEIVER 1//////////////
        if(isValid ==1)
        {
            //PORTCbits.RC0 ^= 1;
            hit += 1;
            hapfront += 1;
        }
        ///////////////////////////////////////////////


        //////RESET VARIABLES TO ZERO//////////////////
        start_on = 0;
        start_off = 0;
        data1_on = 0;
        data1_off = 0;
        data2_on = 0;
        data2_off = 0;
        stop_on = 0;
        stop_off = 0;
        isValid = 0;                                            //Reset validity check
        ///////////////////////////////////////////////


        INTCONbits.INT0IF = 0;
        INTCON3bits.INT1IF = 0;
        INTCON3bits.INT2IF = 0;
        INTCON3bits.INT3IF = 0;


 }

if(INTCON3bits.INT1IF)                                         ///// activates if Pin INT1 interrupts
    {
        INTCONbits.GIE = 0;                                //Disable interrupt pin

        while(PORTBbits.RB1 == 0 && start_on < 200)                               //Count signal low (IR High)
                start_on = start_on + 1;
        while(PORTBbits.RB1 == 1 && start_off < 700)                               //Count signal high (IR Low)
                start_off = start_off +  1;
        while(PORTBbits.RB1 == 0 && data1_on < 200)                               //Count signal low (IR High)
                data1_on = data1_on + 1;
        while(PORTBbits.RB1 == 1 && data1_off < 700)                               //Count signal high (IR Low)
                data1_off = data1_off +  1;
        while(PORTBbits.RB1 == 0 && data2_on < 200)                               //Count signal low (IR High)
                data2_on = data2_on + 1;
        while(PORTBbits.RB1 == 1 && data2_off < 700)                               //Count signal high (IR Low)
                data2_off = data2_off +  1;


        if(start_on > START_COUNT - MIRP_TOLERANCE
        && start_on < START_COUNT + MIRP_TOLERANCE
        && start_off > START_OFF_COUNT - MIRP_TOLERANCE
        && start_off < START_OFF_COUNT + MIRP_TOLERANCE
        && data1_on > DATA_COUNT - MIRP_TOLERANCE
        && data1_on < DATA_COUNT + MIRP_TOLERANCE
        && data1_off > DATA_OFF_COUNT - MIRP_TOLERANCE
        && data1_off < DATA_OFF_COUNT + MIRP_TOLERANCE
        && data2_on > DATA_COUNT - MIRP_TOLERANCE
        && data2_on < DATA_COUNT + MIRP_TOLERANCE
        && data2_off > DATA_OFF_COUNT - MIRP_TOLERANCE
        && data2_off < DATA_OFF_COUNT + MIRP_TOLERANCE)             //Verify data packet
                isValid = 1;



        //////MARK AS HIT FROM RECEIVER 2//////////////
        if(isValid ==1)
        {
            //PORTCbits.RC0 ^= 1;
            hit += 1;
            hapback += 1;
        }
        ///////////////////////////////////////////////


        //////RESET VARIABLES TO ZERO//////////////////
        start_on = 0;
        start_off = 0;
        data1_on = 0;
        data1_off = 0;
        data2_on = 0;
        data2_off = 0;
        stop_on = 0;
        stop_off = 0;
        isValid = 0;                                            //Reset validity check
        ///////////////////////////////////////////////


        INTCONbits.INT0IF = 0;
        INTCON3bits.INT1IF = 0;
        INTCON3bits.INT2IF = 0;
        INTCON3bits.INT3IF = 0;


    }

if(INTCON3bits.INT2IF)                                      ///// activates if Pin INT2 interrupts
    {
        INTCONbits.GIE = 0;                               //Disable interrupt pin

        while(PORTBbits.RB2 == 0 && start_on < 200)                               //Count signal low (IR High)
                start_on = start_on + 1;
        while(PORTBbits.RB2 == 1 && start_off < 700)                               //Count signal high (IR Low)
                start_off = start_off +  1;
        while(PORTBbits.RB2 == 0 && data1_on < 200)                               //Count signal low (IR High)
                data1_on = data1_on + 1;
        while(PORTBbits.RB2 == 1 && data1_off < 700)                               //Count signal high (IR Low)
                data1_off = data1_off +  1;
        while(PORTBbits.RB2 == 0 && data2_on < 200)                               //Count signal low (IR High)
                data2_on = data2_on + 1;
        while(PORTBbits.RB2 == 1 && data2_off < 700)                               //Count signal high (IR Low)
                data2_off = data2_off +  1;


        if(start_on > START_COUNT - MIRP_TOLERANCE
        && start_on < START_COUNT + MIRP_TOLERANCE
        && start_off > START_OFF_COUNT - MIRP_TOLERANCE
        && start_off < START_OFF_COUNT + MIRP_TOLERANCE
        && data1_on > DATA_COUNT - MIRP_TOLERANCE
        && data1_on < DATA_COUNT + MIRP_TOLERANCE
        && data1_off > DATA_OFF_COUNT - MIRP_TOLERANCE
        && data1_off < DATA_OFF_COUNT + MIRP_TOLERANCE
        && data2_on > DATA_COUNT - MIRP_TOLERANCE
        && data2_on < DATA_COUNT + MIRP_TOLERANCE
        && data2_off > DATA_OFF_COUNT - MIRP_TOLERANCE
        && data2_off < DATA_OFF_COUNT + MIRP_TOLERANCE)             //Verify data packet
                isValid = 1;


        //////MARK AS HIT FROM RECEIVER 3//////////////
        if(isValid ==1)
        {
        PORTCbits.RC0 ^= 1;
        hit += 1;
        hapleft += 1;
        }
        ///////////////////////////////////////////////


        //////RESET VARIABLES TO ZERO//////////////////
        start_on = 0;
        start_off = 0;
        data1_on = 0;
        data1_off = 0;
        data2_on = 0;
        data2_off = 0;
        stop_on = 0;
        stop_off = 0;
        isValid = 0;                                            //Reset validity check
        ///////////////////////////////////////////////


        INTCONbits.INT0IF = 0;
        INTCON3bits.INT1IF = 0;
        INTCON3bits.INT2IF = 0;
        INTCON3bits.INT3IF = 0;


    }




if(INTCON3bits.INT3IF)                                      ///// activates if Pin INT3 interrupts
    {
        INTCONbits.GIE = 0;                                //Disable interrupt pin

        while(PORTBbits.RB3 == 0 && start_on < 200)                               //Count signal low (IR High)
                start_on = start_on + 1;
        while(PORTBbits.RB3 == 1 && start_off < 700)                               //Count signal high (IR Low)
                start_off = start_off +  1;
        while(PORTBbits.RB3 == 0 && data1_on < 200)                               //Count signal low (IR High)
                data1_on = data1_on + 1;
        while(PORTBbits.RB3 == 1 && data1_off < 700)                               //Count signal high (IR Low)
                data1_off = data1_off +  1;
        while(PORTBbits.RB3 == 0 && data2_on < 200)                               //Count signal low (IR High)
                data2_on = data2_on + 1;
        while(PORTBbits.RB3 == 1 && data2_off < 700)                               //Count signal high (IR Low)
                data2_off = data2_off +  1;


        if(start_on > START_COUNT - MIRP_TOLERANCE
        && start_on < START_COUNT + MIRP_TOLERANCE
        && start_off > START_OFF_COUNT - MIRP_TOLERANCE
        && start_off < START_OFF_COUNT + MIRP_TOLERANCE
        && data1_on > DATA_COUNT - MIRP_TOLERANCE
        && data1_on < DATA_COUNT + MIRP_TOLERANCE
        && data1_off > DATA_OFF_COUNT - MIRP_TOLERANCE
        && data1_off < DATA_OFF_COUNT + MIRP_TOLERANCE
        && data2_on > DATA_COUNT - MIRP_TOLERANCE
        && data2_on < DATA_COUNT + MIRP_TOLERANCE
        && data2_off > DATA_OFF_COUNT - MIRP_TOLERANCE
        && data2_off < DATA_OFF_COUNT + MIRP_TOLERANCE)             //Verify data packet
                isValid = 1;


        //////MARK AS HIT FROM RECEIVER 4//////////////
        if(isValid ==1)
        {
            //PORTCbits.RC0 ^= 1;
            hit += 1;
            hapright += 1;
        }
        ///////////////////////////////////////////////


        //////RESET VARIABLES TO ZERO//////////////////
        start_on = 0;
        start_off = 0;
        data1_on = 0;
        data1_off = 0;
        data2_on = 0;
        data2_off = 0;
        stop_on = 0;
        stop_off = 0;
        isValid = 0;                                            //Reset validity check
        ///////////////////////////////////////////////


        INTCONbits.INT0IF = 0;
        INTCON3bits.INT1IF = 0;
        INTCON3bits.INT2IF = 0;
        INTCON3bits.INT3IF = 0;


    }

    INTCONbits.GIE = 1;

}


///// Test Main IR Recieve /////
/*
#pragma interrupt irreceive
void irreceive(void)
{


    if(INTCON3bits.INT2IF)
    {
        INTCON3bits.INT2IE = 0;
        Delay100TCYx(10);
        if(PORTBbits.RB2)
        {
            PORTCbits.RC7 ^= 1;
            hit = 1;
            hapleft = 1;
        }

        INTCON3bits.INT2IE = 1;
        INTCON3bits.INT2IF = 0;
     }

    if(INTCONbits.INT0IF)
    {
        INTCONbits.INT0IE = 0;
        Delay100TCYx(10);
        if(PORTBbits.RB0)
        {
         //PORTCbits.RC4 ^= 1;
         hit = 1;
         hapfront = 1;
        }

        INTCONbits.INT0IE = 1;
        INTCONbits.INT0IF = 0;
     }

    if(INTCON3bits.INT1IF)
    {
        INTCON3bits.INT1IE = 0;
        Delay1KTCYx(10);
        if(PORTBbits.RB1)
        {
          //PORTCbits.RC5 ^= 1;
          hit = 1;
          hapback = 1;
        }
        //attack = 1;

        INTCON3bits.INT1IE = 1;
        INTCON3bits.INT1IF = 0;
     }
    if(INTCON3bits.INT3IF)
    {
        INTCON3bits.INT3IE = 0;
        Delay100TCYx(10);
        if(PORTBbits.RB3)
        {
            PORTCbits.RC6 ^= 1;
            hit = 1;
            hapright = 1;
        }


        INTCON3bits.INT3IE = 1;
        INTCON3bits.INT3IF = 0;
     }




}

void main (void)
{
    
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB6 = 0;
    while(1)
    {
      PORTBbits.RB4 = 1;//blue
      PORTBbits.RB5 = 1;//green
      PORTBbits.RB6 = 1;//red
    }
    
}
*/

void main(void)
{

initialize();
MCANinit();

Delay10KTCYx(100);
powerBar(0x00);
///////////////////////////
        a = 0x00; //startup power
        b = 0; //startup counter
        c = 0;
        green_start = 0; //conditional led
        blue_start = 0;
        red_start = 0;
        while(b < 50){
            a = a + 1;
            b = b + 1;
            green_start = green_start + 1; //conditional led
            blue_start = blue_start + 1;
            red_start = red_start + 1;
            powerBar(a);
            if(b%10 == 0){
                PORTBbits.RB4 ^= 1;//blue
            }
            if(b%13 == 0){
                    PORTBbits.RB5 ^= 1;//green
            }
            if(b%16 == 0){
                    PORTBbits.RB6 ^= 1;//red
            }
                        Delay10KTCYx(3);
            }
        Delay10KTCYx(3);
        while(b > 0){
            a = a - 1;
            b = b - 1;
            green_start = green_start + 1; //conditional led
            blue_start = blue_start + 1;
            red_start = red_start + 1;
            powerBar(a);
            if(b%10 == 0){
                PORTBbits.RB4 ^= 1;//blue
            }
              if(b%13 == 0){
                    PORTBbits.RB5 ^= 1;//green
                }
                if(b%16 == 0){
                    PORTBbits.RB6 ^= 1;//red
                }
                        Delay10KTCYx(3);
            }
            powerBar(a);
            Delay10KTCYx(3);
        

//////////////////////////
/*
    PORTBbits.RB4 = 1;//blue        1 is off for these
    PORTBbits.RB5 = 0;//green
    PORTBbits.RB6 = 1;//red
    powerBar(0x32);
    delay
    PORTBbits.RB4 = 0;//blue        1 is off for these
    PORTBbits.RB5 = 1;//green
    PORTBbits.RB6 = 1;//red
    powerBar(0x00);
    delay
    PORTBbits.RB4 = 1;//blue        1 is off for these
    PORTBbits.RB5 = 1;//green
    PORTBbits.RB6 = 0;//red
    powerBar(0x32);
    delay
    PORTBbits.RB4 = 0;//blue        1 is off for these
    PORTBbits.RB5 = 1;//green
    PORTBbits.RB6 = 0;//red
    powerBar(0x00);
    delay
    PORTBbits.RB4 = 1;//blue        1 is off for these
    PORTBbits.RB5 = 1;//green
    PORTBbits.RB6 = 1;//red */
    while(1)
    {
        userinput();
        irsend();
        PORTBbits.RB4 = 0;//blue        1 is off for these
        PORTBbits.RB5 = 1;//green
        PORTBbits.RB6 = 1;//red

        while(hit)
        {
    PORTBbits.RB4 = 1;//blue        1 is off for these
    PORTBbits.RB5 = 1;//green
    PORTBbits.RB6 = 0;//red
    Delay10KTCYx(1);
                PORTBbits.RB4 = 1;//blue        1 is off for these
    PORTBbits.RB5 = 1;//green
    PORTBbits.RB6 = 1;//red

            absorb();
            haptic();
            powerBar(storage);
            if(imDead)
            {

                INTCONbits.GIE = 0;

                 Left_Shoulder = 1; //turns on pin 2
                    Right_Shoulder = 1;
                    Chest = 1;
                    Back = 1;

                while(storage > 0)
                {
                   // PORTCbits.RC0 ^= 1;
                    attack();
                    Delay10KTCYx(20);
                    storage = storage - 1;
                    powerBar(storage);
                }

                     Left_Shoulder = 0; //turns on pin 2
                    Right_Shoulder = 0;
                    Chest = 0;
                    Back = 0;
    PORTBbits.RB4 = 1;//blue        1 is off for these
    PORTBbits.RB5 = 1;//green
    PORTBbits.RB6 = 0;//red
    delay
    PORTBbits.RB4 = 0;//blue        1 is off for these
    PORTBbits.RB5 = 1;//green
    PORTBbits.RB6 = 0;//red
    delay
    PORTBbits.RB4 = 1;//blue        1 is off for these
    PORTBbits.RB5 = 1;//green
    PORTBbits.RB6 = 0;//red
    delay
    PORTBbits.RB4 = 0;//blue        1 is off for these
    PORTBbits.RB5 = 1;//green
    PORTBbits.RB6 = 0;//red
    delay
    PORTBbits.RB4 = 1;//blue        1 is off for these
    PORTBbits.RB5 = 1;//green
    PORTBbits.RB6 = 0;//red

   

                //hapfirst = 0;
                while(blink < 5)
                {
                    powerBar(0x32);
                    Delay10KTCYx(50);

                    Left_Shoulder = 1; //turns on pin 2
                    Right_Shoulder = 1;
                    Chest = 1;
                    Back = 1;
                    Delay10KTCYx(40); //On time
                    Left_Shoulder = 0;
                    Right_Shoulder = 0;
                    Chest = 0;
                    Back = 0;

                    Delay10KTCYx(10); //Delay until next packet


                    powerBar(0x00);
                    Delay10KTCYx(50);
                    blink = blink + 1;
                    sendImDead();
                }
                sendImDead();
                while(1)
                {
                    //do nothing
                }

            }
            hit = hit - 1;


        }


            readyToFire = 1;



        ////////////////////
        //hapleft= 0;
        //haptic();
        //Delay10KTCYx(50);

        ///////////////////
    }   ///end first while loop

} ///end main


void initialize(void)
{

    /////// Haptic  /////////////////////////////////////////////////////
    TRISAbits.TRISA0 = 0;
    PORTAbits.RA0 = 0;
    TRISAbits.TRISA1 = 0;
    PORTAbits.RA1 = 0;
    TRISAbits.TRISA2 = 0;
    PORTAbits.RA2 = 0;
    TRISAbits.TRISA3 = 0;
    PORTAbits.RA3 = 0;
    /////////////////////////////////////////////////////////////////////

    ////// Send IR ////////////////////////////////////////////////////////
    TRISAbits.TRISA6 = 0;
    PORTAbits.RA6 = 0;
    ////////////////////////////////////////////////////////////////////////


    ///// Recieve IR ///////////////////////////////////////////////////////////

    //// Set Trisbits /////////
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;
    ///////////////////////////


    /// ENABLE INTERRUPTS /////
    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT2IE = 1;
    INTCON3bits.INT3IE = 1;
    ///////////////////////////

    // SET HIGH PRIORITY //////
    INTCON3bits.INT1IP = 1;
    INTCON3bits.INT2IP = 1;
    INTCON2bits.INT3IP = 1;
    ///////////////////////////

    // CLEAR INTERRUPT FLAGS //
    INTCONbits.INT0IF = 0;
    INTCON3bits.INT1IF = 0;
    INTCON3bits.INT2IF = 0;
    INTCON3bits.INT3IF = 0;
    //////////////////////////

    // GLOBAL INTERRUPT ENABLE //
    RCONbits.IPEN = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    /////////////////////////////

    // SET FALLING EDGE ////////
    INTCON2bits.INTEDG0 = 0;
    INTCON2bits.INTEDG1 = 0;
    INTCON2bits.INTEDG2 = 0;
    INTCON2bits.INTEDG3 = 0;
    ////////////////////////////


    ///////////////////////////////////////////////////////////////////////////

    //////////////////////////// Visuals ///////////////////////////////////////

    ///// Set Trisbits //////////////////
    TRISCbits.TRISC5 = 0; //SDO output
    TRISCbits.TRISC3 = 0; //clk out
    TRISCbits.TRISC4 = 1; //SPI input
    TRISAbits.TRISA5 = 0; //SS output

    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB6 = 0;

    PORTBbits.RB4 = 1;//blue        1 is off for these
    PORTBbits.RB5 = 1;//green
    PORTBbits.RB6 = 1;//red
    /////////////////////////////////////

    ////////////// Other Initilizations /////////////////
    //initialize the two SPI registers
    SSPSTAT = 0b11000000;
    SSPCON1 = 0b00110001;

    hSig
    SPI_Data = decode;  //sets up the decode mode
    SPI_Wait
    SPI_Data = 0x00;
    SPI_Wait
    lSig
    hSig
    SPI_Data = sLimit;  //sets up the scan limit register to display digits 0-7
    SPI_Wait
    SPI_Data = 0x07;
    SPI_Wait
    lSig
    hSig
    SPI_Data = intensity;   //sets up the intensity register to have the leds at
    SPI_Wait                //maximum brightness
    SPI_Data = 0x0F;
    SPI_Wait
    lSig
    hSig
    delay
    SPI_Data = shutdown;    //sets up the shutdown register to normal operation
    SPI_Wait                //of the driver
    SPI_Data = 0x01;
    SPI_Wait
    lSig


    ////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////

   ///////////////////////////// Vibration ////////////////////////////////////
   // TRISAbits.TRISA0=0; //set pin 3 as output
   // TRISAbits.TRISA1=0; //set pin 4 as output
   // TRISAbits.TRISA2=0; //set pin 5 as output
   // TRISAbits.TRISA3=0; //set pin 7 as output
    ///////////////////////////////////////////////////////////////////////////

    ///// Power Light //////
    TRISAbits.TRISA7 = 0;
    PORTAbits.RA7 = 1;
    ///////////////////////////////

    /////// Switches //////////////
    TRISCbits.TRISC1 = 1;
    TRISCbits.TRISC2 = 1;
    PORTCbits.RC1 = 0;
    PORTCbits.RC2 = 0;
    ///////////////////////////////

    ///// Switch Test Lights //////
    //TRISCbits.TRISC3 = 0;
    //PORTCbits.RC3 = 0;

    TRISCbits.TRISC0 = 0;
    PORTCbits.RC0 = 0;
    ///////////////////////////////


    ///// Recieve Test Lights //////
    //TRISCbits.TRISC4 = 0;
    //PORTCbits.RC4 = 0;
    //TRISCbits.TRISC5 = 0;
    //PORTCbits.RC5 = 0;
    //TRISCbits.TRISC6 = 0;
    //PORTCbits.RC6 = 0;
    //TRISCbits.TRISC7 = 0;
    //PORTCbits.RC7 = 0;
    ////////////////////////////////


    //// Make special pins GPIO ////
    ANCON0 = 0x00;
    ANCON1 = 0x00;
    ADCON0 = 0x00;
    CM1CON = 0b00000000;
    CM2CON = 0b00000000;
    ////////////////////////////////




}

void absorb(void)
{
    storage = storage + 0x01;
    if(storage > 50)
    {
        imDead = 1;
    }
}
/*
void haptic(void)
{

    if(hapfront)
    {
        PORTAbits.RA3 ^= 1;
        hapfront = 0;
    }
    if(hapback)
    {
        PORTAbits.RA2 ^= 1;
        hapback = 0;
    }
    if(hapleft)
    {
        PORTAbits.RA0 ^= 1;
        hapleft = 0;
    }
    if(hapright)
    {
        PORTAbits.RA1 ^= 1;
        hapright = 0;
    }
    if(imDead && hapfirst)
    {
        PORTAbits.RA3 = 1;
        PORTAbits.RA2 = 1;
        PORTAbits.RA1 = 1;
        PORTAbits.RA0 = 1;
    }
    if(imDead && !hapfirst)
    {
        PORTAbits.RA3 ^= 1;
        PORTAbits.RA2 ^= 1;
        PORTAbits.RA1 ^= 1;
        PORTAbits.RA0 ^= 1;
    }

}
*/
void visuals(void)
{
    //PORTAbits.RA5 ^= 1;
}


void userinput(void)
{
    if(PORTCbits.RC1)
    {
        heal1 = 1;
        a = 0;
        b = 0;

    }

    if(PORTCbits.RC2)
    {
       attack1 = 1;
       a = 0;
       b = 0;
    }
}

void irsend(void)
{
    if(readyToFire)
        {
            if(attack1)
            {

            PORTBbits.RB4 = 1;//blue        1 is off for these
            PORTBbits.RB5 = 1;//green
            PORTBbits.RB6 = 1;//red
                while(storage > 0)
                {
                    INTCONbits.GIE = 0;
                    PORTBbits.RB6 = 0;//red
                    attack();
                    INTCONbits.GIE = 1;
                    PORTCbits.RC0 ^= 1;
                    Delay10KTCYx(20);
                    storage = storage - 1;
                    powerBar(storage);
                    PORTBbits.RB6 = 1;//red
                }

                attack1 = 0;
            }
            if(heal1)
            {

            PORTBbits.RB4 = 1;//blue        1 is off for these
            PORTBbits.RB5 = 1;//green
            PORTBbits.RB6 = 1;//red
                while(storage > 0)
                {
                    INTCONbits.GIE = 0;
                    PORTBbits.RB5 = 0;//green
                    heal();
                    INTCONbits.GIE = 1;
                    PORTCbits.RC0 ^= 1;
                    Delay10KTCYx(20);
                    storage = storage - 1;
                    powerBar(storage);
                    PORTBbits.RB5 = 1;//green
                }
                 heal1 = 0;
            }
        }
}



///////////////////////// IR Send Functions ///////////////////////////////////


void signal_on(unsigned char a){
   //Turn on the LED for 1 duty cycle

   unsigned char i;
   for (i=0;i<a;i++){
       IRLED = 1;
       //1 Duty Cycle is 12 delays
       Delay10TCYx(1);
       Delay1TCY();
       Delay1TCY();
       Delay1TCY();
       IRLED = 0;
       Delay10TCYx(1);
       Delay1TCY();
       Delay1TCY();
       Delay1TCY();
   }

}



void signal_off(unsigned char b){
   unsigned char i;
   for (i=0;i<b;i++){
       IRLED = 1;
       //1 Duty Cycle is 12 delays
       Delay10TCYx(1);
       Delay1TCY();
       Delay1TCY();
       Delay1TCY();
       IRLED = 1;
       Delay10TCYx(1);
       Delay1TCY();
       Delay1TCY();
       Delay1TCY();
   }
}

void attack(){
   signal_on(10);
   signal_off(140);
   signal_on(20);
   signal_off(130);
   signal_on(20);
   signal_off(130);
   signal_on(150);
}

void heal(){
   signal_on(10);
   signal_off(140);
   signal_on(30);
   signal_off(120);
   signal_on(30);
   signal_off(120);
   signal_on(150);
}

///////////////////////////// Visuals Functions ///////////////////////////////

/*This function turns a bar off depending on the address that was sent*/
void addr_off(int addr){
   hSig
   SPI_Data = addr;
   SPI_Wait
   SPI_Data = 0x00;
   SPI_Wait
   lSig
}

/*This function turns a bar on depending on the address that was sent*/
void addr_on(int addr){
   hSig
   SPI_Data = addr;
   SPI_Wait
   SPI_Data = 0xFF;
   SPI_Wait
   lSig
}

/*This function turns all of the bars off*/
void all_off(){
   addr_off(0x01);
   addr_off(0x02);
   addr_off(0x03);
   addr_off(0x04);
   addr_off(0x05);
   addr_off(0x06);
   addr_off(0x07);
   addr_off(0x08);
}

/*This function turns all of the bars on*/
void all_on(){
   addr_on(0x01);
   addr_on(0x02);
   addr_on(0x03);
   addr_on(0x04);
   addr_on(0x05);
   addr_on(0x06);
   addr_on(0x07);
   addr_on(0x08);
}

/*This function turns bars 2-8 off*/
void addr_2thru8_off(){
   addr_off(0x02);
   addr_off(0x03);
   addr_off(0x04);
   addr_off(0x05);
   addr_off(0x06);
   addr_off(0x07);
   addr_off(0x08);
}

/*This function turns bars 3-8 off*/
void addr_3thru8_off(){
   addr_off(0x03);
   addr_off(0x04);
   addr_off(0x05);
   addr_off(0x06);
   addr_off(0x07);
   addr_off(0x08);
}

/*This function turns bars 4-8 off*/
void addr_4thru8_off(){
   addr_off(0x04);
   addr_off(0x05);
   addr_off(0x06);
   addr_off(0x07);
   addr_off(0x08);
}

/*This function turns bars 5-8 off*/
void addr_5thru8_off(){
   addr_off(0x05);
   addr_off(0x06);
   addr_off(0x07);
   addr_off(0x08);
}

/*This function turns bars 6-8 off*/
void addr_6thru8_off(){
   addr_off(0x06);
   addr_off(0x07);
   addr_off(0x08);
}

/*This function turns bars 7 and 8 off*/
void addr_7thru8_off(){
   addr_off(0x07);
   addr_off(0x08);
}

/*This function turns bars 1 and 2 on*/
void addr_1thru2_on(){
   addr_on(0x01);
   addr_on(0x02);
}

/*This function turns bars 1-3 on*/
void addr_1thru3_on(){
   addr_on(0x01);
   addr_on(0x02);
   addr_on(0x03);
}

/*This function turns bars 1-4 on*/
void addr_1thru4_on(){
   addr_on(0x01);
   addr_on(0x02);
   addr_on(0x03);
   addr_on(0x04);
}

/*This function turns bars 1-5 on*/
void addr_1thru5_on(){
   addr_on(0x01);
   addr_on(0x02);
   addr_on(0x03);
   addr_on(0x04);
   addr_on(0x05);
}

/*This function turns bars 1-6 on*/
void addr_1thru6_on(){
   addr_on(0x01);
   addr_on(0x02);
   addr_on(0x03);
   addr_on(0x04);
   addr_on(0x05);
   addr_on(0x06);
}

/*This function turns bars 1-7 on*/
void addr_1thru7_on(){
   addr_on(0x01);
   addr_on(0x02);
   addr_on(0x03);
   addr_on(0x04);
   addr_on(0x05);
   addr_on(0x06);
   addr_on(0x07);
}

/*This function takes in the power level supplied by the main code
and then lights up the appropriate number of LEDs*/
void powerBar(int power){

   if(power == 0x00)
   {
       all_off();
   }
   else if(power == 0x01)  //first LED block
   {
       hSig
       SPI_Data = 0x01;
       SPI_Wait
       SPI_Data = 0x80;
       SPI_Wait
       lSig

       addr_2thru8_off();
   }
   else if(power == 0x02)
   {
       hSig
       SPI_Data = 0x01;
       SPI_Wait
       SPI_Data = 0xC0;
       SPI_Wait
       lSig

       addr_2thru8_off();
   }
   else if(power == 0x03)
   {
       hSig
       SPI_Data = 0x01;
       SPI_Wait
       SPI_Data = 0xE0;
       SPI_Wait
       lSig

       addr_2thru8_off();
   }
   else if(power == 0x04)
   {
       hSig
       SPI_Data = 0x01;
       SPI_Wait
       SPI_Data = 0xF0;
       SPI_Wait
       lSig

       addr_2thru8_off();
   }
   else if(power == 0x05)
   {
       hSig
       SPI_Data = 0x01;
       SPI_Wait
       SPI_Data = 0xF8;
       SPI_Wait
       lSig

       addr_2thru8_off();
   }
   else if(power == 0x06)
   {
       hSig
       SPI_Data = 0x01;
       SPI_Wait
       SPI_Data = 0xFC;
       SPI_Wait
       lSig

       addr_2thru8_off();
   }
   else if(power == 0x07)
   {
       hSig
       SPI_Data = 0x01;
       SPI_Wait
       SPI_Data = 0xFE;
       SPI_Wait
       lSig

       addr_2thru8_off();
   }
   else if(power == 0x08)
   {
       hSig
       SPI_Data = 0x01;
       SPI_Wait
       SPI_Data = 0xFF;
       SPI_Wait
       lSig

       addr_2thru8_off();
   }
   else if(power == 0x09)  //second LED block
   {
       addr_on(0x01);

       hSig
       SPI_Data = 0x02;
       SPI_Wait
       SPI_Data = 0x80;
       SPI_Wait
       lSig

       addr_3thru8_off();
   }
   else if(power == 0x0A)
   {
       addr_on(0x01);

       hSig
       SPI_Data = 0x02;
       SPI_Wait
       SPI_Data = 0xC0;
       SPI_Wait
       lSig

       addr_3thru8_off();
   }
   else if(power == 0x0B)
   {
       addr_on(0x01);

       hSig
       SPI_Data = 0x02;
       SPI_Wait
       SPI_Data = 0xE0;
       SPI_Wait
       lSig

       addr_3thru8_off();
   }
   else if(power == 0x0C)
   {
       addr_on(0x01);

       hSig
       SPI_Data = 0x02;
       SPI_Wait
       SPI_Data = 0xF0;
       SPI_Wait
       lSig

       addr_3thru8_off();
   }
   else if(power == 0x0D)
   {
       addr_on(0x01);

       hSig
       SPI_Data = 0x02;
       SPI_Wait
       SPI_Data = 0xF8;
       SPI_Wait
       lSig

       addr_3thru8_off();
   }
   else if(power == 0x0E)
   {
       addr_on(0x01);

       hSig
       SPI_Data = 0x02;
       SPI_Wait
       SPI_Data = 0xFC;
       SPI_Wait
       lSig

       addr_3thru8_off();
   }
   else if(power == 0x0F)
   {
       addr_on(0x01);

       hSig
       SPI_Data = 0x02;
       SPI_Wait
       SPI_Data = 0xFE;
       SPI_Wait
       lSig

       addr_3thru8_off();
   }
   else if(power == 0x10)
   {
       addr_on(0x01);

       hSig
       SPI_Data = 0x02;
       SPI_Wait
       SPI_Data = 0xFF;
       SPI_Wait
       lSig

       addr_3thru8_off();
   }
   else if(power == 0x11)  //third LED block
   {
       addr_1thru2_on();

       hSig
       SPI_Data = 0x03;
       SPI_Wait
       SPI_Data = 0x80;
       SPI_Wait
       lSig

       addr_4thru8_off();
   }
   else if(power == 0x12)
   {
       addr_1thru2_on();

       hSig
       SPI_Data = 0x03;
       SPI_Wait
       SPI_Data = 0xC0;
       SPI_Wait
       lSig

       addr_4thru8_off();
   }
   else if(power == 0x13)
   {
       addr_1thru2_on();

       hSig
       SPI_Data = 0x03;
       SPI_Wait
       SPI_Data = 0xE0;
       SPI_Wait
       lSig

       addr_4thru8_off();
   }
   else if(power == 0x14)
   {
       addr_1thru2_on();

       hSig
       SPI_Data = 0x03;
       SPI_Wait
       SPI_Data = 0xF0;
       SPI_Wait
       lSig

       addr_4thru8_off();
   }
   else if(power == 0x15)
   {
       addr_1thru2_on();

       hSig
       SPI_Data = 0x03;
       SPI_Wait
       SPI_Data = 0xF8;
       SPI_Wait
       lSig

       addr_4thru8_off();
   }
   else if(power == 0x16)
   {
       addr_1thru2_on();

       hSig
       SPI_Data = 0x03;
       SPI_Wait
       SPI_Data = 0xFC;
       SPI_Wait
       lSig

       addr_4thru8_off();
   }
   else if(power == 0x17)
   {
       addr_1thru2_on();

       hSig
       SPI_Data = 0x03;
       SPI_Wait
       SPI_Data = 0xFE;
       SPI_Wait
       lSig

       addr_4thru8_off();
   }
   else if(power == 0x18)
   {
       addr_1thru2_on();

       hSig
       SPI_Data = 0x03;
       SPI_Wait
       SPI_Data = 0xFF;
       SPI_Wait
       lSig

       addr_4thru8_off();
   }
   else if(power == 0x19)  //fourth LED block
   {
       addr_1thru3_on();

       hSig
       SPI_Data = 0x04;
       SPI_Wait
       SPI_Data = 0x80;
       SPI_Wait
       lSig

       addr_5thru8_off();
   }
   else if(power == 0x1A)
   {
       addr_1thru3_on();

       hSig
       SPI_Data = 0x04;
       SPI_Wait
       SPI_Data = 0xC0;
       SPI_Wait
       lSig

       addr_5thru8_off();
   }
   else if(power == 0x1B)
   {
       addr_1thru3_on();

       hSig
       SPI_Data = 0x04;
       SPI_Wait
       SPI_Data = 0xE0;
       SPI_Wait
       lSig

       addr_5thru8_off();
   }
   else if(power == 0x1C)
   {
       addr_1thru3_on();

       hSig
       SPI_Data = 0x04;
       SPI_Wait
       SPI_Data = 0xF0;
       SPI_Wait
       lSig

       addr_5thru8_off();
   }
   else if(power == 0x1D)
   {
       addr_1thru3_on();

       hSig
       SPI_Data = 0x04;
       SPI_Wait
       SPI_Data = 0xF8;
       SPI_Wait
       lSig

       addr_5thru8_off();
   }
   else if(power == 0x1E)
   {
       addr_1thru3_on();

       hSig
       SPI_Data = 0x04;
       SPI_Wait
       SPI_Data = 0xFC;
       SPI_Wait
       lSig

       addr_5thru8_off();
   }
   else if(power == 0x1F)
   {
       addr_1thru3_on();

       hSig
       SPI_Data = 0x04;
       SPI_Wait
       SPI_Data = 0xFE;
       SPI_Wait
       lSig

       addr_5thru8_off();
   }
   else if(power == 0x20)
   {
       addr_1thru3_on();

       hSig
       SPI_Data = 0x04;
       SPI_Wait
       SPI_Data = 0xFF;
       SPI_Wait
       lSig

       addr_5thru8_off();
   }
   else if(power == 0x21)  //fifth LED block
   {
       addr_1thru4_on();

       hSig
       SPI_Data = 0x05;
       SPI_Wait
       SPI_Data = 0x80;
       SPI_Wait
       lSig

       addr_6thru8_off();
   }
   else if(power == 0x22)
   {
       addr_1thru4_on();

       hSig
       SPI_Data = 0x05;
       SPI_Wait
       SPI_Data = 0xC0;
       SPI_Wait
       lSig

       addr_6thru8_off();
   }
   else if(power == 0x23)
   {
       addr_1thru4_on();

       hSig
       SPI_Data = 0x05;
       SPI_Wait
       SPI_Data = 0xE0;
       SPI_Wait
       lSig

       addr_6thru8_off();
   }
   else if(power == 0x24)
   {
       addr_1thru4_on();

       hSig
       SPI_Data = 0x05;
       SPI_Wait
       SPI_Data = 0xF0;
       SPI_Wait
       lSig

       addr_6thru8_off();
   }
   else if(power == 0x25)
   {
       addr_1thru4_on();

       hSig
       SPI_Data = 0x05;
       SPI_Wait
       SPI_Data = 0xF8;
       SPI_Wait
       lSig

       addr_6thru8_off();
   }
   else if(power == 0x26)
   {
       addr_1thru4_on();

       hSig
       SPI_Data = 0x05;
       SPI_Wait
       SPI_Data = 0xFC;
       SPI_Wait
       lSig

       addr_6thru8_off();
   }
   else if(power == 0x27)
   {
       addr_1thru4_on();

       hSig
       SPI_Data = 0x05;
       SPI_Wait
       SPI_Data = 0xFE;
       SPI_Wait
       lSig

       addr_6thru8_off();
   }
   else if(power == 0x28)
   {
       addr_1thru4_on();

       hSig
       SPI_Data = 0x05;
       SPI_Wait
       SPI_Data = 0xFF;
       SPI_Wait
       lSig

       addr_6thru8_off();
   }
   else if(power == 0x29)  //sixth LED block
   {
       addr_1thru5_on();

       hSig
       SPI_Data = 0x06;
       SPI_Wait
       SPI_Data = 0x80;
       SPI_Wait
       lSig

       addr_7thru8_off();
   }
   else if(power == 0x2A)
   {
       addr_1thru5_on();

       hSig
       SPI_Data = 0x06;
       SPI_Wait
       SPI_Data = 0xC0;
       SPI_Wait
       lSig

       addr_7thru8_off();
   }
   else if(power == 0x2B)
   {
       addr_1thru5_on();

       hSig
       SPI_Data = 0x06;
       SPI_Wait
       SPI_Data = 0xE0;
       SPI_Wait
       lSig

       addr_7thru8_off();
   }
   else if(power == 0x2C)
   {
       addr_1thru5_on();

       hSig
       SPI_Data = 0x06;
       SPI_Wait
       SPI_Data = 0xF0;
       SPI_Wait
       lSig

       addr_7thru8_off();
   }
   else if(power == 0x2D)
   {
       addr_1thru5_on();

       hSig
       SPI_Data = 0x06;
       SPI_Wait
       SPI_Data = 0xF8;
       SPI_Wait
       lSig

       addr_7thru8_off();
   }
   else if(power == 0x2E)
   {
       addr_1thru5_on();

       hSig
       SPI_Data = 0x06;
       SPI_Wait
       SPI_Data = 0xFC;
       SPI_Wait
       lSig

       addr_7thru8_off();
   }
   else if(power == 0x2F)
   {
       addr_1thru5_on();

       hSig
       SPI_Data = 0x06;
       SPI_Wait
       SPI_Data = 0xFE;
       SPI_Wait
       lSig

       addr_7thru8_off();
   }
   else if(power == 0x30)
   {
       addr_1thru5_on();

       hSig
       SPI_Data = 0x06;
       SPI_Wait
       SPI_Data = 0xFF;
       SPI_Wait
       lSig

       addr_7thru8_off();
   }
   else if(power == 0x31)  //seventh LED block
   {
       addr_1thru6_on();

       hSig
       SPI_Data = 0x07;
       SPI_Wait
       SPI_Data = 0x80;
       SPI_Wait
       lSig

       addr_off(0x08);
   }
   else if(power == 0x32)
   {
       addr_1thru6_on();

       hSig
       SPI_Data = 0x07;
       SPI_Wait
       SPI_Data = 0xC0;
       SPI_Wait
       lSig

       addr_off(0x08);
   }
}

//////////////////////////// Vibration ////////////////////////////////////////
void haptic(void)
{

    if(hapleft)
    {

            Left_Shoulder = 1; //turns on pin 2
            Delay10KTCYx(40); //On time
            Left_Shoulder = 0;
            Delay10KTCYx(10); //Delay until next packet
            hapleft = hapleft - 1;

    }
    if(hapright)
    {

        Right_Shoulder = 1; //turns on pin 3
        Delay10KTCYx(40); //On time
        Right_Shoulder = 0;
        Delay10KTCYx(10); //Delay until next packet
        hapright = hapright - 1;

    }
    if(hapfront)
    {

        Chest = 1; //turns on pin 4
        Delay10KTCYx(40); //On time
        Chest = 0;
        Delay10KTCYx(10); //Delay until next packet
        hapfront = hapfront - 1;

    }
    if(hapback)
    {

        Back = 1; //turns on pin 5
        Delay10KTCYx(40); //On time
        Back = 0;
        Delay10KTCYx(10); //Delay until next packet
        hapback = hapback - 1;

    }


}
//////////////////////// CAN /////////////////////////////////////////////////
void MCANinit()
{
    //TRISAbits.TRISA1=0;                 //set pin 3 as output
    //TRISB |= 0x08; // Sets TXD pin to output, RXD pin to input

    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 0;

    CANCON = 0x80; // Requests configuration mode
    while(CANSTAT!=0x80)                // Waits until request for configuration mode is honored

    ECANCONbits.MDSEL0 = 0;	 // Selects mode 0
    ECANCONbits.MDSEL1 = 0;	 // Selects mode 0

    BRGCON1 = 0x07;
    BRGCON2 = 0x83;
    BRGCON3 = 0x01;

    //Initialize receive masks - disabled
    RXM0EIDH = 0x00;
    RXM0EIDL = 0x00;
    RXM0SIDH = 0x00;
    RXM0SIDL = 0x00;

    RXM1EIDH = 0x00;
    RXM1EIDL = 0x00;
    RXM1SIDH = 0x00;
    RXM1SIDL = 0x00;

    RXFCON0 = 0x00;                     //Initializes and disabled filters
    RXFCON1 = 0x00;                     //Initializes and disabled filters

    CANCON = 0x00;	 // Requests normal mode
    while(CANSTAT!=0x00);	 // Waits until request for normal mode is honored

    RXB0CON = 0x60;	 // Set to receive all messages
    RXB1CON = 0x60;	 // Set to receive all messages
}

void sendImDead()
{
    TXB0EIDH = 0x00;
    TXB0EIDL = 0x00;
    TXB0SIDH = 0x00;
    TXB0SIDL = 0x00;
    TXB0DLC = 0x02;
    TXB0D0 = 0xF0;
    TXB0D1 = 0xFE;
    TXB0CONbits.TXREQ = 1;
}