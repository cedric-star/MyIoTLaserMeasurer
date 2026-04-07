#include "project.h"

HM330XErrorCode parse_pm_data(u8* data) {
  if (NULL == data)
    return ERROR_PARAM;

  pmValues.pm1_0_cf = (u16)data[2] << 8 | data[3];
  pmValues.pm2_5_cf = (u16)data[4] << 8 | data[5];
  pmValues.pm10_cf = (u16)data[6] << 8 | data[7];
  pmValues.pm1_0_atm = (u16)data[8] << 8 | data[9];
  pmValues.pm2_5_atm = (u16)data[10] << 8 | data[11];
  pmValues.pm10_atm = (u16)data[12] << 8 | data[13];

  u8 sum = 0;
  for (int i = 0; i < 28; i++) {
    sum += data[i];
  }
  if (sum != data[28]) {
    Serial.println("Warning: Checksum mismatch!");
  }

  return NO_ERROR;
}