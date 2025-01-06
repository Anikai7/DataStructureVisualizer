import clang.cindex
import json

variables = []

def find_variable_value(tu, variable_name):
    for node in tu.cursor.walk_preorder():
        if node.kind == clang.cindex.CursorKind.BINARY_OPERATOR:
            # Check if it's an assignment
            op = list(node.get_children())
            if len(op) == 2 and op[0].spelling == variable_name:
                rhs = op[1]
                print(f"Found assignment: {variable_name} = {rhs.spelling}")  # Debug statement
                return rhs.spelling
        elif node.kind == clang.cindex.CursorKind.CALL_EXPR:
            # Check for constructor or function call initializations
            for child in node.get_children():
                if child.spelling == variable_name:
                    rhs = node
                    print(f"Found function call assignment: {variable_name} initialized with {rhs.spelling}")  # Debug statement
                    return rhs.spelling
        elif node.kind == clang.cindex.CursorKind.INIT_LIST_EXPR: 
            # Check for aggregate initialization 
            if node.semantic_parent and node.semantic_parent.spelling == variable_name:
                print(f"Found aggregate initialization for {variable_name}:  {node.get_tokens()}") 
                # Debug statement 
                var_val = []
                for token in node.get_tokens():
                    if token.spelling != ',' and token.spelling != '{' and token.spelling != '}':
                        var_val.append(token.spelling)
                return var_val
    return None

def parsing_var(tu,file_path):
    global variables  # Ensure we are using the global 'variables' list
    for node in tu.cursor.walk_preorder():
        if node.kind == clang.cindex.CursorKind.VAR_DECL and node.location.file and node.location.file.name == file_path:
            var_name = node.spelling
            var_type = node.type.spelling
            print(f"Variable declaration found: {var_name} of type {var_type}")  # Debug statement

            with open('data_structures.json', 'r') as data_file:
                data = json.load(data_file)
                # Iterate over the data structures to find the var_type
                for ds in data.get('data_structures'):
                    if ds["name"] == var_type:
                        print(f"'{var_type}' exists in the JSON file.")
                        # Find the assigned value of the variable
                        var_value = find_variable_value(tu, var_name)
                        if var_value:
                            print(f"Value assigned to {var_name}: {var_value}")  # Debug statement
                            variables.append({"name": var_name, "type": var_type, "value": var_value})
                        else:
                            print(f"No value assigned to {var_name}")  # Debug statement
                        break  # Exit loop once the type is found
                

    print(f"Variables collected: {variables}")  # Debug statement
    with open('variables.json', 'w') as outfile:
        json.dump({"variables": variables}, outfile, indent=4)
