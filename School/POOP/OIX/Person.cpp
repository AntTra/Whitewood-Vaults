#include "Person.h"

Person::Person(const std::string& name, const std::string& email, unique_ptr<Car> car)
    : name(name), email(email), car(std::move(car))
{}

std::string Person::getEmail() const {
    return email;
}

std::string Person::getName() const {
    return name;
}

void Person::setEmail(const std::string& email) {
    // Her brukes this for å skille mellom klassens email og variabelen som tas
    // inn i funksjonen. Du kan lese mer om this-pekeren i kapittel 17.10 i PPP.
    this->email = email;
}

bool Person::hasAvailableSeats() const {
    if (car != nullptr) {
        return car->hasFreeSeats();
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Person& p) {
	return os << p.name << " (" << p.email << ")";
}
