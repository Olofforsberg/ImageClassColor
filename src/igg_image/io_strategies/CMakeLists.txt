add_library(strategies
            # TODO: Add other files here when needed.
            dummy_strategy.cpp
            png_strategy.cpp
            ppm_strategy.cpp)

# TODO: link strategies against needed libraries.

SET(CMAKE_MODULE_PATH
	${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(PNG REQUIRED)

include_directories(${PNG_INCLUDE_DIRS})

target_link_libraries(strategies
   ${PNG_LIBRARIES})