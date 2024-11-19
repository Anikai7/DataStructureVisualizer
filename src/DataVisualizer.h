#ifndef DATA_VISUALIZER_H
#define DATA_VISUALIZER_H

#include <vector>
#include <string>

struct DataStructure {
    std::string name;
    std::vector<std::string> data;
};

class DataVisualizer {
public:
    DataVisualizer(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void render();

private:
    std::vector<DataStructure> data_structures;
};


#endif
