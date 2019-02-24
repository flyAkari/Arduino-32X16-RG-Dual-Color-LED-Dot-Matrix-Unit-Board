#include <FlexiTimer2.h>

boolean vmemory[16][32] = 
{               //              //              //  
{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1},
{0,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1},
{1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1},
{1,1,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1},
{1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
{1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1},
{1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,0,0,0,0,0,1,1,1,1,1},
{1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1},
{1,1,0,1,1,1,0,1,0,1,1,1,1,0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,0,1},
{0,0,0,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1},
{1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,1},
{1,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1},
{1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0,0,0,1,1,1,1,0,1,0,1},
{1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,1},
{1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
};//测试

const int SCAN_A = 1;
const int SCAN_B = 2;
const int SCAN_C = 3;
const int SCAN_D0 = 4;
const int SCAN_D1 = 5;
const int STCLK = 6;
const int DCLK = 7;
const int DATAIN = 8;
int color = 0;
int scana[8] = {0,0,0,0,1,1,1,1};
int scanb[8] = {0,0,1,1,0,0,1,1};
int scanc[8] = {0,1,0,1,0,1,0,1};
int scand0[2] = {1,0};
int scand1[2] = {0,1};
void setup() {
  // put your setup code here, to run once:
  for(int i = 1; i <=8; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);  
  }
  FlexiTimer2::set(3000,flash);
  FlexiTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 2; i++){
  // digitalWrite(SCAN_D0, scand0[i]);
  // digitalWrite(SCAN_D1, scand1[i]);
    for(int j = 0; j < 8; j++){
      for(int k = 127; k >= 0; k--)
      { 
        if(color==0){        
          if((k%2)!=0) digitalWrite(DATAIN, HIGH);
          else digitalWrite(DATAIN, vmemory[8*i+j][(k%64)/2]);
          digitalWrite(DCLK, LOW);
          digitalWrite(DCLK, HIGH);
        }
        else if(color==1){
          if((k%2)==0) digitalWrite(DATAIN, HIGH);
          else digitalWrite(DATAIN, vmemory[8*i+j][((k%64)-1)/2]);
          digitalWrite(DCLK, LOW);
          digitalWrite(DCLK, HIGH);       
        }
        else{
          if((k%2)!=0) digitalWrite(DATAIN, vmemory[8*i+j][((k%64)-1)/2]);
          else digitalWrite(DATAIN, vmemory[8*i+j][(k%64)/2]);
          digitalWrite(DCLK, LOW);
          digitalWrite(DCLK, HIGH);   
        }
      }
      digitalWrite(SCAN_D0, scand0[i]);
      digitalWrite(SCAN_D1, scand1[i]);
      digitalWrite(SCAN_A,scana[j]);
      digitalWrite(SCAN_B,scanb[j]);   
      digitalWrite(SCAN_C,scanc[j]);
      digitalWrite(STCLK, LOW);
      digitalWrite(STCLK, HIGH);
      //delay(1000);
    } 
  }
}

void flash()
{
  if(color<2) color++;
  else color = 0;
}
