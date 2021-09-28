#include "Student.h"

Student::Student() {
    setName("Johnny Appleseed");
    setNumber("100000001");
}

Student::Student(std::string name, std::string number) {
    setName(name);
    setNumber(number);
}

Student::Student(const Student& s) {
    setName(s.getName());
    setNumber(s.getNumber());
}

void Student::setName(std::string name) {
    this->name = name;
}

void Student::setNumber(std::string number) {
    this->number = number;
}

std::string& Student::getName() {
    return this->name;
}

std::string& Student::getNumber() {
    return this->number;
}

std::string Student::getName() const {
    return this->name;
}

std::string Student::getNumber() const {
    return this->number;
}

bool Student::lessThan(Student& s) {
    std::string thatNumber = s.getNumber();
    for (int i = 0; i <= this->number.length(); ++i) {
        if (this->number[i] == thatNumber[i]) {
            continue;
        } else {
            return this->number[i] < thatNumber[i];
        }
    }
}