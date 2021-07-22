/*
 * Project Setup_interval_update
 * Description:
 * Author:
 * Date:
 */
#include "Particle.h"
#include "math.h"
//#include "JsonParserGeneratorRK.h"    //install it JsonParserGeneratorRK

SYSTEM_THREAD(ENABLED);

#define UPDATE_INTERVAL 10000  //1 sec = 1000 millis

int min_time, min_last;

unsigned long UpdateInterval;

SerialLogHandler logHandler(LOG_LEVEL_INFO);

void setup()
{ 
  Serial.begin(9600);
  delay(100);
  
  //Serial1.begin(9600,SERIAL_8N1);
  //Serial1.setTimeout(500);             // Wait up to 500ms for the data to return in full
  //delay(100);
  Log.info("System version: %s", (const char*)System.version());
  Log.info("Setup Complete");
  UpdateInterval = millis();
  min_last=Time.minute()-1;
}

void loop()
{
  Time.zone(-7);

  if(millis() - UpdateInterval > UPDATE_INTERVAL)
  {
    Log.info("if loop");

    min_time=Time.minute();
    if((min_time!=min_last)&&(min_time==0||min_time==10||min_time==20||min_time==30||min_time==40||min_time==50))
    {
      //createEventPayload(CO2, CO2TC, UVAP, UVind);
      min_last = min_time;
      Log.info("Last Update: %d", min_last);
    }
    UpdateInterval = millis();
  }
}

/*
void createEventPayload(int CO2, int CO2TC, float UVAP, float UVind)
{
  JsonWriterStatic<256> jw;
  {
    JsonWriterAutoObject obj(&jw);
    jw.insertKeyValue("CO2(ppm)", CO2);
    jw.insertKeyValue("CO2_T(C)", CO2TC);
    jw.insertKeyValue("UVAPower(mW/cm2)", UVAP);
    jw.insertKeyValue("UVIndex", UVind);
  }
  Particle.publish("CooCooCachoo", jw.getBuffer(), PRIVATE);
}
*/