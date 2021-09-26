#include <iostream>
using namespace std;

int main()
{
  int x, y, z;

  x = 4;
  y = x;
  z = y + 2 * x - 3;
  
  cout << x << " "<< y <<" "<<z<<endl;
  
  if (x == y){
	cout <<"True"<<endl;
  }else{
	cout <<"False"<<endl;
  }
  
  cout << ((x==y) ? "True" : "False") <<endl;
  
  
  cout << x <<endl;
  cout << ++x <<endl;
  cout << x++ <<endl;
  cout << x <<endl;
  
  cout << 2 + 2 * 3 <<endl;
 

  return(0);
}

