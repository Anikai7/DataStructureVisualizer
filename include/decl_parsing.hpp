#pragma once

#include <clang-c/Index.h>
#include <string>
#include <vector>

// Structure to store field information
struct FieldInfo {
    std::string type;
    std::string name;
};

// Structure to store class/struct information
struct ClassStructInfo {
    std::string name;
    std::vector<FieldInfo> fields;
};

// Declaration of the decl_parsing class
class DeclParsing {
public:
    // Stores parsed classes and structs
    std::vector<ClassStructInfo> classesAndStructs;

    // Parses the provided file and populates `classesAndStructs`
    void var_parsing(const std::string& filePath);

private:
    // Static callback for visiting AST nodes
    static CXChildVisitResult visitNode(CXCursor cursor, CXCursor parent, CXClientData clientData);
};
