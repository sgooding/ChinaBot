#include "SongPlayer.h"
#include "Arduino.h"

const unsigned int SongPlayer::c3   = 7634;
const unsigned int SongPlayer::d3   = 6803;
const unsigned int SongPlayer::e3   = 6061;
const unsigned int SongPlayer::f3   = 5714;
const unsigned int SongPlayer::g3   = 5102;
const unsigned int SongPlayer::a3   = 4545;
const unsigned int SongPlayer::b3   = 4049;
const unsigned int SongPlayer::c4   = 3816;
const unsigned int SongPlayer::d4   = 3401;
const unsigned int SongPlayer::e4   = 3030;
const unsigned int SongPlayer::f4   = 2865;
const unsigned int SongPlayer::g4   = 2551;
const unsigned int SongPlayer::a4   = 2272;
const unsigned int SongPlayer::a4s  = 2146;
const unsigned int SongPlayer::b4   = 2028;
const unsigned int SongPlayer::c5   = 1912;
const unsigned int SongPlayer::d5   = 1706;
const unsigned int SongPlayer::d5s  = 1608;
const unsigned int SongPlayer::e5   = 1517;
const unsigned int SongPlayer::f5   = 1433;
const unsigned int SongPlayer::g5   = 1276;
const unsigned int SongPlayer::a5   = 1136;
const unsigned int SongPlayer::a5s  = 1073;
const unsigned int SongPlayer::b5   = 1012;
const unsigned int SongPlayer::c6   = 955 ;
const unsigned int SongPlayer::R = 0;

// Melody 1: Star Wars Imperial March
const int SongPlayer::melody1[] = {  a4, R,  a4, R,  a4, R,  f4, R, c5, R,  a4, R,  f4, R, c5, R, a4, R,  e5, R,  e5, R,  e5, R,  f5, R, c5, R,  g5, R,  f5, R,  c5, R, a4, R};
const int SongPlayer::beats1[]  = {  50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5, 20, 5, 60, 80, 50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5,  20, 5, 60, 40};
 
// Melody 2: Star Wars Theme
const int SongPlayer::melody2[] = {  f4,  f4, f4,  a4s,   f5,  d5s,  d5,  c5, a5s, f5, d5s,  d5,  c5, a5s, f5, d5s, d5, d5s,   c5};
const int SongPlayer::beats2[]  = {  21,  21, 21,  128,  128,   21,  21,  21, 128, 64,  21,  21,  21, 128, 64,  21, 21,  21, 128 }; 
 
const int SongPlayer::MAX_COUNT = sizeof(melody1) / 2; // Melody length, for looping.
 
const long SongPlayer::tempo = 10000; // Set overall tempo
 
const int SongPlayer::pause = 1000; // Set length of pause between notes
 
const int SongPlayer::rest_count = 50; // Loop variable to increase Rest length (BLETCHEROUS HACK; See NOTES)

const unsigned int SongPlayer::speakerOut = 7; 

void SongPlayer::Setup()
{
   pinMode(speakerOut, OUTPUT);
   toneM = 0;
   beat = 0;
   duration = 0;
}

void SongPlayer::Play()
{
  for (int i=0; i<MAX_COUNT; i++) 
  {
    toneM = melody1[i];
    beat = beats1[i];

    duration = beat * tempo; // Set up timing

    PlayTone(); // A pause between notes
    delayMicroseconds(pause);
  }
}

void SongPlayer::PlayTone()
{
  long elapsed_time = 0;
  if (toneM > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(toneM / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(toneM / 2);

      // Keep track of how long we pulsed
      elapsed_time += (toneM);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  } 
}
