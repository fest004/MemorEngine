#pragma once

#include <time.h>

namespace utils {


//Class is Linux specific, TODO: preprocessor statement to make it compatibale with windows if needed

class Timer {
public:
  //Methods
  Timer() 
  {
    m_Frequency = 1.0 / 1000000000.0; // Nanosecond resolution
    clock_gettime(CLOCK_MONOTONIC, &m_Start);
  }

  void reset() { clock_gettime(CLOCK_MONOTONIC, &m_Start); }

  //Returns elapsed time since starting clock in seconds 
  float elapsed() 
  {
    timespec current;
    clock_gettime(CLOCK_MONOTONIC, &current);
    long long elapsedNanos = (current.tv_sec - m_Start.tv_sec) * 1000000000LL + (current.tv_nsec - m_Start.tv_nsec);
    return static_cast<float>(elapsedNanos) * m_Frequency;
  }

private:
  // Variables
  timespec m_Start;
  double m_Frequency;
};

} // namespace utils 
