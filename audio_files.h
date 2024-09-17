#ifndef AUDIO_FILES_H
#define AUDIO_FILES_H
#include <stdbool.h> // Include the necessary header for bool type

// Declare extern variables for audio related data
extern const int kaboom_size;
extern const int slicing_size;
extern bool slice;
extern bool kaboom;

void audio_ISR(void);

struct audio_t {
	volatile unsigned int control;
	volatile unsigned char rarc;
	volatile unsigned char ralc;
	volatile unsigned char wsrc;
	volatile unsigned char wslc;
	volatile unsigned int ldata;
	volatile unsigned int rdata;
};
extern struct audio_t *const audiop;




//audio variables
//Sound sample arrays
extern const int slicing_sound[7941];
extern const int kaboom_sound[11911];
#endif