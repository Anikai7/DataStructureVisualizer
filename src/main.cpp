#include <data_visualizer.h>
#include <iostream>
#include <fstream>
#include <decl_parsing.hpp>

int main() {

    std::string file = "E:\\coding\\DataStructureVisualizer\\test.cpp";

    DeclParsing parse;
    parse.var_parsing(file);

    DataVisualizer visualizer;
    visualizer.render(parse.classesAndStructs);


    return 0;
}