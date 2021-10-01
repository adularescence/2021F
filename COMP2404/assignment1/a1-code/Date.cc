
#include "Date.h"


// constructors

Date::Date() {
    setDate(1, 1, 1901, 0, 1);
}

Date::Date(int year, int month, int day, int hour, int duration) {
    setDate(year, month, day, hour, duration);
}

Date::Date(const Date& date) {
    setDate(
        date.getYear(),
        date.getMonth(),
        date.getDay(),
        date.getHour(),
        date.getDuration()
    );
}


//setters

void Date::setYear(int year) {
    if (year < 1901) year = 1901;
    this->year = year;
}

void Date::setMonth(int month) {
    if (month > 12) month = 12;
    if (month < 1) month = 1;
    this->month = month;
}

void Date::setDay(int day) {
    int max = getMaxDay();
    if (day > max) day = max;
    if (day < 1) day = 1;
    this->day = day;
}
 
void Date::setHour(int hour) {
    if (hour > 23) hour = 23;
    if (hour < 0) hour = 0;
    this->hour = hour;
}

void Date::setDuration(int duration) {
    if (duration > MAX_DURATION) duration = MAX_DURATION;
    if (duration < 0) duration = 0;
    this->duration = duration;
}

void Date::setDate(int year, int month, int day, int hour, int duration) {
    setYear(year);
    setMonth(month);
    setDay(day);
    setHour(hour);
    setDuration(duration);
}

void Date::setDate(Date& date) {
    setDate(
        date.getDay(),
        date.getMonth(),
        date.getYear(),
        date.getHour(),
        date.getDuration()
    );
}


//getters
int Date::getDay() const { return this->day; }
int Date::getMonth() const { return this->month; }
int Date::getYear()const { return this->year; }
int Date::getHour() const { return this->hour; }
int Date::getDuration() const { return this->duration; }
const string& Date::getMonthName() { return months[month - 1]; }


//other

bool Date::lessThan(Date& date) {
    if (this->year == date.getYear()) {
        if (this->month == date.getMonth()) {
            if (this->day == date.getDay()) {
                return this->hour < date.getHour();
            } else {
                return this->day < date.getDay();
            }
        } else {
            return this->month < date.getMonth();
        }
    } else {
        return this->year < date.getYear();
    }
}

bool Date::overlaps(Date& date) {
    bool sameDay =
        (this->year == date.getYear()) &&
        (this->month == date.getMonth()) &&
        (this->day == date.getDay());
    if (!sameDay) {
        return false;
    } else {
        int diff = this->hour - date.getHour();
        if (diff < 0) {
            // need to know if this->duration is longer than the diff
            return getDuration() > std::abs(diff);
        } else {
            // need to know that->duration is longer than the diff
            return date.getDuration() > diff;
        }
    }
}


void Date::print() {
    // [Date] September 28, 2021 (For 3 hours starting from 16h)
    cout <<
        "[Date] " <<
        getMonthName() << " " << getDay() << ", " << getYear() <<
        " (For " << getDuration() << " hours starting from " << getHour() << "h)" << endl;
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

