#ifndef GENERATION_H
#define GENERATION_H

#include <random>
#include <cstdint>

class NumberGenerator {
public:
    static NumberGenerator& getInstance() // Can only be initialized once which drastically reduces overhead and increases performance
    {
        static NumberGenerator instance;
        return instance;
    }

    uint_fast64_t generateNumber();

private:
    NumberGenerator() // Constructor initializes the generator with a seed from random_device
    {
        gen = std::mt19937_64(rd());
    }
    std::random_device rd;
    std::mt19937_64 gen;
};

inline uint_fast64_t GenerateNumber() 
{
    return NumberGenerator::getInstance().generateNumber();
}

#endif

/*For more information
    To generate random num we call generateNumber();
    random device && mt19937_64 are set to private and initialized in the constructor for better performance
    getInstance() is only called once to force the generator to only be initialized once
    to get out random number we call GenerateNumber() which: 1. calls getInstance() to launch the generator only once 
                                                            2. returns the number generated
*/