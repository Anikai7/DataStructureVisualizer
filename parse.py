import clang.cindex
import json

# Set the library file path for libclang
clang.cindex.Config.set_library_file("/usr/local/lib/libclang.so")

def parse_file(file_path):
    index = clang.cindex.Index.create()
    args = ['-std=c++17', '-I/usr/include', '-I/usr/local/include']
    try:
        translation_unit = index.parse(file_path, args=args)
    except clang.cindex.TranslationUnitLoadError as e:
        print(f"Error parsing translation unit: {e}")
        return

    data_structures = []
    variables = []
    for node in translation_unit.cursor.walk_preorder():
        #cheaking out if there is struct in the given source code
        if node.kind == clang.cindex.CursorKind.STRUCT_DECL and node.is_definition() and node.location.file and node.location.file.name == file_path:
            struct_type = node.spelling
            child_type = []

            for child in node.get_children():
                child_type.append(child.type.spelling)

            data_structures.append({"name":struct_type,"data":child_type})
        elif node.kind ==  clang.cindex.CursorKind.CLASS_DECL and node.location.file and node.location.file.name == file_path:
            class_type = node.spelling
            fields = []

            for child in node.get_children():
                if child.kind == clang.cindex.CursorKind.FIELD_DECL:
                    fields.append(child.type.spelling)
            
            data_structures.append({"name":class_type,"data":fields})
        elif node.kind == clang.cindex.CursorKind.VAR_DECL and node.location.file and node.location.file.name == file_path:
            var_name = node.spelling
            var_type = node.type.spelling
            var_value = None

            # Check if there's an initial value
            for child in node.get_children():
                if child.kind == clang.cindex.CursorKind.INTEGER_LITERAL or child.kind == clang.cindex.CursorKind.FLOATING_LITERAL:
                    var_value = child.spelling

            variables.append({"name": var_name, "type": var_type, "value": var_value})

    with open('variables.json', 'w') as outfile:
        json.dump({"variables": variables}, outfile,indent=4)
    
    with open('data_structures.json', 'w') as outfile:
        json.dump({"data_structures": data_structures}, outfile,indent=4)


    print(f"Data structures written to JSON: {data_structures}")
    print(f"Variables written to JSON: {variables}")

def main():
    file_path = "test.cpp"  # Ensure this points to the correct C++ file
    parse_file(file_path)

if __name__ == "__main__":
    main()
