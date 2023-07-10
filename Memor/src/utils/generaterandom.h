#include <random>

namespace utils {



inline int generateRandomNumber(int lowerBound, int upperBound) {
    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a uniform distribution
    std::uniform_int_distribution<int> distribution(lowerBound, upperBound);

    // Generate a random value within the specified range
    return distribution(gen);
}



}
