//petal pin assignments
const int petal1 = 0;
const int petal2 = 1;
const int petal3 = 2;
const int petal4 = 3;

//petal thresholds
int thresh1 = 300;
int thresh2 = 200;
int thresh3 = 400;
int thresh4 = 100;

//photoresistor pin
const int sensorPin = 0;

//lightVal
int lightVal = 0;

//minimum and maximum sensor values
int sensorMin = 1023;
int sensorMax = 0;
int sensorValue = 0;

////////////////////// SETUP //////////////////////////
void setup(){
  Serial.begin(9600);
  
  pinMode(petal1, OUTPUT);
  pinMode(petal2, OUTPUT);
  pinMode(petal3, OUTPUT);
  pinMode(petal4, OUTPUT);
  
  //calibration
  Serial.println("calibrating...ramp light up and down.....");
  while (millis() < 5000) {
   sensorValue = analogRead(sensorPin);

   // record the maximum sensor value
   if (sensorValue > sensorMax) {
     sensorMax = sensorValue;
   }

   // record the minimum sensor value
   if (sensorValue < sensorMin) {
     sensorMin = sensorValue;
   }
 }
 
 Serial.println("calibration finished");
 Serial.print("minimum value: ");
 Serial.println(sensorMin);
 Serial.print("maximum value: ");
 Serial.println(sensorMax);
  
 //wait five seconds to let it all sink in 
 delay(5000);
}


//////////////////// LOOP /////////////////////////////
void loop() {
  //read potentiometer and print value
  lightVal = analogRead(sensorPin);
  
  //map values to 0 500
  lightVal = constrain(lightVal, sensorMin, sensorMax);
  lightVal = map(lightVal, sensorMin, sensorMax, 0.0, 500.0);
  Serial.println(lightVal);

  
  //check threshold for each petal
  if(lightVal > thresh1)
  {
    digitalWrite(petal1, HIGH);
  }else{
    digitalWrite(petal1, LOW);
  }
  
  //check threshold for each petal
  if(lightVal > thresh2)
  {
    digitalWrite(petal2, HIGH);
  }else{
    digitalWrite(petal2, LOW);
  }
  
  //check threshold for each petal
  if(lightVal > thresh3)
  {
    digitalWrite(petal3, HIGH);
  }else{
    digitalWrite(petal3, LOW);
  }
  
  //check threshold for each petal
  if(lightVal > thresh4)
  {
    digitalWrite(petal4, HIGH);
  }else{
    digitalWrite(petal4, LOW);
  }
  
  //check for lower threshold
  //set petalPin to low
  
}



