#ifndef LIBRARY_H
#define LIBRARY_H

#include "Student.h"
#include "Room.h"
#include "Reservation.h"

class Library {
    public:
        Library();
        ~Library();

        bool addStudent(const string& name, const string& number);
        bool addRoom(const string& name, const int& capacity = 1, const int& computers = 0, const bool& hasWhiteboard = false);
        bool getStudent(const string& name, Student **student);
        bool getRoom(const string& roomName, Room **room);
        bool isFree(const string& room, Date& date);
        bool makeReservation(const string& student, const string& room, Date& date);

        void printReservations();

    private:
        Student **students;
        Room **rooms;
        Reservation **reservations;
        int studentCount, roomCount, reservationCount;

        const int MAX_COUNT = 100;
};

#endif