#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>

class Memor
{
  public:
    //Methods
    bool init(std::string name);
    void update();

    //Systems
    void sMovement();
    void sInput();
    void sRender();
    void sEnemySpawner();
    void sCollision();


  public:
    //Variables


  private:
    //Methods


  private:
    //Variables
    sf::Window m_Window;
    // EntityManager m_Entities;
    // Entity m_Player;
    bool m_Paused;
    bool m_Running;
};
