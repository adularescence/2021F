#include <iostream>
using namespace std;
#include <string>

/*
Tracking employees of a video game store
*/

string manager = "Jesse James";

namespace
{
  string cashier = "William H. Bonney";
  string stock = "Pat Garrett";
  string accounting = "Dave Rudabaugh";
}

namespace Orleans
{
  string manager = "Wyatt Earp";
  string cashier   = "Doc Holiday"; 
  string stock    = "Virgil Earp";

  void printEmployees();

  namespace DemoBooth
  {
    enum Consoles { XBOX=101, SWITCH, PLAYSTATION };
  }
}




int main()
{
  cout<<endl<<"Cashier from unnamed space:  "<< cashier <<endl<<endl;

  cout<<"Original manager:  "<< manager <<endl<<endl;

  cout<<"From namespace Orleans:"<<endl;
  cout<<"  Manager:      "<< Orleans::manager <<endl;
  cout<<"  Cashier:      "<< Orleans::cashier   <<endl;
  cout<<"  Stock:        "<< Orleans::stock    <<endl;
  cout<<"  XBox:         "<< Orleans::DemoBooth::XBOX   <<endl;
  cout<<"  Switch:       "<< Orleans::DemoBooth::SWITCH      <<endl;
  cout<<"  Playstation:  "<< Orleans::DemoBooth::PLAYSTATION <<endl;

  Orleans::printEmployees();

  return 0;
}

void Orleans::printEmployees()
{
  cout<<endl<<"Printing employees:"<<endl;
  cout<<"  Manager:      "<< manager <<endl;
  cout<<"  Cashier:      "<< cashier   <<endl;
  cout<<"  Stock:        "<< stock    <<endl;
  cout<<"  Playstation:  "<< DemoBooth::PLAYSTATION <<endl;
  cout<<"  Accounting:   "<< accounting  <<endl;

  cout<<"  Old Manager: "<< ::manager  <<endl;
  cout<<"  Old Cashier: "<< ::cashier  <<endl;
  cout<<"  Old Stock:   "<< ::stock  <<endl<<endl;

}
