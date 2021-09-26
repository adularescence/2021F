#include <iostream>
using namespace std;

int x = 10;

int main()
{
  cout << endl;
  cout<<"in main():  "<< x << endl;

  int x = 20;
  cout<<"in main():  "<< x << endl << endl;

  if (true) {
    x = 30;
    cout<<"in if:  "<< x << endl << endl;
  }

  {
    int x = 40;
    cout<<"in floating block, local:   "<< x << endl;
    cout<<"in floating block, global:  "<< ::x << endl << endl;
  }

  cout<<"in main(), local:   "<< x << endl;
  cout<<"in main(), global:  "<< ::x << endl << endl;

  ::x = 60;
  cout<<"in main(), local:   "<< x << endl;
  cout<<"in main(), global:  "<< ::x << endl << endl;

  return 0;
}

