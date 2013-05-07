//#include <string>
#include "SoundManager.h"
//using std::string;

SoundManager* SoundManager::instance = 0;
Sound SoundManager::playing[];

SoundManager::SoundManager() {
   // Open the audio device. The sound driver will try to give us
   // the requested format, but it might not succeed. The 'obtained'
   // structure will be filled in with the actual format data.
   desired.freq = 22050;     // desired output sample rate
   desired.format = AUDIO_S16;       // request signed 16-bit samples
   desired.samples = 512;   // this is more or less discretionary
   desired.channels = 2;     // ask for stereo
   desired.callback = SoundManager::audioCallback;
   desired.userdata = NULL;  // we don't need this
   if (SDL_OpenAudio(&desired, &obtained) < 0) {
      std::cout << "Unable to open audio device: " << SDL_GetError() << std::endl;
//      throw string("Unable to open audio device: ") + string(SDL_GetError());
   }
   clearPlayingSounds();
   // SDL's audio is initially paused. Start it.
   SDL_PauseAudio(0);
   atexit(SDL_CloseAudio);
}

SoundManager* SoundManager::getInstance() {
   if ( instance == NULL ) {
      instance = new SoundManager;
   }
   return instance;
}


void SoundManager::clearPlayingSounds(void) {
   for (int i = 0; i < MAX_PLAYING_SOUNDS; i++) {
      playing[i].active = 0;
   }
}

Sound::Sound(char* filename) {
   loadAndConvertSound( filename, SoundManager::getInstance()->getSpec() );
}
Sound::~Sound() {
   // Pause and lock the sound system so we can safely delete our sound data.      
   SDL_PauseAudio(1);
   SDL_LockAudio();
   // At this point the output is paused and we know for certain that the
   // callback is not active, so we can safely unlock the audio system.
   SDL_UnlockAudio();
}

void Sound::playSound() {
   SoundManager::getInstance()->playSound(this);
}

// This function loads a sound with SDL_LoadWAV and converts
// it to the specified sample format. 
void Sound::loadAndConvertSound(char *filename, SDL_AudioSpec spec) {
   SDL_AudioCVT cvt;           // audio format conversion structure
   SDL_AudioSpec loaded;       // format of the loaded data
   Uint8 *new_buf;

   // Load the WAV file in its original sample format.
   if (SDL_LoadWAV(filename,
      &loaded, &samples, &length) == NULL) {
      std::cout << "Unable to load sound: " << SDL_GetError() << std::endl;
//      throw string("Unable to load sound: ") + string(SDL_GetError());
   }

   // Build a conversion structure for converting the samples.
   // This structure contains the data SDL needs to quickly
   // convert between sample formats.
   if (SDL_BuildAudioCVT(&cvt, loaded.format,
      loaded.channels,
      loaded.freq,
      spec.format, spec.channels, spec.freq) < 0) {
         std::cout << "Unable to convert sound: " << SDL_GetError() << std::endl;
//         throw string("Unable to convert sound: ") + string(SDL_GetError());
   }

   // Since converting PCM samples can result in more data
   // (for instance, converting 8-bit mono to 16-bit stereo),
   // we need to allocate a new buffer for the converted data.
   // Fortunately SDL_BuildAudioCVT supplied the necessary
   // information.
   cvt.len = length;
   new_buf = (Uint8 *) malloc(cvt.len * cvt.len_mult);
   if (new_buf == NULL) {
      SDL_FreeWAV(samples);
      std::cout << "Memory allocation failed." << std::endl;
//      throw string("Memory allocation failed.");
   }

   // Copy the sound samples into the new buffer.
   memcpy(new_buf, samples, length);

   // Perform the conversion on the new buffer.
   cvt.buf = new_buf;
   if (SDL_ConvertAudio(&cvt) < 0) {
      free(new_buf);
      SDL_FreeWAV(samples);
      std::cout << "Audio conversion error: " << SDL_GetError() << std::endl;
//      throw string("Audio conversion error: ") + string(SDL_GetError());
   }

   // Swap the converted data for the original.
   SDL_FreeWAV(samples);
   samples = new_buf;
   length = length * cvt.len_mult;

   // Success!
   printf("'%s' was loaded and converted successfully.\n", filename);

}

