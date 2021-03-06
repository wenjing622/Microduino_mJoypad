/*************************************************
  本示例给出了控制蜂鸣器响的方法
  说明：按下按键A，蜂鸣器响，松开蜂鸣器关闭
        按下按键B，播放生日歌，播放结束即蜂鸣器关闭
         因为此示例里播歌是通过延时实现的，所以音乐播放结束后程序才执行其他操作

****************************************
   2017-08-10  by CWJ
****************************************/

#include <Microduino_mJoypad.h>

bool button_a, button_b, button_u, button_d, button_l, button_r;

int song[] = {
  262, 262, 294, 262, 349, 330,
  262, 262, 294, 262, 392, 349,
  262, 262, 523, 440, 349, 330, 294,
  494, 494, 440, 349, 392, 349
};

int noteDurations[] = {
  4, 4, 2, 2, 2, 1,
  4, 4, 2, 2, 2, 1,
  4, 4, 2, 2, 2, 2, 2,
  4, 4, 2, 2, 2, 1
};
uint8_t ADC_Data[8];

void setup() {
  Serial.begin(9600);
  mJoypad.begin();
  Serial.println("TEST START");
}

void loop() {
  button_a = mJoypad.getButtonA();
  button_b = mJoypad.getButtonB();

  if (button_a) {
    mJoypad.tone(600);
    mJoypad.setLED(1, HIGH);
  }
  else {
    mJoypad.noTone();
    mJoypad.setLED(1, LOW);
  }
  if (button_b) {
    song_play();
  }
  delay(10);
}

void song_play()
{
  for (int thisNote = 0; thisNote < 25; thisNote++)
  {
    int noteDuration = 1000 / noteDurations[thisNote];
    mJoypad.tone(song[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.20;
    delay(pauseBetweenNotes);
  }
}
