#include <Arduino.h>
#include <Wire.h>
#include <Ciao.h>
#include "UNOWIFI.h"

#define driver "rest"
#define host "api.thingspeak.com"

#define CHAR_SIZE 200
const char* talk_id;
const char* talk_key;
const char* thing_key;

UNOWiFi_Thingspeak::UNOWiFi_Thingspeak(const char* Talk_id,
const char* Talk_key){
	talk_id=Talk_id;
	talk_key=Talk_key;
}
UNOWiFi_Thingspeak::UNOWiFi_Thingspeak(const char* Talk_id,
const char* Talk_key,const char* Thing_key)
{
	talk_id=Talk_id;
	talk_key=Talk_key;
	thing_key=Thing_key;
}
void UNOWiFi_Thingspeak::GetCommand(const char* cdm_id)
{
	String request = "/talkbacks/";
	request += talk_id;
	request += "/commands/";
	request += cdm_id;
	request += "?api_key=";
	request += talk_key;
	
	Ciao.println("Read Talkbackcommands");
	CiaoData data=Ciao.read(driver,host,request,"GET");
	
	String state=data.get(1);
	Command=data.get(2);
	if(!data.isEmpty())
	{
		Ciao.println("State: "+state);
		Ciao.println("Command: "+Command);
	}
	else
	{
		Ciao.println("Error");
		Command="Error";
	}
}
void UNOWiFi_Thingspeak::PublishCommand(String command)
{
	String url = "/talkbacks/";
	url += talk_id;
	url += "/commands?api_key=";
	url += talk_key;
	url += "&command_string=";
	url += command;
	
	Ciao.println("Write new commands");
	CiaoData data=Ciao.write(driver,host,url,"POST");
	
	if(!data.isEmpty())
	{
		Ciao.println("Sate: "+String(data.get(1)));
		Ciao.println("New command: "+String(data.get(2)));
	}
	else
	{
		Ciao.println("Write error");
	}
}
void UNOWiFi_Thingspeak::PublishData(float Eata)
{
	String url = "/update?api_key=";
	url += thing_key;
	url += "&field1=";
	url += String(Eata);
	
	Ciao.println("Publish to Thingspeak Channel");
	CiaoData data=Ciao.write(driver,host,url);
	
	if(!data.isEmpty())
	{
		Ciao.println("State: "+String(data.get(1)));
		Ciao.println("Data is: "+String(data.get(2)));
	}
	else
	{
		Ciao.println("Write error");
	}
}
void UNOWiFi_Thingspeak::GetData(const char* id,const char* field)
{
	//https://api.thingspeak.com/channels/206967/field/1/last.txt
	String url = "/channels/";
	url += id;
	url += "/field/";
	url += field;
	url += "/last.txt";
	
	Ciao.println("Read data from thingspeak");
	CiaoData data=Ciao.read(driver,host,url,"GET");
	
	if(!data.isEmpty())
	{
		Ciao.println("State: "+String(data.get(1)));
		Ciao.println("Data from thingspeak is: "+String(data.get(2)));
		Data=data.get(2);
		Ciao.println(url);
	}
	else
	{
		Ciao.println("Error");
		Data="Error";
		Ciao.println(url);
	}
}
void UNOWiFi_Thingspeak::MutiplegetCommands()
{
    String req = "/talkbacks/";
    req += talk_id;
    req += "/commands";
    req += "?api_key=";
    req += talk_key;
    
    Ciao.println("Read Talkbackcommands");
    CiaoData data=Ciao.read(driver,host,req,"GET");
	
    String state=data.get(1);
    Mutiple_cdm=data.get(2);
    char cdms[50];
    Mutiple_cdm.toCharArray(cdms,50);
    if(!data.isEmpty())
     {
       Ciao.println("State: "+state);
       Ciao.println("Command: "+Mutiple_cdm);
       Ciao.println(req);
       Ciao.println(cdms);
     }
    else
     {
       Ciao.println("Error");
	   Mutiple_cdm="Error";
	   Ciao.println(req);
     }
}
/*void UNOWiFi_Thingspeak::Cutcommand(char cdms[50],int stop)
{
	int i,y;
	int Stop=0;
	char z=cdms[0];
	for(i=0;i<2;i++)
	{
		for(y=0;y<stop;y++)
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
					y=51;
					i=2;	
				}
				else
				{
					continue;
				}
			}
			else
			{
				cdm[i]+=cdms[y];
			}
		}
	}
}*/