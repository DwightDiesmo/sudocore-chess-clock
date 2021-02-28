/*
 * SUDOCORE TECHNOLOGIES INC.
 * PROJECT: CHESS CLOCK MK1
 * AUTHOR: DIESMO, DWIGHT
 * DATE: 2/27/21
 * 
 */

#include <LiquidCrystal.h>

//const int rs = 13, en = 12, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
//const unsigned int buttonA = A0, buttonB = A1, buttonC = A2;
#pragma region define
#define rs 13
#define en 12
#define d4 4
#define d5 5
#define d6 6
#define d7 7
#define buttonA A0
#define buttonB A1
#define buttonC A2
#pragma endregion define
#pragma region icons
byte play_icon[] = {B01000, B01100, B01110, B01111, B01110, B01100, B01000, B00000};
byte rook_icon[] = {B10101, B11111, B11111, B01110, B01110, B01110, B11111, B11111};
byte knight_icon[] = {B00110, B01111, B11111, B01111, B00011, B00111, B01110, B11111};
byte bishop_icon[] = {B00100, B01110, B11111, B01110, B00100, B01110, B01110, B11111};
byte right_arrow_icon[] = {B00000, B00100, B00010, B11111, B00010, B00100, B00000, B00000};
byte left_arrow_icon[]{B00000, B00100, B01000, B11111, B01000, B00100, B00000, B00000};
byte up_arrow_icon[]{ B00100, B01110, B10101, B00100, B00100, B00100, B00000, B00000};
byte down_arrow_icon[]{ B00000, B00000, B00100, B00100, B00100, B10101, B01110, B00100};
#pragma endregion icons
#pragma region global
unsigned int timeControl = 15;
unsigned int increment = 10;
unsigned int player1Time, player1Min, player1Sec, player2Time, player2Min, player2Sec;
#pragma endregion global

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  lcd.begin(16, 2);
  #pragma region createIcons
  lcd.createChar(0, play_icon);
  lcd.createChar(1, rook_icon);
  lcd.createChar(2, knight_icon);
  lcd.createChar(3, bishop_icon);
  lcd.createChar(4, right_arrow_icon);
  lcd.createChar(5, left_arrow_icon);
  lcd.createChar(6, up_arrow_icon);
  lcd.createChar(7, down_arrow_icon);
  #pragma endregion createIcons
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);
  // WELCOME_SCREEN();
  MENU();
  lcd.clear();
}
void loop()
{
  PLAY();
}

void WELCOME_SCREEN()
{
  lcd.setCursor(4, 0);
  lcd.print("SUDOCORE");
  lcd.setCursor(0, 1);
  lcd.print("Chess Clock V1.0");
  delay(5000);
}

bool MENU()
{
  unsigned int userSelected;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.setCursor(6, 0);
  lcd.print("Menu");
  lcd.setCursor(13, 0);
  lcd.write(byte(3));
  lcd.write(byte(2));
  lcd.write(byte(1));

  lcd.setCursor(0, 1);
  lcd.print("Options");
  lcd.write(byte(4));
  lcd.setCursor(10, 1);
  lcd.print("Start");
  lcd.write(byte(0));

  bool exitMenu = false;

  while (exitMenu == false)
  {
    userSelected = menu_select();
    switch(userSelected) {
      case 0:
        OPTIONS();
        break;
      case 1:
        exitMenu = CONFIRM_SETTINGS();
    }
  }
}

int menu_select()
{
  int userSelected = 7;
  while (1)
  {
    lcd.setCursor(userSelected, 1);
    lcd.blink();
    if (digitalRead(buttonC) == HIGH && userSelected == 7)
    {
      userSelected = 15;
    }
    else if (digitalRead(buttonA) == HIGH && userSelected == 15)
    {
      userSelected = 7;
    }
    if (digitalRead(buttonB) == HIGH)
    {
      if (userSelected == 7)
      {
        delay(1000);
        return 0;
      }
      else if (userSelected == 15)
      {
        delay(1000);
        return 1;
      }
    }
  }
}

void OPTIONS()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Options Menu");

  lcd.setCursor(0, 1);
  lcd.print("Time Control");
  lcd.setCursor(15, 1);
  lcd.write(byte(4));

  bool exitOptions = false;

  while (exitOptions == false)
  {
    exitOptions = options_select();
  }
}
bool options_select()
{
  int userSelected = 0;

  while (1)
  {
    lcd.noBlink();
    lcd.setCursor(2, 0);
    lcd.print("Options Menu");

    switch (userSelected)
    {
    case 0:
      lcd.setCursor(0, 1);
      lcd.print("Time Control");
      lcd.setCursor(15, 1);
      lcd.write(byte(4));
      break;
    case 1:
      lcd.setCursor(0, 1);
      lcd.write(byte(5));
      lcd.print(" Increment");
      lcd.setCursor(15, 1);
      lcd.write(byte(4));
      break;
    case 2:
      lcd.setCursor(0, 1);
      lcd.write(byte(5));
      lcd.print(" Exit to Main");
    }

    if (digitalRead(buttonA) == HIGH && userSelected > 0)
    {
      delay(300);
      lcd.clear();
      userSelected--;
    }
    else if (digitalRead(buttonC) == HIGH && userSelected < 2)
    {
      delay(300);
      lcd.clear();
      userSelected++;
    }
    if (digitalRead(buttonB) == HIGH)
    {
      delay(1000);
      if (userSelected == 0)
      {
        set_timecontrol();
      }
      else if (userSelected == 1)
      {
        set_increment();
      }
      else if (userSelected == 2)
      {
        return true;
      }
    }
  }
}

