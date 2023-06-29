#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include "entity/entitymanager.hpp"
#include "entity/entity.hpp"

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Memor
{
  public:
    //Methods
   
  public:
    //Variables
    Memor(const std::string filename);
    void Run();


  private:
    //Methods
    bool init(std::string path);
    void update();

    //Systems
    void sMovement();
    void sUserInput();
    void sLifeSpan();
    void sRender();
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> e);
    void spawnBullet(std::shared_ptr<Entity> e);
    void spawnSpecialWeapon(std::shared_ptr<Entity> e);




  private:
    //Variables
    sf::RenderWindow m_Window;
    EntityManager m_Entities;
    sf::Font m_Font;
    sf::Text m_Text;
    PlayerConfig m_PlayerConfig;
    EnemyConfig m_EnemyConfig;
    BulletConfig m_BulletConfig;
    int m_Score = 0;
    int m_CurrentFrame = 0;
    int m_LastEnemySpawnTime;
    bool m_Paused = false;
    bool m_Running = true;

    std::shared_ptr<Entity> m_Player;
};
