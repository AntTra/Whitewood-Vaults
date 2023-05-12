#include "MeetingWindow.h"
#include <iostream>

MeetingWindow::MeetingWindow(Point position, int width, int height, const string& title)
	: AnimationWindow{position.x, position.y, width, height, title},

	quitBtn{TDT4102::Point{width - btnW - pad, pad + fieldH}, btnW, btnH, "Quit" },

	meetingDay      {TDT4102::Point{fieldPad, pad + fieldH}   	 , fieldW, btnH, "Day" },
	meetingStart    {TDT4102::Point{fieldPad, (pad + fieldH) * 3}, fieldW, btnH, "Start time" },
	meetingEnd      {TDT4102::Point{fieldPad, (pad + fieldH) * 5}, fieldW, btnH, "End time" },
	meetingLocation {TDT4102::Point{fieldPad, (pad + fieldH) * 7}, fieldW, btnH, meetingLocations},
	meetingSubject  {TDT4102::Point{fieldPad, (pad + fieldH) * 9}, fieldW, btnH, "Subject" },
	meetingLeader   {TDT4102::Point{fieldPad, (pad + fieldH) * 11}, fieldW, btnH, peopleStrVec},
	meetingNewBtn   {TDT4102::Point{fieldPad, (pad + fieldH) * 13}, btnW, btnH, "Add meeting" },
	meetingData     {TDT4102::Point{pad, (pad + fieldH) * 15     }, static_cast<unsigned int>(width - pad * 2), fieldW * 2, "All meetings" },

	personName      {TDT4102::Point{fieldPad+200, pad + fieldH}, fieldW, btnH, "Name" },
	personEmail     {TDT4102::Point{fieldPad+200, (pad + fieldH) * 3}, fieldW, btnH, "Email" },
	personSeats   	{TDT4102::Point{fieldPad+200, (pad + fieldH) * 5}, fieldW, btnH, "Car seats" },
	personNewBtn    {TDT4102::Point{fieldPad+200, (pad + fieldH) * 7}, btnW, btnH, "Add person" },
	personData      {TDT4102::Point{pad, (pad + fieldH) * 15     }, static_cast<unsigned int>(width - pad * 2), fieldW * 2, "All persons"},

	createMeetingButton {TDT4102::Point{width - btnW - pad, (pad + fieldH) * 5}, btnW, btnH, "Meetings"}, 
	createPersonButton {TDT4102::Point{width - btnW - pad, (pad + fieldH) * 3}, btnW, btnH, "Persons"}
{
	// Felles
	
	add(quitBtn);
	//attach(headerText);

	// Nytt møte
	attachMeetingWidget(meetingDay);
	attachMeetingWidget(meetingStart);
	attachMeetingWidget(meetingEnd);
	attachMeetingWidget(meetingLocation);
	attachMeetingWidget(meetingSubject);
	attachMeetingWidget(meetingLeader);
	attachMeetingWidget(meetingNewBtn);
	attachMeetingWidget(createPersonButton);

	quitBtn.setCallback(std::bind(&MeetingWindow::cb_quit,this));
	meetingNewBtn.setCallback(std::bind(&MeetingWindow::cb_new_meeting, this));
	personNewBtn.setCallback(std::bind(&MeetingWindow::cb_new_person, this));
	createMeetingButton.setCallback(std::bind(&MeetingWindow::cb_meetings, this));
	createPersonButton.setCallback(std::bind(&MeetingWindow::cb_persons, this));

	// Møte-liste
	attachMeetingWidget(meetingData);

	// Ny person
	attachPersonWidget(personName);
	attachPersonWidget(personEmail);
	attachPersonWidget(personSeats);
	attachPersonWidget(personNewBtn);
	attachPersonWidget(createMeetingButton);

	// Person-liste
	attachPersonWidget(personData);

	// Initielt vindu
	showMeetingPage();
}

MeetingWindow::~MeetingWindow() {}

