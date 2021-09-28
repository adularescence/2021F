#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
    public:
        Student();
        Student(std::string name, std::string number);
        Student(const Student& s);

        void setName(std::string name);
        void setNumber(std::string number);

        std::string& getName();
        std::string& getNumber();
        std::string getName() const;
        std::string getNumber() const;

        bool lessThan(Student& s);

    private:
        std::string name;
        std::string number;
};

#endif