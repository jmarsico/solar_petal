
typedef struct Petal{
  int pin;
  boolean isClosed;
  int timeOpen;
  boolean Start;
};

Petal petal[4];


//petal thresholds
int thresh1 = 100;
int thresh2 = 200;
int thresh3 = 300;
int thresh4 = 400;

//photoresistor pin
const int sensorPin = 0;

//lightVal
int lightVal = 0;

//minimum and maximum sensor values
int sensorMin = 1023;
int sensorMax = 0;
int sensorValue = 0;

//counter for petal timing
int counter = 0;



////////////////////// SETUP //////////////////////////

void setup(){
  Serial.begin(9600);

  petal[0].pin = 6;
  petal[1].pin = 5;
  petal[2].pin = 4;
  petal[3].pin = 3;

  petal[0].isClosed = false;
  petal[1].isClosed = false;
  petal[2].isClosed = false;
  petal[3].isClosed = false;

  pinMode(petal[0].pin, OUTPUT);
  pinMode(petal[1].pin, OUTPUT);
  pinMode(petal[2].pin, OUTPUT);
  pinMode(petal[3].pin, OUTPUT);

  for(int i = 0;i < 4; i++)
  {
    digitalWrite(petal[i].pin, LOW);
  }

  ///////////////calibration/////////////////////////////////
  Serial.println("calibrating...ramp light up and down.....");
  while (millis() < 6000) {
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




/////////// check thresholds ////////////////////
  if(lightVal>thresh1)
  {
    petal[0].isClosed = true;

  } else {
    petal[0].isClosed = false;
  }

  if(lightVal > thresh2)
  {
    petal[1].isClosed = true;
  } else {
    petal[1].isClosed = false;
  }

  if(lightVal > thresh3)
  {
    petal[2].isClosed = true;
  } else {
    petal[2].isClosed = false;
  }

  if(lightVal > thresh4)
  {
    petal[3].isClosed = true;
  } else {
    petal[3].isClosed = false;
  }

  //////////// ACTUATION ///////////////////////

  if(petal[0].isClosed)
  {
    if(counter%100 == 0)
    {
      digitalWrite(petal[0].pin, !digitalRead(petal[0].pin));
    }
  } 


  if(petal[1].isClosed)
  {
    if((counter - 20)%125 == 0)
    {
      digitalWrite(petal[1].pin, !digitalRead(petal[1].pin));
    }
  } 
  else {
    digitalWrite(petal[1].pin, LOW);
  }

  if(petal[2].isClosed)
  {
    if((counter - 50)%115 == 0)
    {
      digitalWrite(petal[2].pin, !digitalRead(petal[2].pin));
    }
  } 
  else {
    digitalWrite(petal[2].pin, LOW);
  }

  if(petal[3].isClosed)
  {
    if((counter - 30)%150== 0)
    {
      digitalWrite(petal[3].pin, !digitalRead(petal[3].pin));
    }
  } 
  else {
    digitalWrite(petal[3].pin, LOW);
  }



  Serial.print("counter: ");
  Serial.print(counter);
  Serial.print(" | Val: ");
  Serial.print(lightVal);
  for(int i = 0; i < 4; i++)
  {
    if(petal[i].isClosed)
    {
      Serial.print(" | ");
      Serial.print(i);

    }
    Serial.print(" state: ");
    Serial.print(digitalRead(petal[i].pin));
  }
  Serial.println();

  //update counter
  counter++;


  //if lightVal very low, turn off all connections.
  if(lightVal < thresh1)
  {
    for(int i = 0; i < 4; i++)
    {
      digitalWrite(petal[i].pin, LOW);
    }
  }

}






