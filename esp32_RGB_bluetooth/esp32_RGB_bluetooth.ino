#include "BluetoothSerial.h"

BluetoothSerial ESP_BT;

#define RED_LED 19
#define BLUE_LED 18 
#define GREEN_LED 21

#define RED_CHANNEL 0
#define BLUE_CHANNEL 1
#define GREEN_CHANNEL 2

void setup() {

  ledcSetup(RED_CHANNEL, 5000, 8); // config PWM (canal, freq, bits)
  ledcSetup(BLUE_CHANNEL, 5000, 8); 
  ledcSetup(GREEN_CHANNEL, 5000, 8);

  ledcAttachPin(RED_LED, RED_CHANNEL); // config port PWM (port, channel)
  ledcAttachPin(BLUE_LED, BLUE_CHANNEL);
  ledcAttachPin(GREEN_LED, GREEN_CHANNEL);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

String valorRecebido;

char auxiliar[20];
char* cores;

int gBright; 
int rBright; 
int bBright; 

void loop() {
  if(ESP_BT.available()){
    char caractere = ESP_BT.read();
    
    if(caractere != ')'){
      valorRecebido += caractere;
    }
    else{
      if(valorRecebido == "ON"){
        ledcWrite(RED_CHANNEL, 255);
        ledcWrite(BLUE_CHANNEL, 255);
        ledcWrite(GREEN_CHANNEL, 255);        
        delay(100);
        ledcWrite(RED_CHANNEL, 0);
        ledcWrite(BLUE_CHANNEL, 0);
        ledcWrite(GREEN_CHANNEL, 0);        
        delay(100);
        ledcWrite(RED_CHANNEL, 255);
        ledcWrite(BLUE_CHANNEL, 255);
        ledcWrite(GREEN_CHANNEL, 255);        
      }
      else if(valorRecebido == "OFF"){
        ledcWrite(RED_CHANNEL, 0);
        ledcWrite(BLUE_CHANNEL, 0);
        ledcWrite(GREEN_CHANNEL, 0);        
      }
      else{
          valorRecebido.toCharArray(auxiliar ,20);
          cores = strtok(auxiliar, ".");
          rBright = atoi(cores);
         
          cores = strtok(NULL, ".");
          gBright = atoi(cores);
          
          cores = strtok(NULL, ".");          
          bBright = atoi(cores);

          ledcWrite(RED_CHANNEL, rBright);
          ledcWrite(BLUE_CHANNEL, bBright);
          ledcWrite(GREEN_CHANNEL, gBright);
      }
      valorRecebido = "";
    }
  }
}
