#include "project.h"
/* using a char as a number because it doesn't need to be large.
 * Doing it because I _can_, not because I need to */
char xPos = 7, yPos = 7;

/* Program stops when 'running' is zero */
int running=1;
int drawing = 0;
int flash = 1;
int previousColor = 0;

void interrupt_handler(int sig){
    running=0;
}
void callbackFunc(unsigned int code);
int input(void) {
	// allocating fb
    pi_joystick_t* joystick=getJoystickDevice();
    allocate_fb();
    //allocating accel 
    float threshold=1;
    pi_i2c_t* device;
    coordinate_t data;
    signal(SIGINT, interrupt_handler);
    device=geti2cDevice();
    if (device){
    int lastX=-1,lastY=-1;
    configureAccelGyro(device);
    float x=0,y=0,z=0;
    float maxx=0,maxy=0,maxz=0;
    while(running && getAccelData(device,&data)){
	float dx=data.x-x,dy=data.y-y,dz=data.z-z;
            if(dx>maxx) maxx=dx;
            if(dy>maxy) maxy=dy;
            if(dz>maxz) maxz=dz;
            if(dx*dx+dy*dy+dz*dz > threshold) {
                printf("bumped: %f %f %f\n",dx,dy,dz);
            	running = 0;	
	    }
            x=data.x; y=data.y; z=data.z;	
        pollJoystick(joystick,callbackFunc,1000);
        if(!flash && !drawing){clearFlash(lastX,lastY);}
	if(previousColor == WHITE){
			display_dot(lastX,lastY);
		}
	if(lastX!=xPos || lastY!=yPos) {
	    previousColor = currentColor(xPos,yPos);
	    lastX=xPos;
            lastY=yPos;
	}
	if(drawing){
            display_dot(xPos,yPos);
	} else {
		clearFlash(xPos,yPos);
		if(flash){display_dot(xPos,yPos); }
	    flash = (flash + 1)%2; 
	    }
    }
    fprintf(stderr,"Looks like 'running' is zero!\n");
    freei2cDevice(device);
    free_fb();
    freeJoystick(joystick);
    }
}

/* Note that the codes don't really match any orientation of the joystick */
void callbackFunc(unsigned int code) {
    fprintf(stderr,"code: %u\t",code);
    if(code == KEY_UP) {
        fprintf(stderr,"up");

        if(yPos==0) {
            yPos=7;
        }else{
            yPos--;
        }
    }else if(code == KEY_DOWN) {
        fprintf(stderr,"down");
	
        if(yPos==7) {
            yPos=0;
        }else{
            yPos++;
        }
    }else if(code == KEY_RIGHT) {
        fprintf(stderr,"left");
	
        if(xPos==7) {
            xPos=0;
        }else{
            xPos++;
        }
    }else if(code == KEY_LEFT) {
        fprintf(stderr,"right");
       
	if(xPos==0) {
            xPos=7;
        }else{
            xPos--;
        }
    }else if(code == KEY_ENTER) {
        fprintf(stderr,"push");
	drawing = (drawing + 1 )% 2;
	previousColor = WHITE;
	if(0){
        running = 0;
	}
    }
    fprintf(stderr,"\n");
}

