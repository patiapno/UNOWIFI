#include <Wire.h>
#include <Ciao.h>
#include <UNOWIFI.h>

#define Talk_id "12429"
#define Talk_key "Y59R6DGGHTNZBPCK" 

#define Opencdm1 "Open_light"
#define Opencdm2 "Open_pump"
#define Closecdm1 "Close_light"
#define Closecdm2 "Close_pump"

#define pin1 2
#define pin2 3
UNOWiFi_Thingspeak UNO(Talk_id,Talk_key);
void setup() {
  Ciao.begin();
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,HIGH);
}
void loop() {
  UNO.MutiplegetCommands();
  int y=UNO.Mutiple_cdm.length();
  char cdms[y];
  UNO.Mutiple_cdm.toCharArray(cdms,y);
  Cutcommands(2,cdms,y);
  delay(5*1000);
}
void Cutcommands(int cout_cdm,char cdms[],int Stop)
{
  String commands[cout_cdm];
  int i,y;
  char z=cdms[0];
  for(i=0;i<cout_cdm;i++)
  {
    for(y=0;y<Stop;y++)
    {
      if(cdms[y]==z)
      {
        if(cdms[y+1]==',')
        {
          y+=2;
          i++;
        }
        else if(cdms[y+1]==' ')
        {
          y=Stop+1;
          i=cout_cdm+1;
        }
        else
        {
          continue;
        }
      }
      else
      {
        commands[i]+=cdms[y];
      }
    }
  }
  for(i=0;i<cout_cdm;i++)
  {
    Ciao.println(commands[i]);
    if(commands[i]==Opencdm1)
    {
      digitalWrite(pin1,LOW);
    }
    else if(commands[i]==Opencdm2)
    {
      digitalWrite(pin2,LOW);
    }
    else if(commands[i]==Closecdm1)
    {
      digitalWrite(pin1,HIGH);
    }
    else if(commands[i]==Closecdm2)
    {
      digitalWrite(pin2,HIGH);
    }
  }
}
