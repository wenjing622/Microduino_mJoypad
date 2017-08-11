/*************************************************
  本示例给出了获取mJoypad上输入传感器的数值的方法
  包含：左侧三路输入模拟信号值（0-255）
        摇杆X轴模拟值（0-255）
        摇杆Y轴模拟值（0-255）
        光照值（0-255）
        声音值（0-255）

        按键A(0/1)
        按键B(0/1)
        摇杆上(0/1)
        摇杆下(0/1)
        摇杆左(0/1)
        摇杆右(0/1)
****************************************
   2017-08-10  by CWJ
****************************************/

#include "Microduino_mJoypad.h"

uint8_t adcData[7];
bool button_a, button_b, button_u, button_d, button_l, button_r;

void setup() {
  Serial.begin(9600);
  mJoypad.begin();
  Serial.println("TEST START");
}

void loop() {
  //*****************get********获取数据
  adcData[0] = mJoypad.getIN(0);     
  adcData[1] = mJoypad.getIN(1);
  adcData[2] = mJoypad.getIN(2);
  adcData[3] = mJoypad.getJoysticX();
  adcData[4] = mJoypad.getJoysticY();
  adcData[5] = mJoypad.getLight();
  adcData[6] = mJoypad.getMic();

  button_a = mJoypad.getButtonA();
  button_b = mJoypad.getButtonB();
  button_u = mJoypad.getButtonUp();
  button_d = mJoypad.getButtonDown();
  button_l = mJoypad.getButtonLeft();
  button_r = mJoypad.getButtonRight();

  //*****************print*****数据监视
  Serial.print("IN[3]: ");
  Serial.print(adcData[0]);         // print the character
  Serial.print(",\t");
  Serial.print(adcData[1]);         // print the character
  Serial.print(",\t");
  Serial.print(adcData[2]);         // print the character
  Serial.print(", \t");
  Serial.print("Joystick_X_Y: ");
  Serial.print(adcData[3]);         // print the character
  Serial.print(", \t");
  Serial.print(adcData[4]);         // print the character
  Serial.print(", \t");
  Serial.print("Light: ");
  Serial.print(adcData[5]);         // print the character
  Serial.print(", \t");
  Serial.print("Mic: ");
  Serial.print(adcData[6]);         // print the character
  Serial.print(", \t");

  Serial.print("Button[6]: ");
  Serial.print(button_a);         // print the character
  Serial.print(",\t");
  Serial.print(button_b);         // print the character
  Serial.print(",\t");
  Serial.print(button_u);         // print the character
  Serial.print(",\t");
  Serial.print(button_d);         // print the character
  Serial.print(",\t");
  Serial.print(button_l);         // print the character
  Serial.print(",\t");
  Serial.print(button_r);         // print the character
  Serial.println(" ");         // print the character

  delay(10);
}

