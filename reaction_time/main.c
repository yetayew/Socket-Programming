#include <NXP/iolpc2124.h>
#include <stdio.h>
void init_LCD(void);
void write_cmd(char);
void write_data(char);
void init_lpc(void);
void delay(unsigned int);
void on_off(void);
void lcd_display_int(int c);//used to convert integer to character array 
void lcd_send_string(char *str);//used to print char from character array
void main()
{
  int ran = rand()%2000;//generating random number
  init_lpc();
  init_LCD();
  int timer =0;
  while(IO0PIN_bit.P0_12==1){
    while(IO0PIN_bit.P0_11==0){ 
      if(IO0PIN_bit.P0_12==0){break;}
      delay(ran);//random waiting time
      on_off();//waiting until green light is on
    }
    delay(1);
    timer++;//counts for ms after green light is on
 }
  IO0CLR_bit.P0_11=1;
  if(timer<=1){
    char text[]="Too Early !";//printed when green light is still off
    for(int i=0;i<sizeof(text);i++){
      write_data(text[i]);
    }
  }
  else{
    lcd_display_int(timer);
    write_data(' ');
    write_data('m');
    write_data('s');
  }  
}
void init_lpc(){
  PINSEL0=0;
  IO0DIR=0X0FFF;
  IO0DIR_bit.P0_12=0;
  T0TCR_bit.CE=0;
  T0PR=47999;
  T0TC=0;  
}
void delay(unsigned int x){ 
  T0TC=0;
  T0TCR_bit.CE=1;
  while(T0TC<x)
  {if(IO0PIN_bit.P0_12==0){break;} } 
}
void on_off(){
IO0SET_bit.P0_11=1;
}
void write_cmd(char cmd){
  IO0CLR_bit.P0_8=1;
  delay(1);
  IO0CLR_bit.P0_9=1;  
  delay(1);
  IO0SET=cmd;
  delay(1);
  IO0SET_bit.P0_10=1;
  delay(1);
  IO0CLR_bit.P0_10=1;
  delay(1);
  IO0CLR=0x000000FF;
}
void write_data(char data){
  IO0SET_bit.P0_8=1;
  delay(1);
  IO0CLR_bit.P0_9=1;  
  delay(1);
  IO0SET=data;
  delay(1);
  IO0SET_bit.P0_10=1;
  delay(1);
  IO0CLR_bit.P0_10=1;
  delay(1);
  IO0CLR=0x000000FF;
}

void init_LCD(){
    write_cmd(0x38);
    delay(1);
    write_cmd(0x06);
    delay(1);
     write_cmd(0x0f);
    delay(1);
     write_cmd(0x01);
    delay(1);
}
void lcd_send_string(char *str) {
    while (*str) {
       char x=*str++;
        write_data(x);
    }
}
void lcd_display_int(int value) {
    char buffer[16];
    sprintf(buffer, "%02d", value);//%d means an integer. : is a : %02d means an integer, left padded with zeros up to 2 digits.
    lcd_send_string(buffer);
}