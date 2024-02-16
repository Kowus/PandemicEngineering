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
  while (!ser_port->available())
  {
    send_buffer(0x01, CMD_SET_REQ_RES, {});
  }
}

void O2_8500FS_L40::send_buffer(int len, int cmd, int frames[8])
{
  transmission_buffer[0] = TX_HEADER;
  transmission_buffer[1] = len;
  transmission_buffer[2] = cmd;
  int check_sum = 0;
  if (len > 0x01)
    for (int i = 3; i < len + 3; i++)
    {
      transmission_buffer[i] = frames[i - 3];
      check_sum += transmission_buffer[i];
    }
  check_sum = 256 - (check_sum + TX_HEADER + len + cmd);
  transmission_buffer[len + 3] = check_sum;
  while (!ser_port->available())
    ser_port->write(transmission_buffer, len + 3);
}

double O2_8500FS_L40::get_volume_percent(Units_oxygen units = Units_oxygen::volume_percent)
{
  send_buffer(0x01, CMD_RD_MSMNT_RSLT, {});
  int timeout = 0;
  while (ser_port->available() < 12)
  {
    timeout++;
    if (timeout > 10)
    {
      while (ser_port->available())
        ser_port->read();
      break;
    }
    delay(RX_TIMEOUT);
  }
}
