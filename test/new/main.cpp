/**

	The basic idea of these tests is that for specific conversions we already know the outcome.
	This means we can convert and check if it's converted correctly.
	(we do a test and verify if the test produced the correct result by using a program, not
	 by having to manually check the gfx output)

	Example:
		ARGB8888		->		RGB565
		0x00ff0000 (red)		0xf800
		0x0000ff00 (green)		0x07e0
		0x000000ff (blue)		0x001f
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <Hermes.h>

void Test32to16()
{
	HermesHandle h=Hermes_BlitterInstance(HERMES_CONVERT_NORMAL);

	HermesFormat *f32=Hermes_FormatNew(32,0xff0000,0x00ff00,0x0000ff,0xff000000,0);
	HermesFormat *f16=Hermes_FormatNew(16,0xf800,0x7e0,0x1f,0,0);

	Hermes_BlitterRequest(h,f32,f16);


	unsigned int *mem32=(unsigned int *)malloc(10*10*4); memset(mem32,0,10*10*4);
	unsigned short *mem16=(unsigned short *)malloc(10*10*2); memset(mem16,0,10*10*2);
	int i;
	unsigned int *m;

	printf("0xff0000 -> 0xf800 ");
	m=mem32;
	for (i=0;i<10*10;i++,m++) *m=0xFF0000;
	Hermes_BlitterBlit(h,mem32,0,0,10,10,10*4,mem16,0,0,10,10,10*2);
	if (*mem16==0xf800) printf("OK\n");
	else printf("FAILED (0x%04x)\n",*mem16);

	printf("0x00ff00 -> 0x07e0 ");
	m=mem32;
	for (i=0;i<10*10;i++,m++) *m=0x00FF00;
	Hermes_BlitterBlit(h,mem32,0,0,10,10,10*4,mem16,0,0,10,10,10*2);
	if (*mem16==0x07e0) printf("OK\n");
	else printf("FAILED (0x%04x)\n",*mem16);

	printf("0x0000ff -> 0x001f ");
	m=mem32;
	for (i=0;i<10*10;i++,m++) *m=0x0000FF;
	Hermes_BlitterBlit(h,mem32,0,0,10,10,10*4,mem16,0,0,10,10,10*2);
	if (*mem16==0x001f) printf("OK\n");
	else printf("FAILED (0x%04x)\n",*mem16);


	Hermes_FormatFree(f32);
	Hermes_FormatFree(f16);

	Hermes_BlitterReturn(h);
	free(mem32);
	free(mem16);
}


int main(int argc, char* argv[])
{
	printf("Initing Hermes ");
	Hermes_Init();
	printf(" done\n");
	
	Test32to16();

	printf("DeIniting Hermes ");
	Hermes_Done();
	printf(" done\n");
	return 0;
}

