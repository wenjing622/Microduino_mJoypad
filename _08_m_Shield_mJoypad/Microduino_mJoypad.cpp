/*
    Microduino_mJoypad.cpp

    Created on: 2017/08/10
        Author: cuiwenjing
*/

#include "Microduino_mJoypad.h"

mJoyPad::mJoyPad() {

}

bool mJoyPad::begin(void) {
  Wire.begin();
  Wire.beginTransmission(mJoyPad_ADDR);
  writeData(I2C_W_8_RESET, 0xFE);
  setSensitive(SENSITIVE);
  return !Wire.endTransmission();
}

uint8_t mJoyPad::requstData(uint8_t _dataAddr) {
  Wire.beginTransmission(mJoyPad_ADDR); //硬件IIC地址
  Wire.write(_dataAddr);             // 数据地址
  Wire.endTransmission();    // stop transmitting
  Wire.requestFrom(mJoyPad_ADDR, (uint8_t)1); //请求数据
  while (Wire.available()) {
    return Wire.read();
  }
}

uint8_t mJoyPad::writeData(uint8_t _dataAddr, uint8_t _data) {
  Wire.beginTransmission(mJoyPad_ADDR); //硬件IIC地址
  Wire.write(_dataAddr);             // 数据地址
  Wire.write(_data);
  Wire.endTransmission();    // stop transmitting
}

uint8_t mJoyPad::getIN(uint8_t _num) {
  if (_num == 0) {
    return requstData(I2C_R_8_LEFT_A);
  }
  else if (_num == 1) {
    return requstData(I2C_R_8_LEFT_B);
  }
  else if (_num == 2) {
    return requstData(I2C_R_8_LEFT_C);
  }
}

uint8_t mJoyPad::getJoysticX(void) {
  return requstData(I2C_R_8_JOY_X);
}

uint8_t mJoyPad::getJoysticY(void) {
  return requstData(I2C_R_8_JOY_Y);
}

uint8_t mJoyPad::getLight(void) {
  return requstData(I2C_R_8_LIGHT);
}

uint8_t mJoyPad::getMic(void) {
  return requstData(I2C_R_8_MIC);
}

uint8_t mJoyPad::getKey(void) {
  return requstData(I2C_R_8_KEY);
}

uint8_t mJoyPad::Button(void) {
  return requstData(I2C_R_8_ALL_BUTTON);
}

bool mJoyPad::getButtonUp(void) {
  uint8_t button = Button();
  if (Button() & 0x01) {
    return true;
  }
  else {
    return false;
  }
}

bool mJoyPad::getButtonDown(void) {
  uint8_t button = Button();
  if (Button() & (0x01 << BUTTON_DOWN)) {
    return true;
  }
  else {
    return false;
  }
}

bool mJoyPad::getButtonLeft(void) {
  uint8_t button = Button();
  if (Button() & (0x01 << BUTTON_LEFT)) {
    return true;
  }
  else {
    return false;
  }
}

bool mJoyPad::getButtonRight(void) {
  uint8_t button = Button();
  if (Button() & (0x01 << BUTTON_RIGHT)) {
    return true;
  }
  else {
    return false;
  }
}

bool mJoyPad::getButtonA(void) {
  uint8_t button = Button();
  if (Button() & (0x01 << BUTTON_A)) {
    return true;
  }
  else {
    return false;
  }
}

bool mJoyPad::getButtonB(void) {
  uint8_t button = Button();
  if (Button() & (0x01 << BUTTON_B)) {
    return true;
  }
  else {
    return false;
  }
}

int8_t mJoyPad::getRAW(uint8_t *_data) {
  uint8_t _num = 0;
  Wire.beginTransmission(mJoyPad_ADDR); //硬件IIC地址
  Wire.write(I2C_R_8_LEFT_A);             // 数据地址
  Wire.endTransmission();    // stop transmitting
  Wire.requestFrom(mJoyPad_ADDR, (uint8_t)GET_DATA_LEN); //请求数据
  while (Wire.available()) {
    _data[_num++] = Wire.read();
  }
  return _num;  //I2Cdev::readBytes(mJoyPad_ADDR, I2C_R_8_LEFT_A, GET_DATA_LEN, _data);
}


void mJoyPad::setOUT(uint8_t _numb, uint8_t _pwm) {
  if (_numb == 0) {
    writeData(I2C_W_8_RIGHT_A, _pwm);
  }
  else if (_numb == 1) {
    writeData(I2C_W_8_RIGHT_B, _pwm);
  }
  else if (_numb == 2) {
    writeData(I2C_W_8_RIGHT_C, _pwm);
  }
}

void mJoyPad::setLED(uint8_t _number, bool _state) {
  if (_number > 0x02) return;
  bitWrite(this->LED_State, _number, _state);
  writeData(I2C_W_8_LED_MODE, this->LED_State);
}

void mJoyPad::setLED(uint8_t _state) {
  if (_state > 0x07) return;
  writeData(I2C_W_8_LED_MODE, _state);
}

void mJoyPad::setColorLED(uint8_t _r, uint8_t _g, uint8_t _b) {
  Wire.beginTransmission(mJoyPad_ADDR); //硬件IIC地址
  Wire.write(I2C_W_8_RGB_R);             // 数据地址
  Wire.write(_r);
  Wire.write(_g);
  Wire.write(_b);
  Wire.endTransmission();    // stop transmitting
}

void mJoyPad::setSensitive(uint8_t _range) {
  constrain(_range, 8, 96);
  Wire.beginTransmission(mJoyPad_ADDR); //硬件IIC地址
  Wire.write(I2C_W_8_SENSITIVE);             // 数据地址
  Wire.write(_range);
  Wire.endTransmission();    // stop transmitting
}

void mJoyPad::tone(uint16_t _frequency, uint16_t _duration) {
  Wire.beginTransmission(mJoyPad_ADDR); //硬件IIC地址
  Wire.write(I2C_W_16_BUZZER);             // 数据地址
  Wire.write((uint8_t)(_frequency >> 8));
  Wire.write((uint8_t)(_frequency ));
  Wire.write((uint8_t)(_duration >> 8));
  Wire.write((uint8_t)(_duration ));
  Wire.endTransmission();    // stop transmitting
}

void mJoyPad::noTone() {
  Wire.beginTransmission(mJoyPad_ADDR); //硬件IIC地址
  Wire.write(I2C_W_16_BUZZER);             // 数据地址
  Wire.write((uint8_t)0);
  Wire.write((uint8_t)0);
  Wire.endTransmission();    // stop transmitting
}

mJoyPad mJoypad = mJoyPad();

