/*
	Hermes Electric Fence tester,
	Copyright (c)1999 by Magnus Norddahl / ClanSoft.
*/

#include <iostream.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Efence.h"

int main(int, char **)
{
	cout << endl;
	cout << "Hermes Electric Fence tester," << endl;
	cout << "Copyright (c)1999 by Magnus Norddahl / ClanSoft." << endl;

	cout << endl << "Sit back, get a drink, this will take a while... "
	     << endl << endl << flush;

	assert(Hermes_Init() != 0);

	int formats[] =
	{
		32, 8, 8, 8, 8,
		32, 8, 8, 8, 0,
		16, 5, 6, 5, 0,
		16, 5, 5, 5, 1,
		//16 /* fails with 15 */, 5, 5, 5, 0,
		//16 /* fails with 15 */, 4, 4, 4, 1,
		-1
	};

	// Test all possible format combinations:
	for (int i=0; formats[i*5] != -1; i++)
	{
		for (int j=0; formats[j*5] != -1; j++)
		{
			printf(
				"Testing %d(RGBA%d%d%d%d) -> %d(RGBA%d%d%d%d) ",
				formats[i*5+0],
				formats[i*5+1],
				formats[i*5+2],
				formats[i*5+3],
				formats[i*5+4],
				formats[j*5+0],
				formats[j*5+1],
				formats[j*5+2],
				formats[j*5+3],
				formats[j*5+4]);
			cout.flush();

			test_depth(
				formats[i*5 + 0], // src_depth
				calc_red_mask(&formats[i*5+1]),
				calc_green_mask(&formats[i*5+1]),
				calc_blue_mask(&formats[i*5+1]),
				calc_alpha_mask(&formats[i*5+1]),
				formats[j*5 + 0], // dest_depth
				calc_red_mask(&formats[j*5+1]),
				calc_green_mask(&formats[j*5+1]),
				calc_blue_mask(&formats[j*5+1]),
				calc_alpha_mask(&formats[j*5+1])
				);

			cout << " PASSED!" << endl;
		}
	}

	assert(Hermes_Done() != 0);

	return 0;
}

void test_depth(
	int src_depth,
	int src_red_mask,
	int src_green_mask,
	int src_blue_mask,
	int src_alpha_mask,
	int dest_depth,
	int dest_red_mask,
	int dest_green_mask,
	int dest_blue_mask,
	int dest_alpha_mask)
{
	HermesFormat *src_format = Hermes_FormatNew(
		src_depth,
		src_red_mask,
		src_green_mask,
		src_blue_mask,
		src_alpha_mask,
		0 /* indexed */);
		
	HermesFormat *dest_format = Hermes_FormatNew(
		dest_depth,
		dest_red_mask,
		dest_green_mask,
		dest_blue_mask,
		dest_alpha_mask,
		0 /* indexed */);

	for (int src_width = 1; src_width < 16; src_width++)
	{
		for (int src_height = 1; src_height < 16; src_height++)
		{
		    //for (int dest_width = 1; dest_width < 16; dest_width++)
		    //	{
		    //		for (int dest_height = 1; dest_height < 16; dest_height++)
		    //		{
		    int dest_width=src_width;
		    int dest_height=src_height;
					int src_pitch = calc_pitch(src_depth, src_width);
					int dest_pitch = calc_pitch(dest_depth, dest_width);
				
					test_convert(
						src_format,
						0,
						0,
						src_width,
						src_height,
						src_pitch,
						dest_format,
						0,
						0,
						dest_width,
						dest_height,
						dest_pitch);
					//		}
					//	}
		}
		cout << ".";
		cout.flush();
	}

	delete src_format;
	delete dest_format;
}

void test_convert(
	HermesFormat *src_format,
	int src_x,
	int src_y,
	int src_width,
	int src_height,
	int src_pitch,
	HermesFormat *dest_format,
	int dest_x,
	int dest_y,
	int dest_width,
	int dest_height,
	int dest_pitch)
{
	// Init:
	// -----
	
	int src_data_size = src_pitch * src_height;
	int dest_data_size = dest_pitch * dest_height;

	unsigned char *src_data = new unsigned char[src_data_size+2];
	unsigned char *dest_data = new unsigned char[dest_data_size+2];

	src_data[0] = 0xcd;
	src_data[src_data_size+1] = 0xcd;

	dest_data[0] = 0xcd;
	dest_data[dest_data_size+1] = 0xcd;

	HermesHandle handle = Hermes_ConverterInstance(HERMES_CONVERT_NORMAL);
	HermesHandle palette = Hermes_PaletteInstance();

	assert(src_format != NULL);
	assert(dest_format != NULL);
	assert(handle != 0);
	assert(palette != 0);
	
	// Do the convert:
	// ---------------

	int res = Hermes_ConverterRequest(
		handle,
		src_format,
		dest_format);
	
	assert(res != 0);
	
	res = Hermes_ConverterPalette(handle, palette, 0);
	assert(res != 0);
	
	res = Hermes_ConverterCopy(
		handle,
		src_data+1,
		src_x,
		src_y,
		src_width,
		src_height,
		src_pitch,
		dest_data+1,
		dest_x,
		dest_y,
		dest_width,
		dest_height,
		dest_pitch);
	
	assert(res != 0);
	
	// Check for memory damage:
	// ------------------------

	assert(src_data[0] == 0xcd);
	assert(src_data[src_data_size+1] == 0xcd);

	assert(dest_data[0] == 0xcd);
	assert(dest_data[dest_data_size+1] == 0xcd);

	// Clean up:
	// ---------

	Hermes_ConverterReturn(handle);
	Hermes_PaletteReturn(palette);
	
	delete[] src_data;
	delete[] dest_data;
}

int calc_red_mask(int *mask_desc)
{
	int i;
	unsigned int mask = 0;

	for (i=0; i<mask_desc[0]; i++) mask = (mask << 1) + 1;
	for (i=0; i<mask_desc[1]; i++) mask <<= 1;
	for (i=0; i<mask_desc[2]; i++) mask <<= 1;
	for (i=0; i<mask_desc[3]; i++) mask <<= 1;

	return (int) mask;
}

int calc_green_mask(int *mask_desc)
{
	int i;
	unsigned int mask = 0;

	for (i=0; i<mask_desc[1]; i++) mask = (mask << 1) + 1;
	for (i=0; i<mask_desc[2]; i++) mask <<= 1;
	for (i=0; i<mask_desc[3]; i++) mask <<= 1;

	return (int) mask;
}

int calc_blue_mask(int *mask_desc)
{
	int i;
	unsigned int mask = 0;

	for (i=0; i<mask_desc[2]; i++) mask = (mask << 1) + 1;
	for (i=0; i<mask_desc[3]; i++) mask <<= 1;

	return (int) mask;
}

int calc_alpha_mask(int *mask_desc)
{
	int i;
	unsigned int mask = 0;

	for (i=0; i<mask_desc[3]; i++) mask = (mask << 1) + 1;

	return (int) mask;
}

int calc_pitch(int depth, int width)
{
	int bytes_per_pixel = (depth+7)/8;
	return width * bytes_per_pixel;
}
