#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include "address_map_nios2.h"
#include "globals.h" //defines global values
#include "audio_files.h" // Include the header file for audio related data
#include "nios2_ctrl_reg_macros.h"
#include "images.h"


#ifndef __NIOS2_CTRL_REG_MACROS__
#define __NIOS2_CTRL_REG_MACROS__
/*****************************************************************************/
/* Macros for accessing the control registers. */
/*****************************************************************************/
#define NIOS2_READ_STATUS(dest)    \
	do                             \
	{                              \
		dest = __builtin_rdctl(0); \
	} while (0)
#define NIOS2_WRITE_STATUS(src)   \ //has to be 1
do
{
	__builtin_wrctl(0, src);
} while (0)
#define NIOS2_READ_ESTATUS(dest)   \
	do                             \
	{                              \
		dest = __builtin_rdctl(1); \
	} while (0)
#define NIOS2_READ_BSTATUS(dest)   \
	do                             \
	{                              \
		dest = __builtin_rdctl(2); \
	} while (0)
#define NIOS2_READ_IENABLE(dest)   \
	do                             \
	{                              \
		dest = __builtin_rdctl(3); \
	} while (0)
#define NIOS2_WRITE_IENABLE(src)   \ //enable 0xb80
	do
{
	__builtin_wrctl(3, src);
}
while (0)
#define NIOS2_READ_IPENDING(dest)  \
	do                             \
	{                              \
		dest = __builtin_rdctl(4); \
	} while (0)
#define NIOS2_READ_CPUID(dest)     \
	do                             \
	{                              \
		dest = __builtin_rdctl(5); \
	} while (0)
#endif

	/* The assembly language code below handles CPU reset processing */
void the_reset(void) __attribute__((section(".reset")));
void the_reset(void)
/*******************************************************************************
 * Reset code. By giving the code a section attribute with the name ".reset" we
 * allow the linker program to locate this code at the proper reset vector
 * address. This code just calls the main program.
 ******************************************************************************/
{
	asm(".set		noat");		// Magic, for the C compiler
	asm(".set		nobreak");	// Magic, for the C compiler
	asm("movia		r2, main"); // Call the C language main program
	asm("jmp		r2");
}

/* The assembly language code below handles CPU exception processing. This
 * code should not be modified; instead, the C language code in the function
 * interrupt_handler() can be modified as needed for a given application.
 */
