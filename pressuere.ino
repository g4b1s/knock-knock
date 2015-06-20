// Flexiforce quick start example
// Reads A0 every 100ms and sends voltage value over serial

#include <Twitter.h>
#include <SPI.h>
#include <Ethernet.h>

int  voltag[3];
int  i=0;

void setup() 
{
  // Start serial at 9600 baud
  Serial.begin(9600); 
}

    void loop() 
{
  // Read the input on analog pin 0:
  int sensorValue1 = analogRead(0);
  int sensorValue2 = analogRead(1);
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  //float voltage = sensorValue * (5.0 / 1023.0);
  
  float voltage1 = sensorValue1;
  float voltage2 = sensorValue2;
  float med=0;
  
  // Print out the value you read:
  Serial.print("S1 ");
  Serial.println(voltage1);
  
  Serial.print("S2 ");
  Serial.println(voltage2);
  
  if (i<=2){
    voltag[i]=voltage1+voltage2;
    
    if(i==2){ 
       med =(voltag[0]+voltag[1]+voltag[2])/6;
       Serial.print("media ");
       Serial.println(med);
       voltag[0]=0;
       voltag[1]=0;
       voltag[2]=0;
      }
     i++;
    }
    
    if(i==3){ 
      i=0;
    }

    if(med > 150){
      Serial.print("tweet");
      tweet();
      }
  // Wait 100 milliseconds
  delay(1000);
}

void tweet(){
    Twitter twitter("TWITTER TOKEN HERE");
    //Our message (in lolcat, of course)
    String stringMsg = "Alguem chegou ";
    stringMsg += "#intelmaker #edison";

    //Convert our message to a character array
    char msg[140];
    stringMsg.toCharArray(msg, 140);

    //Tweet that sucker!
    twitter.post(msg);
}


