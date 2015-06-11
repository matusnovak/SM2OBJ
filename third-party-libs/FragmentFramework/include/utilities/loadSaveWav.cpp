/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "loadSaveWav.h"
#include "file.h"
#include "../math/stringMath.h"

///=============================================================================
bool ffw::loadWAV(const std::string& Path, unsigned char** Data, int* BitsPerSample, size_t* Size, int* ByteRate, int* SampleRate, int* NumChannels){
    return loadWAV(utf8ToWstr(Path), Data, BitsPerSample, Size, ByteRate, SampleRate, NumChannels);
}

///=============================================================================
bool ffw::loadWAV(const std::wstring& Path, unsigned char** Data, int* BitsPerSample, size_t* Size, int* ByteRate, int* SampleRate, int* NumChannels){
    if(Data == NULL)return false;

    file input;
    if(!input.open(Path, true, false, false)){
        return false;
    }

    // Check if file is RIFF
    char chunkID[4];
    input.read( reinterpret_cast <char*>(&chunkID[0]), sizeof(char));
    input.read( reinterpret_cast <char*>(&chunkID[1]), sizeof(char));
    input.read( reinterpret_cast <char*>(&chunkID[2]), sizeof(char));
    input.read( reinterpret_cast <char*>(&chunkID[3]), sizeof(char));
    if( !(chunkID[0] == 'R' && chunkID[1] == 'I' && chunkID[2] == 'F' && chunkID[3] == 'F') ){
        //logger().error() << "[File loader] " << Path << " Can not be opened as audio! File is not RIFF!";
        input.close();
        return false;
    }

    // Get chunk size
    unsigned int chunkSize;
    input.read( reinterpret_cast <char*>(&chunkSize), sizeof(unsigned int));

    // Check if file is WAVE
    char format[4];
    input.read( reinterpret_cast <char*>(&format[0]), sizeof(char));
    input.read( reinterpret_cast <char*>(&format[1]), sizeof(char));
    input.read( reinterpret_cast <char*>(&format[2]), sizeof(char));
    input.read( reinterpret_cast <char*>(&format[3]), sizeof(char));
    if( !(format[0] == 'W' && format[1] == 'A' && format[2] == 'V' && format[3] == 'E') ){
        //logger().error() << "[File loader] " << Path << " Can not be opened as audio! File is RIFF but not WAVE!";
        input.close();
        return false;
    }

    // Find FMT sub-chunk
    bool foundFMT = false;
    while(!foundFMT && !input.eof()){
        char subchunk1ID[4];
        input.read( reinterpret_cast <char*>(&subchunk1ID[0]), sizeof(char));
        if(subchunk1ID[0] == 'f'){
            input.read( reinterpret_cast <char*>(&subchunk1ID[1]), sizeof(char));
            input.read( reinterpret_cast <char*>(&subchunk1ID[2]), sizeof(char));
            input.read( reinterpret_cast <char*>(&subchunk1ID[3]), sizeof(char));
            if(subchunk1ID[1] == 'm' && subchunk1ID[2] == 't' && subchunk1ID[3] == ' ')foundFMT = true;
        }
    }

    if(!foundFMT){
        //logger().error() << "[File loader] " << Path << " Can not find FMT sub chunk! File might be corrupted!";
        input.close();
        return false;
    }

    // Get sub chunk data
    unsigned int subChunk1Size = 0;
    unsigned short audioFormat = 0;
    unsigned short numChannels = 0;
    unsigned int sampleRate = 0;
    unsigned int byteRate = 0;
    unsigned short blockAlign = 0;
    unsigned short bitsPerSample = 0;

    input.read( reinterpret_cast <char*>(&subChunk1Size), sizeof(unsigned int));
    input.read( reinterpret_cast <char*>(&audioFormat), sizeof(unsigned short));
    input.read( reinterpret_cast <char*>(&numChannels), sizeof(unsigned short));
    input.read( reinterpret_cast <char*>(&sampleRate), sizeof(unsigned int));
    input.read( reinterpret_cast <char*>(&byteRate), sizeof(unsigned int));
    input.read( reinterpret_cast <char*>(&blockAlign), sizeof(unsigned short));
    input.read( reinterpret_cast <char*>(&bitsPerSample), sizeof(unsigned short));

    // Find data sub-chunk
    bool foundData = false;
    while(!foundData && !input.eof()){
        char subchunk1ID[4];
        input.read( reinterpret_cast <char*>(&subchunk1ID[0]), sizeof(char));
        if(subchunk1ID[0] == 'd'){
            input.read( reinterpret_cast <char*>(&subchunk1ID[1]), sizeof(char));
            input.read( reinterpret_cast <char*>(&subchunk1ID[2]), sizeof(char));
            input.read( reinterpret_cast <char*>(&subchunk1ID[3]), sizeof(char));
            if(subchunk1ID[1] == 'a' && subchunk1ID[2] == 't' && subchunk1ID[3] == 'a')foundData = true;
        }
    }

    if(!foundData){
        //logger().error() << "[File loader] " << Path << " Can not find data sub chunk! File might be corrupted!";
        input.close();
        return false;
    }

    // Get size of data
    unsigned int subChunk2Size = 0;
    input.read( reinterpret_cast <char*>(&subChunk2Size), sizeof(unsigned int));

    if(Data != NULL){
        // Read data
        *Data = new unsigned char[subChunk2Size];
        input.read( reinterpret_cast <char*>(*Data), subChunk2Size);

        if(Size != NULL)*Size = subChunk2Size;
    }

    if(BitsPerSample != NULL)*BitsPerSample = bitsPerSample;
    if(ByteRate != NULL)*ByteRate = byteRate;
    if(SampleRate != NULL)*SampleRate = sampleRate;
    if(NumChannels != NULL)*NumChannels = numChannels;

    input.close();
    //logger().debug() << "[File loader] " << Path << " successfully loaded as WAV sound!";
    return true;
}

