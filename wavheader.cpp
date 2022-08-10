#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>

#define ID_SIZE 4

using namespace std;

namespace wavheader {
    char int_buffer[4];
    char short_buffer[2];
    ifstream input_stream;
}

void read_string(char *source, unsigned int size);
void read_int(unsigned int *destination);
void read_int_plus(unsigned int *destination, unsigned int extra);
void read_short(unsigned short *destination);

int main(int argc, char **argv) {

    // Make sure an argument is supplied
    if(argc != 2) {
        cout << "Usage: wavheader <file.wav>" << endl;
        exit(0);
    }

    // Attempt to open the file
    wavheader::input_stream.open(argv[1], ios::in | ios::binary);
    if(wavheader::input_stream.fail()) {
        cout << "Trouble opening file \"" << argv[1] << "\"" << endl;
        wavheader::input_stream.close();
        exit(0);
    }

    // Main chunk information
    char chunk1_id[ID_SIZE + 1];
    unsigned int file_size;
    char file_format[ID_SIZE + 1];

    // Subchunk1 Information
    char sub_chunk1_id[ID_SIZE + 1];
    unsigned int sub_chunk1_size;
    unsigned short audio_format;
    unsigned short number_of_channels;
    unsigned int sample_rate;
    unsigned int byte_rate;
    unsigned short block_align;
    unsigned short bits_per_sample;

    // Subchunk2 Information
    char sub_chunk2_id[ID_SIZE + 1];
    unsigned int sub_chunk2_size;

    // Read the first chunk of the file
    read_string(chunk1_id, ID_SIZE);
    read_int_plus(&file_size, 8);
    read_string(file_format, ID_SIZE);

    // Read the first sub chunk
    read_string(sub_chunk1_id, ID_SIZE);
    read_int(&sub_chunk1_size);
    read_short(&audio_format);
    read_short(&number_of_channels);
    read_int(&sample_rate);
    read_int(&byte_rate);
    read_short(&block_align);
    read_short(&bits_per_sample);

    // Read the second sub chunk
    read_string(sub_chunk2_id, ID_SIZE);
    read_int(&sub_chunk2_size);

    wavheader::input_stream.close();

    // Calculate the number of samples
    unsigned int number_of_samples = sub_chunk2_size / block_align;
    double seconds = (1.0 * number_of_samples) / sample_rate;

    // Calculate length of file name so it can be displayed in the banner
    int file_name_length = strlen(argv[1]);

    // Display a banner
    cout << "****************";
    for(int index = 0; index < file_name_length; index++) {
        cout << "*";
    }
    cout << "*****" << endl;

    cout << "*   WAV HEADER (" << argv[1] << ")   *" << endl;

    cout << "****************";
    for(int index = 0; index < file_name_length; index++) {
        cout << "*";
    }
    cout << "*****" << endl;
    cout << endl;

    // Display the file's characteristics
    cout << "--- FILE CHARACTERISTICS ---" << endl;
    cout << "File format: " << chunk1_id << " -> " << file_format << endl;
    cout << "File size:   " << file_size << " Bytes" << endl;
    cout << endl;

    // Display the audio characteristics
    cout << "--- AUDIO CHARACTERISTICS ---" << endl;
    cout << "Audio format      = " << "Linear Quantization (No Compression)" << endl;
    cout << "Channels          = " << number_of_channels << endl;
    cout << "Sample Rate       = " << sample_rate << " Samples/second" << endl;
    cout << "Byte Rate         = " << byte_rate << " Bytes/second" << endl;
    cout << "Block Alignment   = " << block_align << " Bytes/sample" << endl;
    cout << "Sample Quality    = " << bits_per_sample << " Bits/channel" << endl;
    cout << "Data              = " << sub_chunk2_size << " Bytes" << endl;
    cout << "Number of samples = " << number_of_samples << endl;
    cout << "Time              = " << seconds << " Seconds" << endl;

    exit(0);
}

void read_string(char *source, unsigned int size) {
    wavheader::input_stream.read(source, size);
    source[size] = '\0';
}

void read_int(unsigned int *destination) {
    wavheader::input_stream.read(wavheader::int_buffer, sizeof(int));
    memcpy(destination, wavheader::int_buffer, sizeof(int));
}

void read_int_plus(unsigned int *destination, unsigned int extra) {
    wavheader::input_stream.read(wavheader::int_buffer, sizeof(int));
    memcpy(destination, wavheader::int_buffer, sizeof(int));
    *destination += extra;
}

void read_short(unsigned short *destination) {
    wavheader::input_stream.read(wavheader::short_buffer, sizeof(short));
    memcpy(destination, wavheader::short_buffer, sizeof(short));
}
