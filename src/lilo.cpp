#include <Arduino.h>
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C lcd(U8G2_R0);

// Pinbelegung
#define PinA 7
#define PinB 8
#define PinC 2
#define PinD 3
#define PinE 4
#define PinF 6
#define PinG 5
#define Laenge 10
// ----------------------- Globale Variablen deklarieren
char Anzeige[Laenge];


// Zuweissung der Bin-Zahlen zu den dazugehörigen Hex-Zahlen
bool Zuweissung[16][7] =
    {
        {1, 1, 1, 1, 1, 1, 0}, // 0
        {0, 1, 1, 0, 0, 0, 0}, // 1
        {1, 1, 0, 1, 1, 0, 1}, // 2
        {1, 1, 1, 1, 0, 0, 1}, // 3
        {0, 1, 1, 0, 0, 1, 1}, // 4
        {1, 0, 1, 1, 0, 1, 1}, // 5
        {1, 0, 1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}, // 9
        {1, 1, 1, 0, 1, 1, 1}, // A
        {0, 0, 1, 1, 1, 1, 1}, // b
        {1, 0, 0, 1, 1, 1, 0}, // C
        {0, 1, 1, 1, 1, 0, 1}, // d
        {1, 0, 0, 1, 1, 1, 1}, // E
        {1, 0, 0, 0, 1, 1, 1}  // F
};

// ----------------------- Funktion
void Ausgabe_Segment(int Zahl)
{
    bool LEDZustand[7];

    for (int i = 0; i < 7; i++)
    {
        LEDZustand[i] = Zuweissung[Zahl][i];
    }

    digitalWrite(PinA, !LEDZustand[0]);
    digitalWrite(PinB, !LEDZustand[1]);
    digitalWrite(PinC, !LEDZustand[2]);
    digitalWrite(PinD, !LEDZustand[3]);
    digitalWrite(PinE, !LEDZustand[4]);
    digitalWrite(PinF, !LEDZustand[5]);
    digitalWrite(PinG, !LEDZustand[6]);
}

// ----------------------- Pins Konfigurieren
void setup()
{
    // Pins für 7-Segmentanzeige
    pinMode(PinA, OUTPUT);
    pinMode(PinB, OUTPUT);
    pinMode(PinC, OUTPUT);
    pinMode(PinD, OUTPUT);
    pinMode(PinE, OUTPUT);
    pinMode(PinF, OUTPUT);
    pinMode(PinG, OUTPUT);

    lcd.begin();
}

// ----------------------- Main
void loop()
{
    int Index = 0;
    for (; Index < 16; Index++)
    {
        Ausgabe_Segment(Index);
        // update lcd
        lcd.firstPage();
        do
        {
            lcd.setFont(u8g2_font_helvB24_tf);
            snprintf(Anzeige, Laenge, "%x", Index);
            lcd.drawStr(50, 44, Anzeige);
        } while (lcd.nextPage());
        delay(700);
    }
}