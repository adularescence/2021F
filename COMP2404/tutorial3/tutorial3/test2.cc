#include <iostream>
#include <string>

#include "Date.h"

using namespace std;

int  main(){

    //first take input for two dates
    int y1, m1, d1, h1, dur1;
    int y2, m2, d2, h2, dur2;

    bool overlaps= false;

    cin>>y1>>m1>>d1>>h1>>dur1;
    cin>>y2>>m2>>d2>>h2>>dur2;
    cin>>boolalpha>>overlaps;

    Date date1(y1,m1,d1,h1,dur1);
    Date date2(y2,m2,d2,h2,dur2);

    bool o1 = date1.overlaps(date2);
    bool o2 = date2.overlaps(date1);

    date1.print();
    date2.print();

    if (o1!=o2){
        cout << "Error date1.overlaps(date2) != date2.overlaps(date1)"<<endl;
        return 1;
    }

    if(o1){
        cout<<endl<<"Dates overlap"<<endl;
    }else{
        cout<<endl<<"Dates do not overlap"<<endl;
    }

    if (o1 != overlaps){
        cout<<"Error, you have date1.overlaps(date2) ="<<boolalpha<<o1<<" and it should be "<<boolalpha<<overlaps<<endl;
        return 1;
    }

    cout<<endl<<"Successful overlap test"<<endl;

    return 0;

}