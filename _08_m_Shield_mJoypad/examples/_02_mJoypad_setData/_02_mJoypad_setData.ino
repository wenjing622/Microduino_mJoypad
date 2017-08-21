/*************************************************
  本示例给出了控制mJoypad上传感器的方法
  包含：
        0号LED灯（红）
        1号LED灯（黄）
        2号LED灯（绿）
        全彩RGB灯
        右侧三路DAC输出
        摇杆阈值（默认50）
        (蜂鸣器的控制见:toneTest)
****************************************
   2017-08-10  by CWJ
****************************************/

#include <Microduino_mJoypad.h>

void setup() {
  Serial.begin(9600);
  mJoypad.begin();
  mJoypad.setSensitive(60);  //设置摇杆阈值，可不设置，默认50
  Serial.println("TEST START");
}

void loop() {
  //*****************set*******输出控制
  mJoypad.setLED(0, HIGH);
  delay(150);
  mJoypad.setLED(0, LOW);
  mJoypad.setLED(1, HIGH);
  delay(150);
  mJoypad.setLED(1, LOW);
  mJoypad.setLED(2, HIGH);
  delay(150);
  mJoypad.setLED(2, LOW);
  
  mJoypad.setColorLED(10, 0, 0);
  mJoypad.setOUT(0, map(10, 0, 50, 0, 255));
  mJoypad.setOUT(1, map(30, 0, 50, 0, 255));
  mJoypad.setOUT(2, map(50, 0, 50, 0, 255));  

  delay(100);
}

