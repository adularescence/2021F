#include "Subscriber.h"

Subscriber::Subscriber(const std::string& name, const std::string& creditcard) {
    this->name = name;
    this->creditcard = creditcard;
}

bool Subscriber::matches(const std::string& name) {
    return this->name == name;
}

void Subscriber::print() {
    // don't care about security :)
    // [Subscriber] $name ($creditcard)
    //
    std::cout << "[Subscriber] " << name << " (" << creditcard << ")" << std::endl;
}