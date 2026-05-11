/*
 * File:   lab4.c
 * Author: je-me
 *
 * Created on 12 de febrero de 2025, 07:45 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#define _XTAL_FREQ 1000000
#include "libLCD.h"
#pragma config FOSC=INTOSC_EC
#pragma config WDT=OFF
#pragma  config PBADEN=OFF
#pragma config LVP=OFF
#define ConteoTRIS TRISCbits.RC0 // conteo 
#define Conteo PORTCbits.RC0
#define TRIGGER RC0
#define ECHO RC1
void interrupt ISR(void);
void Timer0_16bits(void);

void Display7Seg(void);
void Reiniciar_Timer0(void);
void ReiniciarLCD_RGB(void);
void ConfiguracionRS232(void);
void Transmitir(unsigned char);
void Detectar(char dist);
unsigned char Recibir(void);
unsigned int Conversion(unsigned char);
char LeerRS232(void);

void ConfiguracionADC(void);

void ConfiguracionPWM(void);

void TransmitirCadena(const char *BufferT);

void EnviarDutyCycle(uint8_t duty);

void LeerRX(void);
void LeerPotenciometro(void);
unsigned char MedirDistancia(void);

void prueba(void);

int seccion=1;
int condicion;
int bandera=0;
int Tecla=99;
int contador=0;
int contados;
int faltan;
int ciclo=1;
char buffer[10];
int objetivo=0;
char tiempo=0;
int presencia=0;


unsigned char display[10]={0x00, 0x01, 0x02, 0x03,0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
unsigned char rgb[6]={0b00000010, 0b00000011, 0b00000001, 0b0000101, 0b000000100, 0b00000000};
unsigned char etimeout=0,ctimeout=0;
char i=0;
char r=0;
int veces=4;
unsigned int resultado1,resultado2,resultado3;

const char custom[] = {
    0b01010,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000,
    0b00100,
    0b00100,0
};



void main(void) {
    
    unsigned char i;
    
    TRISB=0b11110000;
    TRISD=0;
    LATB=0b00000000;
    LATD=0;
    RBPU=0;
    __delay_ms(300);
    RBIF=0;
    RBIE=1;
    GIE=1;
    //ADCON1=0X0F; //QUITAR FUNCIONES ANBALOGAS
    //Puerto A
    TRISA=0;
    TRISA0=1;
    //ConteoTRIS=1;
    TRISC0=0;
    
    //PINES DE CONFIGURACION DE TRANSMISION
    TRISC7=1;
    TRISC6=1;
            
    
    
    LATA1=1;
    
    LATE=0b00000111;
    TRISE0=0;
    TRISE1=0;
    TRISE2=0;
    
    
    
    // Timer
    
    //FinishConf
    
    LCD_init();
    
    
    
    LCD_CGRAM(custom,0);
    
    LCD_Comando(0x01);
    
    
    
    LCD_IZ(0);
    LCD_DER(0);
    
    Timer0_16bits();
    
    ConfiguracionRS232();
    
    ConfiguracionADC();
    
    
    //prueba();
    
    ConfiguracionPWM();
    
    //prueba();
    
    
    //resultado1=Conversion(0);
    
    //char buffer[2];
    
    //itoa(buffer,resultado1,10);
    
    //LCD_Comando(0x01);
    
    //LCD_XY(0,0);
    
    //LCD_Cadena(buffer);
    //__delay_ms(10000);
        
    
    LCD_XY(0,0);
    LCD_Cadena("Hola a todos");
    LCD_XY(1,0);
    LCD_Cadena("Guapisimos");
    __delay_ms(5000);
    seccion=2;
    
    
    
    
    
    //resultado1=Conversion(0);
    
    //char buffer[2];
    
    //itoa(buffer,resultado1,10);
    
    //LCD_Comando(0x01);
    
    //LCD_XY(0,0);
    
    //LCD_Cadena(buffer);
    //__delay_ms(10000);
    
    
    
    
    while(1){
    switch (seccion){ 
        case 2://seteo numero  
            LCD_Comando(0x01);
            LCD_XY(0,0);
            LCD_Cadena("Piezas a contar:");
            __delay_ms(2000);
            LCD_XY(1,0);
            int arreglo[2];
            contador=0;
            objetivo=0;
            ciclo=1;
             while(ciclo==1){
                if(Tecla!=99){                  
                    if(contador==2){
                        if(Tecla==10){ //Borrado
                            contador=contador-1;
                            LCD_XY(1,(contador));
                            LCD_Cadena(" ");
                        }
                        else if(Tecla==16){ //OK
                            objetivo=(arreglo[0]*10)+(arreglo[1]);
                            if(objetivo>=1&&objetivo<=59){
                                ciclo=0;
                            }
                            else{//error valor fuera de rango
                                arreglo[0]=0;
                                arreglo[1]=0;
                                LCD_XY(1,0);
                                LCD_Cadena(" ");
                                LCD_XY(1,1);
                                LCD_Cadena(" ");
                                LCD_XY(1,0);
                                LCD_Cadena("Valor off-limit");
                                __delay_ms(1000);
                                LCD_XY(1,0);
                                LCD_Cadena("                ");
                                contador=0;
                                
                            }
                        }
                        else{ //Error numero mal digitado
                            arreglo[0]=0;
                            arreglo[1]=0;
                            LCD_XY(1,0);
                            LCD_Cadena(" ");
                            LCD_XY(1,1);
                            LCD_Cadena(" ");
                            LCD_XY(1,0);
                            LCD_Cadena("Mal digitado");
                            __delay_ms(1000);
                            LCD_XY(1,0);
                            LCD_Cadena("                ");
                            contador=0;

                        }
                    }
                    else{
                        switch(Tecla){
                            case 10:
                                //borrar
                                contador=contador-1;
                                LCD_XY(1,(contador));
                                LCD_Cadena(" ");
                                break;
                            case 11:
                                //nada
                                break;
                            case 12:
                                //nada
                                break;
                            case 13:
                                //Parado de emergencia (implementado en interrupcion))
                                break;
                            case 14:// tecla 0
                                arreglo[contador]=0;
                                LCD_XY(1,contador);
                                LCD_Cadena("0");
                                contador=contador+1;
                                //mostrar 0 en pantalla
                                break;
                            case 15:
                                //nada
                                break;
                            case 16:
                                 //nada
                                break;
                            default: //teclas 1 al 9
                                arreglo[contador]=Tecla;
                                LCD_XY(1,contador);
                                char buffer[1];
                                itoa(buffer,Tecla,10);
                                LCD_Cadena(buffer);
                                contador=contador+1;
                                break;
                        }
                    } 
                }
                Tecla=99;
            }
            seccion=3;
            break;
        case 3:
            //Seccion 3 conteo
            LCD_Comando(0x01);
            LCD_XY(0,0);
            LCD_Cadena("Objetivo:");
            char buffer[2];
            itoa(buffer,objetivo,10);
            LCD_XY(0,13);
            LCD_Cadena(buffer);
            LCD_XY(1,0);
            LCD_Cadena("Faltan:");
            contados=0;
            char buffer[2];
            itoa(buffer,objetivo,10);
            LCD_XY(1,13);
            LCD_Cadena(buffer);
            condicion=1;
            while(seccion==3){
                char distancia=MedirDistancia();
                Detectar(distancia);
                __delay_ms(100);
                //itoa(buffer,distancia,10);
                //LCD_XY(0,13);
                //LCD_Cadena("  ");
                //LCD_XY(0,11);
                //LCD_Cadena(buffer);
                if (presencia==1){
                    while(condicion==1){
                        char distancia=MedirDistancia();
                        Detectar(distancia);
                        __delay_ms(100);
                        if(presencia==0){    
                            condicion=0;
                            contados=contados+1;
                            faltan=objetivo-contados;
                            Display7Seg();
                            //Reiniciar_Timer0();
                            char buffer[2];
                            itoa(buffer,faltan,10);
                            LCD_XY(1,13);
                            LCD_Cadena("  ");
                            LCD_XY(1,13);
                            LCD_Cadena(buffer);
                            if(contados==objetivo){
                                seccion=4;
                            }    
                        }                       
                    }
                }
                condicion=1;
            }
            break;
        case 4:
            LCD_Comando(0x01);
            while(seccion==4){
            LCD_XY(0,0);
            LCD_Cadena("YIPEEEEEEE");
            
            if(Tecla==16)
            {
                ReiniciarLCD_RGB();
                seccion=2;
                
                
            }
            }
            break;
       
    }       
}
}    

void interrupt ISR(void){
    
    
    if(RBIF==1){
        
        if(PORTB!=0b11110000){
            Tecla=0;
            LATB=0b11111110;
            if(RB4==0){
                //Reiniciar_Timer0();
                Tecla=1;
            }
            else if(RB5==0)
            {
                //Reiniciar_Timer0();
                Tecla=2;
                
            } 
            else if(RB6==0)
            {
                Tecla=3;
                //Reiniciar_Timer0();
                
            } 
            else if(RB7==0)
            {
                Tecla=10;//BORRADO
                //Reiniciar_Timer0();
                
            }
            else{
                LATB=0b11111101;
                if(RB4==0)
                {
                    //Reiniciar_Timer0();
                    Tecla=4;
                }
                else if(RB5==0)
                {
                    //Reiniciar_Timer0();
                    Tecla=5;
                }
                else if(RB6==0)
                {
                    //Reiniciar_Timer0();
                    Tecla=6;
                }
                else if(RB7==0)
                {
                    //Reiniciar_Timer0();
                    Tecla=11;//FINALIZAR CONTEO
                    if(seccion==3){
                        condicion=0;
                        i=objetivo%10;
                        LATD=display[i];
                        r=objetivo/10;
                        LATE=rgb[r];
                        
                                
                        seccion=4;
                        
                    }
                    
                }
                else{
                    LATB=0b11111011;
                    if(RB4==0)
                    {
                        //Reiniciar_Timer0();
                        Tecla=7;
                    } 
                    else if(RB5==0)
                    {
                        //Reiniciar_Timer0();
                        Tecla=8;
                    }
                    else if(RB6==0)
                    {
                        //Reiniciar_Timer0();
                        Tecla=9;
                    } 
                    else if(RB7==0){ 
                        Tecla=12;//REINICIAR
                        if(seccion==3){
                            contados=0;
                            faltan=objetivo;
                            char buffer[2];
                            itoa(buffer,faltan,10);
                            LCD_XY(1,13);
                            LCD_Cadena("  ");
                            LCD_XY(1,13);
                            LCD_Cadena(buffer);
                            ReiniciarLCD_RGB();
                            int condicion=1;
                        }
                    } 
                    else{
                        LATB=0b11110111;
                        if(RB4==0){ //presionado tecla 13 parado de emergencia
                           Tecla=13;
                           LCD_Comando(0x01);
                           LCD_XY(0,0);
                           LCD_Cadena("Parado de ");
                           LCD_XY(1,0);
                           LCD_Cadena("Emergencia");
                           LATEbits.LATE0=0;
                           LATEbits.LATE1=1;
                           LATEbits.LATE2=1;
                           while(1){}
                        }
                        else if(RB5==0)
                        {
                            //Reiniciar_Timer0();
                            Tecla=14;//0
                        }
                        else if(RB6==0)
                        {
                            LATA1=~RA1;//LUZ
                            Tecla=15;
                        } 
                        else if(RB7==0)
                        {
                            //Reiniciar_Timer0();
                            Tecla=16;//OK
                        } 
                    }
                }
            }
            LATB=0b11110000;
        }
        __delay_ms(100);
        RBIF=0;
    }
    else if(TMR0IF==1)
    {
        //LeerPotenciometro();
        
        //LeerRX();
        
                
        TMR0IF=0;
        TMR0=63582;
        LATA3=~RA3;
        tiempo++;
        if(tiempo==10)
        {
            //LATA1=0;
        }
        else if(tiempo==20)      
        {
            //SLEEP();   
        }
}
}
void Timer0_16bits(void)
{
    T0CON=0b00000110;
    TMR0=63582;
    TMR0IE=1;
    TMR0IF=0;
    TMR0ON=1;
    
}

void Display7Seg()
{
    if(i==9)
    {
        i=0;
        if(r!=5)
        {
            r++;
            LATA2=1;
            __delay_ms(100);
            LATA2=0;
            
        }
        else
        {
            r=0;
            LATA2=1;
            __delay_ms(300);
            LATA2=0;
        }
    }
    else
    {
        i++;
    }
    LATD=display[i];
    LATE=rgb[r];
}

void Reiniciar_Timer0(void)
{
    tiempo=0;
    RA1=1;
}

void ReiniciarLCD_RGB(void)
{
    i=0;
    r=0;
    LATD=display[i];
    LATE=rgb[r];
}

unsigned int Conversion(unsigned char canal){
    ADCON0=(ADCON0 & 0b00000011) | (canal<<2); // Con esto yo esperaria elegir el canal por el
    GO=1;   //bsf ADCON0,1                     // cual yo estoy leyendo mis valores de ADC
    while(GO==1);
    return ADRES;
}

void ConfiguracionRS232(void)
{
    //TXSTA=0b00100100;
    //RCSTA=0b10000000;        
    //BAUDCON=0b00001000;        
    //SPBRG=25;
    TXSTA=0b00100100;
    RCSTA=0b10010000;        
    BAUDCON=0b00001000;        
    SPBRG=25;
}

void ConfiguracionADC(void)
{
    ADCON0=0b00000001;
    ADCON1=13;
    ADCON2=0b10001000;
    
}


unsigned char Recibir(void){
    while(RCIF==0);
    return RCREG;
}

void Transmitir(unsigned char BufferT){
    while(TRMT==0);
    TXREG=BufferT;
}

void TransmitirCadena(const char *BufferT) {
    while (*BufferT) {  // Mientras no sea el carácter nulo '\0'
        while (TXSTAbits.TRMT == 0); // Esperar a que el buffer de transmisión esté libre
        TXREG = *BufferT;  // Enviar carácter
        BufferT++;  // Pasar al siguiente carácter
    }
}

void ConfiguracionPWM(void)
{
    
    PR2=249;  /// Este registro es para configurar el periodo de la señal
    
    TRISC2=0;
    
    CCPR1L=100;  // DEFINIENDO EL DUTY CICLE
    
    T2CON=0b00000000; // REGISTRO PARA DEFINIR EL TIMMER 2, PRESCALER :1 Y TIMMER OFF
    
    TMR2=0;  // TIMER 2 OFF
    
    CCP1CON=0b00001100;  
    
    TMR2ON=1; // TIMER 2 ON
    
    
}

void prueba(void)
{
    /*  
    while(1)
    {
        
        resultado1=Conversion(0);
    
        char buffer[2];
    
        itoa(buffer,resultado1,10);
    
        LCD_Comando(0x01);
    
        LCD_XY(0,0);
    
        LCD_Cadena(buffer);
    }
     */
    while(1)
    {
        char distancia=MedirDistancia();
        Detectar(distancia);
        char buffer[2];
        itoa(buffer,distancia,10);
        if (presencia==1){
            LCD_Comando(0x01);
            LCD_XY(0,0);
            LCD_Cadena("DETECTADO");   
            LCD_XY(1,0);
            LCD_Cadena(buffer);   
        }
        else if(presencia==0){
            LCD_Comando(0x01);
            LCD_XY(0,0);
            LCD_Cadena("NO DETECTADO");
            LCD_XY(1,0);
            LCD_Cadena(buffer);   
        }
        else{
            LCD_Comando(0x01);
            LCD_XY(0,0);
            LCD_Cadena("PAPI QUE PUTAS");
            LCD_XY(1,0);
            LCD_Cadena(buffer);
        }
    }
    
}

