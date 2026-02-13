#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#define INPBUF 1024
//error counter?
char dname[25];
int divnum = 0;
int divide(int divnum)
{
  if (divnum %2 == 0)
  {
    divnum = divnum/2;
    return divnum;
  }
  else
  {
    printf("odd number found invalid input");
    return 0;
  }
  //end of divide 
}
int main()
{
  printf("Please type Folder/Directory name here: ");
  scanf("%s", dname);
  //takes directory name

  int file_pid = fork();
  char inf[28];
  char enf[32];
  if (file_pid < 0)
  {
    perror("fork");
  }
  if (file_pid > 0)
  {
    //use directory name for pointer
    DIR *fldr_ptr = opendir(dname);
    if (fldr_ptr == NULL) {
      //PLACEHOLDER FOR ERROR STAT CALL !!!!!!!!!!!!!!!!!!!!!
      printf("invalid or empty directory");
      exit(1);
    }
    struct dirent *dirent_point;
    while ((dirent_point = readdir(fldr_ptr)) != NULL)
    {
      printf("%s\n", dirent_point->d_name);
      if (strcmp(dirent_point->d_name + strlen(dirent_point->d_name) -3, ".in") == 0)
      {
        printf("%s\n", ".in file found!!");
        strcpy(inf, dirent_point->d_name);
        //end of in finder
      }
      if (strcmp(dirent_point->d_name + strlen(dirent_point->d_name) -7, ".expect") == 0)
      {
        printf("%s\n", ".expect file found!!");
        strcpy(enf, dirent_point->d_name);
        //end of expect finder
      }
      //end of while loop
    }
    FILE *infile = fopen(inf, "r");
    if (infile == NULL)
    {
      //PLACEHOLDER FOR EMPTY INFILE ERROR FOR STAT CALL!!!!!!!!!!!
      perror("fopen");
      exit(EXIT_FAILURE);
    }
    else
    {
      int i = 0;
      int inv[100];
      int x = 0;
      while(fscanf(infile, "%d", &x) != EOF)
      {
        //sleep(2);
        x = divide(x);
        inv[i] = x;
        printf("%s %d\n","In value: ", inv[i]);
        //printf("%d\n", inv[i]);
        ++i;
      }
      //exit(1);
      FILE *exfile = fopen(enf, "r");
      if (exfile == NULL)
      {
        printf("%s\n", "empty expect file");
        perror("fopen");
        exit(EXIT_FAILURE);
      }
      else
      {
        int j = 0;
        int exv[100];
        int e = 0;
        while(fscanf(exfile, "%d", &e) != EOF)
        {
          //sleep(2);
          exv[j] = e;
          printf("%s\n", "expected value: ");
          printf("%d\n", exv[j]);
          ++j;
        } 
        printf("%d\n", j);
        printf("%d\n", i);
        fclose(exfile);
        for(int r = j ; r > 0; r = r - 1)
        {
          //printf("%s %d\n", "r equals :", r);
          //printf("%d\n",exv[r-1]);
          //printf("%d\n",inv[r-1]);
          if(exv[r-1] == inv[r-1])
          {
            sleep(3);
            printf("%s %d\n", "values group number: ", r);
            printf("%d",inv[r-1]);
            printf("%s", " equals ");
            printf("%d\n",exv[r-1]);
            //printf("%c %d\n", exv[r-1], "=", inv[r-1]);
          }
          else if (exv[r-1] != inv[r-1])
          {
            printf("%s\n", "not equal");
            //printf("%s %d\n", exv[r-1], "!= ", inv[r-1]);
          }  
          //for r loop end
        }
        //expect loop end
        //else end
      }
      fclose(infile);
      closedir(fldr_ptr);
      //end of infile else
    }
      sleep(30);
      exit(EXIT_SUCCESS);
  }
  //user input
int user_pid = fork();
  if (user_pid == 0) {
    int k = 1;
    int y;
    int j = 0;
    int counter = 0;
    printf("Insert a positive integer here, or 0 to exit.\n");
    fflush(stdout);
    while (scanf("%d", &y) == 1) {
        getchar();
        if (y == 0) {
            printf("%s\n", "Zero input, exiting.");
            sleep(2);
            exit(EXIT_SUCCESS);
        }
        else if (y % 2 == 1) {
            printf("%s\n", "Even numbers only please try again. (you only get three wrong tries)");
            sleep(2);
            j++;
            if (j == 3) {
                exit(1);
            }
        }
        else if (y % 2 == 0) {
            printf("%d\n", divide(y));
        }
        counter++;
        if (counter == 100) {
            printf("%s\n", "Reached 100 inputs so exiting.");
            exit(EXIT_SUCCESS);
        }
        printf("Insert a positive integer here, or 0 to exit.\n");
        fflush(stdout);
    }
}
}