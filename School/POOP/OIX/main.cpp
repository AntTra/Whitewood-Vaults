#include "Person.h"
#include "Meeting.h"
#include "MeetingWindow.h"
#include <iostream>

int main()
{
	unique_ptr<Car> fullCar {new Car{0}};
	unique_ptr<Car> car {new Car{5}};

	shared_ptr<Person> p1 { new Person{"p1", "p1@ntnu.no"}};
	shared_ptr<Person> p2 { new Person{"p2", "p2@ntnu.no"}};
	shared_ptr<Person> p3 { new Person{"p3", "p3@ntnu.no", std::move(fullCar)}};
	shared_ptr<Person> p4 { new Person{"p4", "p4@ntnu.no", std::move(car)}};
	shared_ptr<Person> p5 { new Person{"p5", "p5@ntnu.no", make_unique<Car>(5)}};
	shared_ptr<Person> p6 { new Person{"p6", "p6@ntnu.no"}};

	Meeting trh1{1, 9, 14, Campus::trh, "C++", p1};
	trh1.addParticipant(p3);

	Meeting gjo{1, 9, 14, Campus::gjo, "Fusion", p2};
	gjo.addParticipant(p4);

	Meeting trh2{1, 8, 15, Campus::trh, "Faculty naming", p5};
	trh2.addParticipant(p6);
	trh2.addParticipant(p3);
	trh2.addParticipant(p4);

	cout << "All meetings:" << endl << trh1 << endl << gjo << endl << trh2 << endl;

	cout << "Persons at meetings concurrent with the " << trh1.getSubject() << "-meeting:\n";
	for (auto &p : trh1.findPotentialCoDriving(trh2)) {
		cout << *p << endl;
	}

	// GUI
	constexpr unsigned int width = 800;
	constexpr unsigned int height = 800;
	// Punktet defineres slik at vinduet blir plassert midt på skjermen
	const Point top_left{(1920 - width) / 2, (1080 - height) / 2};

	MeetingWindow mw{{top_left}, width, height, "Meetings"};

	mw.printPeople();
	mw.wait_for_close();
	return 0;
}
