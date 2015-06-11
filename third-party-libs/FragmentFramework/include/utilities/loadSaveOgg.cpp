/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "loadSaveOgg.h"
#include "../math/math.h"
#include "../math/stringMath.h"
#include "file.h"
#include "fileUtilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vorbisenc.h>

#define BYTES_PER_CHUNK 4096

///=============================================================================
// Code is adapted from libvorbis example 'decoder_example.c'
static bool loadOggFile(FILE* File, size_t* FinalSize, int* Channels, int* Frequency, float* Data){
    // Sync and verify incoming physical bitstream
    ogg_sync_state   oy;
    // Take physical pages, weld into a logical stream of packets
    ogg_stream_state os;
    // One Ogg bitstream page. Vorbis packets are inside
    ogg_page         og;
    // One raw packet of data for decode
    ogg_packet       op;
    // Struct that stores all the static vorbis bitstream
    vorbis_info      vi;
    // Struct that stores all the bitstream user comments
    vorbis_comment   vc;
    // Central working state for the packet->PCM decoder
    vorbis_dsp_state vd;
    // local working space for packet->PCM decode
    vorbis_block     vb;

    char *buffer;
    int  bytes;
    int convsize = 0;

    ogg_sync_init(&oy);

    // We repeat if the bitstream is chained
    while(1){
        int eos=0;
        int i;

        // Grab some data at the head of the stream. We want the first page
        // (which is guaranteed to be small and only contain the Vorbis
        // stream initial header) We need the first page to get the stream
        // serialno.

        // Submit a 4k block to libvorbis' Ogg layer
        buffer=ogg_sync_buffer(&oy,4096);
        bytes=fread(buffer,1,4096,File);
        ogg_sync_wrote(&oy,bytes);

        // Get the first page.
        if(ogg_sync_pageout(&oy,&og)!=1){
            // Have we simply run out of data?  If so, we're done.
            if(bytes<4096)break;

            // Error case.  Must not be Vorbis data
            //std::cout << "Input does not appear to be an Ogg bitstream" << std::endl;
            return false;
        }

        // Get the serial number and set up the rest of decode.
        // Serialno first; use it to set up a logical stream
        ogg_stream_init(&os,ogg_page_serialno(&og));

        // Extract the initial header from the first page and verify that the
        // Ogg bitstream is in fact Vorbis data

        vorbis_info_init(&vi);
        vorbis_comment_init(&vc);

        if(ogg_stream_pagein(&os,&og)<0){
            // Error; stream version mismatch perhaps
            //std::cout << "Error reading first page of Ogg bitstream data" << std::endl;
            ogg_stream_clear(&os);
            vorbis_comment_clear(&vc);
            vorbis_info_clear(&vi);
            return false;
        }

        if(ogg_stream_packetout(&os,&op)!=1){
            // No page? must not be vorbis
            //std::cout << "Error reading initial header packet" << std::endl;
            ogg_stream_clear(&os);
            vorbis_comment_clear(&vc);
            vorbis_info_clear(&vi);
            return false;
        }

        if(vorbis_synthesis_headerin(&vi,&vc,&op)<0){
            // Error case; not a vorbis header
            //std::cout << "This Ogg bitstream does not contain Vorbis audio data" << std::endl;
            ogg_stream_clear(&os);
            vorbis_comment_clear(&vc);
            vorbis_info_clear(&vi);
            return false;
        }

        // At this point, we're sure we're Vorbis. We've set up the logical
        // (Ogg) bitstream decoder. Get the comment and codebook headers and
        // set up the Vorbis decoder

        // The next two packets in order are the comment and codebook headers.
        // They're likely large and may span multiple pages. Thus we read
        // and submit data until we get our two packets, watching that no
        // pages are missing. If a page is missing, error out; losing a
        // header page is the only place where missing data is fatal.

        i=0;
        while(i<2){
            while(i<2){
                int result=ogg_sync_pageout(&oy,&og);
                // Need more data
                if(result==0)break;

                // Don't complain about missing or corrupt data yet. We'll
                // catch it at the packet output phase
                if(result==1){
                    ogg_stream_pagein(&os,&og);

                    // we can ignore any errors here
                    // as they'll also become apparent
                    // at packetout
                    while(i<2){
                        result=ogg_stream_packetout(&os,&op);
                        if(result==0)break;
                        if(result<0){
                            // Uh oh; data at some point was corrupted or missing!
                            //  We can't tolerate that in a header. Die.
                            //std::cout << "Corrupt secondary header. Exiting..." << std::endl;
                            ogg_stream_clear(&os);
                            vorbis_comment_clear(&vc);
                            vorbis_info_clear(&vi);
                            return false;
                        }
                        result=vorbis_synthesis_headerin(&vi,&vc,&op);

                        if(result<0){
                            //std::cout << "Corrupt secondary header. Exiting..." << std::endl;
                            ogg_stream_clear(&os);
                            vorbis_comment_clear(&vc);
                            vorbis_info_clear(&vi);
                            return false;
                        }

                        i++;
                    }
                }
            }
            // No harm in not checking before adding more */
            buffer=ogg_sync_buffer(&oy,4096);
            bytes=fread(buffer,1,4096,File);

            if(bytes==0 && i<2){
                //std::cout << "End of file before finding all Vorbis headers!" << std::endl;
                ogg_stream_clear(&os);
                vorbis_comment_clear(&vc);
                vorbis_info_clear(&vi);
                return false;
            }

            ogg_sync_wrote(&oy,bytes);
        }

        // Throw the comments plus a few lines about the bitstream we're decoding
        //char **ptr=vc.user_comments;
        //while(*ptr){
        //    std::cout << *ptr << std::endl;
        //    ++ptr;
        //}
        //std::cout << "Bitstream is " << vi.channels << " channel, " << vi.rate << std::endl;
        //std::cout << "Encoded by: " << vc.vendor << std::endl;
        *Channels = vi.channels;
        *Frequency = vi.rate;

        convsize=4096/vi.channels;

        // OK, got and parsed all three headers. Initialize the Vorbis
        // packet->PCM decoder.

        if(vorbis_synthesis_init(&vd,&vi)==0){
            // Central decode state
            vorbis_block_init(&vd,&vb);

            // local state for most of the decode
            // so multiple block decodes can
            // proceed in parallel. We could init
            // multiple vorbis_block structures
            // for vd here

            // The rest is just a straight decode loop until end of stream
            while(!eos){
                while(!eos){
                    int result=ogg_sync_pageout(&oy,&og);
                    // Need more data
                    if(result==0)break;
                    // Missing or corrupt data at this page position
                    if(result<0){
                        //std::cout << "Corrupt or missing data in bitstream continuing..." << std::endl;

                    } else {
                        ogg_stream_pagein(&os,&og);
                        // Can safely ignore errors at this point
                        while(1){
                            result=ogg_stream_packetout(&os,&op);

                            if(result==0)break;
                            // need more data
                            if(result<0){
                                // Missing or corrupt data at this page position
                                // No reason to complain; already complained above
                            } else {

                                // We have a packet.  Decode it
                                float **pcm;
                                int samples;

                                // Test for success!
                                if(vorbis_synthesis(&vb,&op)==0)
                                    vorbis_synthesis_blockin(&vd,&vb);

                                // **pcm is a multichannel float vector.  In stereo, for
                                // example, pcm[0] is left, and pcm[1] is right.  samples is
                                // the size of each channel.  Convert the float values
                                // (-1.<=range<=1.) to whatever PCM format and write it out

                                while((samples=vorbis_synthesis_pcmout(&vd,&pcm))>0){

                                    int bout=(samples<convsize?samples:convsize);

                                    //std::cout << "reading 1: " << bout << " samples" << std::endl;
                                    if(Data != NULL){
                                        float* dataOffset = &Data[*FinalSize *vi.channels];
                                        for(int c = 0; c < vi.channels; c++){
                                            float *mono = pcm[c];
                                            for(int j = 0; j < bout; j++){
                                               dataOffset[j*vi.channels +c] = mono[j];

                                            }
                                        }
                                    }

                                    *FinalSize += bout;

                                    // tell libvorbis how many samples we actually consumed
                                    vorbis_synthesis_read(&vd, bout);
                                }
                            }
                        }
                        if(ogg_page_eos(&og))eos=1;
                    }
                }
                if(!eos){
                    buffer=ogg_sync_buffer(&oy,4096);
                    bytes=fread(buffer,1,4096,File);
                    ogg_sync_wrote(&oy,bytes);
                    if(bytes==0)eos=1;
                }
            }
            //std::cout << "cycle6 end" << std::endl;
            //std::cout << "finalSize: " << finalSize*4 << std::endl;

            // ogg_page and ogg_packet structs always point to storage in
            // libvorbis.  They're never freed or manipulated directly

            vorbis_block_clear(&vb);
            vorbis_dsp_clear(&vd);
        } else {
            //std::cout << "Error: Corrupt header during playback initialization" << std::endl;
        }

        // clean up this logical bitstream; before exit we see if we're
        // followed by another [chained]

        ogg_stream_clear(&os);
        vorbis_comment_clear(&vc);
        vorbis_info_clear(&vi);

        break;
    }

    // OK, clean up the framer
    ogg_sync_clear(&oy);
    return true;
}

