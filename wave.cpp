#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "wave.hpp"

using namespace std;

void wave::write_wave_header(ofstream &file, short channels, int sample_rate) {

    // The WAVE header needs byte rate and a block align, all of which are
    // by the number of channels and the sample rate
    int byte_rate = wave::BYTES_PER_SAMPLE * sample_rate * channels;
    short block_align = wave::BYTES_PER_SAMPLE * channels;

    // Write the RIFF header
    file.write(wave::RIFF_ID.c_str(), wave::RIFF_ID.length());
    file.write(wave::RIFF_FILLER.c_str(), wave::RIFF_FILLER.length());
    file.write(wave::RIFF_FORMAT.c_str(), wave::RIFF_FORMAT.length());

    // Write the WAVE/fmt sub-chunk
    file.write(wave::FMT_ID.c_str(), wave::FMT_ID.length());
    file.write((const char *)&wave::FMT_SIZE, sizeof(int));
    file.write((const char *)&wave::AUDIO_FORMAT, sizeof(short));
    file.write((const char *)&channels, sizeof(short));
    file.write((const char *)&sample_rate, sizeof(int));
    file.write((const char *)&byte_rate, sizeof(int));
    file.write((const char *)&block_align, sizeof(short));
    file.write((const char *)&wave::BITS_PER_SAMPLE, sizeof(short));

    // Write the WAVE/data sub-chunk
    file.write(wave::DATA_ID.c_str(), wave::DATA_ID.length());
    file.write(wave::RIFF_FILLER.c_str(), wave::RIFF_FILLER.length());

}

void wave::write_data_size(ofstream &file, int sample_count, short channels) {

    int data_size = sample_count * channels * wave::BYTES_PER_SAMPLE;
    int file_size = 36 + data_size;

    file.seekp(wave::FILE_SIZE_OFFSET, ios_base::beg);
    file.write((const char *)&file_size, sizeof(int));
    file.seekp(wave::DATA_SIZE_OFFSET, ios_base::beg);
    file.write((const char *)&data_size, sizeof(int));

}

void wave::parse_music_line(string music_line) {

    string frequency;
    string note;
    string modifier;
    stringstream buffer(music_line);

    buffer >> frequency >> note >> modifier;

    double frequency = wave::get_frequency(frequency);
    double beats = wave::get_beats(note, modifier);

}

