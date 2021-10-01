#include <iostream>
#include <string>

#include "Room.h"

using namespace std;

int  main(){

    string name = "TestRoom";
    int capacity, cap, computers, comp;
    bool whiteboard, wb, matches;

    cin >>capacity>>cap>>computers>>comp;
    cin >>boolalpha>>whiteboard>>boolalpha>>wb;
    cin >>boolalpha>>matches;

    Room r1(name, capacity, computers, whiteboard);

    bool out = r1.meetsCriteria(cap,comp,wb);

    r1.print();

     if (out != matches){
        cout<<"Error, you have meetsCriteria ="<<boolalpha<<out<<" and it should be "<<boolalpha<<matches<<endl;
        return 1;
    }

    cout<<endl<<"meetsCriteria test successful"<<endl;
    
    return 0;
}