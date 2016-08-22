project(tests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(test1_source calc_test_from_example)
add_executable(test1 ${test1_source})
target_link_libraries(test1 ${GTEST_LIBRARIES} pthread calc)

set(test2_source calc_test_getRPN)
add_executable(test2 ${test2_source})
target_link_libraries(test2 ${GTEST_LIBRARIES} pthread calc)

set(test3_source calc_test_calcRPN)
add_executable(test3 ${test2_source})
target_link_libraries(test3 ${GTEST_LIBRARIES} pthread calc)

add_test(NAME calc_test_from_example COMMAND test1)
add_test(NAME calc_test_getRPN COMMAND test2)	
add_test(NAME calc_test_calcRPN COMMAND test3)	
