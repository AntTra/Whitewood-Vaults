#pragma once

class Car
{
	int freeSeats = 0;

public:
	Car(int freeSeats);

	bool hasFreeSeats() const;
	void reserveFreeSeat();
};
