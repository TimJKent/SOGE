
cmake_minimum_required(VERSION 3.10)
project(SOGE VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add submodules
add_subdirectory(submodules/SOGLR)

# Create the SOGE library as a header-only INTERFACE library
add_library(${PROJECT_NAME} INTERFACE)
add_library(SOGE::SOGE ALIAS ${PROJECT_NAME})

# Set include directories for the library (PUBLIC so consuming projects get them)
target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/submodules/SOECS/include>
    $<INSTALL_INTERFACE:include>
)

# Link dependencies (PUBLIC so they propagate to consuming projects)
target_link_libraries(${PROJECT_NAME} INTERFACE SOGLR)

# Require C++23 for consumers
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)

# Optional: Build example executable
option(SOGE_BUILD_EXAMPLES "Build SOGE example executable" OFF)
if(SOGE_BUILD_EXAMPLES)
    add_executable(SOGEExample src/main.cpp)
    target_link_libraries(SOGEExample PRIVATE SOGE::SOGE)
endif()

# Installation rules
include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    EXPORT SOGETargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install header files
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY submodules/SOECS/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install export targets
install(EXPORT SOGETargets
    FILE SOGETargets.cmake
    NAMESPACE SOGE::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SOGE
)

# Create package configuration files
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/SOGEConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/SOGEConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/SOGEConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SOGE
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/SOGEConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/SOGEConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SOGE
)