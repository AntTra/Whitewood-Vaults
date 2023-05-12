#pragma once

#include "Person.h"

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "std_lib_facilities.h"

enum class Campus { trh, aal, gjo };

const std::unordered_map<Campus, std::string> campusToString {
	{ Campus::trh, "Trondheim" },
	{ Campus::aal, "Aalesund" },
	{ Campus::gjo, "Gjovik"}
};

const std::unordered_map<std::string, Campus> stringToCampus {
	{ "Trondheim", Campus::trh },
	{ "Aalesund", Campus::aal },
	{ "Gjovik", Campus::gjo }
};

std::ostream& operator<<(std::ostream& os, Campus c);

class Meeting
{
public:
	// Vi ønsker ikke å tillate kopiering av Meeting-objekter
	Meeting(const Meeting&) = delete;
	Meeting& operator=(const Meeting&) = delete;

	Meeting(int day, int startTime, int endTime, Campus location, const std::string& subject, const shared_ptr<Person> leader);

	int getDay() const { return day; }
	int getStartTime() const { return startTime; }
	int getEndTime() const { return endTime; }
	Campus getLocation() const { return location; }
	std::string getSubject() const { return subject; }
	const shared_ptr<Person> getLeader() const { return leader; }

	void addParticipant(shared_ptr<Person> person);
	std::vector<std::string> getParticipantList() const;

	std::vector<shared_ptr<Person>> findPotentialCoDriving(const Meeting &otherMeeting) const;

private:
	int day;
	int startTime;
	int endTime;
	Campus location;
	std::string subject;
	const shared_ptr<Person> leader;
	std::vector<shared_ptr<Person>> participants;
};

std::ostream& operator<<(std::ostream& os, const Meeting& m);
