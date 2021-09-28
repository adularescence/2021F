#include "Student.h"

#include <iostream>

// constructors

Student::Student() {
    setName("Johnny Appleseed");
    setNumber("100000001");
}

Student::Student(std::string name, std::string number) {
    setName(name);
    setNumber(number);
}

Student::Student(const Student& student) {
    setName(student.getName());
    setNumber(student.getNumber());
}


// get, set

std::string Student::getName() const {
    return this->name;
}

std::string Student::getNumber() const {
    return this->number;
}

void Student::setName(std::string name) {
    this->name = name;
}

void Student::setNumber(std::string number) {
    this->number = number;
}


// other functions

bool Student::lessThan(Student& student) {
    std::string thatNumber = student.getNumber();
    for (int i = 0; i <= this->number.length(); ++i) {
        if (this->number[i] == thatNumber[i]) {
            continue;
        } else {
            return this->number[i] < thatNumber[i];
        }
    }
    return thatNumber.length() <= this->number.length();
}

void Student::print() {
    // [Student] $name ($number)
    std::cout << "[Student] " << getName() << " (" << getNumber() << ")" << std::endl;
}