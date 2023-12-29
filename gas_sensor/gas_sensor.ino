// tokens
#define BLYNK_TEMPLATE_ID "TMPL67AvEXVjE"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "jGfWHMZsW1C0K9krxZKuxP8t1SWji2Ko"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define WIFI_NAME "Swinburne Students"
#define WIFI_PWD "Swinburne@a35"

// devices
const int GAS_PIN       = A0;
const int LIGHT_LED     = 4;
const int MEDIUM_1_LED  = 0;
// const int MEDIUM_2_LED  = 3;
const int SEVERE_1_LED  = 2;
// const int SEVERE_2_LED  = 5;
const int GAS_VPIN      = V0;
const int LIGHT_VPIN    = V1;
const int MEDIUM_VPIN   = V2;
const int SEVERE_VPIN   = V3;

// constants
const int MAX_GAS_ANALOG  = 380;
const int MIN_GAS_ANALOG  = 0;
const int GAS_LIGHT       = 0;      // all modes below are written in percentage
const int GAS_MEDIUM_1    = 20;
// const int GAS_MEDIUM_2    = 40;
const int GAS_SEVERE_1    = 60;
// const int GAS_SEVERE_2    = 80;

// fields
int gas_percentage  = 0;
int light_mode      = LOW;
int medium_1_mode   = LOW;
// int medium_2_mode   = LOW;
int severe_1_mode   = LOW;
// int severe_2_mode   = LOW;

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_NAME);
 
  WiFi.begin(WIFI_NAME, WIFI_PWD);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_NAME, WIFI_PWD);
  pinMode(GAS_PIN, 		INPUT);
  pinMode(LIGHT_LED, 	OUTPUT);
  pinMode(MEDIUM_1_LED, OUTPUT);
  // pinMode(MEDIUM_2_LED, OUTPUT);
  pinMode(SEVERE_1_LED, OUTPUT);
  // pinMode(SEVERE_2_LED, OUTPUT);
}

void loop()
{
  Blynk.run();
  // gather sensor information
  gas_percentage = map(analogRead(GAS_PIN), MIN_GAS_ANALOG, MAX_GAS_ANALOG, 0, 100);
  light_mode = gas_percentage >= GAS_LIGHT ? HIGH : LOW;
  medium_1_mode = gas_percentage >= GAS_MEDIUM_1 ? HIGH : LOW;
  // medium_2_mode = gas_percentage >= GAS_MEDIUM_2 ? HIGH : LOW;
  severe_1_mode = gas_percentage >= GAS_SEVERE_1 ? HIGH : LOW;
  // severe_2_mode = gas_percentage >= GAS_SEVERE_2 ? HIGH : LOW;
  // toggle LED lights
  digitalWrite(LIGHT_LED,     light_mode);
  digitalWrite(MEDIUM_1_LED,  medium_1_mode);
  // digitalWrite(MEDIUM_2_LED,  medium_2_mode);
  digitalWrite(SEVERE_1_LED,  severe_1_mode);
  // digitalWrite(SEVERE_2_LED,  severe_2_mode);
  // send info to Blynk
  Blynk.virtualWrite(GAS_VPIN,    gas_percentage);
  Blynk.virtualWrite(LIGHT_VPIN,  light_mode);
  Blynk.virtualWrite(MEDIUM_VPIN, medium_1_mode);
  Blynk.virtualWrite(SEVERE_VPIN, severe_1_mode); // due to lack of datastream for Blynk, only 4 is available
  Serial.print("Smoke percentage: ");
  Serial.print(gas_percentage);
  Serial.println("%");
//  Serial.println(analogRead(GAS_PIN));
  delay(10); // Delay a little bit to improve simulation performance
}
