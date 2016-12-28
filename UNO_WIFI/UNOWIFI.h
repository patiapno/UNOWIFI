#include <Arduino.h>
#include <Wire.h>
#include <Ciao.h>

class UNOWiFi_Thingspeak{
	public:
	   UNOWiFi_Thingspeak(const char* Talk_id,const char* Talk_key);
	   UNOWiFi_Thingspeak(const char* Talk_id,const char* Talk_key,
	   const char* Thing_key);	  
    public:
    	void MutiplegetCommands();
    	void GetCommand(const char* cdm_id);      //Talkback
    	void PublishCommand(String command);  // Talkback 
		//and input your stringcommands
    	void PublishData(float data);   //Thingspeak
    	void GetData(const char* id,const char* field);       //Thingspeak
    	void CUTString();
		float Convert_toFloat(String data);
    	int Convert_toInt(String data);
   public: String Command;
   public: String Data;	
   public: String Mutiple_cdm;
   //public: void Cutcommand(char cdms[50],int stop);
   //public: String cdm[10];
   //public: char Cdm[200];
    	
};