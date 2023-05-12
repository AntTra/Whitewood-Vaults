#include "fibonacci.h"
#include "matrix.h"
#include "dummy.h"
#include <iostream>


int main()
{
	int choice{-1};
	while(choice != 0){
		std::cout << "0) Quit\n";
		std::cout << "1) createFibonacci()\n";
		std::cout << "2) Test the Matrix Constructors\n";
		std::cout << "3) dummyTest()\n";
		std::cout << "4) testMatrix()\n";
		std::cout << "5) testMatrixExtra()\n";

		Matrix test1{2,4};
		Matrix test2{4};

		std::cout << "Enter choice (0-5): ";
		std::cin >> choice;
		std::cout << '\n';

		switch(choice){
			case 0:
				std::cout << "Goodbye!";
				break;

			case 1:
				createFibonacci();
				std::cout << '\n';
				break;
			
			case 2:
				std::cout << test1 << '\n';
				std::cout << test2 << '\n';
				test1.set(0,0,14.4);
				std::cout << test1.get(0,0) << '\n';
				std::cout << test2[3][3] << '\n';
				std::cout << '\n';
				break;

			case 3:
				dummyTest();
				std::cout << '\n';
				break;
			
			case 4:
				testMatrix();
				std::cout << '\n';
				break;
			
			case 5:
				testMatrixExtra();
				std::cout << '\n';
				break;
			
			default:
				std::cout << "Not a valid input!\n";
				std::cout << '\n';
		}
	}
	return 0;
}