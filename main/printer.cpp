#include "printer.h"
#include <ESP8266WiFi.h>

int aprintf(const char *str, ...) {
  int i, j, count = 0;

  va_list argv;
  va_start(argv, str);
  for (i = 0, j = 0; str[i] != '\0'; i++) {
    if (str[i] == '%') {
      count++;

      Serial.write(reinterpret_cast<const uint8_t*>(str+j), i-j);

      switch (str[++i]) {
        case 'd':
        case 'i': Serial.print(va_arg(argv, int));
          break;
        case 'u': Serial.print(va_arg(argv, unsigned int));
          break;
        case 'l': Serial.print(va_arg(argv, long));
          break;
        case 'f': Serial.print(va_arg(argv, double));
          break;
        case 'c': Serial.print((char) va_arg(argv, int));
          break;
        case 's': Serial.print(va_arg(argv, char *));
          break;
        case 'P': { 
          Printable* printable = va_arg(argv, Printable *);
          Serial.print(*printable);
          break;
        }
        case '%': Serial.print("%");
          break;
        default:;
      };

      j = i+1;
    }
  };
  va_end(argv);

  if (i > j) {
    Serial.write(reinterpret_cast<const uint8_t*>(str+j), i-j);
  }

  return count;
}
