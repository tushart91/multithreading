file(GLOB_RECURSE SRCS "*.cpp" "*.h")

include_directories("/usr/local/include")

add_executable(Multithreading ${SRCS})

find_library(GTEST_LIBRARY NAMES gtest)
target_link_libraries(Multithreading ${GTEST_LIBRARY})
