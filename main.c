/* 
功能：用PS2摇杆的X轴控制LED灯的亮度，摇杆往左亮度降低，往右亮度提升；用SW控制灯的亮灭
 */

#include <Arduino.h>

//设置引脚
#define LED     2
#define PS_X    4
#define PS_SW   5

int PS_X_value;
int PS_SW_value;
int brightness;
bool isOn = false; //SW模拟按键
bool PS_SW_state = false; //按键状态是否改变

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(PS_X, INPUT);
  pinMode(PS_SW, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // 灯默认开启，将PS-X轴的原始值映射为亮度的目标值
  PS_X_value = analogRead(PS_X);
  brightness = map(PS_X_value, 0, 4096, 0, 255);

  //设置PS-SW为开关：SW上拉，因此默认输出1，按下时会输出0
  PS_SW_value = digitalRead(PS_SW);
  if(!PS_SW_value && !PS_SW_state) 
  {
    delay(10);
    isOn = !isOn;
    PS_SW_state = true; //修改state
  }

  else if(PS_SW_value)
  {
    PS_SW_state = false;
  }

  if(isOn){
    analogWrite(LED, brightness);
  }
  else{
    analogWrite(LED, 0);
  }

  //串口查看PS摇杆的状态
  Serial.print("X轴:");
  Serial.print(PS_X_value);
  Serial.print(" SW:");
  Serial.println(PS_SW_value);
}
