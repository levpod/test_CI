find_package(Eigen3 REQUIRED)
add_definitions(-DEIGEN_DONT_VECTORIZE -DEIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT)


set(SOURCES 
	Penalty.cpp
    )
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${EIGEN3_INCLUDE_DIR}
    )

add_library(penalty ${SOURCES})
target_link_libraries(penalty)

