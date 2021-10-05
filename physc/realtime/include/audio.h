#ifdef __linux
#include <SDL2/SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif
#include <cstdint>
#include <cassert>

using MixChunk = Mix_Chunk;
using MixMusic = Mix_Music;

// NOTE(threadedstream): just to follow code writing convention
constexpr  int32_t (*openAudio) (int32_t frequency, uint16_t format, int32_t channels, int32_t chunk_size) = &Mix_OpenAudio;
constexpr  int32_t (*allocateChannels)(int32_t num_channels) = &Mix_AllocateChannels;
constexpr  const char* (*getAudioFailureReason) () = &SDL_GetError;

// music-specific typedefs
constexpr  MixMusic* (*loadMusic) (const char* file) = &Mix_LoadMUS;
constexpr  int32_t (*playMusic) (MixMusic* music, int32_t loops) = &Mix_PlayMusic;
constexpr  void (*freeMusic)(MixMusic* music) = &Mix_FreeMusic;
constexpr  int32_t (*configureMusicVolume) (int32_t volume) = &Mix_VolumeMusic;

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

struct GLFWwindow;

class Audio {
public:

    Audio(const AudioSpecs& audio_specs);

    bool loadChunkIntoMemory(const char* wav_file);
    bool loadMusicIntoMemory(const char* file);

    inline void playChunkedSample(int32_t channel, int32_t loops) {
        assert(chunked_sample_ && "chunked_sample_ is nullptr");
        PLAY_CHANNEL(channel, chunked_sample_, loops);
    }

    inline void playMusicalSample(int32_t loops) {
        assert(musical_sample_ && "musical_sample_ is nullptr");
        playMusic(musical_sample_, loops);
    }

    inline void setMusicVolume(int32_t volume) {
        configureMusicVolume(volume);
    }

    inline void destroy() {
        if (chunked_sample_){
            freeChunk(chunked_sample_);
        }
        if (musical_sample_) {
            freeMusic(musical_sample_);
        }
        closeAudio();
    }

    void handleInput(GLFWwindow* window);

    inline constexpr bool is_constructed() noexcept { return is_constructed_; }

private:
    void setup_(const AudioSpecs& audio_specs);

private:
    MixChunk* chunked_sample_{nullptr};
    MixMusic* musical_sample_{nullptr};

    int32_t music_volume_{0};
    // NOTE(threadedstream): sentinel to indicate whether the audio object
    // has been properly constructed
    bool is_constructed_{false};
};