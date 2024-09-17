#ifndef GLOBALS_H
#define GLOBALS_H

#include "audio_files.h" // Include the header file for audio related data

#define BUF_SIZE 80000
#define BUF_THRESHOLD 96
#define XLIMIT 320
#define YLIMIT 240
#define MAX_ENTITIES 4

void interval_timer_ISR();
void ps2Mouse_ISR();

// Declare variables from audio_files.h as extern
extern const int kaboom_size;
extern const int slicing_size;
extern bool slice;
extern bool kaboom;

// Declare other global variables
extern volatile int timeout;
extern int mouse_xloc;
extern int mouse_yloc;
extern volatile int PS2counter;
extern volatile char byte1;
extern volatile char byte2;
extern volatile char byte3;


typedef struct {
    int left_btn;
    int right_btn;
    int dx;
    int dy;
} mouse_info;

extern mouse_info movement;

#endif
