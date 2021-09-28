
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

const int MAX_DURATION = 3;

using namespace std;

class Date {
    public:
        //constructor
        Date();
        Date(int year, int month, int day);
        
                
        //setters
        void setDay( int);
        void setMonth(int);
        void setYear(int);
        void setDate(int, int, int);
        void setDate(Date&);

        //getters
        int getDay();
        int getMonth();
        int getYear();
        const string& getMonthName();

        //other
        bool lessThan(Date& d);
        void print();

    private:
        //functions
        int getMaxDay();

        //variables
        int day;
        int month;
        int year;
        int hour;
        int duration;

        const string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        const string smonths[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul","Aug", "Sep", "Oct", "Nov", "Dec"};

};
#endif