void EnviarDutyCycle(uint8_t duty) {
    char buffer[10];  
    sprintf(buffer, "Duty: %d\r\n", duty);  // Convertir duty a cadena
    TransmitirCadena(buffer);  // Enviar la cadena por RS232
}

char LeerRS232(void)
{
    return RCREG;
}

void LeerPotenciometro(void)
{
    resultado1=Conversion(0);
    resultado3 = ((250.0 / 1100) * resultado1);
    CCPR2L = resultado3;
    EnviarDutyCycle(resultado3);
}

void LeerRX(void)
{
    while(RCIF==1)
    {
        
            if(RCREG=='X')
            {
                CCPR2L=40;
                EnviarDutyCycle(CCPR2L);
                
            }
            if(RCREG=='Z')
            {
                CCPR2L=50;
                EnviarDutyCycle(CCPR2L);
                
            }
            if(RCREG=='C')
            {
                CCPR2L=100;
                EnviarDutyCycle(CCPR2L);
                
            }
            if(RCREG=='V')
            {
                CCPR2L=150;
                EnviarDutyCycle(CCPR2L);
                
            }
            if(RCREG=='B')
            {
                CCPR2L=200;
                EnviarDutyCycle(CCPR2L);
                
            }
            if(RCREG=='N')
            {
                CCPR2L=240;
                EnviarDutyCycle(CCPR2L);
                
            }
        }
}

