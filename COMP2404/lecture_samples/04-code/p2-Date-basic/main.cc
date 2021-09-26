#include <iostream>
using namespace std;
#include <string>

#define MAX_SIZE  3

#include "Date.h"


int main()
{
  cout << endl;

  Date d1(2020, 9, 9);
  Date d2;

  cout << endl;
  Date dArray[MAX_SIZE];

  cout << endl;
  d1.print();


  cout << endl;
  d2.print();
  d2.setDate(1901, 1, 1);
  d2.print();

  dArray[0].setDate(1922, 2, 2);
  dArray[1].setDate(1933, 3, 3);

  cout << endl;
  for (int i=0; i<MAX_SIZE; ++i)
    dArray[i].print();

  cout << endl;
  return 0;
}
