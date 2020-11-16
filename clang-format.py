# recursively clang format things
import os

cpp_ext = ('.cpp', '.hpp')

for root, dirs, files in os.walk('dummy-device'):
    for file in files:
        if file.endswith(cpp_ext):
            os.system("clang-format -i -style=file " + root + "/" + file)

for root, dirs, files in os.walk('server'):
    for file in files:
        if file.endswith(cpp_ext):
            os.system("clang-format -i -style=file " + root + "/" + file)

for root, dirs, files in os.walk('shared'):
    for file in files:
        if file.endswith(cpp_ext):
            os.system("clang-format -i -style=file " + root + "/" + file)