unsigned char MedirDistancia(void){
  unsigned char aux=0;
  CCP2CON=0b00000100; //Ajustar CCP en modo captura con flanco de bajada
  TMR1=0;             //Iniciamos el timer1 en 0
  CCP2IF=0;           //Iniciar bandera CCPx en 0
  TRIGGER=1;          //Dar inicio al sensor
  __delay_us(10);
  TRIGGER=0;
  etimeout=1;         //Se habilita la condición de antibloqueo
  while(ECHO==0  /* && etimeout==1*/); //Se espera que el sensor empiece la
                     //medición o que pase el antibloqueo (aprox 2s)
  if(etimeout==0){    //Si el sensor no responde se retorna un 0
    return 0;
  }    
  TMR1ON=1;           //Se da inicio al timer1 o medición de tiempo
  while(CCP2IF==0 && TMR1IF==0);   //Espera a que la señal de ultrasonido regrese
  TMR1ON=0;           //Se da parada al timer 1 o medición de tiempo
  if(TMR1IF==1)       //Se comprueba que la medición del pulso del sensor no
    aux=255;          //exceda el rango del timer1, si es asi se limita a 255
  else{  
    if(CCPR2>=3556)  //Si el sensor excede 254cm se limita a este valor
      CCPR2=3556;
    aux=CCPR2/(14) ; //Se calcula el valor de distancia a partir del tiempo
  }
  return aux;         //Se retorna la medición de distancia obtenida
  
}
void Detectar(char dist){ // HAY QUE DECLARAR PRESENCIA COMO GLOBAL =0 EN EL PROGRAMA PIRNCIPAL-
   // Presencia=0 no detectado; =1 detectado
    if(presencia==0 && dist>=0 && dist<=5){
        presencia=1;
    }
    else if(presencia==1 && dist>9){
        presencia=0;
    }
}


