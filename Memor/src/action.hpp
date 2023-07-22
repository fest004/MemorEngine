

#include <string>
class Action
{

public: 
//Methods
Action();
Action(const std::string& name, const std::string& type);


const std::string& getName() const;
const std::string& getType() const;
std::string toString() const;


public:
//Variables


private:
//Methods

private:
//Variables

std::string m_Name;
std::string m_Type;



};

