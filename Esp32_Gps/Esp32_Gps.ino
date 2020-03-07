#include "TinyGPS++.h"
#include <SoftwareSerial.h>
TinyGPSPlus gps;
SoftwareSerial SerialGPS(32,35);

void setup() {
  SerialGPS.begin(9600); // Gps
}
int socketcounter=0;
void loop() {
  gps.encode(SerialGPS.read());
  gpssocket.beginMessage(TYPE_TEXT);
    if(printFloat(gps.location.lat(), gps.location.isValid(), 11, 6).charAt(1) == '*'){
        Serial.println("[{gps:false,loc_lati:0,loc_long:0,lastLocationDate:\""+printDateTime(gps.date, gps.time)+"\"}]");
    }else{
        Serial.println("[{gps:true,count:"+String(socketcounter)+",loc_lati:" + printFloat(gps.location.lat(), gps.location.isValid(), 11, 6) + ",loc_long:" + printFloat(gps.location.lng(), gps.location.isValid(), 12, 6) + ",lastLocationDate:\""+printDateTime(gps.date, gps.time)+"\"}]");
    }socketcounter++;
    
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (SerialGPS.available())
      gps.encode(SerialGPS.read());
  } while (millis() - start < ms);
}
static String printFloat(float val, bool valid, int len, int prec)
{
  String konum;
  if (!valid)
  {
    while (len-- > 1)
      konum+="*";
    konum+=" ";
  }
  else
  {
    konum+=String(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    
      
  }
  smartDelay(0);
  return konum;
}


static String printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  String tarih="";
  if (!d.isValid())
  {
    tarih+=String(F("**** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    tarih+=String(sz);
  }
  
  if (!t.isValid())
  {
    tarih+=String(F("**** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d", t.hour(), t.minute(), t.second());
    tarih+=String(sz);
  }

  smartDelay(0);
  return tarih;
}
