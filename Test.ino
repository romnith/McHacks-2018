#include "cellular_hal.h"

// Set the TELUS APN
STARTUP(cellular_credentials_set("isp.telus.com", "", "", NULL));

int led2 = D7;

void setup() {
  // Set the keep-alive value for TELUS SIM card
  Particle.keepAlive(30);

  Serial.begin(9600);

  pinMode(led2, OUTPUT);

}

void loop () {

   digitalWrite(led2, HIGH);

   delay(1000);

   digitalWrite(led2, LOW);

   delay(1000);

   Serial.printf("probtemp: \n");

}
