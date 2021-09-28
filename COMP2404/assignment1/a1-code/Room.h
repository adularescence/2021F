#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room {
    public:
        Room(std::string name, int capacity, int computers, bool whiteboard);
        Room(const Room& room);

        std::string getName() const;
        int getCapacity() const;
        int getComputers() const;
        bool hasWhiteboard() const;
        void setName(std::string name);
        void setCapacity(int capacity);
        void setComputers(int computers);
        void setWhiteboard(bool whiteboard);

        bool meetsCriteria(int capacity, int computers = 0, bool whiteboard = false);
        bool lessThan(Room& room);

    private:
        std::string name;
        int capacity;
        int computers;
        bool whiteboard;
};

#endif