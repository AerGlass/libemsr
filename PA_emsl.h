/*
PA_EMSL.cpp : Programmer's Arsenal Easy Maxmod Sound Library.
Code fully written by AerGlass, with reference of
https://github.com/qgerman2/streaming_example

Thanks to:

DesCube
devkitPro
PAlib developers.

*/

#ifndef PA_EMSL_INCLUDED
#define PA_EMSL_INCLUDED

#include <PA9.h>
#include <fat.h>
#include <maxmod9.h>
#include <filesystem.h>
#include <stdio.h>

typedef struct{
    int sampling_rate;
    int buffer_length;
    int format;
}ESML_TStreamInfo;
void EMSL_UpdateStream();
void EMSL_CloseStream();
void EMSL_PlayWav(const char* filename);
void EMSL_InitDefault();

extern ESML_TStreamInfo EMSL_StreamInfo;
#endif