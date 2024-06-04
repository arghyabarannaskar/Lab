import os

def findfiles(directory):
    file_paths = []

    # Walk through the directory tree recursively
    for root, dirs, files in os.walk(directory):
        for file in files:
            file_paths.append(os.path.join(root, file))

    return file_paths

# Example usage:
directory = '/path/to/your/directory'
files = findfiles(directory)
for file in files:
    print(file)
