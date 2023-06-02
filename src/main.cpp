#include <Arduino.h>


// pins start from pin 6 and go upwards in proper order
#define SEVSEG_PINS_BASE 6
#define SEVSEG_PINS_NR 8
#define FOR_EACH_SEGMENT for (int segpin = SEVSEG_PINS_BASE; segpin < SEVSEG_PINS_BASE + SEVSEG_PINS_NR; segpin++)


constexpr uint8_t sevseg_char_map[] =
{
    //abcdefg.
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11110110, // 9
    0b11101110, // A
    0b00111110, // B
    0b10011100, // C
    0b01111010, // D
    0b10011110, // E
    0b10001110  // F
};


void sevseg_show(uint8_t _number)
{
    if (_number > 0xf)
        return;
    
    FOR_EACH_SEGMENT
    {
        uint8_t map = sevseg_char_map[_number];
        digitalWrite(segpin, !((map >> (7 - (segpin - SEVSEG_PINS_BASE))) & 0x01) );
    }
}



void setup()
{
    FOR_EACH_SEGMENT
        pinMode(segpin, OUTPUT);
}

void loop()
{
    for (int i = 0; i < 0x10; i++)
    {
        sevseg_show(i);
        delay(500);
    }
}