///=============================================================================
bool ffw::saveWAV(const std::string& Path, unsigned char* Data, int BitsPerSample, size_t Size, int ByteRate, int SampleRate, int NumChannels){
    return saveWAV(utf8ToWstr(Path), Data, BitsPerSample, Size, ByteRate, SampleRate, NumChannels);
}

///=============================================================================
bool ffw::saveWAV(const std::wstring& Path, unsigned char* Data, int BitsPerSample, size_t Size, int ByteRate, int SampleRate, int NumChannels){
    if(Data == NULL)return false;
    if(BitsPerSample == 0 || Size == 0 || ByteRate == 0 || SampleRate == 0 || NumChannels == 0)return false;

    file output;
    if(!output.open(Path, true, true, true)){
        return false;
    }

    // Wrtie header ID
    char chunkID[4] = {'R', 'I', 'F', 'F'};
    output.write(chunkID, sizeof(chunkID));

    unsigned int subChunk1Size = 16; // PCM
    unsigned int subChunk2Size = Size;
    unsigned int chunk1Size = 4 + (8 + subChunk1Size) + (8 + subChunk2Size);
    output.write( reinterpret_cast <char*>(&chunk1Size), sizeof(unsigned int) );

    char format[4] = {'W', 'A', 'V', 'E'};
    output.write(format, sizeof(format));

    // Wrtie FMT sub-chunk
    char subchunk1ID[4] = {'f', 'm', 't', ' '};
    output.write(subchunk1ID, sizeof(subchunk1ID));

    output.write( reinterpret_cast <char*>(&subChunk1Size), sizeof(unsigned int) );

    unsigned short audioFormat = 0;
    if(BitsPerSample == 16) audioFormat = 1;
    else if(BitsPerSample == 32) audioFormat = 3;
    unsigned short blockAlign = NumChannels * BitsPerSample / 8;

    output.write( reinterpret_cast <char*>(&audioFormat), sizeof(unsigned short) );
    output.write( reinterpret_cast <char*>(&NumChannels), sizeof(unsigned short) );
    output.write( reinterpret_cast <char*>(&SampleRate), sizeof(unsigned int) );
    output.write( reinterpret_cast <char*>(&ByteRate), sizeof(unsigned int) );
    output.write( reinterpret_cast <char*>(&blockAlign), sizeof(unsigned short) );
    output.write( reinterpret_cast <char*>(&BitsPerSample), sizeof(unsigned short) );

    // Wrtie chunk ID
    char subchunk2ID[4] = {'d', 'a', 't', 'a'};
    output.write(subchunk2ID, sizeof(subchunk2ID));
    // Wrtie size of data
    output.write( reinterpret_cast <char*>(&subChunk2Size), sizeof(unsigned int) );
    // Write data
    output.write( reinterpret_cast <char*>(Data), Size );

    output.close();
    return true;
}
