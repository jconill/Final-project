/*
  Joan Conill 201
  Maria Casas 201

  Joan Gomez
  Usos Academics en Amglés
*/
// We define each variable in order to have them well annoteded and defined forward on.
unsigned long t;
unsigned long longPressure;
boolean countOn = false;
// we give each variable an exact value
int baseTime = 3000; // It starts to count after 3 seconds
int increaseTime = 1000; // When we press again de button, it adds another second to the counting
int canelTime = 3000; // If you press de button for 3 seconds, it cancels de program
int waitTime = baseTime;

int pressureThreshold = 700; // From wich number the arduino detects it is pressed. When de resistors are 700 or higher it counts.

// All the information that we want ther arduino to start runing only one time after the program has started

void setup() {

  Serial.begin(9600); // Interval were we can see our data refleced in the Serial Monitor.
  Serial.println("Start"); // When you start runing the program after 3 seconds it shows you start
  pinMode (10, OUTPUT); // The thermal strip is conected to the analog pin mode 10
}
// All the information that you want to run in a loop, this information inside this void, it will run forever until its cancel.

void loop() {

  if (analogRead(A0) > pressureThreshold) { // Every time you press the button it sounds

    tone(8, 4400, 100); // The tone we have applyed to the sound
    delay(100); // a delay of 0,1 seconds

    if (!countOn) {

      countOn = true;
      t = millis(); // Millis is a variable that returns the number of milliseconds passed since the arduino board began running the computer program.
      Serial.print("Waiting "); // Until it doesnt get to the final number that you have stablished, it will be waiting time.
      Serial.println(waitTime); // And it will print WaitTime in the Serial monitor.

      longPressure = millis(); // If you press the button for 3 seconds...
      while (analogRead(A0) > pressureThreshold && millis() - longPressure <= canelTime) {} // it cancels de program
      if (millis() - longPressure > canelTime) {
        Serial.println("Cancel"); // And writes Cancel on the Serial Monitor
        tone(8, 2400, 1000); // We have given a different sound and tone to this process
        delay(2000);
        countOn = false;
        while (analogRead(A0) > pressureThreshold) {}
      }

    } else {

      // If the pressure is not bigger than 3 seconds Then do all of this below

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
  // here we have applyed the heating strip, when you are waiting, the arduino maps the program and starts heating that from 0 to 255 the maximum.
  if (countOn) {
    Serial.print("Heating: "); // It prints Heating
    Serial.println(map(millis(), t, t + waitTime, 0, 255)); // It goes form 0 to 255 in the period of thime that we have stablished to wait
    analogWrite(10, ( map( millis(), t, t + waitTime, 0, 255)) ); // It heats



  }
}


// Thank you so much for you attention 
