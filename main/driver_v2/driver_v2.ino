/*
 * Created by Michael Barbour
 * 
 * script to read analog voltage signal from pressure transducer and plot the data
 * 
 * Notes:  
 * Pressure thresholds: 5 cmh20 works well with lung disconnected
                        8.5 chH20 when connected to lung
 */
 
// User inptuts: based on respiratory period
const int exhalationPeriod = 3000; // exhalation period, need for delay in TTL signal
const int injectionTime = 250; // duration of ttl signal being High
const float thresholdPressure = 9.5; // pressure value on which to trigger the syringe pump


const int ttlPin = 12; // Pump trigger pin
const int ledPin = 13; // LED pin to 
const int sensorPin = A0; // Pump trigger pin


const int respiratoryDelay = injectionTime + exhalationPeriod;


int ttlPinValue = 0; // variable to monitor status of syringe pump
int sensorValue = 0; // initialize sensor value: 0-1023
int syringePumpState = LOW; 
float voltage = 0.0; // scaled voltage value
float pressure = 0.0; // pressure value
float zero_offset_sensor = -0.67; // voltage from pressure sensor at zero-flow
long pumpStartTime = 0.0;
long pumpStopTime = 0.0;


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
  
  unsigned long currentMillis = millis();
  
  sensorValue = analogRead(sensorPin);
  voltage = sensorValue * 5.0 / 1023.0; // convert from bits to volts
  pressure = voltageConvert(voltage, 1.0, zero_offset_sensor ) * 70.3; // convert from voltage to psi then to cm H20

  
  Serial.println(pressure); // add value to serial plotter
  Serial.print(","); // not sure what this does
  Serial.println(ttlPinValue); // add value to serial plotter

  // comment this loop if you just want to display pressure
  /*
  if ((pressure > thresholdPressure) && (currentMillis - pumpStopTime >= respiratoryDelay)){
    if (syringePumpState == LOW){
      pumpStartTime = currentMillis;
    }
    syringePumpState = HIGH;
    ttlPinValue = 10;
    digitalWrite(ttlPin, syringPumpState);
  }

  else if ((pressure > thresholdPressure) && (currentMillis - pumpStartTime >= injectionTime)){
    syringePumpState = LOW;
    ttlPinValue = 0;
    pumpStopTime = currentMillis;
    digitalWrite(ttlPin, syringPumpState);
  }
*/

  if (pressure > thresholdPressure){

    if ((syringePumpState == LOW) && (currentMillis - pumpStopTime >= respiratoryDelay)){
      syringePumpState = HIGH;
      pumpStartTime = currentMillis;
      ttlPinValue = 10;
      digitalWrite(ttlPin, syringePumpState);
    }

    else if ((syringePumpState == HIGH) && (currentMillis - pumpStartTime >= injectionTime)){
      syringePumpState = LOW;
      ttlPinValue = 0;
      pumpStopTime = currentMillis;
      digitalWrite(ttlPin, syringePumpState);
    }
  }


  
  delay(100); // control data read rate
}
