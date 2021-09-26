#include <iostream>
#include <string>
using namespace std;


class Computer
{
  public:

    Computer()
    {
      brand = "MacBook Pro";
      cpu   = "m1";
    }

    Computer(string s1, string s2)
    {
      brand = s1;
      cpu   = s2;
    }

    string getBrand() 
    {
      return brand;
    }

    void setCpu(string n) 
    {
      cpu = n;
    }

    void print()
    {
      cout<<"Computer:  "<<brand<<" with a "<<cpu<<" cpu."<<endl;
    }

  private:
	string brand;
    string cpu;

};



int main()
{
  Computer surface("Surface Pro", "i5");
  Computer mac;

  surface.print();
  mac.print();

  mac.setCpu("i5 (with virtualization)");

  cout << endl;
  surface.print();
  mac.print();

  return 0;
}
