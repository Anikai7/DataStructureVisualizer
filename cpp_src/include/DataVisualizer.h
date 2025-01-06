#ifndef DATA_VISUALIZER_H
#define DATA_VISUALIZER_H

#include <vector>
#include <string>

struct Data {
    std::string name;
    std::string type;
    std::string value;

    std::pair<int,int> objPos;
};

class DataVisualizer {
public:

    int cameraX;
    int cameraY;

    DataVisualizer(const std::string& filename);
    void parseJSONFile(const std::string& filename);
    void render();

private:
    std::vector<Data*> variables;
    
};


#endif
