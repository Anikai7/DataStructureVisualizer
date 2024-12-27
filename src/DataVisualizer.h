#ifndef DATA_VISUALIZER_H
#define DATA_VISUALIZER_H

#include <vector>
#include <string>

struct DataStructure {
    std::string name;
    std::string type;
    std::string value;
};

class DataVisualizer {
public:
    DataVisualizer(const std::string& filename);
    void parseJSONFile(const std::string& filename);
    void render();

private:
    std::vector<std::string> variables;
};


#endif
