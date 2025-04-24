#include<NXP/iolpc2124.h>
// LED CHASER PROGRAM
void delay(unsigned int);
void on_off(void);
void initial(void);
int second = 15;//used for delay function parameter
void main()
{
 IO0SET=0X3F00;//starting from ALL LED off
 initial();
 while (1)
 {
   on_off();
 }  
}
void initial()
{
  T0TCR_bit.CE=0;
  T0PR=47999;
  T0TC=0;
  PINSEL0=0X0000;
  IO0DIR=0X3F00;
  /* we can also use this.
  PINSEL0_bit.P0_8=0;
  IO0DIR_bit.P0_8=1;
  PINSEL0_bit.P0_9=0;
  IO0DIR_bit.P0_9=1;
  PINSEL0_bit.P0_10=0;
  IO0DIR_bit.P0_10=1;
  PINSEL0_bit.P0_11=0;
  IO0DIR_bit.P0_11=1;
  PINSEL0_bit.P0_12=0;
  IO0DIR_bit.P0_12=1;
  PINSEL0_bit.P0_13=0;
  IO0DIR_bit.P0_13=1;*/
}
void on_off()
{
  IO0CLR_bit.P0_8=1;
  delay(second);
  IO0SET_bit.P0_8=1;
  IO0CLR_bit.P0_9=1;
  delay(second);
  IO0SET_bit.P0_9=1;
  IO0CLR_bit.P0_10=1;
  delay(second);
  IO0SET_bit.P0_10=1;
  IO0CLR_bit.P0_11=1;
  delay(second);
  IO0SET_bit.P0_11=1;
  IO0CLR_bit.P0_12=1;
  delay(second);
  IO0SET_bit.P0_12=1;
  IO0CLR_bit.P0_13=1;
  delay(second);
  IO0SET_bit.P0_13=1;  
}
void delay(unsigned int x){ 
  T0TC=0;
  T0TCR_bit.CE=1;
  while(T0TC<x)
  { } 
}