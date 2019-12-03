
unsigned long t;
unsigned long longPressure;
boolean countOn = false;

int baseTime = 3000;
int increaseTime = 1000;
int canelTime = 3000;
int waitTime = baseTime;

int pressureThreshold = 700;

void setup() {

  Serial.begin(9600);
  Serial.println("Start");
  pinMode (10, OUTPUT);
}

void loop() {

  if (analogRead(A0) > pressureThreshold) {

    tone(8, 4400, 100);
    delay(100);

    if (!countOn) {

      countOn = true;
      t = millis();
      Serial.print("Waiting ");
      Serial.println(waitTime);

      longPressure = millis();
      while (analogRead(A0) > pressureThreshold && millis() - longPressure <= canelTime) {}
      if (millis() - longPressure > canelTime) {
        Serial.println("Cancel");
        tone(8, 2400, 1000);
        delay(2000);
        countOn = false;
        while (analogRead(A0) > pressureThreshold) {}
      }

    } else {

      waitTime = waitTime + increaseTime;

      Serial.print("Waiting ");
      Serial.println(waitTime);

      longPressure = millis();
      while (analogRead(A0) > pressureThreshold && millis() - longPressure <= canelTime) {}
      if (millis() - longPressure > canelTime) {
        Serial.println("Cancel");
        tone(8, 2400, 1000);
        delay(2000);
        countOn = false;
        while (analogRead(A0) > pressureThreshold) {}
      }
    }
  }

  if (countOn) {
    if (millis() - t > waitTime)
    {
      Serial.println("Timeout");
      countOn = false;
    }
  }

  if (countOn) {
    Serial.print("Heating: ");
    Serial.println(map(millis(), t, t + waitTime, 0, 255));
   analogWrite(10, ( map( millis(), t, t + waitTime, 0, 255)) );



  }
}
