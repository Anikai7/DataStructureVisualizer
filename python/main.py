import clang
from utils.struct_parsing import parse_struct
from utils.var_parsing import parsing_var

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

    return translation_unit

def main():
    file_path = "test.cpp"  # Ensure this points to the correct C++ file
    tu = parse_file(file_path)
    if tu != None:
        parse_struct(tu,file_path)
        parsing_var(tu,file_path)

if __name__ == "__main__":
    main()