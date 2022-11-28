set(target ${MP2_TESTS})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${test} ${srcs} ${hdrs})
target_link_libraries(${test} ${testlib})
target_include_directories(${test} PUBLIC ../gtest)