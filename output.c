#include "project.h"
pi_framebuffer_t *fb = NULL;
void allocate_fb(void) {
    if(fb==NULL) { 
        fb=getFrameBuffer();
    }
	clearFrameBuffer(fb,BLACK);

}

void free_fb(void) { 
    if(fb) {
        clearFrameBuffer(fb,BLACK);
	sleep(1);
        freeFrameBuffer(fb);
        fb=NULL;
    }
}
int currentColor(char x, char y){
	return fb->bitmap->pixel[y][x];
}
void display_dot(char x, char y) { 
    if(fb == NULL) {
	fprintf(stderr,"Tried to draw (%d,%d) to a non-existent frame buffer!\n",x,y);
	return;
    }
    sense_fb_bitmap_t *bm=fb->bitmap;
    //clearFrameBuffer(fb,BLACK);
    fb->bitmap->pixel[y][x] = WHITE;
}
void clearFlash(char x, char y){fb->bitmap->pixel[y][x] = BLACK;}




