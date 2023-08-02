//PA_EMSL.C : Programmer's Arsenal Easy Maxmod Sound Library.
//Code fully written by AerGlass, with reference of
//https://github.com/qgerman2/streaming_example
#include <PA9.h>
#include <fat.h>
#include <maxmod9.h>
#include <filesystem.h>
#include <stdio.h>
#include "PA_emsl.h"
mm_stream ESML_StreamSys;
mm_word EMSL_Stream(mm_word length, mm_addr dest, mm_stream_formats format);
FILE* file;
ESML_TStreamInfo ESML_StreamInfo;

void ESML_InitDefault(){
    ESML_StreamInfo.buffer_length = 16000;
    ESML_StreamInfo.format = MM_STREAM_16BIT_MONO;
    ESML_StreamInfo.sampling_rate =  22050;
}
void ESML_PlayWav(const char* filename) {
	//load audio file
	file = fopen(filename, "rb");

    if(!file) return;
	//initialize maxmod system
	//https://maxmod.devkitpro.org/ref/functions/mmInit.html
	mm_ds_system sys;
	sys.mod_count 			= 0;
	sys.samp_count			= 0;
	sys.fifo_channel		= FIFO_MAXMOD;
	mmInit( &sys );
	//create a stream
	//https://maxmod.devkitpro.org/ref/functions/mm_stream.html
    ESML_StreamSys.sampling_rate = ESML_StreamInfo.sampling_rate;
    ESML_StreamSys.buffer_length = ESML_StreamInfo.buffer_length;
    ESML_StreamSys.callback = EMSL_Stream;
    ESML_StreamSys.format = ESML_StreamInfo.format;
    ESML_StreamSys.timer = MM_TIMER2;
    ESML_StreamSys.manual = 1;
    mmStreamOpen(&ESML_StreamSys);
}
mm_word EMSL_Stream(mm_word length, mm_addr dest, mm_stream_formats format) {
	if (file) {
		int res = fread(dest, sizeof(s16), length, file);
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