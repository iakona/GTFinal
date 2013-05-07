/* Example of audio mixing with SDL. */
#include <iostream>
#include <SDL.h>

// Array for all active sound effects.
const int MAX_PLAYING_SOUNDS = 32;

// The higher this is, the louder each currently playing sound will be.
// However, high values may cause distortion if too many sounds are
// playing. Experiment with this.
const int VOLUME_PER_SOUND = SDL_MIX_MAXVOLUME / 3;

class SoundManager;
class Sound {
public:
    Sound() {}
    Sound(char* filename);
   ~Sound();
   void playSound();
   void loadAndConvertSound(char *filename, SDL_AudioSpec spec);
   friend class SoundManager;
private:
   int active;                 // 1 if this sound should be played
   Uint8 *samples;              // raw PCM sample data
   Uint32 length;               // size of sound data in bytes
   Uint32 position;            // current position in the sound buffer
};

class SoundManager {
public:
   static SoundManager* getInstance();
   SDL_AudioSpec getSpec() const { return obtained; }
   void clearPlayingSounds(void);
   int playSound(Sound* sound);
   static void audioCallback(void *user_data, Uint8 *audio, int length);
private:
   SoundManager();
   static Sound playing[MAX_PLAYING_SOUNDS];

   SDL_AudioSpec desired, obtained;
   static SoundManager* instance;
};
