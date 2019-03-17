/*
	Hermes Electric Fence tester,
	Copyright (c)1999 by Magnus Norddahl / ClanSoft.
*/

#ifndef header_test_hermes
#define header_test_hermes

extern "C"
{
	#include "Hermes.h"
	#include "H_Conv.h"
	#include "H_Pal.h"
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
	int dest_alpha_mask);

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
	int dest_pitch);

int calc_red_mask(int *mask_desc);
int calc_green_mask(int *mask_desc);
int calc_blue_mask(int *mask_desc);
int calc_alpha_mask(int *mask_desc);
int calc_pitch(int depth, int width);

// Map C++ memory allocation to efence:

void *operator new(size_t size)
{
	return malloc(size);
}

void operator delete(void *ptr)
{
	free(ptr);
}

void operator delete[](void *ptr)
{
	free(ptr);
}

#endif
