#include <SDL2/SDL_mixer.h>
#include <cstdint>


using MixChunk = Mix_Chunk;


// NOTE(threadedstream): just to follow code writing convention
constexpr  int32_t (*openAudio) (int32_t frequency, uint16_t format, int32_t channels, int32_t chunk_size) = &Mix_OpenAudio;
constexpr  int32_t (*allocateChannels)(int32_t num_channels) = &Mix_AllocateChannels;
constexpr  const char* (*getAudioFailureReason) () = &SDL_GetError;
constexpr  void (*freeChunk)(MixChunk* chunk) = &Mix_FreeChunk;
constexpr  void (*closeAudio)() = &Mix_CloseAudio;

#define LOAD_WAV(file) Mix_LoadWAV(file)
#define PLAY_CHANNEL(channel, chunk, loops) Mix_PlayChannel(channel, chunk, loops)


struct AudioSpecs {
    int32_t frequency;
    int32_t format;
    int32_t channels;
    int32_t chunk_size;
    int32_t num_channels;
};


class Audio {
public:

    bool loadIntoMemory(const char* wav_file, const AudioSpecs& audio_specs);

    inline void play(int32_t channel, int32_t loops) {
        PLAY_CHANNEL(channel, sample_, loops);
    }

    inline void destroy() {
        freeChunk(sample_);
        closeAudio();
    }

private:
    MixChunk* sample_{nullptr};
};