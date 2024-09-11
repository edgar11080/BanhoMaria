#include <18f4550.h>
#device adc = 10
#fuses hs,nowdt
#use delay(clock = 20M)
#use fast_io(b)
#use standard_io(c)
#use standard_io(d)
#include <stdio.h>

#define LCD_DB4  PIN_D4                     
#define LCD_DB5  PIN_D6
#define LCD_DB6  PIN_D3
#define LCD_DB7  PIN_D2
#define LCD_RS   PIN_D7
#define LCD_E    PIN_D5

#include <lcd_20x4.c>
#include <kbd1.c>

long contador = 4;
float valor_adc,centigrados;
char grado[8] = {0x07,0x05,0x07,0x00,0x00,0x00,0x00,0x00};
char acento[8] = {0x02,0x04,0x00,0x04,0x04,0x04,0x1E,0x00};
char pausa[8] = {0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A};
char play[8] = {0x18,0x1C,0x1E,0x1F,0x1F,0x1E,0x1C,0x18}; 
char agua[8] = {0x03,0x06,0x00,0x04,0x0E,0x1F,0x1F,0x0E};
char tiempo[8] = {0x00,0x0E,0x13,0x15,0x15,0x11,0x0E,0x00}; 
char temp[8] = {0x05,0x0A,0x00,0x0E,0x1F,0x1F,0x0E,0x00}; 
char k;
int A = 0,B = 0,C,D,E,F,G = 0,M = 0,N = 0,L = 1,O = 1,P = 0,Q = 0,R = 1,S = 0,T = 0,U = 0,V = 0,W = 0,X,Y,Z,duty = 0;

#int_Timer0                               
void DesbordeTimer0()                    
{
   set_timer0(60654);
   output_toggle(pin_a2); 
   
   if(W == 1)
   {             
      A = A - 1;    
   }  
}

