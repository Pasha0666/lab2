#include <LedControl.h>
#include "point.h"
const int displaysCount = 1;
const int dataPin = 12;
const int clkPin = 10;
const int csPin = 11;
LedControl lc = LedControl(dataPin, clkPin, csPin, displaysCount);
/*
void setup()
{
  lc.shutdown(0, false);
  lc.setIntensity(0, 16);
  lc.clearDisplay(0);
}

void loop() {
  lc.setLed(0, 3, 4, true);
  delay(500);
  lc.setLed(0, 3, 4, false);
  delay(500);
}
*/
Point keyUp = Point(0, 1);
Point keyDown = Point(0, -1);
Point keyRight = Point(1, 0);
Point keyLeft = Point(-1, 0);
Point keyNone = Point(0, 0);
Point keyFixation = Point(100, 100);
Point keyGo = Point(-1, -1);


const byte rowAmount = 4;
const byte colAmount = 4;

bool lifeMatrix[8][8] ={
  {false, false, false, false},
  {false, false, false, false},
  {false, false, false, false},
  {false, false, false, false}
  };

bool lifeMatrixTwo[8][8] ={
  {false, false, false, false},
  {false, false, false, false},
  {false, false, false, false},
  {false, false, false, false}
  };

Point keyMatrix[rowAmount][colAmount] = {
  {keyNone, keyUp,    keyNone,  keyNone},
  {keyLeft, keyFixation,  keyRight, keyNone},
  {keyNone, keyDown,  keyNone,  keyNone},
  {keyNone, keyNone,  keyNone,  keyGo}
};

static bool keyDownMatrix[rowAmount][colAmount];

byte rowPins[rowAmount] = { 5, 4, 3, 2 };
byte colPins[colAmount] = { 6, 7, 8, 9 };


void setup()
{
  keyFixation.fixation = true;
  lc.shutdown(0, false);
  lc.setIntensity(0, 16);
  lc.clearDisplay(0);
  for (int i = 0; i < rowAmount; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  
  for (int i = 0; i < colAmount; i++) {
    pinMode(colPins[i], INPUT);
    digitalWrite(colPins[i], HIGH);
  }
  Serial.begin(115200);
}

Point curent = Point(0,0);

void loop()
{
  lc.setLed(0, curent.X, curent.Y, true);
  Point key = getKey();
  if(key == keyFixation)
  {
     lifeMatrix[curent.X][ curent.Y] = true;
     return;
  }
  if(key == keyGo)
  {
    while(true)
    {
      PlayGame();
      for(int i = 0; i < 8; i++)
      {
        for(int j = 0; j < 8; j++)
        {
        lc.setLed(0, i, j,  lifeMatrix[i][j]);
        }
      }
      delay(2000);
    }
  }
  if (key != keyNone) {
    if (!lifeMatrix[curent.X] [curent.Y])
      lc.setLed(0, curent.X, curent.Y, false);
    curent = curent.offset(key);
  }
}


void PlayGame(){
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      int sum = 0;
        for(int k = -1; k < 2; k++)
          for(int g = -1; g < 2; g++)
            {
              if(k == 0 && g == 0)
                continue;
              int newX = (i + k) % 8;
              int newY = (j+ g) % 8;
              if (newX < 0)
              {
                  newX += 8;  
              }
              if (newY < 0)
              {
                  newY += 8;  
              }
               if (lifeMatrix[newX][newY])
                  sum += 1;
            }
       if (lifeMatrix[i][j])
          lifeMatrixTwo[i][j] = sum == 2 || sum == 3;
       else
          lifeMatrixTwo[i][j] = sum == 3;
    }
  }  
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
         lifeMatrix[i][j]  = lifeMatrixTwo[i][j];
    }
  }
}
Point getKey()
{
  Point result = keyNone;
  for (int i = 0; i < rowAmount; i++) {
    for (int j = 0; j < colAmount; j++) {
      bool isDown = isKeyDown(i, j);
      if (!keyDownMatrix[i][j] && isDown) {
        result = keyMatrix[i][j];
      }
      keyDownMatrix[i][j] = isDown;
    } 
  }
  return result;
}

bool isKeyDown(int i, int j)
{
  bool result = false;
  digitalWrite(rowPins[i], LOW);
  if (digitalRead(colPins[j]) == LOW) {
    result = true;
  }
  digitalWrite(rowPins[i], HIGH);
  return result;
}
