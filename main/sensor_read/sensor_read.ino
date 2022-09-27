/*
 * Created by Michael Barbour
 * 
 * script to read analog voltage signal from pressure transducer and plot the data
 * 
 */

const int ledPin = 13; // LED pin to 
const int sensorPin = A0; // Pump trigger pin

const int ttlPin = 12; // Pump trigger pin
const int exhalationPeriod = 2000; // exhalation period, need for delay in TTL signal
const int ttlPeriod = 1000; // duration of ttl signal being High

const float thresholdPressure = 8.5; // pressure value on which to trigger the syringe pump
// 5 cmh20 works well with lung disconnected
// 8.5 chH20 when connected to lung

int sensorValue = 0; // initialize sensor value: 0-1023
float voltage = 0.0; // scaled voltage value
float pressure = 0.0; // pressure value
float zero_offset_sensor = -0.67; // voltage from pressure sensor at zero-flow

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ttlPin, OUTPUT);
  Serial.begin(9600);
}


float voltageConvert(float volt_in, float scale, float b) // May need to account for sensor offset
{
  return volt_in * scale + b;
}


void loop() {

  sensorValue = analogRead(sensorPin);
  voltage = sensorValue * 5.0 / 1023.0; // convert from bits to volts

  pressure = voltageConvert(voltage, 1.0, zero_offset_sensor ) * 70.3; // convert from voltage to psi then to cm H20
  
  Serial.println(pressure); // add value to serial plotter
  Serial.print(" "); // not sure what this does

  // comment this loop if you just want to display pressure
  
  if (pressure > thresholdPressure){
    
    digitalWrite(ledPin, HIGH);
    digitalWrite(ttlPin, HIGH);
    delay(ttlPeriod);

    digitalWrite(ledPin, LOW);
    digitalWrite(ttlPin, LOW);
    delay(exhalationPeriod);
  }
  
  delay(100); // control data read rate
}
