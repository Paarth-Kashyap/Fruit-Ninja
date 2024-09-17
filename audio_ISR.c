#include "address_map_nios2.h"
#include "globals.h"
#include "audio_files.h" // Include the header file for audio related data

/* globals used for audio record/playback */


/*******************************************************************************
 * Audio - Interrupt Service Routine                                
 *                                                                          
 * This routine either records or playback audio data
 ******************************************************************************/
void audio_ISR( void )
{
	int i=0;
	audiop->control = 0x8; // clear the output FIFOs
	audiop->control = 0x0; // resume input conversion
	if(slice){
		for (i = 0; i < slicing_size; i++) {
			// output data if there is space in the output FIFOs
			while ((audiop->wsrc == 0) && (audiop->wslc == 0));
			audiop->ldata = slicing_sound[i];
			audiop->rdata = slicing_sound[i];
    	}
		slice=false;
	}

	i=0;
	audiop->control = 0x8; // clear the output FIFOs
	audiop->control = 0x0; // resume input conversion
	if(kaboom){
		for (i = 0; i < kaboom_size; i++) {
			// output data if there is space in the output FIFOs
			while ((audiop->wsrc == 0) && (audiop->wslc == 0));
			audiop->ldata = kaboom_sound[i];
			audiop->rdata = kaboom_sound[i];
    	}
		kaboom= false;
	}
	return;
}
