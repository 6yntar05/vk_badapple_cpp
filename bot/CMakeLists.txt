include_directories(../modules/cpp_vk_lib)
include_directories(../modules/cpp_vk_lib/cpp_vk_lib/include)
include_directories(../modules/cpp_vk_lib/modules/spdlog/include)
include_directories(../modules/cpp_vk_lib/modules/asio/asio/include)
include_directories(include)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})

file(GLOB_RECURSE SRC "*.cpp")
add_executable(vk_badapple_cpp ${SRC})

find_library(cpp_vk_lib HINTS "../cpp_vk_lib")
find_library(simdjson HINTS "../cpp_vk_lib/modules/simdjson")
target_link_libraries(vk_badapple_cpp cpp_vk_lib simdjson ${OpenCV_LIBS})