void the_exception(void) __attribute__((section(".exceptions")));
void the_exception(void)
/*******************************************************************************
 * Exceptions code. By giving the code a section attribute with the name
 * ".exceptions" we allow the linker program to locate this code at the proper
 * exceptions vector address.
 * This code calls the interrupt handler and later returns from the exception.
 ******************************************************************************/
{
	asm(".set		noat");	   // Magic, for the C compiler
	asm(".set		nobreak"); // Magic, for the C compiler
	asm("subi		sp, sp, 128");
	asm("stw		et, 96(sp)");
	asm("rdctl	et, ctl4");
	asm("beq		et, r0, SKIP_EA_DEC"); // Interrupt is not external
	asm("subi		ea, ea, 4");		   /* Must decrement ea by one instruction
											* for external interupts, so that the
											* interrupted instruction will be run */

	asm("SKIP_EA_DEC:");
	asm("stw	r1,  4(sp)"); // Save all registers
	asm("stw	r2,  8(sp)");
	asm("stw	r3,  12(sp)");
	asm("stw	r4,  16(sp)");
	asm("stw	r5,  20(sp)");
	asm("stw	r6,  24(sp)");
	asm("stw	r7,  28(sp)");
	asm("stw	r8,  32(sp)");
	asm("stw	r9,  36(sp)");
	asm("stw	r10, 40(sp)");
	asm("stw	r11, 44(sp)");
	asm("stw	r12, 48(sp)");
	asm("stw	r13, 52(sp)");
	asm("stw	r14, 56(sp)");
	asm("stw	r15, 60(sp)");
	asm("stw	r16, 64(sp)");
	asm("stw	r17, 68(sp)");
	asm("stw	r18, 72(sp)");
	asm("stw	r19, 76(sp)");
	asm("stw	r20, 80(sp)");
	asm("stw	r21, 84(sp)");
	asm("stw	r22, 88(sp)");
	asm("stw	r23, 92(sp)");
	asm("stw	r25, 100(sp)"); // r25 = bt (skip r24 = et, because it is saved above)
	asm("stw	r26, 104(sp)"); // r26 = gp
	// skip r27 because it is sp, and there is no point in saving this
	asm("stw	r28, 112(sp)"); // r28 = fp
	asm("stw	r29, 116(sp)"); // r29 = ea
	asm("stw	r30, 120(sp)"); // r30 = ba
	asm("stw	r31, 124(sp)"); // r31 = ra
	asm("addi	fp,  sp, 128");

	asm("call	interrupt_handler"); // Call the C language interrupt handler

	asm("ldw	r1,  4(sp)"); // Restore all registers
	asm("ldw	r2,  8(sp)");
	asm("ldw	r3,  12(sp)");
	asm("ldw	r4,  16(sp)");
	asm("ldw	r5,  20(sp)");
	asm("ldw	r6,  24(sp)");
	asm("ldw	r7,  28(sp)");
	asm("ldw	r8,  32(sp)");
	asm("ldw	r9,  36(sp)");
	asm("ldw	r10, 40(sp)");
	asm("ldw	r11, 44(sp)");
	asm("ldw	r12, 48(sp)");
	asm("ldw	r13, 52(sp)");
	asm("ldw	r14, 56(sp)");
	asm("ldw	r15, 60(sp)");
	asm("ldw	r16, 64(sp)");
	asm("ldw	r17, 68(sp)");
	asm("ldw	r18, 72(sp)");
	asm("ldw	r19, 76(sp)");
	asm("ldw	r20, 80(sp)");
	asm("ldw	r21, 84(sp)");
	asm("ldw	r22, 88(sp)");
	asm("ldw	r23, 92(sp)");
	asm("ldw	r24, 96(sp)");
	asm("ldw	r25, 100(sp)"); // r25 = bt
	asm("ldw	r26, 104(sp)"); // r26 = gp
	// skip r27 because it is sp, and we did not save this on the stack
	asm("ldw	r28, 112(sp)"); // r28 = fp
	asm("ldw	r29, 116(sp)"); // r29 = ea
	asm("ldw	r30, 120(sp)"); // r30 = ba
	asm("ldw	r31, 124(sp)"); // r31 = ra

	asm("addi	sp,  sp, 128");

	asm("eret");
}

// VGA display global variables
volatile int drawBuffer;
short int Buffer1[400][512]; // 400 (240 + padding) rows, 512 (320 + padding) columns
short int Buffer2[400][512];

// Character buffer string initialization
char text_row[40] = "SCORE:\0";
char text_clear[40] = "                                     \0";
char text_start[40] = "PRESS ANY DE1_SOC KEY TO BEGIN\0";
char text_gameOver[40] = "PRESS ANY DE1_SOC KEY TO RESTART\0";
char text_score[40] = "0\0";

// Character buffer display function -- from DE1_SoC User Manual
void video_text(int x, int y, char *text_ptr);
// Low level VGA display functions -- from Lab 7
void plot_pixel(int x, int y, short int line_color);
void wait_for_vsync();

// Background drawing functions
void clear_screen();
void draw_start();
void draw_end();

// Object drawing functions
void draw_watermelon(int y, int x);
void draw_banana(int y, int x);
void draw_pineapple(int y, int x);
void draw_bomb(int y, int x);
void draw_splat(int y, int x);
void draw_explosion(int y, int x);
void draw_knife(int y, int x);

// Game state functions
void checkGameStart();
void checkGameRestart();
void checkGameEnd();
unsigned int createLivesRep(int n);

// Game loop functions
void launch();
void drawEntities();
void updateEntities();
bool withinRange(int x1, int y1, int x2, int y2);
void checkCollisions(int mouseX, int mouseY, bool clicked);

