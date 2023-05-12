#include "Meeting.h"

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

std::ostream& operator<<(std::ostream& os, Campus c)
{
	return os << campusToString.at(c);
}

Meeting::Meeting(int day, int startTime, int endTime, Campus location, const std::string& subject, shared_ptr<Person> leader)
	: day{day},
	  startTime{startTime},
	  endTime{endTime},
	  location{location},
	  subject{subject},
	  leader{leader}
{
	addParticipant(leader);
}

void Meeting::addParticipant(shared_ptr<Person> person)
{
	participants.push_back(person);
}

std::vector<std::string> Meeting::getParticipantList() const
{
	std::vector<std::string> participantList;
	for (auto p : participants) {
		participantList.push_back(p->getName());
	}

	return participantList;
}

std::vector<shared_ptr<Person>> Meeting::findPotentialCoDriving(const Meeting &otherMeeting) const
{
	std::vector<shared_ptr<Person>> potentialDrivers;
	if (otherMeeting.location == location && otherMeeting.day == day
		&& abs(otherMeeting.startTime - startTime) <= 1 && abs(otherMeeting.endTime - endTime) <= 1) {

		for (const shared_ptr<Person> &p : otherMeeting.participants) {
			if (p->hasAvailableSeats()) {
				potentialDrivers.push_back(p);
			}
		}
	}

	return potentialDrivers;
}

std::ostream& operator<<(std::ostream& os, const Meeting& m)
{
	os << m.getSubject() << "-meeting at " << m.getLocation() << " campus, "
	   << "from " << m.getStartTime() << " to " << m.getEndTime() << " by " << m.getLeader()->getName()
	   << "\n > Participants:";

	auto participants{m.getParticipantList()};
	for (const auto& p : participants) { // Alternativt: for (const string& p:. participants)
		os << " " << p;
	}

	return os;
}
