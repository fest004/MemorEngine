#include "component.hpp"
#include "../renderables/animation.hpp"


class CAnimation : public Component
{
  public:
    CAnimation() {}
    CAnimation(const Animation& animation, bool r)
    :
    m_Animation(animation),
    m_Repeat(r)
    {}


    Animation m_Animation;
    bool m_Repeat = false;
};
