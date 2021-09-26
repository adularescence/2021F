#include "Character.h"

Character::Character(std::string& name, int maxHealth, int damage) {
    m_name = name;
    m_maxHealth = maxHealth;
    m_currentHealth = maxHealth;
    m_damage = damage;
}

void Character::takeDamage(int damage) {
    m_currentHealth -= damage;
    if (m_currentHealth < 0) {
        m_currentHealth = 0;
    }
}

int Character::strike() {
    return m_damage;
}

void Character::print() {
    std::cout << m_name << " (" << m_currentHealth << ")" << std::endl;
}