// Copyright (c) 2024 Barnabas Nomo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#include "oxygen_sensor.h"

O2_8500FS_L40::O2_8500FS_L40(HardwareSerial *s, int baud_rate = 9600)
{
  ser_port = s;
  baud = baud_rate;
}
void O2_8500FS_L40::init()
{
  ser_port->begin(baud);
  initialized = true;
  byte temp_tx_buffer[5] = {TX_HEADER, 0x01, CMD_SET_REQ_RES, 0xE7};
  memcpy(transmission_buffer, temp_tx_buffer, 4);
  while (!ser_port->availableForWrite())
    ;
}

void O2_8500FS_L40::send_buffer(int len, int cmd, int frames[8])
{
  transmission_buffer[0] = TX_HEADER;
  transmission_buffer[1] = len;
  transmission_buffer[2] = cmd;
  for (int i = 3; i < len + 3; i++)
  {
    transmission_buffer[i] = frames[i - 3];
  }
}

double O2_8500FS_L40::get_volume_percent(Units_oxygen units = Units_oxygen::volume_percent)
{
}