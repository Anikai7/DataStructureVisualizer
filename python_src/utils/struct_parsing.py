import clang.cindex
import json

def parse_struct(tu,file_path):
    data_structures = []
    for node in tu.cursor.walk_preorder():
        # Checking if there is a struct in the given source code
        if node.kind == clang.cindex.CursorKind.STRUCT_DECL and node.is_definition() and node.location.file and node.location.file.name == file_path:
            struct_type = node.type.spelling
            child_type = []

            for child in node.get_children():
                child_type.append(child.type.spelling)

            data_structures.append({"name": struct_type, "data_type": child_type})
        # Checking if there is a class declaration in the given source code
        elif node.kind == clang.cindex.CursorKind.CLASS_DECL and node.location.file and node.location.file.name == file_path:
            class_type = node.spelling
            fields = []
            fields_name = []

            for child in node.get_children():
                if child.kind == clang.cindex.CursorKind.FIELD_DECL:
                    fields.append(child.type.spelling)
                    fields_name.append(child.spelling)
            
            data_structures.append({"name": class_type, "fields": fields_name, "data_type": fields})
    
    with open('data_structures.json', 'w') as outfile:
        json.dump({"data_structures": data_structures}, outfile, indent=4)

    print(f"Data structures written to JSON: {data_structures}")

