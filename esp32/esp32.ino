#include "MPU6050.h"

// 자이로 센서 정의
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;

unsigned long active_value, step_number = 0;
unsigned long k = 3000;
boolean isEmergncy = false;

void setup() 
{
  // 시리얼 설정
  Serial.begin(115200);

  // GPS를 위한 시리얼
  Serial2.begin(9600, SERIAL_8N1, 2, 23);

  // 자이로 시작
  Wire.begin();
  accelgyro.initialize();
}

void loop() 
{
  // 가속도 센서 측정
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  if (abs(ax) > k)
  {
    active_value = active_value + abs(ax);
    delay(1000);
  }

   if (abs(ay) > k)
  {
    active_value = active_value + abs(ay);
    delay(1000);
  }

   if (abs(az) > k)
  {
    active_value = active_value + abs(az);
    delay(1000);
  }

  if (// 압전센서 sensing 없을 때)
    {
      if (active_value > 3000)
      {
        if (// 압전센서 sensing 없을 때)
          {
            isEmergency = true;
          }
      }
    }



  // 활동량 출력
  Serial.println(active_value);
  delay(100);

  Serial.println("");
  delay(1000);


  
  
  // GPS 값 받아와서 출력하기
//  if(Serial2.available())
//  {
//    Serial.write(Serial2.read());
//  }
}