#int_timer1  
void sampling_time()
{     
   set_timer1(63000);
   output_bit(PIN_A1,!input(PIN_A1));  
   
   lcd_gotoxy(17,3);
   lcd_putc(" ");
      
   if(L == 1)
   {
      lcd_gotoxy(6,1);
      lcd_putc("Ba o Mar a");
      lcd_gotoxy(8,1);
      lcd_putc((char)238);
      lcd_gotoxy(14,1);
      CGRAM_putc(1);
      lcd_gotoxy(3,2);
      lcd_putc("temporizado para");
      lcd_gotoxy(1,3);
      lcd_putc("reacciones qu micas");
      lcd_gotoxy(14,3);
      CGRAM_putc(1);
   }
   
   if(N == 1)
   {
      lcd_gotoxy(1,2);
      lcd_putc("        HH:MM");
      lcd_gotoxy(1,3);
      lcd_putc("               ");      
   }
   
   if(U == 1)
   {                          
      contador ++;
            
      if(contador = 5)
      { 
         contador = 0;
         set_adc_channel(0);
         valor_adc = read_adc();  
         delay_us(20);  
         centigrados = ((valor_adc*500.0))/1023.0;          
         lcd_gotoxy(13,1);
         printf(lcd_putc,"%0.2f",centigrados);
      }
      
      lcd_gotoxy(1,1);
      lcd_putc("Temp. real:");
      lcd_gotoxy(1,2);
      lcd_putc("Temp. deseada:");     
      lcd_gotoxy(18,1);
      CGRAM_putc(0);   
      lcd_gotoxy(19,1);
      lcd_putc("C ");
      lcd_gotoxy(19,2);
      CGRAM_putc(0);   
      lcd_gotoxy(20,2);
      lcd_putc("C");
   } 
   
   if(V == 1)
   {
   
      if(centigrados < Z)
      {
         output_high(pin_d0);
      }  
      
      if(centigrados > Z)
      {
         output_low(pin_d0);    
      }   
   }
   
   R = R + 1;
      
   if(R == 2)
   {
      R = 0;
   }
   
   switch(S)
   {
      case(1):
      
      lcd_gotoxy(18,2);
      lcd_putc("_");
      
      if(R == 0)
      {
         lcd_gotoxy(17,2);
         lcd_putc("_");
      }
      
      if(R == 1)
      {
         lcd_gotoxy(17,2);
         lcd_putc(" ");
      }      
      break;

      case(2):
      
      if(R == 0)
      {
         lcd_gotoxy(18,2);
         lcd_putc("_");
      }
      
      if(R == 1)
      {
         lcd_gotoxy(18,2);
         lcd_putc(" ");
      }      
      break;

      case(3):
      lcd_gotoxy(10,1);
      lcd_putc("_");
      
      if(R == 0)
      {
         lcd_gotoxy(9,1);
         lcd_putc("_");
      }
      
      if(R == 1)
      {
         lcd_gotoxy(9,1);
         lcd_putc(" ");
      }      
      break;
      
      case(4):
      lcd_gotoxy(12,1);
      lcd_putc("_");
      
      if(R == 0)
      {
         lcd_gotoxy(10,1);
         lcd_putc("_");
      }
      
      if(R == 1)
      {
         lcd_gotoxy(10,1);
         lcd_putc(" ");
      }      
      break;
            
      case(5):
      lcd_gotoxy(13,1);
      lcd_putc("_");
      
      if(R == 0)
      {
         lcd_gotoxy(12,1);
         lcd_putc("_");
      }
      
      if(R == 1)
      {
         lcd_gotoxy(12,1);
         lcd_putc(" ");
      }      
      break;
      
      case(6):
      
      if(R == 0)
      {
         lcd_gotoxy(13,1);
         lcd_putc("_");
      }
      
      if(R == 1)
      {
         lcd_gotoxy(13,1);
         lcd_putc(" ");
      }      
      break;                
   }
   
   if(O == 1)
   {    
      
      if(R == 0)
      {
         lcd_gotoxy(1,4);
         lcd_putc("Pulse # para avanzar");
      }
      
      if(R == 1)
      {
         lcd_gotoxy(1,4);
         lcd_putc("                    ");
      }   
   }  
   
   if(O == 0)
   {
      lcd_gotoxy(1,4);
      lcd_putc("                    ");
   }
   
   if(O == 2)
   {
      if(duty == 0)
      {
         lcd_gotoxy(11,4);
         lcd_putc("Apagado");
      }
      
      if(duty == 5)
      { 
         lcd_gotoxy(11,4);
         lcd_putc("       ");
         lcd_gotoxy(11,4);
         lcd_putc("10 %");
      }
      
      if(duty == 10)
      {
         lcd_gotoxy(11,4);
         lcd_putc("       ");
         lcd_gotoxy(11,4);
         lcd_putc("20 %");
      }
      
      if(duty == 15)
      { 
         lcd_gotoxy(11,4);
         lcd_putc("       ");
         lcd_gotoxy(11,4);
         lcd_putc("30 %");
      }
      
      if(duty == 20)
      {
         lcd_gotoxy(11,4);
         lcd_putc("       ");
         lcd_gotoxy(11,4);
         lcd_putc("40 %");
      }
      
      if(duty == 25)
      {
         lcd_gotoxy(11,4);
         lcd_putc("       ");
         lcd_gotoxy(11,4);
         lcd_putc("50 %");
      }
      
      if(duty == 30)
      {
         lcd_gotoxy(11,4);
         lcd_putc("       ");
         lcd_gotoxy(11,4);
         lcd_putc("60 %");
      }
      
      if(duty == 35)
      {
         lcd_gotoxy(11,4);
         lcd_putc("       ");
         lcd_gotoxy(11,4);
         lcd_putc("70 %");
      }
      
      if(duty == 40)
      {
         lcd_gotoxy(11,4);
         lcd_putc("       ");
         lcd_gotoxy(11,4);
         lcd_putc("80 %");
      }
      
      if(duty == 45)
      {
         lcd_gotoxy(11,4);
         lcd_putc("       ");
         lcd_gotoxy(11,4);
         lcd_putc("90 %");
      } 
      
      if(duty == 50)
      {
         lcd_gotoxy(11,4);
         lcd_putc("       ");
         lcd_gotoxy(11,4);
         lcd_putc("100 %");
      } 
   }
}

#int_Timer3                              
void agitador()                    
{
   set_timer3(63000);
   output_toggle(pin_a3); 
   
   if(P == 1)
   {        
      lcd_gotoxy(16,3);
      printf(lcd_putc,"%d",A);
   
      lcd_gotoxy(15,3);
      printf(lcd_putc,"%d",B);
      
      lcd_gotoxy(13,3);
      printf(lcd_putc,"%d",C);
      
      lcd_gotoxy(12,3);
      printf(lcd_putc,"%d",D);
      
      lcd_gotoxy(10,3);
      printf(lcd_putc,"%d",E);
      
      lcd_gotoxy(9,3);
      printf(lcd_putc,"%d",F);
      
      lcd_gotoxy(17,2);
      printf(lcd_putc,"%2d",Z);
   }   
}