void set_timecontrol()
{
  lcd.clear();
  lcd.noBlink();
  while (1)
  {
    lcd.setCursor(2, 0);
    lcd.print("Time Control");
    lcd.setCursor(0, 1);
    lcd.print("Minutes:");
    print_integer(timeControl);
    //lcd.print(timeControl);

    lcd.setCursor(14, 1);
    lcd.write(byte(7));
    lcd.write(byte(6));
    if (digitalRead(buttonA) == HIGH && timeControl > 0)
    {
      lcd.setCursor(14, 1);
      lcd.blink();
      delay(300);
      timeControl--;
    }
    else if (digitalRead(buttonB) == HIGH)
    {
      delay(300);
      break;
    }
    else if (digitalRead(buttonC) == HIGH)
    {
      lcd.setCursor(15, 1);
      lcd.blink();
      delay(300);
      timeControl++;
    }
  }
  lcd.clear();
}
void set_increment()
{
  lcd.clear();
  lcd.noBlink();
  while (1)
  {
    lcd.setCursor(3, 0);
    lcd.print("Increment");
    lcd.setCursor(0, 1);
    lcd.print("Seconds:");
    print_integer(increment);
    //lcd.print(increment);

    lcd.setCursor(14, 1);
    lcd.write(byte(7));
    lcd.write(byte(6));
    if (digitalRead(buttonA) == HIGH && increment > 0)
    {
      lcd.setCursor(14, 1);
      lcd.blink();
      delay(300);
      increment--;
    }
    else if (digitalRead(buttonB) == HIGH)
    {
      delay(300);
      break;
    }
    else if (digitalRead(buttonC) == HIGH)
    {
      lcd.setCursor(15, 1);
      lcd.blink();
      delay(300);
      increment++;
    }
  }
  lcd.clear();
}

void CONFIRM_SETTINGS()
{
  lcd.clear();
  lcd.print("Minutes:");
  lcd.print(timeControl);
  lcd.setCursor(15, 0);
  lcd.print("Y");
  lcd.setCursor(0, 1);
  lcd.print("Increment:");
  lcd.print(increment);
  lcd.setCursor(15, 1);
  lcd.print("N");

  bool exitConfirm = false;
  int confirmedStatus;

  while (exitConfirm == false)
  {
    confirmedStatus = confirmation_select();
    if(confirmedStatus == 0) {
      return true;
    } else if (confirmedStatus == 1) {
      return false;
    }
  }
}

int confirmation_select()
{
  int userSelected = 0;
  while (1)
  {
    lcd.setCursor(15, userSelected);
    lcd.blink();
    if (digitalRead(buttonA) == HIGH && userSelected == 0)
    {
      userSelected = 1;
    }
    else if (digitalRead(buttonC) == HIGH && userSelected == 1)
    {
      userSelected = 0;
    }
    if (digitalRead(buttonB) == HIGH)
    {
      delay(1000);
      return userSelected;
    }
  }
}

void set_time()
{
  player1Time = timeControl * 60;
  player2Time = timeControl * 60;
}
void get_time()
{
  player1Min = player1Time / 60;
  player1Sec = player1Time % 60;
  player2Min = player2Time / 60;
  player2Sec = player2Time % 60;
}
void update_time()
{
  int player1Pressed, player2Pressed;
  if (digitalRead(buttonA) == HIGH)
  {
    delay(50);
    player1Pressed = 1;
    player2Pressed = 0;
    player1Time += increment;
  }
  else if (digitalRead(buttonC) == HIGH)
  {
    delay(50);
    player1Pressed = 0;
    player2Pressed = 1;
    player2Time += increment;
  }

  if (player1Pressed == 1)
  {
    player2Time--;
  }
  if (player2Pressed == 1)
  {
    player1Time--;
  }
}
void print_time()
{
  lcd.setCursor(0, 0);
  lcd.print("White   Black");
  lcd.setCursor(0, 1);
  print_integer(player1Min);
  lcd.print(":");
  print_integer(player1Sec);
  lcd.setCursor(8, 1);
  print_integer(player2Min);
  lcd.print(":");
  print_integer(player2Sec);
}

void print_integer(int integer)
{
  if (integer > 9)
  {
    lcd.print(integer);
  }
  else
  {
    lcd.print("0" + String(integer));
  }
}

void LOADING()
{
  lcd.clear();
  for (int i = 0; i < 16; i++)
  {
    lcd.setCursor(0, 0);
    lcd.print("LOADING");
    lcd.setCursor(i, 1);
    lcd.blink();
    delay(200);
    lcd.write(byte(1));
  }
}

void PLAY()
{
  lcd.noBlink();
  print_time();
  update_time();
  delay(1000);
}