// Mouse Input functions
void mouseBoundCheck();
// Interrupt Functions
void interrupt_handler(void);

volatile int *vgaBase = (int *)PIXEL_BUF_CTRL_BASE;

// Game info variables
int score = 0;
int lives = 7;
bool gameStart = 0;
bool gameEnd = 0;

// Object management variables
bool entities[MAX_ENTITIES]; // Whether or not to draw an entity
int type[MAX_ENTITIES];
int xPositions[MAX_ENTITIES];
int yPositions[MAX_ENTITIES];
int xChange[MAX_ENTITIES];
int yChange[MAX_ENTITIES];




// Main game loop program
int main(void){
	// Initialize randomness
	srand(time(NULL));

	// VGA Initialization -- from Lab 7

	*(vgaBase + 1) = (int)&Buffer1;
	drawBuffer = *(vgaBase + 1);
	clear_screen();
	wait_for_vsync();
	*(vgaBase + 1) = (int)&Buffer2;
	drawBuffer = *(vgaBase + 1);
	clear_screen();
	wait_for_vsync();

	// Initialize board peripherals - LEDs, Keys, HEX Displays
	volatile int *pLeds = (int *)LED_BASE;
	*(pLeds) = 0;
	volatile int *pKeys = (int *)KEY_BASE;
	*(pKeys + 3) = 0b1111;
	volatile int *pHex = (int *)HEX3_HEX0_BASE;
	*(pHex) = 0b00110000001111100111100101101101; //"IVES" 7-segment representation
	*(pHex + 4) = 0b0111000;					  //"L" 7-segment representation

	// Initialize objects
	launch();

	/* Declare volatile pointers to I/O registers (volatile means that IO load
	   and store instructions will be used to access these pointer locations,
	   instead of regular memory loads and stores) */
	volatile int *interval_timer_ptr =
		(int *)TIMER_BASE;						 // interal timer base address
	volatile int *PS2_ptr = (int *)PS2_BASE;	 // PS/2 port address
	volatile int *audio_ptr = (int *)AUDIO_BASE; // audio port address

	/* initialize some variables */
	byte1 = 0;
	byte2 = 0;
	byte3 = 0;	 // used to hold PS/2 data
	timeout = 0; // synchronize with the timer

	slice=false;

	/* set the interval timer period for scrolling the HEX displays */
	int counter = 20000000; // 1/(100 MHz) x (20000000) = 200 msec
	*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
	*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;

	/* start interval timer, enable its interrupts */
	*(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1

	*(PS2_ptr) = 0xFF; /* reset */
	*(PS2_ptr + 1) = 0x1; /* write to the PS/2 Control register to enable interrupts */

	NIOS2_WRITE_IENABLE(0xc1); /* set interrupt mask bits for levels 0 (interval
								* timer), 6 (audio), and 7 (PS/2) */

	NIOS2_WRITE_STATUS(1); // enable Nios II interrupts
	
	// Main game loop
	while (1)
	{
		audiop->control = 0x8; // clear the output FIFOs
		audiop->control = 0x2; // resume input conversion
		// Case: draw starting screen
		if (!gameStart)
		{
			video_text(1, 1, text_clear);
			video_text(46, 36, text_clear);
			draw_start();
			checkGameStart();
			wait_for_vsync();			 // Swap front and back buffers on VGA Vsync
			drawBuffer = *(vgaBase + 1); // New back buffer
		} // Case: draw game over screen
		else if (gameEnd)
		{
			draw_end();
			video_text(1, 1, text_clear);
			checkGameRestart();
		} // Case: play the game loop
		else
		{
			clear_screen();
			//Initialize rest of screen
			video_text(15, 36, text_clear);
			video_text(22, 36, text_clear);
			video_text(1, 1, text_clear);
			video_text(1, 1, text_row);
			video_text(8, 1, text_score);
			sprintf(text_score, "%d", score);

			mouseBoundCheck();

			// Draw knife cursor
			draw_knife(mouse_xloc, mouse_yloc);
			// Check for collisions and lives count
			checkCollisions(mouse_xloc + 10, mouse_yloc - 10, movement.left_btn);
			checkGameEnd();

			// Draw and update all objects as necessa
			drawEntities();
			updateEntities();
		}

		// Double buffer the display
		wait_for_vsync();			 // Swap front and back buffers on VGA Vsync
		drawBuffer = *(vgaBase + 1); // New back buffer
	}
}

//**************************GAME LOOP FUNCTIONS*******************************//

// Resets/initializes the positions of all game board entities
void launch()
{
	// Load the entities list to determine whether or not to launch an entity
	entities[0] = 1; // Always launch at least 1 entity
	for (int entIdx = 1; entIdx < MAX_ENTITIES; entIdx++)
	{
		entities[entIdx] = rand() % 2; // 0 or 1
	}

	// Initialize positions
	for (int objIdx = 0; objIdx < MAX_ENTITIES; objIdx++)
	{
		xPositions[objIdx] = (rand() % 185) + 30; // between 30 and 215
		yPositions[objIdx] = (rand() % 11) + 250; // between 250 and 260

		xChange[objIdx] = (((rand() % 2) * 2) - 1) * (rand() % 7); // between -6 and 6
		yChange[objIdx] = ((rand() % 5) + 15) * -1;				   // between -15 and -19

		type[objIdx] = rand() % 4; // between 0 and 3
	}

	return;
}

// Draws each object at its given position based on its type (integer value from 0->3)
void drawEntities()
{
	for (int entity = 0; entity < MAX_ENTITIES; entity++)
	{
		if (entities[entity] == 1)
		{						   // only draw entity if it exists
			if (type[entity] == 0) // 0 -> Bomb
				draw_bomb(xPositions[entity], yPositions[entity]);
			else if (type[entity] == 1) // 1 -> Watermelon
				draw_watermelon(xPositions[entity], yPositions[entity]);
			else if (type[entity] == 2) // 2 -> Banana
				draw_banana(xPositions[entity], yPositions[entity]);
			else if (type[entity] == 3) // 3 -> Pineapple
				draw_pineapple(xPositions[entity], yPositions[entity]);
		}
	}
	return;
}

// Updates the position of each object based on its xChange and yChange
void updateEntities()
{
	// Check if all entities out of bounds
	bool allEmpty = true;
	for (int entity = 0; entity < MAX_ENTITIES; entity++)
	{
		if (entities[entity] == 1)
			allEmpty = false;
	}
	if (allEmpty)
	{
		launch();
		return;
	}

	// Else update positions for existing entities
	for (int entity = 0; entity < MAX_ENTITIES; entity++)
	{
		if (entities[entity] == 1)
		{
			// Check boundaries -- handle accordingly
			if (xPositions[entity] <= 23 || xPositions[entity] >= XLIMIT - 23)
			{
				xChange[entity] *= -1;
			}
			if (yPositions[entity] <= 23)
			{
				yChange[entity] *= -1;
			}
			if (yPositions[entity] >= YLIMIT + 50)
			{
				entities[entity] = 0;
				if (type[entity] != 0)
					lives--;
			}

			// Increment positions
			xPositions[entity] += xChange[entity];
			yPositions[entity] += yChange[entity];

			// Update Y change to add 'gravity'
			yChange[entity]++;
		}
	}
	return;
}

// Checks for any collisions between the knife cursor and objects on the screen
void checkCollisions(int mouseX, int mouseY, bool clicked)
{
	for (int entity = 0; entity < MAX_ENTITIES; entity++)
	{
		if (entities[entity])
		{
			if (clicked && withinRange(mouseX, mouseY, xPositions[entity], yPositions[entity]))
			{ // Collision detected
				entities[entity] = 0;
				xChange[entity] = 0;
				yChange[entity] = 0;
				if (type[entity] != 0)
				{
					updateEntities();

					clear_screen();
					drawEntities();
					draw_knife(mouse_xloc, mouse_yloc);
					draw_splat(xPositions[entity], yPositions[entity]);
					wait_for_vsync();
					drawBuffer = *(vgaBase + 1); //New back buffer
					
					clear_screen();
					drawEntities();
					draw_knife(mouse_xloc, mouse_yloc);
					draw_splat(xPositions[entity], yPositions[entity]);
					slice=true;
					
					clear_screen();
					updateEntities();
					drawEntities();
					draw_knife(mouse_xloc, mouse_yloc);
					wait_for_vsync();
					drawBuffer = *(vgaBase + 1);
				
					score++; // Fruit -> increment score
				}
				else
				{
					updateEntities();

					clear_screen();
					drawEntities();
					draw_knife(mouse_xloc, mouse_yloc);
					draw_explosion(xPositions[entity], yPositions[entity]);
					wait_for_vsync();
					drawBuffer = *(vgaBase + 1); //New back buffer
					
					clear_screen();
					drawEntities();
					draw_knife(mouse_xloc, mouse_yloc);
					draw_explosion(xPositions[entity], yPositions[entity]);
					kaboom=true;
					
					clear_screen();
					updateEntities();
					drawEntities();
					draw_knife(mouse_xloc, mouse_yloc);
					wait_for_vsync();
					drawBuffer = *(vgaBase + 1);
				
					lives--; // Bomb -> deincrement lives
				}
			}
		}
	}
}

// Collision helper function -- checks if two objects are within range of each other
bool withinRange(int x1, int y1, int x2, int y2)
{
	int dThreshold = 16; // The collision length

	// Calculate the distance between the two points using the distance formula
	int deltaX = abs(x2 - x1);
	int deltaY = abs(y2 - y1);

	// Check if the distance is less than or equal to the collision length
	if ((deltaX <= dThreshold) && (deltaY <= dThreshold))
		return true;
	else
		return false;
}

// Polls key input to see if the user wants to start the game
void checkGameStart()
{
	volatile int *pKeys = (int *)KEY_BASE;
	if (*(pKeys) != 0)
	{
		*(pKeys + 3) = 0b1111;
		gameStart = 1;
		clear_screen();
		wait_for_vsync();
		drawBuffer = *(vgaBase + 1);
		clear_screen();
	}
	return;
}

// Polls key input to see if the user wants to restart the game while on the end screen
void checkGameRestart()
{
	volatile int *pKeys = (int *)KEY_BASE;
	if (*(pKeys) != 0)
	{
		*(pKeys + 3) = 0b1111;

		// Reset game Info variables
		gameEnd = 0;
		gameStart = 1;
		lives = 7;
		score = 0;
		clear_screen();
		wait_for_vsync();
		drawBuffer = *(vgaBase + 1);
		clear_screen();

		// Reset objects
		launch();
	}
	return;
}

// Displays live count intuitively on the DE1_SoC LEDs and checks live count game end condition
void checkGameEnd()
{
	volatile int *pLeds = (int *)LED_BASE;
	*(pLeds) = createLivesRep(lives);

	// Check game end condition
	if (lives == 0)
	{
		gameEnd = 1;
	}

	return;
}

// Helper function -- Converts the live count integer value into a tally representation for display on the DE1_SoC LEDs
unsigned int createLivesRep(int n)
{
	if (n == 0)
	{
		return 0;
	}
	unsigned int result = 1;
	for (int i = 1; i < n; i++)
	{
		result = (result << 1) | 1;
	}
	return result;
}

// Low level VGA buffer pixel drawing function -- from Lab 7
void plot_pixel(int x, int y, short int line_color)
{
	volatile short int *one_pixel_address;
	one_pixel_address = drawBuffer + (y << 10) + (x << 1);
	*one_pixel_address = line_color;
}

// Double buffer synchronization function -- from Lab 7
void wait_for_vsync()
{
	volatile int *pixel_ctrl_ptr = (int *)0xff203020; // Base address
	int status;
	*pixel_ctrl_ptr = 1;			// start the synchronization process -- write 1 into front buffer address register
	status = *(pixel_ctrl_ptr + 3); // read the status register
	while ((status & 0x01) != 0)	// polling loop waiting for S bit to go to 0
	{
		status = *(pixel_ctrl_ptr + 3);
	}
	return;
}

// Background drawing function -- adapted from Lab 7
void clear_screen()
{
	for (int xIdx = 0; xIdx < 240; xIdx++)
	{
		for (int yIdx = 0; yIdx < 320; yIdx++)
		{
			plot_pixel(yIdx, xIdx, Board[xIdx][yIdx]);
		}
	}
	return;
}

// Start screen drawing function
void draw_start()
{
	// Draw start background
	for (int xIdx = 0; xIdx < 240; xIdx++)
	{
		for (int yIdx = 0; yIdx < 320; yIdx++)
		{
			plot_pixel(yIdx, xIdx, Start[xIdx][yIdx]);
		}
	}

	// Write prompt text
	video_text(15, 36, text_clear);
	video_text(15, 36, text_start);

	return;
}

// End screen drawing dunction
void draw_end()
{
	// Draw end screen background
	for (int xIdx = 0; xIdx < 240; xIdx++)
	{
		for (int yIdx = 0; yIdx < 320; yIdx++)
		{
			plot_pixel(yIdx, xIdx, End[xIdx][yIdx]);
		}
	}

	// Write prompt text
	video_text(22, 36, text_clear);
	video_text(22, 36, text_gameOver);

	return;
}

//**************************MOUSE FUNCTIONS*******************************//

//update mouse x and y locations based on the data packets loaded during ISR 
void ps2Mouse_ISR(){

	// initilize ps2 mouse address and important bits
	volatile int *PS2_ptr = (int *)PS2_BASE; // PS/2 port address
	int PS2_data, RAVAIL;
	PS2_data = *(PS2_ptr);					// read the Data register in the PS/2 port
	RAVAIL = (PS2_data & 0xFFFF0000) >> 16; // extract the RAVAIL field
	int RVALID = (int)(PS2_data & 0x8000);

	// store the 3 bytes
	byte1 = byte2;
	byte2 = byte3;
	byte3 = (char)(PS2_data & 0xFF);
	if (RVALID){

		// mouse inserted; initialize sending of data
		if ((byte2 == ((char)(0xAA)) && (byte3 == (char)0x00))){
			*(PS2_ptr) = 0xF4;
			PS2counter = -1;
		}
		// if all three packets of mouse data are lined up
		else if (PS2counter == 2){

			// get the mouse direction and buttons clicked
			movement.left_btn = (byte1 & 0x01) ? 1 : 0;

			mouse_xloc += (int)byte2;
			mouse_yloc -= (int)byte3;
			PS2counter = 0;

		} // increment if packets not lined up
		else{
			PS2counter++;
		}
	}
}

// function bounds the mouse location from going out of the vga size
void mouseBoundCheck(){
	// Ensure mouse_xloc is within bounds
	if (mouse_xloc > XLIMIT - 30){
		mouse_xloc = XLIMIT - 30;
	}
	else if (mouse_xloc < 30){
		mouse_xloc = 30;
	}

	// Ensure mouse_yloc is within bounds
	if (mouse_yloc > YLIMIT - 30){
		mouse_yloc = YLIMIT - 30;
	}
	else if (mouse_yloc < 30){
		mouse_yloc = 30;
	}
}



//**************************OBJECT DRAWING FUNCTIONS*******************************//

// Watermelon object drawing function
void draw_watermelon(int y, int x)
{
	int xOffset = x - 16;
	int yOffset = y - 16;
	for (int xIDX = 0; xIDX < 32; xIDX++)
	{
		for (int yIDX = 0; yIDX < 32; yIDX++)
		{
			if (Watermelon[xIDX][yIDX] != (short int)65535)
			{
				plot_pixel(yOffset + yIDX, xOffset + xIDX, Watermelon[xIDX][yIDX]);
			}
		}
	}
	return;
}

// Banana object drawing function
void draw_banana(int y, int x)
{
	int xOffset = x - 16;
	int yOffset = y - 16;
	for (int xIDX = 0; xIDX < 32; xIDX++)
	{
		for (int yIDX = 0; yIDX < 32; yIDX++)
		{
			if (Banana[xIDX][yIDX] != (short int)65535)
			{
				plot_pixel(yOffset + yIDX, xOffset + xIDX, Banana[xIDX][yIDX]);
			}
		}
	}
	return;
}

// Pineapple object drawing function
void draw_pineapple(int y, int x)
{
	int xOffset = x - 16;
	int yOffset = y - 16;
	for (int xIDX = 0; xIDX < 32; xIDX++)
	{
		for (int yIDX = 0; yIDX < 32; yIDX++)
		{
			if (Pineapple[xIDX][yIDX] != (short int)65535)
			{
				plot_pixel(yOffset + yIDX, xOffset + xIDX, Pineapple[xIDX][yIDX]);
			}
		}
	}
	return;
}

// Bomb object drawing function
void draw_bomb(int y, int x)
{
	int xOffset = x - 16;
	int yOffset = y - 16;
	for (int xIDX = 0; xIDX < 32; xIDX++)
	{
		for (int yIDX = 0; yIDX < 32; yIDX++)
		{
			if (Bomb[xIDX][yIDX] != (short int)65535)
			{
				plot_pixel(yOffset + yIDX, xOffset + xIDX, Bomb[xIDX][yIDX]);
			}
		}
	}
	return;
}

// Splat drawing function
void draw_splat(int y, int x)
{
	int xOffset = x - 16;
	int yOffset = y - 16;
	for (int xIDX = 0; xIDX < 32; xIDX++)
	{
		for (int yIDX = 0; yIDX < 32; yIDX++)
		{
			if (Splat[xIDX][yIDX] != (short int)65535)
			{
				plot_pixel(yOffset + yIDX, xOffset + xIDX, Splat[xIDX][yIDX]);
			}
		}
	}
	return;
}

// Explosion drawing function
void draw_explosion(int y, int x){
	int xOffset = x - 32;
	int yOffset = y - 32;
	for (int xIDX = 0; xIDX < 64; xIDX++){
		for (int yIDX = 0; yIDX < 64; yIDX++){
			if (Explosion[xIDX][yIDX] != (short int)65535){
				plot_pixel(yOffset + yIDX, xOffset + xIDX, Explosion[xIDX][yIDX]);
			}
		}
	}
	return;
}

// Knife object drawing function
void draw_knife(int y, int x){
	int xOffset = x - 16;
	int yOffset = y - 16;
	for (int xIDX = 0; xIDX < 32; xIDX++){
		for (int yIDX = 0; yIDX < 32; yIDX++){
			if (Knife[xIDX][yIDX] != (short int)65535){
				plot_pixel(yOffset + yIDX, xOffset + xIDX, Knife[xIDX][yIDX]);
			}
		}
	}
	return;
}

// Character buffer display function -- from DE1_SoC User Manual
void video_text(int x, int y, char *text_ptr){
	int offset;
	volatile char *character_buffer = (char *)FPGA_CHAR_BASE;

	offset = (y << 7) + x;
	while (*(text_ptr)){
		*(character_buffer + offset) = *(text_ptr);
		++text_ptr;
		++offset;
	}
}


//interup handler function for timer, ps2, and audio interrupts
void interrupt_handler(void)
{
	int ipending;
	NIOS2_READ_IPENDING(ipending);
	if (ipending & 0x01)
	{ // interval timer is interrupt level 0
		interval_timer_ISR();	
	}
	if (ipending & 0x80 )
	{ // PS/2 port is interrupt level 7
		ps2Mouse_ISR();
	}
	if (ipending & 0x40 )
	{ // PS/2 port is interrupt level 7
		audio_ISR();
	}
	// else, ignore the interrupt
	return;
}