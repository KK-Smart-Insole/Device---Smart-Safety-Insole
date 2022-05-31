#include "MPU6050.h"

// 압력센서 아날로그 핀 정의
const int pressSensor = 15;

// 자이로 센서 정의
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;

unsigned long active_value, step_number, count = 0;
unsigned long  real_count = 10;
unsigned long k = 3000;
boolean isEmergency = false;

void setup() 
{
  // 시리얼 설정
  Serial.begin(115200, SERIAL_8N1, 15);


  // GPS를 위한 시리얼
  Serial2.begin(9600, SERIAL_8N1, 2, 23);

  // 자이로 시작
  Wire.begin();
  accelgyro.initialize();
}

void loop() 
{
  
  // 압력센서
  int value = analogRead(pressSensor);
  Serial.println(value);
 
  
  // 가속도 센서 측정
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  if (abs(ax) > k && abs(ay) > k && abs(az) > k && abs(gx) > k && abs(gy) > k)
  {
    active_value = active_value + abs(ax) + abs(ay) + abs(az) + abs(gx) + abs(gy);

  }

 
   // 넘어짐 state 판단
    if (active_value > 10000 && value < 800)
    {
      isEmergency = true;
    }

    // 걸음수
    if (2500 < value < 4000)
    {
      count = count + 1;
      if (count > 10)
      {
        real_count = real_count + 1;
      }
    }
   


  // 활동량 출력
  Serial.println(active_value);


  Serial.println("");
 
  //GPS 값 받아와서 출력하기
  if (Serial2.available())
  {
    Serial.write(Serial2.read());
    
    
  }

}
