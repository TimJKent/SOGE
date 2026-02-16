# SOGE
Simple Open Game Engine
## About
SOGE is a header-only C++23 game engine library built on top of SOGLR (renderer) and SOECS (entity component system).

## Usage

### As a Submodule
Add SOGE as a git submodule to your project:
```bash
git submodule add <repository-url> external/SOGE
git submodule update --init --recursive
```

In your CMakeLists.txt:
```cmake
add_subdirectory(external/SOGE)
target_link_libraries(YourTarget PRIVATE SOGE::SOGE)
```

### Using add_subdirectory
Clone or copy SOGE into your project, then:
```cmake
add_subdirectory(path/to/SOGE)
target_link_libraries(YourTarget PRIVATE SOGE::SOGE)
```

### Using find_package (After Installation)
Install SOGE, then in your CMakeLists.txt:
```cmake
find_package(SOGE REQUIRED)
target_link_libraries(YourTarget PRIVATE SOGE::SOGE)
```

## Requirements
- C++23 compiler
- CMake 3.10 or higher