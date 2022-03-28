#ifndef FORFEDREDIAGRAM_GLOBALS_HPP
#define FORFEDREDIAGRAM_GLOBALS_HPP

#include "../include/date.hpp"

class uuid{
private:
    unsigned int nextFreeIdx = 0;

public:
    unsigned int operator()(){
        return ++nextFreeIdx;
    }
    void update(unsigned int otherIdx){
        if(otherIdx > nextFreeIdx){
            nextFreeIdx = otherIdx;
        }
    }
};

uuid TreeId;
Today today;


#endif //FORFEDREDIAGRAM_GLOBALS_HPP
