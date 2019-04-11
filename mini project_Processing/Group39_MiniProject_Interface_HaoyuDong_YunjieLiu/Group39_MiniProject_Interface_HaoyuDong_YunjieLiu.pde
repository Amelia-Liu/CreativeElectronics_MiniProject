//Processing Code of the interface of the "Smart Shadow"
//Mini project for Creative Electronics Course (DBB200)
//By Group 39: Haoyu Dong and Yunjie Liu

import processing.serial.*; 
import controlP5.*; 

Serial myPort; //Create object from Serial class
String val; //Data received from the serial port
ControlP5 controlP5; //Create objetc from ControlP5 class
PFont font; //Declare a new font

void setup() {
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600); //Declare the new port

  controlP5 = new ControlP5(this); //Create a top level control manager

  fullScreen();
  pixelDensity(2); // ask Processing to render using all of the pixels on high resolutions screens
  background (255); //Set up the background color
  controlP5.setColorBackground(200);
  font = createFont("Montserrat-Light.ttf", 21); //Create the font and the default size
  controlP5.setFont(font); //Declare to use the font in the controlP5 controlers
  controlP5.addButton("Manual", 1, 300, 700, 200, 60); // set the name, value, x-position, y-position, width and height of the "Manual" button
  controlP5.addButton("LightControl", 2, 600, 700, 350, 60); //set the name, value, x-position, y-position, width and height of the "LightControl" button
}

void Manual(float value) {

  print(value); // print 1 when the "Manual" button is clicked
  myPort.write('1'); // send the signal to the Arduino
}
void LightControl(float value) {
  print(value); // print 2 when the "LightControl" button is clicked
  myPort.write('2');// send the signal to the Arduino
}

void draw() {
  textFont(font);
  textSize(70);

  noStroke();

  fill(#767676);
  text("Smart Shadow", 300, 500); // create the text "Smart Shadow" in the interface
}