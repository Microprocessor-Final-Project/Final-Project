/*
 * Before run this program, make should that POT's resolution isn't greater than 128
 * or the result is undefined.
 */

#include <xc.h>
#include <pic18f4520.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma config OSC = INTIO67    // Oscillator Selection bits
#pragma config WDT = OFF        // Watchdog Timer Enable bit 
#pragma config PWRT = OFF       // Power-up Enable bit
#pragma config BOREN = ON       // Brown-out Reset Enable bit
#pragma config PBADEN = OFF     // Watchdog Timer Enable bit 
#pragma config LVP = OFF        // Low Voltage (single -supply) In-Circute Serial Pragramming Enable bit
#pragma config CPD = OFF        // Data EEPROM?Memory Code Protection bit (Data EEPROM code protection off)
#define _XTAL_FREQ 125000

char mystring[20];
int lenStr = 0;
char rec_char = '\0';
unsigned int value;
int OUTPUT_flag = 0;
void Print_Morse(char* str);
char morse_code_check(char* str);
void UART_Write(unsigned char data) {
    while(!PIR1bits.TXIF);
    TXREG = data;
}

void UART_Write_Text(char* text) {
    for(int i=0; text[i] != '\0'; i++){
        UART_Write(text[i]);
    }
}

void ClearBuffer(){
    for(int i = 0; i < 20 ; i++){
        mystring[i] = '\0';
    }
    lenStr = 0;
}
void Print_Morse(char* str) {    
    //* The char* str requirements:
    // 1. The string must be a morse code string with 0 and 1
    // 2. The string must be null-terminated (like "101010\0", not "101010\n" or "101010")
    
    // accordig to the lenStr value, backspace the number of characters on the screen
    int strLen = strlen(str);
    for (int i = 0; i < strLen; i++) {
        UART_Write('\b');       // Send backspace character
        UART_Write(' ');        // Send space character
        UART_Write('\b');       // Send backspace character
    }
    
    char decoded_char = morse_code_check(str);
    if (decoded_char == '\n') {
        UART_Write('\r');
        UART_Write('\n');
    } else {
        UART_Write(decoded_char);
    }

    ClearBuffer();              // clear the string buffer
    return;
}
//? Check the morse code
char morse_code_check(char* str) {
    //* Use the length of the string to determine the morse code
    // I use 'X' as the default return value if the input is not a valid morse code
    // Input: a character string of 0 and 1
    // Output: a character
    switch (strlen(str)) {
        case 1:
            if (strcmp(str, "0") == 0) return 'e';
            if (strcmp(str, "1") == 0) return 't';
            return 'X';
            break;
        case 2:
            if (strcmp(str, "01") == 0) return 'a';
            if (strcmp(str, "00") == 0) return 'i';
            if (strcmp(str, "11") == 0) return 'm';
            if (strcmp(str, "10") == 0) return 'n';
            return 'X';
            break;
        case 3:
            if (strcmp(str, "000") == 0) return 's';
            if (strcmp(str, "001") == 0) return 'u';
            if (strcmp(str, "010") == 0) return 'r';
            if (strcmp(str, "011") == 0) return 'w';
            if (strcmp(str, "100") == 0) return 'd';
            if (strcmp(str, "101") == 0) return 'k';
            if (strcmp(str, "110") == 0) return 'g';
            if (strcmp(str, "111") == 0) return 'o';
            return 'X';
            break;
        case 4:
            if (strcmp(str, "0000") == 0) return 'h';
            if (strcmp(str, "0001") == 0) return 'v';
            if (strcmp(str, "0010") == 0) return 'f';
            if (strcmp(str, "0100") == 0) return 'l';
            if (strcmp(str, "0110") == 0) return 'p';
            if (strcmp(str, "0111") == 0) return 'j';
            if (strcmp(str, "1000") == 0) return 'b';
            if (strcmp(str, "1001") == 0) return 'x';
            if (strcmp(str, "1010") == 0) return 'c';
            if (strcmp(str, "1011") == 0) return 'y';
            if (strcmp(str, "1100") == 0) return 'z';
            if (strcmp(str, "1101") == 0) return 'q';
            return 'X';
            break;
        case 5:
            if (strcmp(str, "11111") == 0) return '0';
            if (strcmp(str, "01111") == 0) return '1';
            if (strcmp(str, "00111") == 0) return '2';
            if (strcmp(str, "00011") == 0) return '3';
            if (strcmp(str, "00001") == 0) return '4';
            if (strcmp(str, "00000") == 0) return '5';
            if (strcmp(str, "10000") == 0) return '6';
            if (strcmp(str, "11000") == 0) return '7';
            if (strcmp(str, "11100") == 0) return '8';
            if (strcmp(str, "11110") == 0) return '9';
            if (strcmp(str, "10001") == 0) return '=';
            if (strcmp(str, "10010") == 0) return '/';
            if (strcmp(str, "10110") == 0) return '(';
            if (strcmp(str, "01000") == 0) return '&';
            if (strcmp(str, "01010") == 0) return '+';
            return 'X';
            break;
        case 6:
            if (strcmp(str, "010101") == 0) return '.';
            if (strcmp(str, "111000") == 0) return ':';
            if (strcmp(str, "110011") == 0) return ',';
            if (strcmp(str, "101010") == 0) return ';';
            if (strcmp(str, "001100") == 0) return '?';
            if (strcmp(str, "011110") == 0) return '\'';
            if (strcmp(str, "101011") == 0) return '!';
            if (strcmp(str, "100001") == 0) return '-';
            if (strcmp(str, "001101") == 0) return '_';
            if (strcmp(str, "010010") == 0) return '\"';
            if (strcmp(str, "101101") == 0) return ')';
            if (strcmp(str, "011010") == 0) return '@';
            return 'X';
            break;
        case 7:
            if (strcmp(str, "0001001") == 0) return '$';
            if (strcmp(str, "1001010") == 0) return '#';    // from here is extra decode value
            if (strcmp(str, "1010010") == 0) return '%';
            if (strcmp(str, "1010101") == 0) return '*';
            if (strcmp(str, "1011001") == 0) return '^';
            if (strcmp(str, "1011101") == 0) return '~';
            if (strcmp(str, "1100101") == 0) return '[';
            if (strcmp(str, "1101010") == 0) return ']';
            if (strcmp(str, "1101101") == 0) return '{';
            if (strcmp(str, "1110010") == 0) return '}';
            if (strcmp(str, "1110101") == 0) return '<';
            if (strcmp(str, "1111001") == 0) return '>';
            if (strcmp(str, "0000000") == 0) return ' ';
            if (strcmp(str, "0000001") == 0) return '\n';
            return 'X';
            break;
        default:
            return 'X';
            break;
    }
}
void MyusartRead(){
    rec_char = RCREG;
    mystring[lenStr] = rec_char;  // read the received character
    
    UART_Write(rec_char); // output the received character
    lenStr++;
    return;
}

