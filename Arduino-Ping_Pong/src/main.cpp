#include <Arduino.h>

// Game variables
int time = 400;
int speedUp = 10;
int minLedPin = 2;
int maxLedPin = 8;
int initialScore = 5;

// Player button pins
int playerOne = 13;
int playerTwo = 12;

int playerOneStatus = 0;
int playerTwoStatus = 0;

int playerOneScore = initialScore;
int playerTwoScore = initialScore;

void playerOneTurn();
void playerTwoTurn();
void resetGame();

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(playerOne, INPUT);
  pinMode(playerTwo, INPUT);
  Serial.begin(9600);
}

void loop()
{
  playerOneTurn();
  playerTwoTurn();
}

void playerOneTurn()
{
  for (int i = minLedPin; i <= maxLedPin; i++)
  {
    digitalWrite(i, HIGH);
    delay(time);
    playerOneStatus = digitalRead(playerOne);
    if (i != maxLedPin && playerOneStatus == HIGH)
    {
      playerOneScore--;
      if (playerOneScore < 1)
      {
        resetGame();
        break;
      }
    }
    else if (i == maxLedPin && playerOneStatus == LOW)
    {
      playerOneScore--;
      if (playerOneScore < 1)
      {
        resetGame();
        break;
      }
    }
    digitalWrite(i, LOW);
    delay(time);
  }
  time = time - speedUp;
}

void playerTwoTurn()
{
  for (int i = maxLedPin; i >= minLedPin; i--)
  {
    digitalWrite(i, HIGH);
    delay(time);
    playerTwoStatus = digitalRead(playerTwo);
    if (i != minLedPin && playerTwoStatus == HIGH)
    {
      playerTwoScore--;
      if (playerTwoScore < 1)
      {
        resetGame();
        break;
      }
    }
    else if (i == minLedPin && playerTwoStatus == LOW)
    {
      playerTwoScore--;
      if (playerTwoScore < 1)
      {
        resetGame();
        break;
      }
    }
    digitalWrite(i, LOW);
    delay(time);
  }
  time = time - speedUp;
}

void resetGame()
{
    for (size_t i = 0; i < 4; i++)
    {
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      delay(400);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      delay(400);
    }
    time = 400;
    playerOneScore = initialScore;
    playerTwoScore = initialScore;
}
