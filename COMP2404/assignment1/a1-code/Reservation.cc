#include "Reservation.h"

#include <iostream>
#include <string>

// constructor

Reservation::Reservation(Student *student, Room *room, Date& date) {
    this->student = student;
    this->room = room;
    this->date = &date;
}

Reservation::~Reservation() {
    // not necessary to do anything
    // because the pointers are accessible and still used elsewhere (Library)
}


// get

Student Reservation::getStudent() const { return *(this->student); }
Room Reservation::getRoom() const { return *(this->room); }
Date& Reservation::getDate() const { return *(this->date); }


// other

bool Reservation::lessThan(Reservation& reservation) {
    return getDate().lessThan(reservation.getDate());
}

bool Reservation::overlaps(std::string name, Reservation& reservation) {
    return (
        (name == getRoom().getName()) &&
        (getDate().overlaps(reservation.getDate()))
    );
}

void Reservation::print() {
    // [Reservation]
    //     [Student] $name ($number)
    //     [Room] $name ($capacity, $computers, $hasWhiteboard)
    //     [Date] $monthName $day, $year (For $duration hours starting from ${hour}h)
    std::cout << "[Reservation]" << std::endl << "    ";
    getStudent().print();
    std::cout << "    ";
    getRoom().print();
    std::cout << "    ";
    getDate().print();
}