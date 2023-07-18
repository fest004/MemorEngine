#include <vector>
#include "math/math.hpp"
#include "math/vec2.hpp"
#include <SFML/Graphics.hpp>

class Animation {
public:
//Methods
Animation();
Animation(const std::string& name, const sf::Texture& t);
Animation(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed);

void update();
bool hasEnded() const;

const std::string &getName() const;
const math::vec2& getSize() const;
sf::Sprite& getSprite();


private:
//Variables
  sf::Sprite m_Sprite;
  size_t m_FrameCount = 1;
  size_t m_CurrentFrame = 0;
  size_t m_Speed = 0;
  math::vec2 m_Size = {1, 1};
  std::string m_Name;
};
