
#include "Date.h"

Date::Date() {
    setDate(1,1,1901);
}

Date::Date(int y, int m, int d) {
    setDate(y, m, d);
}


//setters
void Date::setDay(int d) {
    int max = getMaxDay();
    if (d > max) d = max;
    if (d < 1) d = 1;
    day = d;
}

void Date::setMonth(int m) {
    if (m > 12) m = 12;
    if (m < 1) m = 1;
    month = m;
}

void Date::setYear(int y) {
    if (y < 1901) y = 1901;
    year = y;
}

void Date::setDate(int y, int m, int d) {
    setMonth(m);
    setDay(d);
    setYear(y);
}

void Date::setDate(Date& d) {
    setDate(d.day, d.month, d.year);
}


//getters
int Date::getDay() { return day; }
int Date::getMonth() { return month; }
int Date::getYear() { return year; }
const string& Date::getMonthName() { return months[month - 1]; }


//other

bool Date::lessThan(Date& d) {
    if (this->year == d.year) {
        if (this->month == d.month) {
            return this->day < d.day;
        } else {
            return this->month < d.month;
        }
    } else {
        return this->year < d.year;
    }
}

void Date::print() {
    cout << getMonthName() << " " << getDay() << ", " << getYear() < <endl;
}

int Date::getMaxDay() {
    switch (getMonth()) {
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return 28;
        default:
            return 31;
    }
}

