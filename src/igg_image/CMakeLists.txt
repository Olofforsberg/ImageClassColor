add_subdirectory(io_strategies)

# TODO: create image library from image.cpp.
# TODO: link image library to any other libraries if needed.


add_library(image image.cpp)
add_executable(image_main image_main.cpp)
target_link_libraries(image_main image strategies ${TOOLS})