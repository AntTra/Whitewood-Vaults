#pragma once

#include "AnimationWindow.h"
#include "Meeting.h"
#include "Person.h"
#include "widgets/Button.h"
#include "widgets/TextInput.h"
#include "widgets/DropdownList.h"

#include <string>
#include <vector>


// Meeting GUI
struct MeetingWindow : TDT4102::AnimationWindow
{
	static constexpr int pad = 4;
	static constexpr int btnW = 100;
	static constexpr int btnH = 20;
	static constexpr int fieldW = 200;
	static constexpr int fieldH = 20;
	static constexpr int fieldPad = 80;
	static constexpr int headerFontSize = 20;

	MeetingWindow(Point position, int width, int height, const std::string& title);
	~MeetingWindow();
	void printPeople() const;

private:
	// Program-tilstand
	std::vector<std::string> meetingLocations{"Trondheim","Aalesund","Gjovik"};
	std::vector<std::string> peopleStrVec{"\0"};   
	std::vector<unique_ptr<Meeting>> meetings;
	std::vector<shared_ptr<Person>> people;

	// Avslutt knapp
	TDT4102::Button quitBtn;

	// Møte
	TDT4102::TextInput meetingDay;
	TDT4102::TextInput meetingStart;
	TDT4102::TextInput meetingEnd;
	TDT4102::DropdownList meetingLocation;
	TDT4102::TextInput meetingSubject;
	TDT4102::DropdownList meetingLeader;
	TDT4102::Button meetingNewBtn;
	// Vi kan ha en vector her av vanlige pekere fordi alle verdiene som lagres innenfor vectoren er medlemsvariabler i denne klassen
	// Dermed fjernes denne vectoren på samme tid som inneholdet av vectoren, som betyr at eierskapet av minnet er løst.
	std::vector<TDT4102::Widget*> meetingWidgets;

	// Møte-liste
	TDT4102::TextInput meetingData;

	// Person
	TDT4102::TextInput personName;
	TDT4102::TextInput personEmail;
	TDT4102::TextInput personSeats;
	TDT4102::Button personNewBtn;
	std::vector<TDT4102::Widget*> personWidgets;

	// Person-liste
	TDT4102::TextInput personData;

	// Bytte side
	TDT4102::Button createMeetingButton;
	TDT4102::Button createPersonButton;

	void newMeeting();
	void newPerson();
	void showMeetingPage();
	void showPersonPage();
	void hideWidgets(std::vector<TDT4102::Widget*>& widgets);

	// Hjelpefunksjoner
	void attachMeetingWidget(TDT4102::Widget& mw);
	void attachPersonWidget(TDT4102::Widget& pw);
	void updateMeetingList();
	void updatePersonList();
	
	// Callback-funksjoner
	void cb_quit();
	void cb_new_meeting();
	void cb_new_person();
	void cb_meetings();
	void cb_persons();
};
