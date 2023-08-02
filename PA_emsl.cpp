/*
PA_EMSL.cpp : Programmer's Arsenal Easy Maxmod Sound Library.
Code fully written by AerGlass, with reference of
https://github.com/qgerman2/streaming_example

Thanks to:

DesCube
devkitPro
PAlib developers.

*/
#include <PA9.h>
#include <fat.h>
#include <maxmod9.h>
#include <filesystem.h>
#include <stdio.h>
#include "PA_emsl.h"

mm_stream EMSL_StreamSys;
mm_word EMSL_Stream(mm_word length, mm_addr dest, mm_stream_formats format);
FILE* file;
ESML_TStreamInfo EMSL_StreamInfo;

void EMSL_InitDefault(){
    EMSL_StreamInfo.buffer_length = 16000;
    EMSL_StreamInfo.format = MM_STREAM_16BIT_MONO;
    EMSL_StreamInfo.sampling_rate =  22050;
	mm_ds_system sys;
	sys.mod_count 			= 0;
	sys.samp_count			= 0;
	sys.fifo_channel		= FIFO_MAXMOD;
	mmInit( &sys );
}
void EMSL_PlayWav(const char* filename) {
	//load audio file
	file = fopen(filename, "rb");

    if(!file) return;
	//initialize maxmod system
	//https://maxmod.devkitpro.org/ref/functions/mmInit.html
	//create a stream
	//https://maxmod.devkitpro.org/ref/functions/mm_stream.html
    EMSL_StreamSys.sampling_rate = EMSL_StreamInfo.sampling_rate;
    EMSL_StreamSys.buffer_length = EMSL_StreamInfo.buffer_length;
    EMSL_StreamSys.callback = EMSL_Stream;
    EMSL_StreamSys.format = EMSL_StreamInfo.format;
    EMSL_StreamSys.timer = MM_TIMER2;
    EMSL_StreamSys.manual = 1;
    mmStreamOpen(&EMSL_StreamSys);
}
mm_word EMSL_Stream(mm_word length, mm_addr dest, mm_stream_formats format) {
	if (file) {
		u32 res = fread(dest, sizeof(s16), length, file);
		
		if (res != length) {
			fseek(file,0,SEEK_SET);
		} else {
			length = res;
		}
	}
	return length;
}
void EMSL_CloseStream(){
    mmStreamClose();
    fclose(file);
}
void EMSL_UpdateStream() {
    mmStreamUpdate();
}