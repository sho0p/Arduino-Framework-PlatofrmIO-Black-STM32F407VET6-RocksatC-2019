#include <stdint.h>

#define SETUP_FLAG      B10000000
#define SCAN_MODE_NONE  B00000110
#define SCAN_MODE_0_N   B00000000
#define SCAN_MODE_4_4   B00000100
#define CS_PIN_1        41
#define CS_PIN_2        3
#define MISO_PIN        PC12
#define MOSI_PIN        PC11
#define SCK_PIN         PC10

void printData(uint32_t chData);
uint32_t readAdc(int csPin);