#include "Room.h"


// constructors

Room::Room(std::string name, int capacity, int computers, bool whiteboard) {
    setName(name);
    setCapacity(capacity);
    setComputers(computers);
    setWhiteboard(whiteboard);
}

Room::Room(const Room& r) {
    setName(r.getName());
    setCapacity(r.getCapacity());
    setComputers(r.getComputers());
    setWhiteboard(r.hasWhiteboard());
}


// get, set

std::string Room::getName() const {
    return this->name;
}

int Room::getCapacity() const {
    return this->capacity;
}

int Room::getComputers() const {
    return this->computers;
}

bool Room::hasWhiteboard() const {
    return this->whiteboard;
}

void Room::setName(std::string name) {
    this->name = name;
}

void Room::setCapacity(int capacity) {
    this->capacity = capacity;
}

void Room::setComputers(int computers) {
    this->computers = computers;
}

void Room::setWhiteboard(bool whiteboard) {
    this->whiteboard = whiteboard;
}


// other functions

bool Room::meetsCriteria(int capacity, int computers, bool whiteboard) {
    return (
        (this->capacity >= capacity) &&
        (this->computers >= computers) &&
        (this->whiteboard >= whiteboard)
    );
}

bool Room::lessThan(Room& r) {
    std::string thatName = r.getName();
    for (int i = 0; i <= this->name.length(); ++i) {
        if (this->name[i] == thatName[i]) {
            continue;
        } else {
            return this->name[i] < thatName[i];
        }
    }
    return thatName.length() >= this->name.length();
}
