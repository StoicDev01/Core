#pragma once
#include <random>
#include <vector>

namespace core{

    class RandomMachine {
        private:
        std::mt19937 rng;
        
        public:

        RandomMachine();

        int rand_int(int min, int max);
        uint32_t rand_uint(uint32_t min, uint32_t max);
        float rand_float(float min, float max);
        double rand_double(double min, double max);

        template <typename T>
        int rand_choice(std::vector<T>& vector);
    };

}

