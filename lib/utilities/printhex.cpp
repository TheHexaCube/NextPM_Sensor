#include <printhex.h>

void printHex(int num, int precision) {
      char tmp[16];
      char format[128];

      sprintf(format, "0x%%.%dX ", precision);

      sprintf(tmp, format, num);
      Serial.print(tmp);
}