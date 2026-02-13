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