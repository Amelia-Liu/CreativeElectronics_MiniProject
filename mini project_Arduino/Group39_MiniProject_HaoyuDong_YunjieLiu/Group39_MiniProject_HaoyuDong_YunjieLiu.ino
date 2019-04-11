//Arduino Code of "Smart Shadow"
//Mini project for Creative Electronics Course (DBB200)
//By Group 39: Haoyu Dong and Yunjie Liu

#include <Servo.h>
Servo myservo;

int LightSensor = A0; //Set the light sensor to pin A0
int touchup = 3; //Set the touch module 1 to pin 3 for opening the curtain
int touchdown = 4;//Set the touch module 2 to pin 4 for opening the curtain
boolean up = false; //Initialize the touch module 1 as untouched
boolean down = false; //Initialize the touch module 2 as untouched
long lighttime = 0;// Initialize the value of timing light intensity
boolean open = true; //Toggle the curtain as open
int status = 0; //Initialize the control mode as 0

void setup() {
  Serial.begin(9600); //Initialize serial communications at a 9600 baud rate
  pinMode(touchup, INPUT);// Set pin as INPUT
  pinMode(touchdown, INPUT);// Set pin as INPUT
  myservo.attach(9);//Servo attaching to pin 9
  myservo.write(90);//Servo stops
}

void loop() {
  if (Serial.available() > 0) { //Checking if Processing
    char val = Serial.read(); //Reading the value and store it in val
    if (val == '1') { //If 1 was received
      status = 1;//Then set it as manual control mode
      Serial.println("Status = 1");
    }
    if (val == '2') { //If 2 was received
      status = 2;//Then set it as light sensor control mode
    }
  }
  //----------------------Manual Control Mode:---------------------------
  if (status == 1) {
    Serial.println("Status - manual");
    up = digitalRead(touchup); //Read the value from the touchup pin
    down = digitalRead(touchdown);//Read the value from the touchdown pin
    if (up == true) { //Touch module 1 is touched
      Serial.println("Going Up");
      myservo.write(180);//Servo rotating clockwise
    } else if (down == true) {//Touch module 2 is touched
      Serial.println("Going Down");
      myservo.write(0);//Servo rotating counterclockwise
    } else { //If no touch module was touched
      Serial.println("Stop");
      myservo.write(90);//Servo stops
    }
  }
  //--------------------Light Sensor Control Mode:-----------------------
  if (status == 2) {
    Serial.println("Status - ligh control");
    int light = analogRead(LightSensor);//Read the value from the light sensor
    Serial.println(light);

    //If the light intensity is higher than the threshold and the curtain is open
    if (light > 500 && open) {
      if (lighttime == 0) {
        lighttime = millis(); //Timing the high light intensity
        //Serial.println(lighttime);
      }

      if (millis() - lighttime > 5000) { //Define the valid time as 5 seconds
        Serial.println(millis());
        myservo.write(0); //Servo rotating clockwise
        delay(9500); //Delay for 9.5 seconds to close the curtain entirely
        myservo.write(90);//Servo stops
        lighttime = 0; //Initializing the lighttime
        open = false; //Curtain closed
      }

      //If the light intensity is lower than the threshold and the curtain is closed
    } else if (light <= 500 && !open) {
      if (lighttime == 0) {
        lighttime = millis();//Timing the low light intensity
        Serial.println(lighttime);
      }
      if (millis() - lighttime > 5000) {//Define the valid time as 5 seconds
        Serial.println(millis());
        myservo.write(180);//Servo rotating counterclockwise
        delay(9500);//Delay for 9.5 seconds to open the curtain entirely
        myservo.write(90);//Servo stops
        lighttime = 0;//Initializing the lighttime
        open = true;//Curtain open
      }
    }
  }
}