///=============================================================================
bool ffw::loadOGG(const std::string& Path, unsigned char** Data, int* BitsPerSample, size_t* Size, int* ByteRate, int* SampleRate, int* NumChannels){
    return loadOGG(utf8ToWstr(Path), Data, BitsPerSample, Size, ByteRate, SampleRate, NumChannels);
}

///=============================================================================
// Code is adapted from libvorbis example 'decoder_example.c'
bool ffw::loadOGG(const std::wstring& Path, unsigned char** Data, int* BitsPerSample, size_t* Size, int* ByteRate, int* SampleRate, int* NumChannels){
    FILE* input = _wfopen(Path.c_str(), L"rb");
    if(input == NULL){
        //std::cout << "failed to open" << std::endl;
        return false;
    }

    size_t totalSamples = 0;
    int numOfChannels;
    int frequency;
    if(loadOggFile(input, &totalSamples, &numOfChannels, &frequency, NULL)){
        //std::cout << "Done" << std::endl;
        //std::cout << "finalSize: " << totalSamples << std::endl;
        //std::cout << "numOfChannels: " << numOfChannels << std::endl;
        //std::cout << "frequency: " << frequency << std::endl;
    } else {
        return false;
    }

    if(NumChannels != NULL)
        *NumChannels = numOfChannels;

    if(BitsPerSample != NULL)
        *BitsPerSample = sizeof(float)*8;

    if(ByteRate != NULL)
        *ByteRate = (*BitsPerSample/8)*frequency*numOfChannels;

    if(Size != NULL)
        *Size = totalSamples*(*BitsPerSample/8)*numOfChannels;

    if(SampleRate != NULL)
        *SampleRate = frequency;

    if(Data != NULL){
        fseek(input, 0, SEEK_SET);
        float** pcm = (float**)Data;
        *pcm = new float[totalSamples*numOfChannels];
        //std::cout << "loading..." << std::endl;
        totalSamples = 0;
        loadOggFile(input, &totalSamples, &numOfChannels, &frequency, *pcm);
    }

    //std::cout << "NumChannels: " << *NumChannels << std::endl;
    //std::cout << "BitsPerSample: " << *BitsPerSample << std::endl;
    //std::cout << "ByteRate: " << *ByteRate << std::endl;
    //std::cout << "Size: " << *Size << std::endl;
    //std::cout << "SampleRate: " << *SampleRate << std::endl;

    fclose(input);

    return true;
}

