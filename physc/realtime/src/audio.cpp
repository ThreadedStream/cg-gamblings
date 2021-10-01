#include <include/audio.h>
#include <spdlog/spdlog.h>
#include <cstdint>


bool Audio::loadIntoMemory(const char* const wav_file, const AudioSpecs& audio_specs) {
    if (!openAudio(audio_specs.frequency,
                  audio_specs.format,
                  audio_specs.channels,
                  audio_specs.chunk_size)){

        spdlog::error("{}", getAudioFailureReason());
        return false;
    }

    if (!allocateChannels(audio_specs.num_channels)) {
        spdlog::error("{}", getAudioFailureReason());
        closeAudio();
        return false;
    }

    sample_ = LOAD_WAV(wav_file);

    if (sample_ == nullptr) {
        destroy();
        return false;
    }

    return true;
}

