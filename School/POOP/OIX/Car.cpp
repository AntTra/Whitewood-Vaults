#include "Car.h"

#include <cassert>

Car::Car(int freeSeats) : freeSeats(freeSeats) {}

bool Car::hasFreeSeats() const
{
	return freeSeats > 0;
}

void Car::reserveFreeSeat()
{
	// Vi antar at denne funksjonen kun kalles når det er et ledig sete.
	assert(hasFreeSeats());
	--freeSeats;
}