void main()
{
   lcd_init();
   kbd_init();
   port_b_pullups(true);
   output_low(pin_d0);
   
   setup_adc_ports(AN0);
   setup_adc(adc_clock_internal);
   
   CGRAM_position(0);
   CGRAM_create_char(grado);
   CGRAM_position(1);
   CGRAM_create_char(acento);
   CGRAM_position(2);
   CGRAM_create_char(pausa);
   CGRAM_position(3);
   CGRAM_create_char(play);
   CGRAM_position(4);
   CGRAM_create_char(agua);
   CGRAM_position(5);
   CGRAM_create_char(tiempo);
   CGRAM_position(6);
   CGRAM_create_char(temp);
   
   set_tris_b(0x00);                      
   output_b(0x00);  
   
   setup_timer_0(rtcc_div_256|rtcc_internal);               
   enable_interrupts(int_Timer0);         
   enable_interrupts(GLOBAL);     
   set_timer0(60654);       
                                          
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);                                                        
   enable_interrupts(int_Timer1);         
   enable_interrupts(GLOBAL); 
   set_timer1(63000);  
   
   setup_timer_2(t2_div_by_4,49,1);
   setup_ccp1(ccp_pwm);
   set_pwm1_duty(0);  
   
   setup_timer_3(T3_INTERNAL | T1_DIV_BY_8);                                                        
   enable_interrupts(int_Timer3);         
   enable_interrupts(GLOBAL); 
   set_timer3(63000);  
   
   while(true)
   {   
      S = 0;      
      
      k = kbd_getc(); 
      
      if(k == '#')
      {
         L = 0;
         O = 0;
         lcd_putc("\f");
         lcd_gotoxy(17,2);
         lcd_putc("_");
         lcd_gotoxy(18,2);
         lcd_putc("_");
         
         while(true)
         {
            S = 1;
            N = 0;
            U = 1;
            Q = 0;
            k = kbd_getc();
      
            if(k != 0)
            {         
            
               if ((k != 0) & (k != '*') & (k != 'A') & (k != 'B') & (k != 'C') & (k != 'D') & (k != '#'))
               {

                  while(true)
                  {  
                     S = 2;
                     
                     if(Q == 1)
                     {
                        break;
                     }
                     
                     if ((k != 0) & (k != 'A') & (k != 'B') & (k != 'C') & (k != 'D') & (k != '#') & (k != '*'))
                     {
                        lcd_gotoxy(17,2);
                        lcd_putc(k);  
                        
                        if(k == '1')
                        {
                           X = 1;
                        }
                        if(k == '2')
                        {
                           X = 2;
                        }
                        if(k == '3')
                        {
                           X = 3;
                        }
                        if(k == '4')
                        {
                           X = 4;
                        }
                        if(k == '5')
                        {
                           X = 5;
                        }
                        if(k == '6')
                        {
                           X = 6;
                        }
                        if(k == '7')
                        {
                           X = 7;
                        }
                        if(k == '8')
                        {
                           X = 8;
                        }
                        if(k == '9')
                        {
                           X = 9;
                        }
                        if(k == '0')
                        {
                           X = 0;
                        }       
                     }   
                    
                     k = kbd_getc();                     
                     
                     if (k != 0)
                     {
                     
                        if (k == '*')
                        {
                           break;
                        }
                        
                        if ((k != 0) & (k != '*') & (k != 'A') & (k != 'B') & (k != 'C') & (k != 'D') & (k != '#'))
                        {
                           lcd_gotoxy(1,4);
                           O = 1;
                           S = 0;
                                                   
                           while(true)
                           {
                              if(Q == 1)
                              {
                                 break;
                              }
                                                            
                              if ((k != 0) & (k != 'A') & (k != 'B') & (k != 'C') & (k != 'D') & (k != '#') & (k != '*'))
                              {   
                                 lcd_gotoxy(18,2);
                                 lcd_putc(k);  
                                 
                                 if(k == '1')
                                 {
                                    Y = 1;
                                 }
                                 if(k == '2')
                                 {
                                    Y = 2;
                                 }
                                 if(k == '3')
                                 {
                                    Y = 3;
                                 }
                                 if(k == '4')
                                 {
                                    Y = 4;
                                 }
                                 if(k == '5')
                                 {
                                    Y = 5;
                                 }
                                 if(k == '6')
                                 {
                                    Y = 6;
                                 }
                                 if(k == '7')
                                 {
                                    Y = 7;
                                 }
                                 if(k == '8')
                                 {
                                    Y = 8;
                                 }
                                 if(k == '9')
                                 {
                                    Y = 9;
                                 }
                                 if(k == '0')
                                 {
                                    Y = 0;
                                 }
                                 
                                 Z = X*10 + Y;
                                 M = Z;
                              }   
                                 
                              k = kbd_getc();    
                                 
                              if (k == '*')
                              {
                                 S = 2;
                                 O = 0;
                                 break;
                              }
                                                         
                              if(k == '#')
                              {
                                 U = 0; 
                                 O = 0;
                                 lcd_putc("\f");
                                 
                                 if(Q == 0)
                                 {
                                    lcd_gotoxy(1,1);
                                    lcd_putc("Tiempo: __:__");
                                    S = 3;
                                 }
                        
                                 while(true)
                                 {
                                    if(Q == 1)
                                    {
                                       break;
                                    }
                              
                                    if(Z < centigrados)
                                    {
                                    
                                       while(true)
                                       { 
                                          N = 0;
                                          O = 3;
                                          U = 0;
                                          S = 0;
                                          lcd_putc("\f");
                                          lcd_gotoxy(4,1);
                                          lcd_putc("La temperatura");
                                          lcd_gotoxy(3,2);
                                          lcd_putc("deseada debe ser");
                                          lcd_gotoxy(6,3);
                                          lcd_putc("mayor a la");
                                          lcd_gotoxy(3,4);
                                          lcd_putc("temperatura real");
                                          delay_ms(500);
                                          lcd_putc("\f");
                                          lcd_gotoxy(17,2);
                                          lcd_putc("_");
                                          lcd_gotoxy(18,2);
                                          lcd_putc("_");
                                          U = 1;
                                          Q =  1;
                                          contador = 4;
                                          break;
                                       }   
                                    } 
                                    
                                    S = 3; 
                                    N = 1;
                                    k = kbd_getc();   
                                    
                                    if ((k != 0) & (k != '*') & (k != 'A') & (k != 'B') & (k != 'C') & (k != 'D') & (k != '#'))
                                    {                                    
                                       while(true)
                                       { 
                                          S = 4;
                                                                      
                                          if ((k != 0) & (k != 'A') & (k != 'B') & (k != 'C') & (k != 'D') & (k != '#') & (k != '*'))
                                          {
                                             lcd_gotoxy(9,1);
                                             lcd_putc(k);  
                                            
                                             if(k == '1')
                                             {
                                                F = 1;
                                             }
                                             if(k == '2')
                                             {
                                                F = 2;
                                             }
                                             if(F == '3')
                                             {
                                                F = 3;
                                             }
                                             if(k == '4')
                                             {
                                                F = 4;
                                             }
                                             if(k == '5')
                                             {
                                                F = 5;
                                             }
                                             if(k == '6')
                                             {
                                                F = 6;
                                             }
                                             if(k == '7')
                                             {
                                                F = 7;
                                             }
                                             if(k == '8')
                                             {
                                                F = 8;
                                             }
                                             if(k == '9')
                                             {
                                                F = 9;
                                             }
                                             if(k == '0')
                                             {
                                                F = 0;
                                             }    
                                          }   
                                          
                                          k = kbd_getc();  
                                          
                                          if (k != 0)
                                          {
                                          
                                             if (k == '*')
                                             {
                                                break;
                                             }
                                             
                                             if ((k != 0) & (k != '*') & (k != 'A') & (k != 'B') & (k != 'C') & (k != 'D') & (k != '#'))
                                             {
                                             
                                                while(true)
                                                {
                                                   S = 5; 
                                                                                       
                                                   if ((k != 0) & (k != 'A') & (k != 'B') & (k != 'C') & (k != 'D') & (k != '#') & (k != '*'))
                                                   {   
                                                      lcd_gotoxy(10,1);
                                                      lcd_putc(k);  
                                                      
                                                      if(k == '1')
                                                      {
                                                         E = 1;
                                                      }
                                                      if(k == '2')
                                                      {
                                                         E = 2;
                                                      }
                                                      if(k == '3')
                                                      {
                                                         E = 3;
                                                      }
                                                      if(k == '4')
                                                      {
                                                         E = 4;
                                                      }
                                                      if(k == '5')
                                                      {
                                                         E = 5;
                                                      }
                                                      if(k == '6')
                                                      {
                                                         E = 6;
                                                      }
                                                      if(k == '7')
                                                      {
                                                         E = 7;
                                                      }
                                                      if(k == '8')
                                                      {
                                                         E = 8;
                                                      }
                                                      if(k == '9')
                                                      {
                                                         E = 9;
                                                      }
                                                      if(k == '0')
                                                      {
                                                         E = 0;
                                                      }                                                    
                                                   }   
                                          
                                                   k = kbd_getc();                                                                                                     
                                          
                                                   if (k != 0)
                                                   {
                                                 
                                                      if (k == '*')
                                                      {
                                                         break;
                                                      }
                                                      
                                                      if ((k != 0) & (k != '*') & (k != 'A') & (k != 'B') & (k != 'C') & (k != 'D') & (k != '#'))
                                                      {
                                                      
                                                         while(true)
                                                         {
                                                            S = 6;
                                                                                                            
                                                            if ((k != 0) & (k != 'A') & (k != 'B') & (k != 'C') & (k != 'D') & (k != '#') & (k != '*'))
                                                            {
                                                               lcd_gotoxy(12,1);
                                                               lcd_putc(k);  
                                                               
                                                               if(k == '1')
                                                               {
                                                                  D = 1;
                                                               }
                                                               if(k == '2')
                                                               {
                                                                  D = 2;
                                                               }
                                                               if(k == '3')
                                                               {
                                                                  D = 3;
                                                               }
                                                               if(k == '4')
                                                               {
                                                                  D = 4;
                                                               }
                                                               if(k == '5')
                                                               {
                                                                  D = 5;
                                                               }
                                                               if(k == '6')
                                                               {
                                                                  D = 6;
                                                               }
                                                               if(k == '7')
                                                               {
                                                                  D = 7;
                                                               }
                                                               if(k == '8')
                                                               {
                                                                  D = 8;
                                                               }
                                                               if(k == '9')
                                                               {
                                                                  D = 9;
                                                               }
                                                               if(k == '0')
                                                               {
                                                                  D = 0;
                                                               }
                                                            }   
                                          
                                                            k = kbd_getc();
                                          
                                                            if (k != 0)
                                                            {
                                                            
                                                               if (k == '*')
                                                               {
                                                                  break;
                                                               }
                                                               
                                                               if ((k != 0) & (k != '*') & (k != 'A') & (k != 'B') & (k != 'C') & (k != 'D') & (k != '#'))
                                                               {
                                                               
                                                                  while(true)
                                                                  {        
                                                                     O = 1;
                                                                     S = 0;
                                                                     
                                                                     if ((k != 0) & (k != 'A') & (k != 'B') & (k != 'C') & (k != 'D') & (k != '#') & (k != '*'))
                                                                     {
                                                                        lcd_gotoxy(13,1);
                                                                        lcd_putc(k);
                                                                        
                                                                        if(k == '1')
                                                                        {
                                                                           C = 1;
                                                                        }
                                                                        if(k == '2')
                                                                        {
                                                                           C = 2;
                                                                        }
                                                                        if(k == '3')
                                                                        {
                                                                           C = 3;
                                                                        }
                                                                        if(k == '4')
                                                                        {
                                                                           C = 4;
                                                                        }
                                                                        if(k == '5')
                                                                        {
                                                                           C = 5;
                                                                        }
                                                                        if(k == '6')
                                                                        {
                                                                           C = 6;
                                                                        }
                                                                        if(k == '7')
                                                                        {
                                                                           C = 7;
                                                                        }
                                                                        if(k == '8')
                                                                        {
                                                                           C = 8;
                                                                        }
                                                                        if(k == '9')
                                                                        {
                                                                           C = 9;
                                                                        }
                                                                        if(k == '0')
                                                                        {
                                                                           C = 0;
                                                                        }         
                                                                     }                                                                           
                                                                                       
                                                                     k = kbd_getc();
                                                                     
                                                                     if (k == '*')
                                                                     {  
                                                                        O = 0;
                                                                        break;
                                                                     }
                                                            
                                                                     if(k == '#')
                                                                     {
                                                                        N = 0;
                                                                        O = 2;
                                                                        contador = 4;
                                                                        lcd_putc("\f");
                                                                        lcd_gotoxy(1,3);
                                                                        lcd_putc("Tiempo:   :  :  ");
                                                                        lcd_gotoxy(1,4);
                                                                        lcd_putc("Agitador: Apagado");
                                                                        lcd_gotoxy(17,2);
                                                                        printf(lcd_putc,"%d",Z);
                                                                        V = 1;
                                                                        
                                                                        while(true)
                                                                        {
                                                                           P = 1;
                                                                           U = 1;                                                                                                                                                                                                                                                                                       
                                                                           k = kbd_getc();
                                                   
                                                                           if(k == 'A')
                                                                           {                                                                                                                                                          
                                                                              if(duty < 50)
                                                                              {
                                                                                 duty = duty + 5;
                                                                              }

                                                                              set_pwm1_duty(duty);
                                                                           }
                                                                           
                                                                           if(k == 'B')
                                                                           {                                                                                                                                                          
                                                                              if(duty > 0)
                                                                              {
                                                                                 duty = duty - 5;
                                                                              }

                                                                              set_pwm1_duty(duty);
                                                                           }
                                                                           
                                                                           if(G == 1)
                                                                           {                                                                                 
                                                                              if(k == 'C')
                                                                              {                                                                           
                                                                                 if(C <= 4)
                                                                                 {
                                                                                    if(D <= 5)
                                                                                    {                                                                                
                                                                                       C = C + 5;
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                       if(E <= 8)
                                                                                       {
                                                                                          E = E + 1;
                                                                                          D = D + 4 - 10;
                                                                                          C = C + 5;
                                                                                       }
                                                                                       else
                                                                                       {
                                                                                          if(F <= 8)
                                                                                          {
                                                                                             F = F + 1;
                                                                                             E = 0;
                                                                                             D = D + 4 - 10;
                                                                                             C = C + 5;
                                                                                          }
                                                                                          else
                                                                                          {
                                                                                             C = C + 5;
                                                                                          }
                                                                                       }
                                                                                    }
                                                                                 } 
                                                                                 else
                                                                                 {
                                                                                    if(D <= 4)
                                                                                    {
                                                                                       D = D + 1;
                                                                                       C = C + 5 - 10;
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                       if(E <= 8)
                                                                                       {
                                                                                          E = E + 1;
                                                                                          D = D + 5 - 10;
                                                                                          C = C + 5 - 10;
                                                                                       }
                                                                                       else 
                                                                                       {
                                                                                          if(F <= 8)
                                                                                          {
                                                                                             F = F + 1;
                                                                                             E = 0;
                                                                                             D = D + 5 - 10;
                                                                                             C = C + 5 - 10;
                                                                                          }
                                                                                          else
                                                                                          {
                                                                                             D = D + 1;
                                                                                             C = C + 5 - 10;
                                                                                          }
                                                                                       }
                                                                                       
                                                                                    }
                                                                                 }
                                                                              }  
                                                                              
                                                                              if(k == 'D')
                                                                              {                                                                           
                                                                                 if(C >= 5)
                                                                                 {
                                                                                    if(D <= 5)
                                                                                    {
                                                                                       C = C - 5;
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                       if(E <= 8)
                                                                                       {
                                                                                          E = E + 1;
                                                                                          D = D + 4 - 10;
                                                                                          C = C - 5;
                                                                                       }
                                                                                       else
                                                                                       {
                                                                                          if(F <= 8)
                                                                                          {
                                                                                             F = F + 1;
                                                                                             E = 0;
                                                                                             D = D + 4 - 10;
                                                                                             C = C - 5;
                                                                                          }
                                                                                          else
                                                                                          {
                                                                                             C = C - 5;
                                                                                          }
                                                                                       }
                                                                                    }
                                                                                 }
                                                                                 else
                                                                                 {                                                                                 
                                                                                    if(D >= 1)
                                                                                    {
                                                                                       if(D <= 5)
                                                                                       {
                                                                                          D = D - 1;
                                                                                          C = C - 5 + 10;
                                                                                       }
                                                                                       else
                                                                                       {
                                                                                          if(E <= 8)
                                                                                          {
                                                                                             E = E + 1;
                                                                                             D = D + 3 - 10;
                                                                                             C = C - 5 + 10;
                                                                                          }
                                                                                          else
                                                                                          {
                                                                                             if(F <= 8)
                                                                                             {
                                                                                                F = F + 1;
                                                                                                E = 0;
                                                                                                D = D + 3 - 10;
                                                                                                C = C - 5 + 10;
                                                                                             }   
                                                                                             else
                                                                                             {
                                                                                                D = D - 1;
                                                                                                C = C - 5 + 10;
                                                                                             }
                                                                                          }
                                                                                       }
                                                                                    }   
                                                                                    else
                                                                                    {
                                                                                       if(E >= 1)
                                                                                       {
                                                                                          E = E - 1;
                                                                                          D = 5; 
                                                                                          C = C - 5 + 10;
                                                                                       }
                                                                                       else
                                                                                       {
                                                                                          if(F >= 1)
                                                                                          {
                                                                                             F = F - 1;
                                                                                             E = 9;
                                                                                             D = 5; 
                                                                                             C = C - 5 + 10;
                                                                                          }
                                                                                       }
                                                                                    } 
                                                                                 }
                                                                              }  
                                                                           }
                                                                           
                                                                           if(G == 2)
                                                                           {                                                                              
                                                                              if(k == 'C')
                                                                              {
                                                                                 if(Z < 99)
                                                                                 {
                                                                                    Z = Z + 1;
                                                                                 }                   
                                                                              }
                                                                              
                                                                              if(k == 'D')
                                                                              {                                                                              
                                                                                 if(Z > M)
                                                                                 {
                                                                                    Z = Z - 1;
                                                                                 }                   
                                                                              }                                                                                 
                                                                           }
                                                                           
                                                                           if (k == '1')
                                                                           {
                                                                              G = 1;
                                                                              lcd_gotoxy(18,3);
                                                                              CGRAM_putc(5);
                                                                           }
                                                                           
                                                                           if (k == '2')
                                                                           {
                                                                              G = 2;
                                                                              lcd_gotoxy(18,3);
                                                                              CGRAM_putc(6);
                                                                           }
                                                                           
                                                                           if (k == '0')
                                                                           {
                                                                              G = 0;
                                                                              lcd_gotoxy(18,3);
                                                                              lcd_putc(" ");
                                                                           }
                                                                                                                                                       
                                                                           if (k == '*')
                                                                           {
                                                                              output_low(pin_d0);
                                                                              reset_cpu();
                                                                           }
                                                                           
                                                                           if (centigrados > Z)                                                                                   
                                                                           {
                                                                              W = 1; 
                                                                              lcd_gotoxy(19,3);
                                                                              CGRAM_putc(2);  
                                                           
                                                                              while(true)
                                                                              {                                                                                                                                                                                                                                                                                          
                                                                                 k = kbd_getc();
                                                                                 
                                                                                 if(k == 'A')
                                                                                 {                                                                                                                                                          
                                                                                    if(duty < 50)
                                                                                    {
                                                                                       duty = duty + 5;
                                                                                    }
      
                                                                                    set_pwm1_duty(duty);
                                                                                 }
                                                                                 
                                                                                 if(k == 'B')
                                                                                 {                                                                           
                                                                                    if(duty > 0)
                                                                                    {
                                                                                       duty = duty - 5;
                                                                                    }
      
                                                                                    set_pwm1_duty(duty);
                                                                                 }     
                                                                                 
                                                                                 if(G == 1)
                                                                                 {                                                                                 
                                                                                    if(k == 'C')
                                                                                    {                                                                           
                                                                                       if(C <= 4)
                                                                                       {
                                                                                          if(D <= 5)
                                                                                          {                                                                                
                                                                                             C = C + 5;
                                                                                          }
                                                                                          else
                                                                                          {
                                                                                             if(E <= 8)
                                                                                             {
                                                                                                E = E + 1;
                                                                                                D = D + 4 - 10;
                                                                                                C = C + 5;
                                                                                             }
                                                                                             else
                                                                                             {
                                                                                                if(F <= 8)
                                                                                                {
                                                                                                   F = F + 1;
                                                                                                   E = 0;
                                                                                                   D = D + 4 - 10;
                                                                                                   C = C + 5;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                   C = C + 5;
                                                                                                }
                                                                                             }
                                                                                          }
                                                                                       } 
                                                                                       else
                                                                                       {
                                                                                          if(D <= 4)
                                                                                          {
                                                                                             D = D + 1;
                                                                                             C = C + 5 - 10;
                                                                                          }
                                                                                          else
                                                                                          {
                                                                                             if(E <= 8)
                                                                                             {
                                                                                                E = E + 1;
                                                                                                D = D + 5 - 10;
                                                                                                C = C + 5 - 10;
                                                                                             }
                                                                                             else 
                                                                                             {
                                                                                                if(F <= 8)
                                                                                                {
                                                                                                   F = F + 1;
                                                                                                   E = 0;
                                                                                                   D = D + 5 - 10;
                                                                                                   C = C + 5 - 10;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                   D = D + 1;
                                                                                                   C = C + 5 - 10;
                                                                                                }
                                                                                             }
                                                                                             
                                                                                          }
                                                                                       }
                                                                                    }  
                                                                                    
                                                                                    if(k == 'D')
                                                                                    {                                                                           
                                                                                       if(C >= 5)
                                                                                       {
                                                                                          if(D <= 5)
                                                                                          {
                                                                                             C = C - 5;
                                                                                          }
                                                                                          else
                                                                                          {
                                                                                             if(E <= 8)
                                                                                             {
                                                                                                E = E + 1;
                                                                                                D = D + 4 - 10;
                                                                                                C = C - 5;
                                                                                             }
                                                                                             else
                                                                                             {
                                                                                                if(F <= 8)
                                                                                                {
                                                                                                   F = F + 1;
                                                                                                   E = 0;
                                                                                                   D = D + 4 - 10;
                                                                                                   C = C - 5;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                   C = C - 5;
                                                                                                }
                                                                                             }
                                                                                          }
                                                                                       }
                                                                                       else
                                                                                       {                                                                                 
                                                                                          if(D >= 1)
                                                                                          {
                                                                                             if(D <= 5)
                                                                                             {
                                                                                                D = D - 1;
                                                                                                C = C - 5 + 10;
                                                                                             }
                                                                                             else
                                                                                             {
                                                                                                if(E <= 8)
                                                                                                {
                                                                                                   E = E + 1;
                                                                                                   D = D + 3 - 10;
                                                                                                   C = C - 5 + 10;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                   if(F <= 8)
                                                                                                   {
                                                                                                      F = F + 1;
                                                                                                      E = 0;
                                                                                                      D = D + 3 - 10;
                                                                                                      C = C - 5 + 10;
                                                                                                   }   
                                                                                                   else
                                                                                                   {
                                                                                                      D = D - 1;
                                                                                                      C = C - 5 + 10;
                                                                                                   }
                                                                                                }
                                                                                             }
                                                                                          }   
                                                                                          else
                                                                                          {
                                                                                             if(E >= 1)
                                                                                             {
                                                                                                E = E - 1;
                                                                                                D = 5; 
                                                                                                C = C - 5 + 10;
                                                                                             }
                                                                                             else
                                                                                             {
                                                                                                if(F >= 1)
                                                                                                {
                                                                                                   F = F - 1;
                                                                                                   E = 9;
                                                                                                   D = 5; 
                                                                                                   C = C - 5 + 10;
                                                                                                }
                                                                                             }
                                                                                          } 
                                                                                       }
                                                                                    }  
                                                                                 }
                                                                                 
                                                                                 if(G == 2)
                                                                                 {                                                                              
                                                                                    if(k == 'C')
                                                                                    {
                                                                                       if(Z < 99)
                                                                                       {
                                                                                          Z = Z + 1;
                                                                                       }                   
                                                                                    }
                                                                                    
                                                                                    if(k == 'D')
                                                                                    {                                                                              
                                                                                       if(Z > 0)
                                                                                       {
                                                                                          Z = Z - 1;
                                                                                       }                   
                                                                                    }                                                                                 
                                                                                 }
                                                                                 
                                                                                 if (k == '1')
                                                                                 {
                                                                                    G = 1;
                                                                                    lcd_gotoxy(18,3);
                                                                                    CGRAM_putc(5);
                                                                                 }
                                                                                 
                                                                                 if (k == '2')
                                                                                 {
                                                                                    G = 2;
                                                                                    lcd_gotoxy(18,3);
                                                                                    CGRAM_putc(6);
                                                                                 }  
                                                                                 
                                                                                 if (k == '0')
                                                                                 {
                                                                                    G = 0;
                                                                                    lcd_gotoxy(18,3);
                                                                                    lcd_putc(" ");
                                                                                 }
                                                                          
                                                                                 if (k == '#')
                                                                                 {
                                                                                    W = 0;
                                                                                    V = 0;
                                                                                    T = T + 1;                                                                                               
                                                                                    output_low(pin_d0);
                                                                                    lcd_gotoxy(19,3);
                                                                                    CGRAM_putc(3);   
                                                                                    lcd_gotoxy(20,3);
                                                                                    lcd_putc(" "); 
                                                                                 }
                                                                                 
                                                                                 if (T == 2)
                                                                                 {
                                                                                    T = 0;
                                                                                    V = 1;
                                                                                    lcd_gotoxy(19,3);
                                                                                    CGRAM_putc(2);   
                                                                                    break;                                                                                                
                                                                                 }
                                                                                 
                                                                                 if (k == '*')
                                                                                 {
                                                                                    output_low(pin_d0);
                                                                                    reset_cpu();
                                                                                 }
                                                                                                                                                                                                                                                                                                                                                                      
                                                                                 if((A == -1) & (B != 0))
                                                                                 {                                                                         
                                                                                    B = B - 1;
                                                                                    A = 9;    
                                                                                 }
                                                                                 
                                                                                 if((A == -1) & (B == 0) & (C != 0))
                                                                                 {
                                                                                    C = C - 1; 
                                                                                    B = 5;
                                                                                    A = 9;
                                                                                 }
                                                                                 
                                                                                 if((A == -1) & (B == 0) & (C == 0) & (D != 0))
                                                                                 {
                                                                                    D = D - 1;
                                                                                    C = 9;
                                                                                    B = 5;
                                                                                    A = 9;
                                                                                 }
                                                                                 
                                                                                 if((A == -1) & (B == 0) & (C == 0) & (D == 0) & (E != 0))
                                                                                 {
                                                                                    E = E - 1;
                                                                                    D = 5;
                                                                                    C = 9;
                                                                                    B = 5;
                                                                                    A = 9; 
                                                                                 }                                                                   
                                                                                 
                                                                                 if((A == -1) & (B == 0) & (C == 0) & (D == 0) & (E == 0) & (F != 0))
                                                                                 {
                                                                                    F = F - 1;
                                                                                    E = 9;
                                                                                    D = 5;
                                                                                    C = 9;
                                                                                    B = 5;
                                                                                    A = 9; 
                                                                                 } 
                                                                                 
                                                                                 if((A == -1) & (B == 0) & (C == 0) & (D == 0) & (E == 0) & (F == 0))
                                                                                 {
                                                                                    V = 0;
                                                                                    W = 0;
                                                                                    output_low(pin_d0);
                                                                                    output_high(pin_d1);
                                                                                    delay_ms(500);
                                                                                    output_low(pin_d1);
                                                                                    reset_cpu();   
                                                                                 }  
                                                                              }
                                                                           }
                                                                        }
                                                                     }
                                                                  }
                                                               }
                                                            }
                                                         }
                                                      }
                                                   }
                                                }
                                             }
                                          }                                                                             
                                       }
                                    }                                           
                                 }       
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }   
   }
}
