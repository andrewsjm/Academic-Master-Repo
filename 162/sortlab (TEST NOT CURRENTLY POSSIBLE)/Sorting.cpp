#include <iostream>
#include <fstream>
//#include <stdlib.h>
//#include <algorithm> 
#include <string.h>
#include "tools.h"
using namespace std;


int main(int argc, char* argv[])
{
        //the program should be run with 3 arguments, file name, input file and code for sorting number
        if (argc < 3) {
                cout << "Syntax: ./Sort <testX.input> int_code" << endl;
                return 1;
        }

        //Read input filename from command line
        string input_file = argv[1];

        //Check that it ends with .input
        size_t pos = input_file.find(".input");
        if (pos != input_file.size() - 6) {
        cout << "Syntax: ./Sort <testX.input> int_code" << endl;
                return 1;
        }
        int int_code = stoi(argv[2]);
        if(int_code<0 || int_code>3)
          {
            cout<<"int_code should be 0 or 1 or 2."<<endl;
            return 1;
          }
        //If it does, replace .input with .data in the output name
        
        string output_file = input_file.substr(0, input_file.size()-6) + ".data";
        //Create a Sorter and read all the data from the input file
        //Sort the data
        //Then write the data to the output file
        
        int *data_array;//dynamic array to store my data
        int data_size; //size of the data
        read(data_array,&data_size,input_file);//read the input_file and load data
        //Check the array contents in screen if needed
        /*
        for(int i=0;i<data_size;i++)
                  cout<<data_array[i]<<"\t";
        cout<<endl;
        */
        if(int_code==0){
          insertionSort(data_array,data_size);
        }
        else if(int_code==1){
        
          //    Implement qsort here (should be one function call only)
        int cmpfunc (const void* a, const void* b);}
        else if(int_code==2){
//      Implement sort function here(should be one function call only)
        insertionSort(data_array, data_size);
          
          write(data_array,data_size,output_file);
        }
}
