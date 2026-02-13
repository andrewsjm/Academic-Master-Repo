#include "glitter.h"
#include <stdio.h>
#include <unistd.h>

void glitter_reset() {
    GlitterState defaultState = {kWhite, kBlack, kBold};//get back to default
    glitter_setState(defaultState); //set to default state
    printf("\033[H"); //move cursor             //fix!!!
    fflush(stdout); //flush
}

void glitter_setState(GlitterState state) {
    //set fore color
    printf("\033[38;5;%dm", state.foreColor);
    
    //set back color
    printf("\033[48;5;%dm", state.backColor);
    
    //set font
    if (state.font == kUnderline) {
        printf("\033[4m");  //underline
    } else if (state.font == kBold) {
        printf("\033[1m");  //bold
    } else if (state.font == kItalic) {
        printf("\033[3m");  //italic
    } else if (state.font == kFaint) {
        printf("\033[2m");  //faint
    }
    
    fflush(stdout); //flush to apply changes without newline
}



void glitter_drawProgress(GlitterProgress* bar) {
    // Ensure percent is within the valid range [0, 1]
    if (bar->percent < 0.0) {
        bar->percent = 0.0;
    } else if (bar->percent > 1.0) {
        bar->percent = 1.0;
    }

    // Calculate the number of filled characters in the progress bar
    int filledChars = (int)(bar->percent * bar->width);

    // Print the progress bar characters
    printf("\r"); // Move cursor to the beginning of the line
    for (int i = 0; i < bar->width; ++i) {
        if (i < filledChars) {
            printf("="); // Filled character
        } else {
            printf("-"); // Empty character
        }
    }

    // Print the percentage at the end
    printf(" %.1f%%", bar->percent * 100.0);

    // Flush the output to ensure immediate display
    fflush(stdout);
}


void glitter_setCursorPosition(int x, int y) {
  // Ensure valid coordinates (start from 1)
  if (x < 1 || y < 1) {
    return; // Handle invalid input
  }

  // Move cursor to specified position
  printf("\033[%d;%dH", y, x);
  fflush(stdout);
}

void glitter_getCursorPosition(int* x, int* y) {
    printf("\033[6n");

    scanf("\033[%d;%dR", y, x);
}
/*int main() {
    glitter_reset();
    GlitterState testState = {kRed, kGreen, kBold};
    glitter_setState(testState);
    GlitterProgress bar;
    bar.percent = 0.0; // Start from 0%
    bar.width = 50;    // Width of the progress bar

    for (int i = 0; i <= 100; ++i) { // Loop from 0% to 100%
        bar.percent = i / 100.0;     // Update percentage
        glitter_drawProgress(&bar);   // Draw progress bar
        usleep(100000);               // Short delay for visualization
    }

    return 0;
}*/
[andrewsjm@amdahl lab1]$ cat glitter.h
#ifndef GLITTER_H
#define GLITTER_H
/*Fix this header file and implement the functions in a file named glitter.c
  you will submit the files (in a directory) using the handin script
  handin cmsc242 lab1 name_of_your_directory_here
 */

/*
   Create an enumerated type GlitterColor
   with values kBlack, kRed, kGreen, kYellow, kBlue, kMagenta, kCyan, kWhite 
 */
typedef enum{
  kBlack, kRed, kGreen, kYellow, kBlue, kMagenta, kCyan, kWhite
} GlitterColor;
/*Create an enumerated type GlitterFont
  with values kUnderline, kBold, kItalic, kFaint
 */
typedef enum {
kUnderline, kBold, kItalic, kFaint
} GlitterFont;



typedef struct {
    GlitterColor foreColor;
    GlitterColor backColor;
    GlitterFont font;
} GlitterState;

typedef struct{
double percent;
int width;
} GlitterProgress;

//Reset the attributes
void glitter_reset();    //USE FLUSH NOT NEWLINE
//Should change the current attributes but not print out new lines hint:flush
//The attributes you are changing are the font, foreground color and background color
void glitter_setState(GlitterState state);


//Draws an inline progress bar of length bar.width
//===------- 02.7%
//width is 10 here and percent in 0.027
//values under 0 should be changed to 0 and over 1 should change to 1
//at the end of the bar should be the percent in xx.x format
//You may make your bar look as you wish... but should be width characters wide
//you may change the attributes as well
void glitter_drawProgress(GlitterProgress* bar);  //can be progress of whatever i want, probably some dumb recursion that changes the values of each value in an array
/*Example usage:
  GlitterState state;
  ...
  GlitterProgress bar;
  bar.percent = 0.0;
  bar.width = 20;
  for(int i = 0; i < 30; ++i){
  glitter_drawProgess(&bar);
  bar.percent += 0.05;
  sleep(1);
  }
  glitter_reset();
  glitter_setState(state);
 */

//Set the current cursor position
void glitter_setCursorPosition(int x, int y);
//Get the current cursor position
void glitter_getCursorPosition(int* x, int* y);
#endif