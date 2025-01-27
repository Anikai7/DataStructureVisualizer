#include "decl_parsing.hpp"
#include <iostream>

// Callback to visit AST nodes
CXChildVisitResult DeclParsing::visitNode(CXCursor cursor, CXCursor /* parent */, CXClientData clientData) {
    auto* classesAndStructs = static_cast<std::vector<ClassStructInfo>*>(clientData);

    // Check if the cursor is in the main file (user's source file)
    CXSourceLocation location = clang_getCursorLocation(cursor);
    if (!clang_Location_isFromMainFile(location)) {
        return CXChildVisit_Continue; // Skip if not from the user's source file
    }

    // Check for struct or class declarations
    if ((clang_getCursorKind(cursor) == CXCursor_StructDecl || clang_getCursorKind(cursor) == CXCursor_ClassDecl) &&
        clang_isDeclaration(clang_getCursorKind(cursor))) {

        // Get the name of the class/struct
        CXString cxName = clang_getCursorSpelling(cursor);
        std::string name = clang_getCString(cxName);
        clang_disposeString(cxName);

        if (name.empty()) {
            return CXChildVisit_Continue; // Skip anonymous classes/structs
        }

        ClassStructInfo info;
        info.name = name;

        // Visit fields of the class/struct
        clang_visitChildren(
            cursor,
            [](CXCursor c, CXCursor /* parent */, CXClientData clientData) -> CXChildVisitResult {
                auto* info = static_cast<ClassStructInfo*>(clientData);

                // Check if the field is in the main file
                CXSourceLocation fieldLocation = clang_getCursorLocation(c);
                if (!clang_Location_isFromMainFile(fieldLocation)) {
                    return CXChildVisit_Continue; // Skip fields not from the main file
                }

                if (clang_getCursorKind(c) == CXCursor_FieldDecl) {
                    // Get field name and type
                    CXString cxFieldName = clang_getCursorSpelling(c);
                    CXString cxFieldType = clang_getTypeSpelling(clang_getCursorType(c));

                    std::string fieldName = clang_getCString(cxFieldName);
                    std::string fieldType = clang_getCString(cxFieldType);

                    info->fields.push_back({ fieldType, fieldName });

                    clang_disposeString(cxFieldName);
                    clang_disposeString(cxFieldType);
                }

                return CXChildVisit_Continue;
            },
            &info);

        classesAndStructs->push_back(info);
    }

    return CXChildVisit_Recurse;
}



void DeclParsing::var_parsing(const std::string& filePath) {
    CXIndex index = clang_createIndex(0, 0); // Create index
    std::cout << filePath.c_str() << std::endl;
    CXTranslationUnit unit = clang_parseTranslationUnit(index, filePath.c_str(), nullptr, 0, nullptr, 0, CXTranslationUnit_None);

    if (unit == nullptr) {
        std::cerr << "Unable to parse translation unit. Quitting." << std::endl;
        clang_disposeIndex(index);
        return;
    }

    CXCursor cursor = clang_getTranslationUnitCursor(unit);

    // Traverse the AST and populate `classesAndStructs`
    clang_visitChildren(cursor, visitNode, &classesAndStructs);

    // Clean up
    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
}
