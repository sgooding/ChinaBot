#ifndef SONG_PLAYER_H
#define SONG_PLAYER_H
class SongPlayer
{
  public:
    void Setup();
    void Play();
  private:
    void PlayTone();
static const unsigned int c3 ; 
static const unsigned int d3 ; 
static const unsigned int e3 ; 
static const unsigned int f3 ; 
static const unsigned int g3 ; 
static const unsigned int a3 ; 
static const unsigned int b3 ; 
static const unsigned int c4 ;     // 261 Hz 
static const unsigned int d4 ;     // 294 Hz 
static const unsigned int e4 ;     // 329 Hz 
static const unsigned int f4 ;     // 349 Hz 
static const unsigned int g4 ;     // 392 Hz 
static const unsigned int a4 ;     // 440 Hz 
static const unsigned int a4s; 
static const unsigned int b4 ;     // 493 Hz 
static const unsigned int c5 ;     // 523 Hz
static const unsigned int d5 ; 
static const unsigned int d5s; 
static const unsigned int e5 ;     // 659 Hz
static const unsigned int f5 ;     // 698 Hz
static const unsigned int g5 ; 
static const unsigned int a5 ; 
static const unsigned int a5s; 
static const unsigned int b5 ; 
static const unsigned int c6 ; 
static const unsigned int R;

// Melody 1: Star Wars Imperial March
static const int melody1[];
static const int beats1[];
// Melody 2: Star Wars Theme
static const int melody2[];
static const int beats2[];
static const int MAX_COUNT;
static const long tempo;
static const int pause;
static const int rest_count;
static const unsigned int speakerOut;

int toneM;
int beat;
long duration;
int potVal;
 
};

#endif

