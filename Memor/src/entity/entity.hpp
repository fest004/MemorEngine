#include <iostream>
#include <memory.h>


class Entity
{

  public:
    //Methods
    bool isActive();
    const std::string getTag();
    const size_t getID();
    void destroy();

 public:
    //Variables
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CInput> cInput;
    std::shared_ptr<CScore> cScore;
    std::shared_ptr<CLifespan> cLifespan;

 private:
    //Methods
    // Private constructor so only the entitymanager can create
    Entity(const size_t id, const std::string tag);

 private:
    //Variables
    std::string m_Tag    = "default";
    bool        m_Active = true;
    size_t      m_ID     = 0;


};
