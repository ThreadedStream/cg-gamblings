#include <include/audio.h>
#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>

#include <cstdint>


Audio::Audio(const AudioSpecs& audio_specs) {
    setup_(audio_specs);
}

void Audio::setup_(const AudioSpecs& audio_specs) {
    if (openAudio(audio_specs.frequency,
                  audio_specs.format,
                  audio_specs.channels,
                  audio_specs.chunk_size)){

        spdlog::error("{}", getAudioFailureReason());
        is_constructed_ = false;
    }

    if (!allocateChannels(audio_specs.num_channels)) {
        spdlog::error("{}", getAudioFailureReason());
        closeAudio();
        is_constructed_ = false;
    }

    setMusicVolume(music_volume_);
    is_constructed_ = true;
}

bool Audio::loadChunkIntoMemory(const char* const wav_file) {
    chunked_sample_ = LOAD_WAV(wav_file);

    if (!chunked_sample_) {
        spdlog::error(getAudioFailureReason());
        destroy();
        return false;
    }

    return true;
}

bool Audio::loadMusicIntoMemory(const char* const file) {
    musical_sample_ = loadMusic(file);

    if (!musical_sample_) {
        spdlog::error(getAudioFailureReason());
        destroy();
        return false;
    }

    return true;
}

void Audio::handleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        music_volume_ += 8;
        setMusicVolume(music_volume_);
    } else if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        music_volume_ -= 8;
        setMusicVolume(music_volume_);
    }
}

