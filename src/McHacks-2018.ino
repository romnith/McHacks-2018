/*
 * Project McHacks-2018
 * Description: Home monitoring utilizing AWS and Cisco Spark Bot
 * Author: Romain Nith, Greg Woo, Milo Sobral, Romain Couperier
 * Date: 02/04/2018
 */

#include "cellular_hal.h"
#include "DHT.h"
#include "application.h"
#include "HttpClient/HttpClient.h"

// Defining pin for DHT sensor
#define DHTPIN 0
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Set the Telus APN
STARTUP(cellular_credentials_set("isp.telus.com","","", NULL));

// Var setup
float h, t, f;


void setup() {

  Serial.begin(9600);
  // Set the keep-alive value for TELUS SIM card
  Particle.keepAlive(30);

  // Init DHT sensor
  dht.begin();
}

void loop () {

  /* --------------------- Humidity -----------------------*/
  // Read Humidity in %
  h = dht.readHumidity();
  // Send to cloud
  Particle.publish("Humidity", String::format("%.2f",h), NO_ACK);

  // Delay 5 sec before checking for next sensor input
  delay(12000);

  /* ------------------- Temperature C --------------------*/
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Send to cloud
  Particle.publish("TemperatureC", String::format("%.2f",t), NO_ACK);

  // Read temperature as Fahrenheit (isFahrenheit = true)
  f = dht.readTemperature(true);
  // Send to cloud
  Particle.publish("TemperatureF", String::format("%.2f",f), NO_ACK);


  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Delay 5 sec before checking for next sensor input
  delay(12000);
}
