#include <iostream>
using namespace std;
#include <string>

#include "TestView.h"

void TestView::showMenu(int& choice)
{
  int numOptions = 5;

  cout << endl;
  cout << "Which test would you like to run?"<< endl;
  cout << "  (1) Test the podcast array" << endl;
  cout << "  (2) Test retrieving and playing episodes" << endl;
  cout << "  (3) Test network add/remove podcasts and subscribers and streaming" << endl;
  cout << "  (4) Test downloading and removing podcasts" << endl;
  cout << "  (5) Test client" << endl;
  cout << "  (0) Exit" << endl<<endl;

  cout << "Enter your selection: ";
  cin >> choice;
  if (choice == 0)
    return;

  while (choice < 0 || choice > numOptions) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
}




