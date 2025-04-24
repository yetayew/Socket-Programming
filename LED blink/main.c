#include <NXP/iolpc2124.h>
#include "system.h"
void initial(void);
void on_off(void);
void delay(unsigned int);
void main()
{
  clock_init();
  initial();
  while(1){
  on_off();
  }
}
void initial(){
  PINSEL0_bit.P0_8=0;
  IO0DIR_bit.P0_8=1;
  T0TCR_bit.CE=0;
  T0PR=47999;
  T0TC=0;
}
void on_off(){
IO0CLR_bit.P0_8=1;
delay(43);
IO0SET_bit.P0_8=1;
delay(43);
}
void delay(unsigned int x){ 
  T0TC=0;
  T0TCR_bit.CE=1;
  while(T0TC<x)
  { } 

}