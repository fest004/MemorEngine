#pragma once
#include <cmath>

//Degrees to radians 

namespace math {

inline float toRadians(float degrees) { return degrees * (M_PI / 180.0f); }

}