///=============================================================================
bool ffw::saveOGG(const std::string& Path, unsigned char* Data, int BitsPerSample, size_t Size, int ByteRate, int SampleRate, int NumChannels){
    return saveOGG(utf8ToWstr(Path), Data, BitsPerSample, Size, ByteRate, SampleRate, NumChannels);
}

///=============================================================================
// Code is adapted from libvorbis example 'encoder_example.c'
bool ffw::saveOGG(const std::wstring& Path, unsigned char* Data, int BitsPerSample, size_t Size, int ByteRate, int SampleRate, int NumChannels){
    if(BitsPerSample != 32)return false;

    FILE* output = _wfopen(Path.c_str(), L"wb");

    if(output == NULL){
        //std::cout << "failed to save!" << std::endl;
        return false;
    }

    // Take physical pages, weld into a logical stream of packets
    ogg_stream_state os;
    // One Ogg bitstream page. Vorbis packets are inside
    ogg_page         og;
    // One raw packet of data for decode
    ogg_packet       op;
    // Struct that stores all the static vorbis bitstream settings
    vorbis_info      vi;
    // Struct that stores all the user comments
    vorbis_comment   vc;
    // Central working state for the packet->PCM decoder
    vorbis_dsp_state vd;
    // Local working space for packet->PCM decode
    vorbis_block     vb;

    int eos=0;
    int ret;

    vorbis_info_init(&vi);

    // Encoding using an average bitrate mode (ABR).
    // example: 44kHz stereo coupled, average 128kbps VBR
    // ret = vorbis_encode_init(&vi,2,44100,-1,128000,-1);

    ret = vorbis_encode_init(&vi, NumChannels, SampleRate, -1, ByteRate*8, -1);

    // do not continue if setup failed; this can happen if we ask for a
    // mode that libVorbis does not support (eg, too low a bitrate, etc,
    // will return 'OV_EIMPL')

    if(ret){
        vorbis_info_clear(&vi);
        fclose(output);
        return false;
    }

    // Add a comment
    vorbis_comment_init(&vc);
    vorbis_comment_add_tag(&vc, "ENCODER", "vorbis");

    // set up the analysis state and auxiliary encoding storage
    vorbis_analysis_init(&vd,&vi);
    vorbis_block_init(&vd,&vb);

    // Set up our packet->stream encoder
    // Pick a random serial number; that way we can more likely build
    // chained streams just by concatenation

    srand((unsigned int)time(NULL));
    ogg_stream_init(&os, rand());

    // Vorbis streams begin with three headers; the initial header (with
    // most of the codec setup parameters) which is mandated by the Ogg
    // bitstream spec.  The second header holds any comment fields.  The
    // third header holds the bitstream codebook.  We merely need to
    // make the headers, then pass them to libvorbis one at a time;
    // libvorbis handles the additional Ogg bitstream constraints

    ogg_packet header;
    ogg_packet header_comm;
    ogg_packet header_code;

    vorbis_analysis_headerout(&vd,&vc,&header,&header_comm,&header_code);

    // automatically placed in its own page
    ogg_stream_packetin(&os,&header);
    ogg_stream_packetin(&os,&header_comm);
    ogg_stream_packetin(&os,&header_code);

    // This ensures the actual
    // audio data will start on a new page, as per spec

    while(!eos){
        int result=ogg_stream_flush(&os,&og);
        if(result==0)break;
        fwrite(og.header,1,og.header_len,output);
        fwrite(og.body,1,og.body_len,output);
    }

    float* dataPtr = (float*)Data;
    size_t totalSamples = (Size/NumChannels) / (BitsPerSample/8);

    size_t samplesLeft = totalSamples;
    size_t samplesWritten = 0;
    while(!eos){
        long i;
        // stereo hardwired here
        //long bytes = fread(readbuffer,1,READ*4,stdin);

        long bytes = BYTES_PER_CHUNK;
        if(samplesLeft < BYTES_PER_CHUNK){
            bytes = samplesLeft;
        }
        samplesLeft -= bytes;

        if(bytes==0){
            // end of file.  this can be done implicitly in the mainline,
            // but it's easier to see here in non-clever fashion.
            // Tell the library we're at end of stream so that it can handle
            // the last frame and mark end of stream in the output properly
            vorbis_analysis_wrote(&vd,0);

        } else {
            // data to encode

            // expose the buffer to submit data
            float **buffer=vorbis_analysis_buffer(&vd, BYTES_PER_CHUNK);

            // uninterleave samples
            for(i = 0; i < bytes; i++){
                /*buffer[0][i]=((readbuffer[i*4+1]<<8)|
                      (0x00ff&(int)readbuffer[i*4]))/32768.f;
                buffer[1][i]=((readbuffer[i*4+3]<<8)|
                      (0x00ff&(int)readbuffer[i*4+2]))/32768.f;*/
                for(int c = 0; c < NumChannels; c++){
                    buffer[c][i] = dataPtr[samplesWritten];
                    samplesWritten++;
                }
            }

            // tell the library how much we actually submitted
            vorbis_analysis_wrote(&vd, i);
        }

        // vorbis does some data preanalysis, then divvies up blocks for
        // more involved (potentially parallel) processing.  Get a single
        // block for encoding now
        while(vorbis_analysis_blockout(&vd,&vb)==1){

            // analysis, assume we want to use bitrate management
            vorbis_analysis(&vb,NULL);
            vorbis_bitrate_addblock(&vb);

            while(vorbis_bitrate_flushpacket(&vd,&op)){

                // weld the packet into the bitstream
                ogg_stream_packetin(&os,&op);

                // write out pages (if any)
                while(!eos){
                    int result=ogg_stream_pageout(&os,&og);
                    if(result==0)break;
                    fwrite(og.header,1,og.header_len,output);
                    fwrite(og.body,1,og.body_len,output);

                    // this could be set above, but for illustrative purposes, I do
                    // it here (to show that vorbis does know where the stream ends)

                    if(ogg_page_eos(&og))eos=1;
                }
            }
        }
    }

    // clean up and exit.  vorbis_info_clear() must be called last

    ogg_stream_clear(&os);
    vorbis_block_clear(&vb);
    vorbis_dsp_clear(&vd);
    vorbis_comment_clear(&vc);
    vorbis_info_clear(&vi);

    // ogg_page and ogg_packet structs always point to storage in
    // libvorbis.  They're never freed or manipulated directly

    fclose(output);
    return true;
}
