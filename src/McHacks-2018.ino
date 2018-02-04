/*
 * Project McHacks-2018
 * Description:
 * Author:
 * Date:
 */

#include "cellular_hal.h"
#include "DHT.h"
#include "application.h"
#include "HttpClient/HttpClient.h"

#define DHTPIN 0
#define DHTTYPE DHT22

// Set the Telus APN
STARTUP(cellular_credentials_set("isp.telus.com","","", NULL));

// Var setups
int led2 = D7;
int temp = D0;
float h, t, f;
//bool  httpSucess = false;

DHT dht(DHTPIN, DHTTYPE);
//
// HttpClient http;

// Headers currently need to be set at init, useful for API keys etc.
// http_header_t headers[] = {
//     //  { "Content-Type", "application/json" },
//     //  { "Accept" , "application/json" },
//     { "Accept" , "*/*"},
//     { NULL, NULL } // NOTE: Always terminate headers will NULL
// };
//
// http_request_t request;
// http_response_t response;

void setup() { // Set the keep-alive value for TELUS SIM card Particle.keepAlive(30);
  Serial.begin(9600);
  // Set the keep-alive value for TELUS SIM card
  Particle.keepAlive(30);

  dht.begin();

  pinMode(led2, OUTPUT);
}

void loop () {
  // digitalWrite(led2, HIGH);
  // delay(1000);
  // digitalWrite(led2, LOW);
  //delay(2000);
  // probtemp = digitalRead(temp);
  //Serial.printf("probtemp:" );
  // Particle.publish("The temperature is: ", probtemp);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


  Particle.publish("Humidity: ", String::format("%.2f",h), NO_ACK);
  Particle.publish("Temperature C: ", String::format("%.2f",t), NO_ACK);
  Particle.publish("Temperature F: ", String::format("%.2f",f), NO_ACK);

  Particle.publish("TempSensor", String::format("%.2f",h), PRIVATE);
  // Wait 60 seconds

  // Serial.print("Humidity: ");
  // Serial.print(h);
  // Serial.print(" %\t");
  // Serial.print("Temperature: ");
  // Serial.print(t);
  // Serial.print(" *C ");
  // Serial.print(f);
  // Serial.print(" *F\t");

//  try{
    // // Request path and body can be set at runtime or at setup.
    // request.hostname = "eac5rb7t98.execute-api.us-east-2.amazonaws.com/";
    // //request.port = 80;
    // request.path = "/testStage/temp";
    //
    // // The library also supports sending a body with your request:
    // request.body = "{\"key\":\"value\"}";
    //
    // // Get request
    // http.post(request, response, headers);
    // Serial.print("Application>\tResponse status: ");
    // Serial.println(response.status);
    //
    // Serial.print("Application>\tHTTP Response Body: ");
    // Serial.println(response.body);

    //httpSucess = true;

  // }catch(const std::exception& e){
  //   httpSucess = false;
  // }
  //
  // if(httpSucess){
  //   Particle.publish("HTTP Success", "Success");
  // }
  // else{
  //   Particle.publish("HTTP Success", "Failed");
  // }

  delay(10000);

}
