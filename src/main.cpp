#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C lcd(U8G2_R0);

// pins start from pin 6 and go upwards in proper order
#define SEVSEG_PINS_BASE 6
#define SEVSEG_PINS_NR 8
#define FOR_EACH_SEGMENT for (int segpin = SEVSEG_PINS_BASE; segpin < SEVSEG_PINS_BASE + SEVSEG_PINS_NR; segpin++)

// number of ms between the digit incrementing
#define INCREMENT_PERIOD_MS 500

#define BUFLEN 10

constexpr uint8_t sevseg_char_map[] =
    {
        // abcdefg.
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
        digitalWrite(segpin, !((map >> (7 - (segpin - SEVSEG_PINS_BASE))) & 0x01));
    }
}

void setup()
{
    FOR_EACH_SEGMENT
    pinMode(segpin, OUTPUT);

    lcd.begin();
}

void loop()
{
    static uint32_t last_increment = 0;
    static uint8_t current_digit = 0;
    static char textbuf[BUFLEN];

    if (last_increment + INCREMENT_PERIOD_MS < millis())
    {
        current_digit++;
        if (current_digit > 0xf)
            current_digit = 0;
        last_increment = millis();

        // update sevenseg
        sevseg_show(current_digit);

        // update lcd
        lcd.firstPage();
        do
        {
            lcd.setFont(u8g2_font_helvB24_tf);
            snprintf(textbuf, BUFLEN, "%x", current_digit);
            lcd.drawStr(50, 44, textbuf);
        } while (lcd.nextPage());
    }
}