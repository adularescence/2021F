#ifndef RESERVATION_H
#define RESERVATION_H

#include "Student.h"
#include "Room.h"
#include "Date.h"

class Reservation {
    public:
        Reservation(Student *student, Room *room, Date& date);
        ~Reservation();

        Student getStudent() const;
        Room getRoom() const;
        Date& getDate() const;

        bool lessThan(Reservation& reservation);
        bool overlaps(std::string roomName, Reservation& reservation);
        void print();

    private:
        Student *student;
        Room *room;
        Date *date;
};

#endif