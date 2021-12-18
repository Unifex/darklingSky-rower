const int trigPin = 3;
const int echoPin = 2;

float  timeVal = 0.07;
float  readDelayTime = 1000 * timeVal;
int    speedIndex = 0;

long   durationVal;
int    firstDistance;
int    secondDistance;
int    distanceVal;

double speedVal;
double speedVals[10];
bool   resetSpeedVals = false;
int    speedValCount = 0;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 
}

void loop() {
  speedVal = GetSpeed();

  // We're on the pull part of the stroke.
  if (speedVal < 0) {
    // Negative values are the stroke. Count these for adding velocity.
    if (speedIndex < 10) {
      speedVals[speedIndex++] = speedVal;
      resetSpeedVals = true;
    }
  }

  // We are on the return to prepare for the next stroke.
  if (speedVal > 0 && resetSpeedVals) {
    speedVal = 0;
    speedValCount = 0;
    for (int i = 0; i < 10; i++) {
      if (speedVals[i] < 0) {
        speedVal += abs(speedVals[i]);
        speedValCount++;
      }
//      Serial.println(speedVals[i]);
      // Zero the array as we go.
      speedVals[i] = 0;
    }
    if (speedValCount > 3) {
      Serial.print("speedVal : ");
      Serial.println(speedVal);
      Serial.print("speedValCount : ");
      Serial.println(speedValCount);
      // We have something worth working with.
      speedVal = speedVal / speedValCount;
      Serial.print("The speed (km/h) of the stroke was  :  ");
      Serial.println(speedVal);
    }

    // Reset for the next stroke.
    resetSpeedVals = false;
    speedIndex = 0;
  }
}

float GetDistance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds.
  durationVal = pulseIn(echoPin, HIGH);
  
  // Calculating distance.
  distanceVal = durationVal * 0.034 / 2;
  
  // Return if we have a propper value.  The sensor occasionally returns
  // false readings.  These are around the 1185 mark.
  if (distanceVal < 1100) {
    return distanceVal;
  }
  else {
    return 0;
  }
}

float GetSpeed(){ 
   firstDistance = GetDistance();
   // Wait the readDelayTime.
   delay(readDelayTime);
   secondDistance = GetDistance();

   if (firstDistance > 0 && secondDistance > 0) {
     // Now calculate the difference.
     speedVal = (firstDistance - secondDistance) / timeVal;
     speedVal = speedVal / 27.778;
     return speedVal;
   }
   return 0;
}
