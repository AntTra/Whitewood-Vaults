#pragma once
#include "Car.h"
#include <string>
#include <iostream>
#include "std_lib_facilities.h"

class Person
{
public:
	Person(const std::string& name, const std::string& email, unique_ptr<Car> car = nullptr);

	// Vi ønsker ikke å tillate kopiering av Person-objekter
	Person(const Person&) = delete;
	Person& operator=(const Person&) = delete;

	std::string getEmail() const;
	std::string getName() const;

	void setEmail(const std::string& email);

	bool hasAvailableSeats() const;

	friend std::ostream& operator<<(std::ostream& os, const Person& person);

private:
	std::string name;
	std::string email;

	unique_ptr<Car> car;
};
