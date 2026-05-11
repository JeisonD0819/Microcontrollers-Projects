//DATA RD4-RD7
//CONTROL A3 A4
#define D4 LATDbits.LATD4
#define D4_TRIS TRISDbits.RD4
#define D5 LATDbits.LATD5
#define D5_TRIS TRISDbits.RD5
#define D6 LATDbits.LATD6
#define D6_TRIS TRISDbits.RD6
#define D7 LATDbits.LATD7
#define D7_TRIS TRISDbits.RD7
#define EN LATAbits.LATA4
#define EN_TRIS TRISAbits.RA4
#define RS LATAbits.LATA5
#define RS_TRIS TRISAbits.RA5
#define E LATA4
#define RS LATA5
#define LCD_PORT LATD
#define LCD_TRIS TRISD


void LCD_init(void);
void LCD_Comando(char);
void LCD_Caracter(char);
void LCD_XY(int x, int y);
void LCD_Cadena(char *dat);
void LCD_CGRAM(const char *buffer,char add);
void LCD_CGRAM_ADDR(char CGAddr);
void LCD_IZ(char);


void LCD_init(void)
{
    LCD_TRIS=0x00;
    
    LCD_Comando(0x30);
    __delay_ms(5);
    LCD_Comando(0x30);
    __delay_ms(1);
    LCD_Comando(0x32);// el "2" indica que la configuracion es de 4 BITS
    LCD_Comando(0x28); // 2 Lineas 5X8
    LCD_Comando(0x0C);  // DISPLAY ON CURSOR OFF
    LCD_Comando(0x01); // Display Clear
    LCD_Comando(0x06); // Incrementar DDRAM Y NO MOVIMIENTO 
}

void LCD_Comando(char cmd){
    
    RS=0;
    
    //Estamos dejando que los pines menos significativos permanezcan en lo que sea que esten
    // pues recordemos que los pines que utilizamos son D4-D7 osea que D3-D0 no se deben utilizar
    // asi que tienen que permanecer como sea que esten
    LCD_PORT= LCD_PORT & 0x0F;
    
    
    LCD_PORT=LCD_PORT | (cmd & 0xF0);
    
    // cmd = 0x03
    // Estoy utilizando 4 bits, entonces lo que envie se va a partir en 2
    // 4 bits -> RD4 - RD7
    
    __delay_ms(1);
    E=1;
    __delay_ms(1);
    E=0;
    
    
    //Corrimiento de el bus de datos
    
    LCD_PORT= LCD_PORT & 0x0F;
    
    LCD_PORT=LCD_PORT | (cmd << 4);
    
    __delay_ms(1);
    E=1;
    __delay_ms(1);
    E=0;
}

void LCD_Caracter(char data)
{
    RS=1; // MODO CARACTER

    LCD_PORT= LCD_PORT & 0x0F;
    
    
    LCD_PORT=LCD_PORT | (data & 0xF0);
    
    __delay_ms(1);
    E=1;
    __delay_ms(1);
    E=0;
    
    LCD_PORT= LCD_PORT & 0x0F;
    
    LCD_PORT=LCD_PORT | (data << 4);
    
    __delay_ms(1);
    E=1;
    __delay_ms(1);
    E=0;
    
}

void LCD_XY(int x, int y)
{
    // x Fila , y Columna
    
    if(x>0)
    {
        // Fila 2
        LCD_Comando(0xC0 + y);
        
    }
    else
    {
        // Fila 1
        LCD_Comando(0x80 + y);
        
    }
}

void LCD_Cadena(char *dat)
{
    // str /0 al final de una cadena siempre tenemos un nulo(\0)
    
    while(*dat != '\0')
    {
        LCD_Caracter(*dat);
        dat++;
    }
}
void LCD_CGRAM(const char *buffer,char add)
{
    char p=0;
    LCD_CGRAM_ADDR(add*8);
    for(p=0; p<8;p++)
    {
        LCD_Caracter(*buffer);
        buffer++;
    }
    
}
void LCD_CGRAM_ADDR(char CGAddr)
{
    RS=0; // MODO COMANDO

    LCD_PORT= LCD_PORT & 0x0F;
    
    
    LCD_PORT=LCD_PORT | ((CGAddr | 0b01000000) & 0xF0);
    
    __delay_ms(1);
    E=1;
    __delay_ms(1);
    E=0;
    
    LCD_PORT= LCD_PORT & 0x0F;
    
    LCD_PORT=LCD_PORT | (CGAddr << 4);
    
    __delay_ms(1);
    E=1;
    __delay_ms(1);
    E=0;
}
void LCD_IZ(char dat)
{
    for(int w=0; w<16; w++)
    {
        LCD_XY(0,w);
        LCD_Caracter(dat);
        __delay_ms(100);
        LCD_XY(0,w);
        LCD_Caracter(' ');
        __delay_ms(100);
        
    }
}

void LCD_DER(char dat)
{
    for(int r=16; r>0; r--)
    {
        LCD_XY(0,r);
        LCD_Caracter(dat);
        __delay_ms(100);
        LCD_XY(0,r);
        LCD_Caracter(' ');
        __delay_ms(100);
        
    }
}
