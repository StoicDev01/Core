#pragma once

namespace core{
    template <typename T>
    class Range{
        public:

        T min;
        T max;

        Range(){}

        Range(T min, T max){
            this->min = min;
            this->max = max;
        }

        bool fits(T value){
            return min <= value && value <= max;
        }
    };
}
