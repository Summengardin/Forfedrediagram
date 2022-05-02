#pragma once // FORFEDREDIAGRAM_GLOBALS_HPP

#include "date.hpp"

class uuid
{
  private:
    unsigned int nextFreeIdx = 0;

  public:
    inline unsigned int operator()() { return ++nextFreeIdx; }

    inline void update(unsigned int otherIdx)
    {
        if (otherIdx > nextFreeIdx)
        {
            nextFreeIdx = otherIdx;
        }
    }
};

inline uuid TreeId;
inline uuid DummyId;
inline Today today;

// FORFEDREDIAGRAM_GLOBALS_HPP
