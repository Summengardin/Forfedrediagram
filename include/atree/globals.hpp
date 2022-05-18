#pragma once // FORFEDREDIAGRAM_GLOBALS_HPP


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

    inline void reset() { nextFreeIdx = 0; }
};

inline uuid TreeId;
inline uuid DummyId;

// FORFEDREDIAGRAM_GLOBALS_HPP
