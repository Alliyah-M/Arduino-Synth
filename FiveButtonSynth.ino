#include <synth.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
synth edgar;

/* Uncomment the corresponding variables for the song you want to play */

//int songC = 1;
//char song[] = "Avicii - Levels";
//B,C#,D#,E,F#  
//int freqs[] = {987,554,622,659,739};

//int songC = 2;
//char song[] = "Avicii-WakeMeUp";
//G,A,C,D,E
//int freqs[] = {1567,1760,2093,2349,2637};

//int songC = 3;
//char song[] = "Happy Birthday";
//CDEFG
//int freqs[] = {2093, 2349, 2637, 2793, 3135};

int songC = 4;
char song[] = "Deadmau5-MoarGnS";
//Bb F Ab Bb Db
int freqs[] = {116, 698, 830, 932, 1108};

void sweep()
{
  float f = 1000;

  for (int i = 0; i < 1000; i++)
  {
    Serial.println(f);
    edgar.setFrequency(0, f);
    edgar.trigger(0);
    delay(200);
    f += 100;
  }
}

void lightup(byte value)
{
  Serial.println(value);

  if (value & 1)
  {
    pinMode(A1, OUTPUT);
    digitalWrite(A1, LOW);
  }
  if (value & 2)
  {
    pinMode(A2, OUTPUT);
    digitalWrite(A2, HIGH);
  }
  if (value & 4)
  {
    pinMode(A3, OUTPUT);
    digitalWrite(A3, LOW);
  }
  if (value & 8)
  {
    pinMode(A4, OUTPUT);
    digitalWrite(A4, LOW);
  }
  if (value & 16)
  {
    pinMode(A5, OUTPUT);
    digitalWrite(A5, LOW);
  }
}

void alloff()
{
  pinMode(A1, INPUT);
  digitalWrite(A1, HIGH);

  pinMode(A2, INPUT);
  digitalWrite(A2, HIGH);

  pinMode(A3, INPUT);
  digitalWrite(A3, HIGH);

  pinMode(A4, INPUT);
  digitalWrite(A4, HIGH);

  pinMode(A5, INPUT);
  digitalWrite(A5, HIGH);
}

byte voice = 0;

void play(int freq)
{
  edgar.setFrequency(voice, freq);
  edgar.trigger(voice);

  voice++;

  if (voice == 4)
  {
    voice = 0;
  }
}

void setup()
{
  Serial.begin(250000);

  lcd.begin(16, 2);
  lcd.print(song);
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);

  edgar.begin(CHA);

  edgar.setupVoice(0, SAW, 127, ENVELOPE0, 75, 64);
  edgar.setupVoice(1, SAW, 127, ENVELOPE0, 75, 64);
  edgar.setupVoice(2, SAW, 127, ENVELOPE0, 75, 64);
  edgar.setupVoice(3, SAW, 127, ENVELOPE0, 75, 64);

  alloff();
}

byte ppA5 = 0;
byte ppA4 = 0;
byte ppA3 = 0;
byte ppA2 = 0;
byte ppA1 = 0;

void loop()
{
  byte pA5, pA4, pA3, pA2, pA1;

  // turn off all the key lights
  alloff();
  lcd.setCursor(0, 1);

 //Light up LED when note is played
  pA5 = digitalRead(A5);
  if(pA5 == 0)
  {
    play(freqs[4]);
    if (songC == 1)
    {
      lcd.print("Note: F#");
    }
    else if (songC == 2)
    {
      lcd.print("Note: E");
    }
    else if (songC == 3)
    {
      lcd.print("Note: G");
    }
    else
    {
      lcd.print("Note: Db");
    }
    
    pA5 = 1;
  }
  pA4 = digitalRead(A4);
  if(pA4 == 0)
  {
    play(freqs[3]);
    if (songC == 1)
    {
      lcd.print("Note: E");
    }
    else if (songC == 2)
    {
      lcd.print("Note: D");
    }
    else if (songC == 3)
    {
      lcd.print("Note: F");
    }
    else
    {
      lcd.print("Note: Bb");
    }
    pA4 = 1;
  }
  pA3 = digitalRead(A3);
  if(pA3 == 0)
  {
    play(freqs[2]);
    if (songC == 1)
    {
      lcd.print("Note: D#");
    }
    else if (songC == 2)
    {
      lcd.print("Note: C");
    }
    else if (songC == 3)
    {
      lcd.print("Note: E");
    }
    else
    {
      lcd.print("Note: Ab");
    }
    pA3 = 1;
  }
  pA2 = digitalRead(A2);
  if(pA2 == 0)
  {
    play(freqs[1]);
    if (songC == 1)
    {
      lcd.print("Note: C#");
    }
    else if (songC == 2)
    {
      lcd.print("Note: A");
    }
    else if (songC == 3)
    {
      lcd.print("Note: D");
    }
    else
    {
      lcd.print("Note: F");
    }
    pA2 = 1;
  }
  pA1 = digitalRead(A1);
  if(pA1 == 0)
  {
    play(freqs[0]);
    if (songC == 1)
    {
      lcd.print("Note: B");
    }
    else if (songC == 2)
    {
      lcd.print("Note: G");
    }
    else if (songC == 3)
    {
      lcd.print("Note: C");
    }
    else
    {
      lcd.print("Note: Bb");
    }
    pA1 = 1;
  }

}