// This function is called by SDL whenever the sound card
// needs more samples to play. It might be called from a
// separate thread, so we should be careful what we touch.
void SoundManager::audioCallback(void *user_data, Uint8 *audio, int length) {
    // Avoid compiler warning.
    user_data = user_data;

    // Clear the audio buffer so we can mix samples into it.
    memset(audio, 0, length);

    // Mix in each sound.
    for (int i = 0; i < MAX_PLAYING_SOUNDS; i++) {
        if (playing[i].active) {
            Uint8 *sound_buf;
            Uint32 sound_len;

            // Locate this sound's current buffer position.
            sound_buf = playing[i].samples;
            sound_buf += playing[i].position;

            // Determine the number of samples to mix.
            if ((playing[i].position + length) > playing[i].length) {
                sound_len = playing[i].length - playing[i].position;
            } else {
                sound_len = length;
            }

            // Mix this sound into the stream.
            SDL_MixAudio(audio, sound_buf, sound_len, VOLUME_PER_SOUND);

            // Update the sound buffer's position.
            playing[i].position += length;

            // Have we reached the end of the sound?
            if (playing[i].position >= playing[i].length) {
                playing[i].active = 0;  // mark it inactive
            }
        }
    }
}

// Adds a sound to the list of currently playing sounds.
// audioCallback will start mixing this sound into the stream
// the next time it is called (probably in a fraction of a second).
int SoundManager::playSound(Sound* sound) {
    int i;

    // Find an empty slot for this sound.
    for (i = 0; i < MAX_PLAYING_SOUNDS; i++) {
                        if (playing[i].active == 0)
                                        break;
    }

    // Report failure if there were no free slots.
    if (i == MAX_PLAYING_SOUNDS)
                        return 1;

    // The 'playing' structures are accessed by the audio callback,
    // so we should obtain a lock before we access them.
    SDL_LockAudio();
    playing[i].active = 1;
    playing[i].samples = sound->samples;
    playing[i].length = sound->length;
    playing[i].position = 0;
    SDL_UnlockAudio();

    return 0;
}/*

#include "SoundManager.h"



SoundManager::SoundManager(){
        fmt.freq = 22050;
        fmt.format = AUDIO_S16;
        fmt.channels = 2;
        fmt.samples = 512;
        fmt.callback = mixAudio;
        fmt.userdata = NULL;
        
        if(SDL_OpenAudio(&fmt, NULL) < 0){
                fprintf(stderr, "Unable to open audio: &sz\n", SDL_GetError());
                exit(1);
        }
        clearSounds();
        SDL_PauseAudio(0);
}

SoundManager* SoundManager::instance = NULL;
Sound SoundManager::sounds[];

SoundManager* SoundManager::getInstance(){
        if(instance == NULL){
                instance = new SoundManager();
        }
        return instance;
}

void SoundManager::clearSounds(){
        for(int i=0;i<NUM_SOUNDS;i++){
                sounds[i].active = 0;
        }
}

void SoundManager::mixAudio(void *unused, Uint8 *audio, int length){
        memset(audio, 0, length);
        
        for(int i=0; i<NUM_SOUNDS; i++){
                if(sounds[i].active) {
                        Uint8 *sound_buf;
                        Uint32 sound_len;
                        
                        sound_buf = sounds[i].data;
                        sound_buf += sounds[i].dpos;
                        
                        if((sounds[i].dpos + length) > sounds[i].dlen){
                                sound_len = sounds[i].dlen - sounds[i].dpos;
                        }
                        else{
                                sound_len = length;
                        }
                        
                        SDL_MixAudio(audio, sound_buf, sound_len, VOLUME);
                        
                        sounds[i].dpos += length;
                        
                        if(sounds[i].dpos >= sounds[i].dlen){
                                sounds[i].active = 0;
                        }
                }
        }
}

// Adds a sound to the list of currently playing sounds.
// mixAudio will start mixing this sound into the stream
// the next time it is called (probably in a fraction of a second).
int SoundManager::playSound(Sound* sound) {
                int i;
                
    // Find an empty slot for this sound.
    for (i = 0; i < NUM_SOUNDS; i++) {
                        if (sounds[i].active == 0){
                                break;
                        }
    }

    // Report failure if there were no free slots.
    if (i == NUM_SOUNDS){
        return 1;
    }


    // The 'playing' structures are accessed by the audio callback,
    // so we should obtain a lock before we access them.
    SDL_LockAudio();
    sounds[i].active = 1;
    sounds[i].data = sound->data;
    sounds[i].dlen = sound->dlen;
    sounds[i].dpos = 0;
    SDL_UnlockAudio();

    return 0;
}*/


