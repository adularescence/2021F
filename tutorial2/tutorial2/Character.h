#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>

class Character {
    private:
        std::string m_name;
        int m_maxHealth;
        int m_currentHealth;
        int m_damage;

    public:
        Character(std::string& name, int maxHeatlh, int damage);

        std::string getName() { return m_name; }

        void takeDamage(int damage);
        int strike();
        void print();
};

#endif