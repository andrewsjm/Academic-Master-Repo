#include <iostream>
#include <fstream>
using namespace std;
void read(int *&m_data,int *m_size,const string filename);
void write(int *m_data, int m_size,const string filename);
void insertionSort(int theArray[], int n)
    {
       for (int unsorted = 1; unsorted < n; unsorted++)
          {
                int nextItem = theArray[unsorted];
                int loc = unsorted;
                 while ((loc > 0) && (theArray[loc - 1] > nextItem))
                       {
                           // Shift theArray[loc - 1] to the right
                             theArray[loc] = theArray[loc - 1];
                              loc--;
                         }  // end while
                         
                          // At this point, theArray[loc] is where nextItem belongs
                          theArray[loc] = nextItem; // Insert nextItem into sorted region
          }  // end for
    }  // end insertionSort

//m_data is pointer passed as reference to update the values in data_array
void read(int *&m_data,int *m_size,const string filename)
{
  
        ifstream fin(filename);
        fin >> *m_size;
        m_data = new int[*m_size];
        for (int i=0; i < *m_size; ++i) {
                fin >> m_data[i];
        
                                                                }
}

void write(int *m_data, int m_size,const string filename)
{
  ofstream fout(filename);
  for (int i=0; i < m_size-1; ++i)
        {
        fout << m_data[i] << " ";
        }
        if (m_size > 0) {
                fout << m_data[m_size-1] << endl;
        }
}
//compare functin for integer comparison
int cmpfunc (const void * a, const void * b) 
{
     return ( *(int*)a - *(int*)b );
}
