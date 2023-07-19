
#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h> // Library for LCD
LiquidCrystal_I2C lcd(32, 16, 2); // I2C address 0x27, 16 column and 2 rows

Servo ServoMotor;
char*   password = "5614";  // change the password here, just pick any 3 numbers
int   position = 0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS]   = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte   rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };
Keypad   keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int RedpinLock   = 12;
int GreenpinUnlock = 13;

void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
  ServoMotor.write(0);
  pinMode(RedpinLock,   OUTPUT);
  pinMode(GreenpinUnlock, OUTPUT);
  ServoMotor.attach(11);
  LockedPosition(true);
  Serial.begin(9600);

}

void   loop()
{
    char key = keypad.getKey();
    if (key == '*' || key == '#')
    {
    position   = 0;
    LockedPosition(true);
    }
    if (key == password[position])
    {
        lcd.print(key);
    	position   ++;
    }
    if (position == 4)
    {
      LockedPosition(false);
    }
    delay(100);
}
void   LockedPosition(int locked)
    {
      if (locked)
      {
        digitalWrite(RedpinLock,   HIGH);
        digitalWrite(GreenpinUnlock, LOW);
        ServoMotor.write(0);
        lcd.clear();                 // clear display
        lcd.setCursor(0, 0);         // move cursor to   (0, 0)
        lcd.print("Please Enter PIN");        // print message at (0, 0)
        lcd.setCursor(5, 1);   
      }
      else
      {
        digitalWrite(RedpinLock,   LOW);
        digitalWrite(GreenpinUnlock, HIGH);
        ServoMotor.write(90);
        lcd.clear();                 // clear display
        lcd.setCursor(0, 0);         // move cursor to   (0, 0)
        lcd.print("Successful!");        // print message at (0, 0)
        lcd.setCursor(2, 1);         // move cursor to   (2, 1)
        lcd.print("Door Unlocked"); // print message at (2, 1)
      }
      
}