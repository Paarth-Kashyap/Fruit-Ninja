// globals.c

#include "globals.h"

volatile int timeout = 0;

int mouse_xloc = XLIMIT / 2;
int mouse_yloc = YLIMIT / 2;

volatile char byte1 = 0;
volatile char byte2 = 0;
volatile char byte3 = 0;

volatile int PS2counter = 0;

mouse_info movement = {0};

// Define the pointer to the audio structure
struct audio_t *const audiop = ((struct audio_t *)0xff203040);

const int kaboom_size=11911;
const int slicing_size=7941;
bool slice=false;
bool kaboom=false;
