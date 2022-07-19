#include "random_machine.h"

namespace core{

    RandomMachine::RandomMachine(){
        std::random_device dev;
        std::mt19937 rng(dev());
        this->rng = rng;
    }

    int RandomMachine::rand_int(int min, int max){
        std::uniform_int_distribution<std::mt19937::result_type> dist(min,max);
        return dist(rng);
    }

    uint RandomMachine::rand_uint(uint min, uint max){
        std::uniform_int_distribution<uint> dist(min, max);
        return dist(rng);
    }

    float RandomMachine::rand_float(float min, float max){
        std::uniform_real_distribution<float> dist(min, max);
        return dist(rng);
    }

    double RandomMachine::rand_double(double min, double max){
        std::uniform_real_distribution<double> dist(min, max);
        return dist(rng);
    }

    template <typename T>
    int RandomMachine::rand_choice(std::vector<T>& vector){
        return rand_int(0, vector.size() - 1);
    }
}