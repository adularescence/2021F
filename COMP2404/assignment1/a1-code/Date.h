
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

using namespace std;

class Date {
    public:
        //constructors
        Date();
        Date(int year, int month, int day, int hour, int duration);
        Date(const Date& date);

        //setters
        void setYear(int year);
        void setMonth(int month);
        void setDay(int day);
        void setHour(int hour);
        void setDuration(int duration);
        void setDate(int year, int month, int day, int hour, int duration);
        void setDate(Date& date);

        //getters
        int getYear() const;
        int getMonth() const;
        int getDay() const;
        int getHour() const;
        int getDuration() const;
        const string& getMonthName();

        //other
        bool lessThan(Date& date);
        bool overlaps(Date& date);
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
        const int MAX_DURATION = 3;
};
#endif
