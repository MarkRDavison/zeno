#include <zeno/Audio/WaveLoader.hpp>
#include <iostream>
#include <cstdlib>
#include <AL/al.h>
#include <AL/alc.h>

namespace ze {

    int WaveLoader::getSourceState(unsigned _source) {
        ALint state;
        alGetSourcei(_source, AL_SOURCE_STATE, &state);
        return state;
    }
    unsigned WaveLoader::getFormat(unsigned channels, unsigned bitsPerSample) {
        if (channels == 1 && bitsPerSample == 8)
            return AL_FORMAT_MONO8;
        else if (channels == 1 && bitsPerSample == 16)
            return AL_FORMAT_MONO16;
        else if (channels == 2 && bitsPerSample == 8)
            return AL_FORMAT_STEREO8;
        else if (channels == 2 && bitsPerSample == 16)
            return AL_FORMAT_STEREO16;
        else
            return AL_INVALID_VALUE;
    }
	int WaveLoader::convert_to_int(char* _buffer, unsigned _length) {
        int a = 0;
        const int n = 1;
        if (*(char*)&n == 1) {
            /*Little Endian*/
            std::memcpy(&a, _buffer, _length);
        } else {
            /*Big Endian*/
            for (std::size_t i = 0; i < _length; ++i) {
                reinterpret_cast<char*>(&a)[3 - i] = _buffer[i];
            }
        }
        return a;
    }

    bool WaveLoader::load(const std::string& _filename,
        std::vector<char>& _data,
        unsigned& _numberChannels,
        int& _sampleRate,
        unsigned& _bitsPerSample) {

        std::ifstream file(_filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "ERROR: could not open file '" << _filename << "'" << std::endl;
            return false;
        }

        return load(
            file,
            _data,
            _numberChannels,
            _sampleRate,
            _bitsPerSample);
    }

    bool WaveLoader::parseHeader(std::ifstream& _file,
        unsigned& _numberChannels,
        int& _sampleRate,
        unsigned& _bitsPerSample,
        unsigned& _size) {
        char buffer[4];

        // the RIFF
        if (!_file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read RIFF" << std::endl;
            return false;
        }
        if (std::strncmp(buffer, "RIFF", 4) != 0) {
            std::cerr << "ERROR: file is not a valid WAVE file (header doesn't begin with RIFF)" << std::endl;
            return false;
        }

        // the size of the file
        if (!_file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read size of file" << std::endl;
            return false;
        }

        // the WAVE
        if (!_file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read WAVE" << std::endl;
            return false;
        }
        if (std::strncmp(buffer, "WAVE", 4) != 0) {
            std::cerr << "ERROR: file is not a valid WAVE file (header doesn't contain WAVE)" << std::endl;
            return false;
        }

        // "fmt/0"
        if (!_file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read fmt/0" << std::endl;
            return false;
        }

        // this is always 16, the size of the fmt data chunk
        if (!_file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read the 16" << std::endl;
            return false;
        }

        // PCM should be 1?
        if (!_file.read(buffer, 2)) {
            std::cerr << "ERROR: could not read PCM" << std::endl;
            return false;
        }

        // the number of channels
        if (!_file.read(buffer, 2)) {
            std::cerr << "ERROR: could not read number of channels" << std::endl;
            return false;
        }

        _numberChannels = convert_to_int(buffer, 2);

        // sample rate
        if (!_file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read sample rate" << std::endl;
            return false;
        }
        _sampleRate = convert_to_int(buffer, 4);

        // (sampleRate * bitsPerSample * channels) / 8
        if (!_file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read (sampleRate * bitsPerSample * channels) / 8" << std::endl;
            return false;
        }

        // ?? dafaq
        if (!_file.read(buffer, 2)) {
            std::cerr << "ERROR: could not read dafaq" << std::endl;
            return false;
        }

        // bitsPerSample
        if (!_file.read(buffer, 2)) {
            std::cerr << "ERROR: could not read bits per sample" << std::endl;
            return false;
        }
        _bitsPerSample = convert_to_int(buffer, 2);

        // data chunk header "data"
        if (!_file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read data chunk header" << std::endl;
            return false;
        }
        if (std::strncmp(buffer, "data", 4) != 0) {
            std::cerr << "ERROR: file is not a valid WAVE file (doesn't have 'data' tag)" << std::endl;
            return false;
        }

        // size of data
        if (!_file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read data size" << std::endl;
            return false;
        }
        _size = convert_to_int(buffer, 4);

        /* cannot be at the end of file */
        if (_file.eof()) {
            std::cerr << "ERROR: reached EOF on the file" << std::endl;
            return false;
        }
        if (_file.fail()) {
            std::cerr << "ERROR: fail state set on the file" << std::endl;
            return false;
        }

        return true;
    }

    bool WaveLoader::load(std::ifstream& _file,
        std::vector<char>& _data,
        unsigned& _numberChannels,
        int& _sampleRate,
        unsigned& _bitsPerSample) {

        _data.clear();

        unsigned size = 0;

        if (!parseHeader(
            _file,
            _numberChannels,
            _sampleRate,
            _bitsPerSample,
            size)) {
            return false;
        }

        _data.resize(size);
        _file.read(&_data[0], size);

        return true;
    }
}