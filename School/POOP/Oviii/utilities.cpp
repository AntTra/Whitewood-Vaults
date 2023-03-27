#include "std_lib_facilities.h"
#include "utilities.h"

int randomWithLimits(double bottomLimit, double upperLimit) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(bottomLimit, upperLimit);

    //for (int i = 0; i < 10; i++) {
    int number = distribution(generator);
        
    //}
    return number;
}

