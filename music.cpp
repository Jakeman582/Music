#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "include/wave.hpp"

using namespace std;

double get_frequency(string note);
double get_beats();

int main(int argc, char **argv) {

    // Make sure there are exactly 2 arguments provided
    if(argc != 3) {
        cout << "Usage: music <input_file_1.txt> [<input_file_2.txt> ...] <output_file.wav>" << endl;
        exit(0);
    }

    short channels = argc - 2;  // Number of channels depends on the number of input files
    int sample_rate = 44100;

    // WAV files are binary files
    string input_file = argv[1];
    string wav_file = argv[argc - 1];
    ifstream input_stream;
    ofstream output_stream;

    // Attempt to open the input file
    input_stream.open(input_file);
    if(input_stream.fail()) {
        cout << "Failed to open file \"" << input_file << "\"" << endl;
        exit(0);
    }

    // Attempt to open the output file
    output_stream.open(wav_file, ios::out | ios::binary);
    if(output_stream.fail()) {
        cout << "Failed to open file \"" << wav_file << "\n" << endl;
        output_stream.close();
        exit(0);
    }

    wave::write_wave_header(output_stream, channels, 44100);

    // We need to know what the tempo is, as well as which note gets one beat
    // The tempo is the first number of the file, and the beat note is the
    // second
    int tempo;
    int beat_note;
    input_stream >> tempo >> beat_note;

    // Get the next newline character character, and ignore it
    string whitespace;
    getline(input_stream, whitespace);

    // We need to know how many samples there are so that information can be
    // put in the WAVE file header
    int sample_count = 0;
    while(!input_stream.eof()) {

        // Get the note, and the number of beats
        //int beats;
        //input_stream >> note >> beats;

        getline(input_stream, whitespace);
        wave::parse_music_line(whitespace);

        /*

        // Get the note's frequency
        double frequency = get_frequency(note);

        // If there is an unrecognized note, abort
        if(frequency < 0) {
            cout << "Note " << note << " is unrecognized" << endl;
            input_stream.close();
            output_stream.close();
            exit(0);
        }

        int number_of_samples = (int)(60.0 * 44100 * beats) / tempo;
        sample_count += number_of_samples;

        for(index = 0; index < number_of_samples; index++) {

            // Write the sample to the wav file
            double sample = frequency * M_PI / 44100;
            short value = (short) wave::VOLUME * sin(sample * index);
            output_stream.write((const char *)&value, sizeof(short));

        }

        */
    }

    wave::write_data_size(output_stream, sample_count, channels);

    // Close the file
    output_stream.close();

    // Exit this process
    exit(0);

}

double get_frequency(string note) {

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