int getIntegerValue(string value, string nameOfField) {
	int interpretedValue = 0;
	//input validation 
	try{
		interpretedValue = stoi(value);
		throw 505;
	}
	catch (...){
		cout<<"ERROR: You entered a non-int value in a field that is meant to be int!\n Int fields are: Day and Car Seats"<<endl;
	}
	return interpretedValue;
}

void MeetingWindow::newMeeting()
{
	int day = getIntegerValue(meetingDay.getText(), "day");
	int start = getIntegerValue(meetingStart.getText(), "start time");
	int end = getIntegerValue(meetingEnd.getText(), "end time");
	
	Campus campus = static_cast<Campus>(stringToCampus.at(meetingLocation.getValue()));
	const string subject = meetingSubject.getText();
	string leaderName = meetingLeader.getValue();

	meetingDay.setText("");
	meetingStart.setText("");
	meetingEnd.setText("");
	meetingSubject.setText("");

	if(leaderName=="\0"){
		cout<<"Invalid leader!"<<endl;
		return;
	}

	for (auto &p : people){
		
		if (p->getName() == leaderName){
			shared_ptr<Person> leader = p;
			meetings.emplace_back(new Meeting{ day, start, end, campus, subject, leader});
		}
	}

	updateMeetingList();
}

void MeetingWindow::newPerson()
{
	int freeSeetCount = getIntegerValue(personSeats.getText(), "Free seats");
	
	Car* carInstanceOrNullptr = nullptr;
	if (freeSeetCount != 0) {
		carInstanceOrNullptr = new Car{ freeSeetCount } ;
	}
	std::unique_ptr<Car> car {carInstanceOrNullptr};

	const string& name = personName.getText();
	const string& email = personEmail.getText();

	personSeats.setText("");
	personName.setText("");
	personEmail.setText("");

	people.emplace_back(new Person{ name, email, std::move(car) });

	if(peopleStrVec.at(0)=="\0"){
		peopleStrVec.at(0) = people.back()->getName();

	} else {
		peopleStrVec.emplace_back(people.back()->getName());
	}
	meetingLeader.setOptions(peopleStrVec);
	
	updatePersonList();
}

void MeetingWindow::showMeetingPage()
{
	hideWidgets(personWidgets);

	for (auto* mw : meetingWidgets) {
		mw->setVisible(true);
	}
}

void MeetingWindow::showPersonPage()
{

	for (auto* pw : meetingWidgets) {
		pw->setVisible(false);
	}

	for (auto* pw : personWidgets) {
		pw->setVisible(true);
	}
	hideWidgets(meetingWidgets);	
}

void MeetingWindow::hideWidgets(vector<TDT4102::Widget*>& widgets)
{
	cout<<"now hding meeting widgets!";
	for (auto* w : widgets) {
		w->setVisible(false);
	}
	cout<<"all widgets should be hidden. len: "<<widgets.size()<<endl;
}

void MeetingWindow::updateMeetingList()
{
	stringstream ss;
	for (auto &m : meetings) {
		ss << *m << endl;
	}
	meetingData.setText(ss.str());//.c_str());  //CHANGE
}

void MeetingWindow::updatePersonList()
{
	stringstream ss;
	for (auto &p : people) {
		ss << *p << endl;
	}
	personData.setText(ss.str());//.c_str());//CHANGE
}

void MeetingWindow::attachMeetingWidget(TDT4102::Widget& mw)
{
	add(mw);
	meetingWidgets.push_back(&mw);   
}

void MeetingWindow::attachPersonWidget(TDT4102::Widget& pw)
{
	add(pw);
	personWidgets.push_back(&pw);
}

// Callbackfunksjoner
void MeetingWindow::cb_quit()
{
	close();
}

void MeetingWindow::cb_new_meeting()
{
	newMeeting();
}


void MeetingWindow::cb_new_person()
{
	newPerson();
}

void MeetingWindow::cb_meetings()
{
	showMeetingPage();
}

void MeetingWindow::cb_persons()
{
	showPersonPage();
}

void MeetingWindow::printPeople() const {
	for (const auto &person : people) {
		std::cout << *person << endl;
	}
}
