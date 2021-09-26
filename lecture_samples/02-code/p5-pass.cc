#include <iostream>
using namespace std;

void doubleNum(int, int&);
bool checkNum(int);

int main()
{ 
  bool inputOK = false;
  int num, result = 0;
  
  while(!inputOK){
	cout << "Please enter a number from 0 to 100"<<endl;
	cin >> num;
	inputOK =  checkNum(num);
  }
  
  doubleNum(num, result);
  
  cout <<result<<endl;

  return 0;
}

/* Parameter n is a input parameter */
/* Parameter res is a output parameter */
void doubleNum(int n, int& res)
{
  res = n * 2;
}

/* Parameter n is a input parameter */
bool checkNum(int n)
{
  return ( n >= 0 && n <= 100 );
}

