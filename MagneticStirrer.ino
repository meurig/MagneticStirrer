
// PINS
float potValue   = 0;  // A0 fom the potentiometer, speed control
int   fanSensor  = 0;  // Pulse indicating current RPM of the fan interrupt 0 = D2 (digital pin 2)
float fanPWM     = 3;  // PWM pin writes speed out to the fan

// Other
int   fanDivider = 4;  // Number of pulses per complete revolution
unsigned long SensorPulseWidth;
unsigned long counter = 0;
unsigned long counter2 = 0;
volatile int pwm_value = 0;
volatile int prev_time = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(potValue, INPUT);
  pinMode(fanSensor, INPUT);
  digitalWrite(fanSensor, HIGH);
  pinMode(fanPWM, OUTPUT);

  analogWrite(fanPWM, 0.0); // start off slow!

  attachInterrupt(fanSensor, rising, RISING);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(potValue);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // convert the analog reading (which goes from 0 - 1023) to a fan speed (0 - 255): 
  float fanSpeed = sensorValue / 4.0;
  
  // write it out to the PWM pin:
  analogWrite(fanPWM, fanSpeed);

  counter++;
  counter2++;

  if (counter >= 500)
  {
    // print out the value you read:
    //Serial.println(String(voltage) + " " + String(fanSpeed));
    
    //SensorPulseWidth = pulseIn(fanSensor, LOW, 100000); // read pulse width, 1000 microsecond timeout
    SensorPulseWidth = pwm_value;
    double frequency = 1000000/SensorPulseWidth;  // 1000000 microsec / SensorPulsTijd = aantal microsec per puls.

    /*Serial.print("Pulse width in microsec.  = ");
    Serial.println(SensorPulseWidth);
    Serial.print("Rotatietijd in microsec.  = ");
    Serial.println(SensorPulseWidth*fanDivider);
    Serial.print("Frequency in Herz         = ");
    Serial.println(frequency/fanDivider, 0); */
    Serial.print("Revolutions per Minute    = ");
    Serial.println(frequency/fanDivider*60);
    //Serial.println();
    //Serial.println();
    counter = 0; 
  }

  if (counter2 >= 50000)
  {
    pwm_value = 0;
    counter2 = 0;
  }
}

void rising() {
  attachInterrupt(fanSensor, falling, FALLING);
  prev_time = micros();
}
 
void falling() {
  attachInterrupt(fanSensor, rising, RISING);
  pwm_value = micros()-prev_time;
  //Serial.println(pwm_value);
}
