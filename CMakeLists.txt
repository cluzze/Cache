cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

set(PROJECT_NAME cache)
project(${PROJECT_NAME} LANGUAGES CXX)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-g")

include_directories(include hash_table/include list/include LRUcache/include PSScache/include)

set(MAIN main.cc)
set(STAT stat.cc)
set(CACHE_SOURCE src/cache.cc)

add_library(${PROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/cache.cc)

add_dependencies(${PROJECT_NAME} list hash_table LRUcache PSScache)
target_link_libraries(${PROJECT_NAME} list hash_table LRUcache PSScache)

option(TESTING "Include testing" ON)

add_executable(main ${MAIN})
add_executable(stat ${STAT})

target_link_libraries(main PRIVATE cache)
target_link_libraries(stat PRIVATE cache)

if (TESTING)
	message("Include testing")
	set(SOURCE_TEST tests/tests.cc)

	find_package(GTest REQUIRED)
	include_directories(${GTest_INCLUDE_DIRS} include)

	add_executable(${PROJECT_NAME}_tests ${SOURCE_TEST})
	target_link_libraries(${PROJECT_NAME}_tests PRIVATE GTest::GTest GTest::Main cache)

	add_custom_target(run_${PROJECT_NAME}_tests
		COMMENT "Running ${PROJECT_NAME}_tests"
		COMMAND ./${PROJECT_NAME}_tests
	)
	add_dependencies(run_${PROJECT_NAME}_tests ${PROJECT_NAME}_tests)

	enable_testing()
endif()

add_subdirectory(list)
add_subdirectory(hash_table)
add_subdirectory(LRUcache)
add_subdirectory(PSScache)

option(SANITIZERS "Include sanitizers" ON)
if (SANITIZERS)
	message("Build with sanitizers")

	add_compile_options(-fsanitize=address -fsanitize=undefined -g)
	set_target_properties(${PROJECT_NAME}_tests PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif()
