#include "Library.h"

Library::Library() {
    this->students = new Student::Student*[MAX_COUNT];
    this->rooms = new Room::Room*[MAX_COUNT];
    this->reservations = new Reservation::Reservation*[MAX_COUNT];
    studentCount = roomCount = reservationCount = 0;
}

Library::~Library() {
    delete[] students;
    delete[] rooms;
    delete[] reservations;
}

bool Library::addStudent(const string& name, const string& number) {
    if (studentCount < MAX_COUNT) {
        this->students[studentCount++] = new Student(name, number);
        return true;
    } else {
        return false;
    }
}

bool Library::addRoom(const string& name, const int& capacity = 1, const int& computers = 0, const bool& hasWhiteboard = false) {
    if (roomCount < MAX_COUNT) {
        this->rooms[roomCount++] = new Room(name, capacity, computers, hasWhiteboard);
        return true;
    } else {
        return false;
    }
}

bool Library::getStudent(const string& name, Student::Student **student) {
    for (int i = 0; i < studentCount; ++i) {
        if ((*this->students[i]).getName() == name) {
            student = &students[i];
            return true;
        }
    }
    return false;
}

bool Library::getRoom(const string& roomName, Room::Room **room) {
    for (int i = 0; i < roomCount; ++i) {
        if ((*this->rooms[i]).getName() == roomName) {
            room = &rooms[i];
            return true;
        }
    }
    return false;
}

bool Library::isFree(const string& room, Date& date) {
    bool roomExists = getRoom(room, NULL);
    if (roomExists) {
        for (int i = 0; i < reservationCount; ++i) {
            if ((*this->reservations[i]).getDate().overlaps(date)) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool Library::makeReservation(const string& student, const string& room, Date& date) {
    if (reservationCount < MAX_COUNT) {
        Student::Student **registree = NULL;
        Room::Room **targetRoom = NULL;
        bool studentExists = getStudent(student, registree);
        bool roomExists = getRoom(room, targetRoom);
        bool roomIsFree = isFree(room, date);
        if (studentExists && roomExists && roomIsFree) {
            this->reservations[reservationCount++] = new Reservation(*registree, *targetRoom, date);
        } else {
            return false;
        }
    } else {
        return false;
    }
}