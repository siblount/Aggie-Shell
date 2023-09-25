import os
import re

# Directory containing header files
header_dir = os.getcwd()

# Loop through each header file in the directory and generate a forward declaration header file
for root, dirs, files in os.walk(header_dir):
    # Skip directories beginning with a dot
    dirs[:] = [d for d in dirs if not d.startswith('.')]
    for filename in files:
        if filename.endswith(".hpp") and not filename.endswith(".fwd.hpp"):
            print("Generating forward declarations for " + filename)
            # Extract the class name from the header file name
            class_name = os.path.splitext(filename)[0]

            # Generate the forward declaration header file name
            forward_declaration_filename = class_name + ".fwd.hpp"

            # Read in the header file
            with open(os.path.join(root, filename), "r") as f:
                header_contents = f.read()

            # Find all class and struct definitions in the header file
            class_regex = r"(class|struct)\s+(\w+)\s*(?::\s*(?:public|private|protected)\s+(\w+))?\s*{"
            class_matches = re.findall(class_regex, header_contents)

            # Generate the forward declarations for each class and struct
            forward_declarations = ""
            for match in class_matches:
                if match[0] == "class":
                    forward_declaration = "class " + match[1] + ";\n"
                else:
                    forward_declaration = "struct " + match[1] + ";\n"
                forward_declarations += forward_declaration

            # Write the forward declarations to the header file

            with open(os.path.join(root, forward_declaration_filename), "w") as f:
                f.write("#pragma once\n\n" + forward_declarations)
                
print("Done")