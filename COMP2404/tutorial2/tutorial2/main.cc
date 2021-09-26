#include "Character.h"
#include "battle.h"

int main() {
    std::string fighterName, orcName;
    int fighterHealth, orcHealth;
    int fighterDamage, orcDamage;

    std::cout << "Please enter the fighter's name, health, and damage: ";
    std::cin >> fighterName >> fighterHealth >> fighterDamage;
    Character fighter = Character(fighterName, fighterHealth, fighterDamage);

    std::cout << "Please enter the orc's name, health, and damage: ";
    std::cin >> orcName >> orcHealth >> orcDamage;
    Character orc = Character(orcName, orcHealth, orcDamage);

    fighter.print();
    orc.print();

    Gondor::fight(fighter, orc);
    fighter.print();
    orc.print();

    Mordor::fight(fighter, orc);
    fighter.print();
    orc.print();
}