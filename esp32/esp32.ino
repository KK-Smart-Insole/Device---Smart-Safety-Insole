#include "MPU6050.h"

// 자이로 센서 정의
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;

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
  // 자이로 값 받아와서 출력하기
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print(ax); Serial.print(",");
  Serial.print(ay); Serial.print(",");
  Serial.print(az); Serial.print(",");
  Serial.print(gx); Serial.print(",");
  Serial.print(gy); Serial.print(",");
  Serial.print(gz); Serial.print(",");

  Serial.println("");

  // GPS 값 받아와서 출력하기
  if(Serial2.available())
  {
    Serial.write(Serial2.read());
  }
}
