#include <Adafruit_MLX90614.h> //Library for MLX90614 temperature sensor
#include <Adafruit_SSD1306.h>  //Library for SSD1306 OLED display
#include <SPI.h>               //Library used for communicating with peripheral devices 
#include <Wire.h>              //Library used for communicating with I2C devices
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET  4
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire, OLED_RESET);  //Initialising the OLED display

Adafruit_MLX90614 mlx = Adafruit_MLX90614();    //Initialising the temperature sensor

#define ir 8
#define relay 3

void setup(){

  pinMode(ir,INPUT);
  pinMode(relay, OUTPUT);

  mlx.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);     //Initialising the OLED display
    display.clearDisplay();                     //clears the OLED display
  display.setTextSize(2);                      //Sets text size
  display.setTextColor(WHITE);                //sets text color  
  display.setCursor(0,0);                    //Sets cursor to first row first column
  display.print("   SMART     DOORBELL");
  display.display();                        //this function is used for the changes to make effect
}

void loop(){
  delay(500);                                   //delay of 500 milliseconds
  if(digitalRead(ir) == LOW){                  //IR sensor will output 0 or LOW if it detects any object
    float temp = mlx.readObjectTempC() + 4;   //temp variable stores temperature 
    if(temp <= 38) {
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Temp:");display.print(temp);display.print(" !WELCOME!");  //Prints temperature and welcomes user if the perso has normal body temperature
      display.display();
      digitalWrite(relay,HIGH);                                              //Triggers relay to ring door bell
    } else{
      digitalWrite(relay, LOW);
    display.clearDisplay();
      display.setCursor(0,0);
      display.print("HIGH TEMP! GO AWAY!");                             //Turns off the relay which does not ring the bell and tells person to go away due to high temperature
      display.display();
      }
  } else {                         //If the IR sensor does not detect anything
    digitalWrite(relay,LOW);
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("   SMART     DOORBELL");        //Just prints
    display.display();
  }
 
}
