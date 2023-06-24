#include <fstream>
#include <iostream>


class FileReader
{
  public:
    FileReader() {}

    std::string ReadFile(std::string filepath)
    {
      std::string result; // Result to be returned
      std::ifstream ReadFile(filepath); // Reads file
      std::string currentLine;

      while (getline(ReadFile, currentLine)) 
      {
        result += currentLine;
        result += "\n";
        m_Length++;
      }

      return result;
    }

    int getLength() { return m_Length; }


  private:
    //Variables
    int m_Length = 0;


};
