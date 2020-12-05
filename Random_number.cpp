#include "Random_number.h"

namespace Random_number
{
    std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    int roll(int from, int to)
    {
        std::uniform_int_distribution<> die{ from, to };
        return die(Random_number::mersenne);
    }
}