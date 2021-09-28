#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
    public:
        Student();
        Student(std::string name, std::string number);
        Student(const Student& s);

        std::string getName() const;
        std::string getNumber() const;
        void setName(std::string name);
        void setNumber(std::string number);

        bool lessThan(Student& s);

    private:
        std::string name;
        std::string number;
};

#endif