char* GetString(){
    return mystring;
}
void Interrupt_Enable(){
    RCONbits.IPEN = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    INTCONbits.PEIE = 1; // Enable peripheral interrupts
    return;
}
void UART_Init(void){
    TRISCbits.TRISC6 = 1;            
    TRISCbits.TRISC7 = 1;            
    
    //  Setting baud rate
    TXSTAbits.SYNC = 0;           
    BAUDCONbits.BRG16 = 1;       
    TXSTAbits.BRGH = 1;         
    SPBRG = 25;        
    SPBRGH = 0;
    
    RCSTAbits.SPEN = 1;    
    PIR1bits.TXIF = 1;
    PIR1bits.RCIF = 0;
    TXSTAbits.TXEN = 1;    
    RCSTAbits.CREN = 1;      

    // PIE1bits.TXIE = 0;       
    // IPR1bits.TXIP = 0;    
    PIE1bits.RCIE = 1;          
    IPR1bits.RCIP = 0;  // low priority
}
void ADC_init(void){
    ADCON1 = 0x0E;
    ADCON0bits.CHS = 0b0000;  //AN0 as analog input
    ADCON2bits.ADCS = 0b000;  //set 000 since 125kHz < 2.86MHZ -> Tad = 2 * 8 us
    ADCON2bits.ACQT = 0b001;  //Tad = 16 us acquisition time: 2Tad = 32 > 2.4
    ADCON0bits.ADON = 1;
    ADCON2bits.ADFM = 0;    //left justified 
    
    PIR1bits.ADIF = 0;
    IPR1bits.ADIP = 0;   //LOW priority
    PIE1bits.ADIE = 1;
}
void PORT_init(void){
    TRISA = 1;
    LATAbits.LA3 = 0;
}
void __interrupt(high_priority)H_ISR(){
    return;
}

void __interrupt(low_priority)L_ISR(){
    if(PIR1bits.ADIF){
        PIR1bits.ADIF = 0;
        value = ADRESH;
        if(value <= 128){
            // Input mode
            LATAbits.LA3 = 1;
            OUTPUT_flag = 0;
        }else{
            // Output mode
            LATAbits.LA3 = 0;
            if(!OUTPUT_flag && mystring[0]!='\0'){
                mystring[lenStr] = '\0';
                Print_Morse(mystring);
            }
            OUTPUT_flag = 1;
        }
        __delay_us(100);
        ADCON0bits.GO = 1;
    }
    if(OUTPUT_flag){
        // This statement should just follow the ADIF block
        return;
    }
    
    if(PIR1bits.RCIF){
        MyusartRead(); // Call the function to read the received character
        PIR1bits.RCIF = 0; // Clear the interrupt flag
    }
    return;
}
void main(void){
    // Tosc = 125kHz
    OSCCONbits.IRCF = 0b001;
    ADC_init();
    PORT_init();
    UART_Init();
    Interrupt_Enable();
    ADCON0bits.GO = 1;
    while(1);
    return;
}