double wave::get_frequency(string note) {

    if(note == "0") {
        return 0.0;
    } else if(note == "C0") {
        return 16.35;
    } else if(note == "C#0" || note == "Db0") {
        return 17.32;
    } else if(note == "D0") {
        return 18.35;
    } else if(note == "D#0" || note == "Eb0") {
        return 19.45;
    } else if(note == "E0") {
        return 20.60;
    } else if(note == "F0") {
        return 21.83;
    } else if(note == "F#0" || note == "Gb0") {
        return 23.12;
    } else if(note == "G0") {
        return 24.50;
    } else if(note == "G#0" || note == "Ab0") {
        return 25.96;
    } else if(note == "A0") {
        return 27.50;
    } else if(note == "A#0" || note == "Bb0") {
        return 29.14;
    } else if(note == "B0") {
        return 30.87;
    } else if(note == "C1") {
        return 32.70;
    } else if(note == "C#1" || note == "Db1") {
        return 34.65;
    } else if(note == "D1") {
        return 36.71;
    } else if(note == "D#1" || note == "Eb1") {
        return 38.89;
    } else if(note == "E1") {
        return 41.20;
    } else if(note == "F1") {
        return 43.65;
    } else if(note == "F#1" || note == "Gb1") {
        return 46.25;
    } else if(note == "G1") {
        return 49.00;
    } else if(note == "G#1" || note == "Ab1") {
        return 51.91;
    } else if(note == "A1") {
        return 55.00;
    } else if(note == "A#1" || note == "Bb1") {
        return 58.27;
    } else if(note == "B1") {
        return 61.74;
    } else if(note == "C2") {
        return 65.41;
    } else if(note == "C#2" || note == "Db2") {
        return 69.30;
    } else if(note == "D2") {
        return 73.42;
    } else if(note == "D#2" || note == "Eb2") {
        return 77.78;
    } else if(note == "E2") {
        return 82.41;
    } else if(note == "F2") {
        return 87.31;
    } else if(note == "F#2" || note == "Gb2") {
        return 92.50;
    } else if(note == "G2") {
        return 98.00;
    } else if(note == "G#2" || note == "Ab2") {
        return 103.83;
    } else if(note == "A2") {
        return 110.00;
    } else if(note == "A#2" || note == "Bb2") {
        return 116.54;
    } else if(note == "B2") {
        return 123.47;
    } else if(note == "C3") {
        return 130.81;
    } else if(note == "C#3" || note == "Db3") {
        return 138.59;
    } else if(note == "D3") {
        return 146.83;
    } else if(note == "D#3" || note == "Eb3") {
        return 155.56;
    } else if(note == "E3") {
        return 164.81;
    } else if(note == "F3") {
        return 174.61;
    } else if(note == "F#3" || note == "Gb3") {
        return 185.00;
    } else if(note == "G3") {
        return 196.00;
    } else if(note == "G#3" || note == "Ab3") {
        return 207.65;
    } else if(note == "A3") {
        return 220.00;
    } else if(note == "A#3" || note == "Bb3") {
        return 233.08;
    } else if(note == "B3") {
        return 246.94;
    } else if(note == "C4") {
        return 261.63;
    } else if(note == "C#4" || note == "Db4") {
        return 277.18;
    } else if(note == "D4") {
        return 293.66;
    } else if(note == "D#4" || note == "Eb4") {
        return 311.13;
    } else if(note == "E4") {
        return 329.63;
    } else if(note == "F4") {
        return 349.23;
    } else if(note == "F#4" || note == "Gb4") {
        return 369.99;
    } else if(note == "G4") {
        return 392.00;
    } else if(note == "G#4" || note == "Ab4") {
        return 415.30;
    } else if(note == "A4") {
        return 440.00;
    } else if(note == "A#4" || note == "Bb4") {
        return 466.16;
    } else if(note == "B4") {
        return 493.88;
    } else if(note == "C5") {
        return 523.25;
    } else if(note == "C#5" || note == "Db5") {
        return 554.37;
    } else if(note == "D5") {
        return 587.33;
    } else if(note == "D#5" || note == "Eb5") {
        return 622.25;
    } else if(note == "E5") {
        return 659.25;
    } else if(note == "F5") {
        return 698.46;
    } else if(note == "F#5" || note == "Gb5") {
        return 739.99;
    } else if(note == "G5") {
        return 783.99;
    } else if(note == "G#5" || note == "Ab5") {
        return 830.61;
    } else if(note == "A5") {
        return 880.00;
    } else if(note == "A#5" || note == "Bb5") {
        return 932.33;
    } else if(note == "B5") {
        return 987.77;
    } else if(note == "C6") {
        return 1046.50;
    } else if(note == "C#6" || note == "Db6") {
        return 1108.73;
    } else if(note == "D6") {
        return 1174.66;
    } else if(note == "D#6" || note == "Eb6") {
        return 1244.51;
    } else if(note == "E6") {
        return 1318.51;
    } else if(note == "F6") {
        return 1396.91;
    } else if(note == "F#6" || note == "Gb6") {
        return 1479.98;
    } else if(note == "G6") {
        return 1567.98;
    } else if(note == "G#6" || note == "Ab6") {
        return 1661.22;
    } else if(note == "A6") {
        return 1760.00;
    } else if(note == "A#6" || note == "Bb6") {
        return 1864.66;
    } else if(note == "B6") {
        return 1975.53;
    } else if(note == "C7") {
        return 2093.00;
    } else if(note == "C#7" || note == "Db7") {
        return 2217.46;
    } else if(note == "D7") {
        return 2349.32;
    } else if(note == "D#7" || note == "Eb7") {
        return 2489.02;
    } else if(note == "E7") {
        return 2637.02;
    } else if(note == "F7") {
        return 2793.83;
    } else if(note == "F#7" || note == "Gb7") {
        return 2959.96;
    } else if(note == "G7") {
        return 3135.96;
    } else if(note == "G#7" || note == "Ab7") {
        return 3322.44;
    } else if(note == "A7") {
        return 3520.00;
    } else if(note == "A#7" || note == "Bb7") {
        return 3729.31;
    } else if(note == "B7") {
        return 3951.07;
    } else if(note == "C8") {
        return 4186.01;
    } else if(note == "C#8" || note == "Db8") {
        return 4434.92;
    } else if(note == "D8") {
        return 4698.63;
    } else if(note == "D#8" || note == "Eb8") {
        return 4978.03;
    } else if(note == "E8") {
        return 5274.04;
    } else if(note == "F8") {
        return 5587.65;
    } else if(note == "F#8" || note == "Gb8") {
        return 5919.91;
    } else if(note == "G8") {
        return 6271.93;
    } else if(note == "G#8" || note == "Ab8") {
        return 6644.88;
    } else if(note == "A8") {
        return 7040.00;
    } else if(note == "A#8" || note == "Bb8") {
        return 7458.62;
    } else if(note == "B8") {
        return 7902.13;
    } else {
        return -1.0;
    }
}