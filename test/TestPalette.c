/* Hermes Test 
   Most of the code just c&p from a file that the Rasterman sent to me..
   But well.. It's just opening an X window :)
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XShm.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "Hermes.h"

#define WIDTH 259
#define HEIGHT 259

static XImage *xim;
static XShmSegmentInfo shminfo;
static Pixmap pmap;
static Display *disp;
static Window win;
static Visual *vis;
static int scr;
static GC gc;
static int depth;
static Colormap cmap;


void X_Setup(int w,int h)
{
  XGCValues gcvals;
  Window root;
  

  disp=XOpenDisplay(NULL);
  if (!disp)
  fprintf(stderr,"X-Error: unable to connect to display\n");

  scr=DefaultScreen(disp);
  vis=DefaultVisual(disp,scr);
  root=DefaultRootWindow(disp);
  depth=DefaultDepth(disp,scr);

  win=XCreateSimpleWindow(disp,root,0,0,w,h,0,0,0);
  gc=XCreateGC(disp,win,(unsigned long)0,&gcvals);
  XSetForeground(disp,gc,0);
  XSetBackground(disp,gc,1);

  XMapWindow(disp,win);
  cmap = DefaultColormap(disp, scr);
  XSync(disp,False);
  
  xim=XShmCreateImage(disp,vis,depth,ZPixmap,NULL,&shminfo,w,h);
  if (!xim)
  fprintf(stderr,"X-Error: unable to create XShm XImage\n");

  shminfo.shmid=shmget(IPC_PRIVATE,
		       xim->bytes_per_line*xim->height,
		       IPC_CREAT|0777);
  if (shminfo.shmid==-1)
  fprintf(stderr,"SharedMemory Error: unable to get identifier\n");

  shminfo.shmaddr=xim->data=shmat(shminfo.shmid,0,0);
  if(!XShmAttach(disp,&shminfo))
    fprintf(stderr,"X-Error: unable to attach XShm Shared Memory Segment\n");

  pmap=XShmCreatePixmap(disp,win,shminfo.shmaddr,&shminfo,w,h,depth);
  if (!pmap)
    fprintf(stderr,"Unable to create pixmap\n");

  XSetWindowBackgroundPixmap(disp,win,pmap);
}


void X_Display(void)
{
  XSync(disp, False);
  XShmPutImage(disp,win,gc,xim,0,0,0,0,xim->width,xim->height,False);
}


void paintpattern(char8 *dest) 
{ int i,j;

   // Red strip

  for (i=0;i<256;i++)
  for (j=0;j<256;j++)
  *(dest+j*259+i)=(char8)(sin((float)i*(float)j/512)*127.0+127.0);
}



void main(int argc,char *argv[]) 
{ HermesHandle conv;
  XEvent e;
  char8 *source;
  HermesFormat fmt_source,fmt_dest;
  HermesHandle palhandle;
  unsigned long timediff;
  struct timeval tv;
  float frames=0.0f;
  int i;
  
  if (!Hermes_Init()) {
    printf("Couldn't initialise Hermes!\n");
    exit(1);
  }

  conv=Hermes_ConverterInstance(HERMES_CONVERT_NORMAL);
  if (!conv) {
    printf("Could not obtain converter instance from Hermes!\n");
    exit(1);
  }
  
  X_Setup(WIDTH,HEIGHT);
  XSelectInput(disp,win,KeyPressMask); 
  

  source=(char8*)malloc(259*259*sizeof(char8*));
  if (!source) exit(2);


  fmt_source.indexed=1;
  fmt_source.bits=8;
  fmt_source.r=0x0;
  fmt_source.g=0x0;
  fmt_source.b=0x0;
  fmt_source.a=0;

  fmt_dest.indexed=0;
  fmt_dest.bits=16;
  fmt_dest.r=0xf800;
  fmt_dest.g=0x7e0;
  fmt_dest.b=0x1f;
  fmt_dest.a=0;

  palhandle=Hermes_PaletteInstance();
  for (i=0;i<256;i++) {
    int32* p=Hermes_PaletteGet(palhandle)+i;
    *p=(i<<16)|(((i>>2)+32)<<8)|(((128-i)>>1)&0xff);
  }
  
  paintpattern(source);

  gettimeofday(&tv,NULL);
  timediff=(unsigned long)tv.tv_sec*(unsigned long)1000000+
           (unsigned long)tv.tv_usec;
               
  for (;;) {

    Hermes_ConverterRequest(conv,&fmt_source,&fmt_dest);
    Hermes_ConverterPalette(conv,palhandle,0);
    Hermes_ConverterCopy(conv,source,0,0,259,259,259,
			      xim->data,0,0,WIDTH,HEIGHT,xim->bytes_per_line);

    XCheckMaskEvent(disp,KeyPressMask,&e);

    if (e.type==KeyPress)
    break;

    X_Display();
  
    frames+=1.0f;
    if (frames==3000.0) break;
  }

  gettimeofday(&tv,NULL);
  timediff=((unsigned long)tv.tv_sec*(unsigned long)1000000+
            (unsigned long)tv.tv_usec)-timediff;
              
  printf("Time elapsed: %d microseconds\n",(int)timediff);
  printf("Frames/second (including X updates!): %f\n",(1000000.0/(float)timediff)*frames);

  Hermes_ConverterReturn(conv);
  Hermes_Done();
}