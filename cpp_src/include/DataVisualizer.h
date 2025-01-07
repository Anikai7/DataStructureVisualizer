#ifndef DATA_VISUALIZER_H
#define DATA_VISUALIZER_H

#include <vector>
#include <string>


int cameraX;
int cameraY;

struct Data {
    std::string name;
    std::string type;
    std::string value;

    std::pair<int,int> objPos;
};

class DataVisualizer {
public:

    DataVisualizer(const std::string& filename);
    void parseJSONFile(const std::string& filename);
    void render();

private:
    std::vector<Data*> variables;
    
};

class menu{
    public:

        menu(){
            
        }
};


#endif
