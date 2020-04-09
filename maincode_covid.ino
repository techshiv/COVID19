//Defining the libraries
//Links in the Readme section

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int actind = 0, recovind = 0, deadind = 0, actkar = 0, deadkar = 0;
//Connect the SCL pin of OLED to D1 of NodeMCU
//Connect the SDA pin of OLED to D2 of NodeMCU

const char* ssid = "WIFI SSID";  //Enter your SSID of your WiFi (keep it within double quote)
const char* password = "WIFI PSWD";  //Enter your PASSWORD of your WiFi (keep it within double quote)
WiFiClient client;

// Set your hosting Website (Here it is www.thingspeak.com)
const char* host = "api.thingspeak.com";
const int httpPortRead = 80;
// "XXXXXXXXXXXXXXX" represents your 16 digit API Key generated from Thingspeak i.e ThingHTTP
//India ContryData of COVID19
const char* url = "/apps/thinghttp/send_request?api_key=5DJOPQOJLC4ABMNV"; //cases
const char* url2 = "/apps/thinghttp/send_request?api_key=Y2PXJ91VE87FGR21"; // deaths
const char* url3 = "/apps/thinghttp/send_request?api_key=PW4FQ5BRR81EJUFP"; //recovered

//Karnataka State data of COVID19
const char* url4 = "/apps/thinghttp/send_request?api_key=YM6ITOP96WUTFEQQ"; //cases
const char* url5 = "/apps/thinghttp/send_request?api_key=T95BB7I1J3MYFL5W"; // deaths
const char* url6 = "/apps/thinghttp/send_request?api_key=TWBUHH1NR11HDQ7I"; //recovered

HTTPClient http;

void setup() {


  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("COVIDInfo INDIA");
  lcd.setCursor(3, 1);
  lcd.print("LIVE UPDATE ");
  lcd.setCursor(0, 2);
 
  Serial.begin(9600);
  WiFi.disconnect();
  delay(1000);
  Serial.println();
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");


  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP
}

void loop()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(ssid, password);
    Serial.println("Reconnecting to WiFi..");
    delay(20000);
  }
 

  if ( http.begin(host, httpPortRead, url))
  {
    int httpCode = http.GET();
    if (httpCode > 0)
    {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String actind = http.getString();
        Serial.print("Confirmed Cases: ");
        Serial.println(actind);
        //
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("India COVID19");
        lcd.setCursor(3, 1);
        lcd.print("Cases:");
        lcd.setCursor(10, 1);
        lcd.print(actind);
        delay(1000);
      }
      if ( http.begin(host, httpPortRead, url2))
      {
        int httpCode = http.GET();
        if (httpCode > 0)
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
          {
            String deadind = http.getString();
            Serial.print("Deaths: ");
            Serial.println(deadind);

            lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("India COVID19");
        lcd.setCursor(3, 1);
        lcd.print("Death:");
        lcd.setCursor(10, 1);
        lcd.print(deadind);
        delay(1000);
         
          }
          if ( http.begin(host, httpPortRead, url3))
          {
            int httpCode = http.GET();
            if (httpCode > 0)
            {
              if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
              {
                String recovind = http.getString();
                Serial.print("Recovered: ");
                Serial.println(recovind);
                  lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("India COVID19");
        lcd.setCursor(2, 1);
        lcd.print("Recovered:");
        lcd.setCursor(13, 1);
        lcd.print(recovind);
        delay(1000);

               }
            }
          }
          delay(3000);
         
  if ( http.begin(host, httpPortRead, url4))
          {
            int httpCode = http.GET();
            if (httpCode > 0)
            {
              if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
              {
                String actkar = http.getString();
                Serial.print("karnataka cases: ");
                Serial.println(actkar);
lcd.clear();
                 lcd.setCursor(0, 0);
        lcd.print("KARNATAKA COVID");
        lcd.setCursor(2, 1);
        lcd.print("CASES:");
        lcd.setCursor(8, 1);
        lcd.print(actkar);
        delay(1000);
                
              }
            }
          }
          if ( http.begin(host, httpPortRead, url5))
          {
            int httpCode = http.GET();
            if (httpCode > 0)
            {
              if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
              {
                String deadkar = http.getString();
                Serial.print(" karnataka Death: ");
                Serial.println(deadkar);

lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("KARNATAKA COVID");
        lcd.setCursor(2, 1);
        lcd.print("DEATH:");
        lcd.setCursor(9, 1);
        lcd.print(deadkar);
        delay(1000);
              
              }
            }
          }
        
          if ( http.begin(host, httpPortRead, url6))
          {
            int reckar = http.GET();
            if (httpCode > 0)
            {
              if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
              {
                String reckar = http.getString();
                Serial.print(" karnataka Recvrd:");
                Serial.println(reckar);
                // lcd.setCursor(0, 0);
                lcd.clear();
        lcd.print("KARNATAKA COVID");
        lcd.setCursor(1, 1);
        lcd.print("Recovered:");
        lcd.setCursor(12, 1);
        lcd.print(reckar);
        delay(1000);
               
              }
            }
          }
        }
      }
      else
      {
        Serial.println("Error in response");
      }
      http.end();  //Close connection
      delay(3000);  //GET Data at every 5 seconds
      Serial.println("NEW INFO");
    }
  }
 


}
