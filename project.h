#include "sense.h"
#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stddef.h>
#include <linux/input.h>
#include <stdio.h>
#define WHITE 0xFFFF
#define BLACK 0x0000
void allocate_fb(void);
void free_fb(void);
void display_dot(char x, char y);
int currentColor(char x, char y);
void clearFlash(char x, char y);
void clearScreen();
void interrupt_handler(int sig);
void callbackFunc(unsigned int code);
int input(void);
