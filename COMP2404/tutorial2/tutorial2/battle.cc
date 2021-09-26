#include "battle.h"
#include <iostream>

void Gondor::fight(Character& fighter, Character& orc) {
    int fighterDamage = fighter.strike() + 1;
    int orcDamage = orc.strike() - 1;

    fighter.takeDamage(orcDamage);
    orc.takeDamage(fighterDamage);

    std::cout << fighter.getName() << " hits " << orc.getName() << " for " << fighterDamage << " damage!" << std::endl;
    std::cout << orc.getName() << " hits " << fighter.getName() << " for " << orcDamage << " damage!" << std::endl;
}

void Mordor::fight(Character& fighter, Character& orc) {
    int fighterDamage = fighter.strike() - 1;
    int orcDamage = orc.strike() + 1;

    orc.takeDamage(fighterDamage);
    fighter.takeDamage(orcDamage);

    std::cout << orc.getName() << " hits " << fighter.getName() << " for " << orcDamage << " damage!" << std::endl;
    std::cout << fighter.getName() << " hits " << orc.getName() << " for " << fighterDamage << " damage!" << std::endl;
}