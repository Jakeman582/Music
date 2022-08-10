#ifndef WAVE_H
#define WAVE_H

#include <fstream>
#include <string>

using namespace std;

namespace wave {

    struct note {
        double frequency;
        int beats;
    };

    const string RIFF_ID = "RIFF";
    const string RIFF_FILLER = "iiii";
    const string RIFF_FORMAT = "WAVE";
    const string FMT_ID = "fmt ";
    const string DATA_ID = "data";
    const int FMT_SIZE = 16;
    const short AUDIO_FORMAT = 1;
    const short BYTES_PER_SAMPLE = 2;
    const short BITS_PER_SAMPLE = 8 * BYTES_PER_SAMPLE;
    const double VOLUME = 20000.0;
    const int FILE_SIZE_OFFSET = 4;
    const int DATA_SIZE_OFFSET = 40;

    void write_wave_header(ofstream &file, short channels, int sample_rate);
    void write_data_size(ofstream &file, int sample_count, short channels);
    void parse_music_line(string music_line);
    double get_frequency(string note);


}

#endif