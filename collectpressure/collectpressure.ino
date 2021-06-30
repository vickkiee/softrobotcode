// https://softroboticstoolkit.com/low-cost-ep-circuit
// By Victoria Oguntosin

const int ADCFULLSCALE = 1024;              // ADC full scale of arduino is 10-bit (0-1023)
const float reference_voltage_mv = 5000.0;  // Vcc is 5000mv (5V) for ASDXACX100PAAA05
const int Pmax = 100;                       // 100psi for ASDXACX100PAAA05
const int Pmin = 0;                         // 0 psi FOR ASDXACX100PAAA05

const int analogInPin = A0;    // Analog input pin that the asdx pressure sensor is attached to

int sensorValue = 0;           // value read from the pressure sensor

float voltage_mv = 0.0;        // pressure sensor voltage in mV
float voltage_v = 0.0;         // pressure sensor voltage in volts
float output_pressure = 0.0;   // output pressure in psi
float vacuum_pressure = 0.0;   // vacuum pressure in psi (substract atmospheric pressure from output_preesure)
// We need to declare the data exchange
// variable to be volatile - the value is
// read from memory.


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  
   pinMode(5, OUTPUT);  // air pump
   pinMode(6, OUTPUT);  // air valve
   pinMode(7, OUTPUT);  // vacuum valve
   pinMode(13, OUTPUT);
   pinMode(2, INPUT);   // switch

}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);                              // digital value of pressure sensor voltage
  voltage_mv =  (sensorValue * reference_voltage_mv) / ADCFULLSCALE;  // pressure sensor voltage in mV
  voltage_v = voltage_mv / 1000;                                      
  output_pressure = ( ( (voltage_v - (0.10 * (reference_voltage_mv/1000) )) * (Pmax - Pmin) ) / (0.8 * (reference_voltage_mv/1000) ) ) + Pmin;
  vacuum_pressure = output_pressure - 14.6;                           // subtract atmospheric pressure

  Serial.println(analogRead(A0));
  
  if ( digitalRead(2) == HIGH) {
    digitalWrite(5,HIGH);  // air pump ON
    digitalWrite(6,HIGH);   // turn air valve HIGH
    digitalWrite(7,LOW);  // turn exhaust valve LOW 
    digitalWrite(13,HIGH);  // LED ON
  }
  
  else if ( digitalRead(2) == LOW) {    
    digitalWrite(5,LOW);  // air pump OFF
    digitalWrite(6,LOW);   //  turn air valve LOW
    //digitalWrite(7,HIGH);  //  turn exhaust valve HIGH 
    digitalWrite(7,LOW);   // im using this to check for pressure reading when pump is off but it is still holding pressure
    digitalWrite(13,LOW);  //  LED off
  }   

  delay(16);
}
