#include "Library.h"

#include <iostream>

Library::Library() {
    this->students = new Student*[MAX_COUNT];
    this->rooms = new Room*[MAX_COUNT];
    this->reservations = new Reservation*[MAX_COUNT];
    this->studentCount = 0;
    this->roomCount = 0;
    this->reservationCount = 0;
}

Library::~Library() {
    for (int i = 0; i < this->studentCount; ++i) {
        delete(this->students[i]);
    }
    delete[](this->students);
    for (int i = 0; i < this->roomCount; ++i) {
        delete(this->rooms[i]);
    }
    delete[](this->rooms);
    for (int i = 0; i < this->reservationCount; ++i) {
        delete(this->reservations[i]);
    }
    delete[](this->reservations);
}

bool Library::addStudent(const string& name, const string& number) {
    if (this->studentCount < MAX_COUNT) {
        this->students[this->studentCount] = new Student(name, number);
        ++this->studentCount;
        return true;
    } else {
        return false;
    }
}

bool Library::addRoom(const string& name, const int& capacity, const int& computers, const bool& hasWhiteboard) {
    if (this->roomCount < MAX_COUNT) {
        this->rooms[this->roomCount] = new Room(name, capacity, computers, hasWhiteboard);
        ++this->roomCount;
        return true;
    } else {
        return false;
    }
}

bool Library::getStudent(const string& name, Student **student) {
    for (int i = 0; i < this->studentCount; ++i) {
        if ((*this->students[i]).getName() == name) {
            *student = this->students[i];
            return true;
        }
    }
    return false;
}

bool Library::getRoom(const string& roomName, Room **room) {
    for (int i = 0; i < this->roomCount; ++i) {
        if ((*this->rooms[i]).getName() == roomName) {
            Room *r = this->rooms[i];
            *room = this->rooms[i];
            return true;
        }
    }
    return false;
}

bool Library::isFree(const string& room, Date& date) {
    Room *roomPtr;
    bool roomExists = getRoom(room, &roomPtr);
    if (roomExists) {
        for (int i = 0; i < reservationCount; ++i) {
            if (
                (*this->reservations[i]).getRoom().getName() == room &&
                (*this->reservations[i]).getDate().overlaps(date)
            ) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool Library::makeReservation(const string& student, const string& room, Date& date) {
    if (this->reservationCount < MAX_COUNT) {
        Student *registree;
        Room *targetRoom;
        bool studentExists = getStudent(student, &registree);
        bool roomExists = getRoom(room, &targetRoom);
        bool roomIsFree = isFree(room, date);
        if (studentExists && roomExists && roomIsFree) {
            this->reservations[this->reservationCount] = new Reservation(registree, targetRoom, date);
            ++this->reservationCount;
        } else {
            return false;
        }
    }
    return false;
}

void Library::printReservations() {
    for (int i = 0; i < this->reservationCount; ++i) {
        (*this->reservations[i]).print();
    }
}