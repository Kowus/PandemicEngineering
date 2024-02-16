// Copyright (c) 2024 Barnabas Nomo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#ifndef _O2_8500FS_L40_
#define _O2_8500FS_L40_

#include "../config/uvent_conf.h"
#include <Arduino.h>

typedef enum class units_oxygen
{
  volume_percent,
  lpm
} Units_oxygen;
typedef enum class units_thermohygrometry
{
  celsius,
  fahrenheit,
  kelvin
} Units_thermohygrometry;
class O2_8500FS_L40
{
public:
  // O2_8500FS_L40(int uart_rx, int uart_tx, int baud = 9600) : uart_rx(uart_rx), uart_tx(uart_tx), baud(baud){};
  O2_8500FS_L40(HardwareSerial *s, int baud_rate = 9600);
  void init();
  void change_baud_rate(int br);
  double get_volume_percent(Units_oxygen units = Units_oxygen::volume_percent);
  double get_thermohygrometry(Units_thermohygrometry units = Units_thermohygrometry::celsius);
  void send_buffer(int len, int cmd_data, int frames[8]);
  // void set_tx_buffer(int len, );

private:
  // config vars
  int baud;
  HardwareSerial *ser_port;
  bool initialized;

  // tx/rx buffers
  byte transmission_buffer[5];
  byte reception_buffer[12];
  const uint8_t RX_TIMEOUT = 10;

  // conversion constants
  double const CELSIUS_TO_FAHRENHEIT = 0;
  double const CELSIUS_TO_KELVIN = 0;
  double const KELVIN_TO_CELSIUS = 0;
  double const KELVIN_TO_FAHRENHEIT = 0;
  double const FAHRENHEIT_TO_KELVIN = 0;
  double const FAHRENHEIT_TO_CELSIUS = 0;

  // data transceiver bytes
  const uint8_t TX_HEADER = 0x11;
  const uint8_t RX_HEADER = 0x16;

  // serial protocol command constants
  const uint8_t CMD_RD_MSMNT_RSLT = 0x01;
  const uint8_t CMD_RD_SFTWR_VRSN = 0x1E;
  const uint8_t CMD_RD_SRL_NMBR = 0x1F;
  const uint8_t CMD_CHNG_BD_RT = 0x08;
  const uint8_t CMD_RD_THRMHGRMTR = 0x03;
  const uint8_t CMD_SET_REQ_RES = 0x07;
};
#endif // _O2_8500FS_L40_