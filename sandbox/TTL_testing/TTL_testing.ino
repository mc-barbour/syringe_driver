/*
 * Created by Michael Barbour
 * 
 * Script to test the TTL comm with the syringe pumpe
 * 
 * Delivers a 5V TTL signal for 5 sec than switches off
 * Turn LED on for output signal
 */
 
const int ledPin = 13; // LED pin to visualize when pump is triggered
const int ttlPin = 12; // Pump trigger pin
const int exhalationPeriod = 5000; // exhalation period, need for delay in TTL signal
const int ttlPeriod = 3000; // duration of ttl signal being High
 
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ttlPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // Turn LED and TTL high
  digitalWrite(ledPin, HIGH);
  digitalWrite(ttlPin, HIGH);

  // Wait for a duration
  delay(ttlPeriod);

  //Turn LED and TTL pin Low
  digitalWrite(ledPin, LOW);
  digitalWrite(ttlPin, LOW);

  // Wait for another duration
  delay(exhalationPeriod);
  
}
