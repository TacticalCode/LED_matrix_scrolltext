/**************************************
 *
 *	LED Matrix scroll text
 *	Author:	Damon Dransfeld
 *	Website: http://tacticalcode.de
 *	License: CC-BY-SA 3.0
 *	font8x8 by Daniel Hepper (https://github.com/dhepper/font8x8)
 *
 **************************************/
 
 // When compiling w/ Arduino IDE, you have to copy this
 // header file to your arduino/libraries folder!
#include <font8x8_basic.h>

// Offsets for rows/cols
const int start_rows = 38;
const int start_cols = 22;

// Amount of rows/cols
const int num_rows = 8;
const int num_cols = 8;

// Amount of picture repeats (scroll speed)
const int num_prts = 50;

// Array of chars to display
const char text[] = { "Visit TacticalCode.de :D" };

// Bitmask for comparison
const char bitmask = B000001;

void setup()
{
	// Set up rows
	for(int i = 0; i < num_rows; i++)
	{
		pinMode(start_rows + (2*i), OUTPUT);
		digitalWrite(start_rows + (2*i), LOW);
	}

	// Set up cols
	for(int i = 0; i < num_cols; i++)
	{
		pinMode(start_cols + (2*i), OUTPUT);
		digitalWrite(start_cols + (2*i), LOW);
	}
}

void loop()
{
	// scroll-counter loop (yes, you can do that with a global variable)
	for(int s = 0; s < sizeof(text)*num_cols; s++)
	{
		// loop everything num_prts times for a stable image
		for(int t = 0; t < num_prts; t++)
		{
			// iterate rows
			for(int r = 0; r < num_rows; r++)
			{
				digitalWrite(start_rows + (2*r), HIGH);
				// iterate cols
				for(int c = 0; c < num_cols; c++)
				{
					// c+s must be within the amount of total cols in text[]
					if(c+s < sizeof(text)*num_cols)
					{
						// do the display magic
						if((font8x8_basic[text[(c+s)/num_cols]][r] >> (c+s)%num_cols) & bitmask)
							digitalWrite(start_cols + (2*c), HIGH);
					}
					// but we want a blank display at the end, looks smooth
					else
					{
						// switch off all cols until we have a blank display
						digitalWrite(start_cols + (2*c), LOW);
					}
				}
				// cols are now switched on and were lit for some time
				for(int c = 0; c < num_cols; c++)
				{
					// so we switch them off
					digitalWrite(start_cols + (2*c), LOW);
				}
				digitalWrite(start_rows + (2*r), LOW);
			}
		}
	}
}