include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(hash_table STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/hash_table.cc)
set(PROJECT_NAME hash_table)

#tests
option(TESTING "Include testing" ON)
if (TESTING)
	message ("Include " ${PROJECT_NAME} " testing")
	
	set(SOURCE_TEST tests/tests.cc)
	include_directories(include)
	
	find_package(GTest REQUIRED)
	include_directories(${GTEST_INCLUDE_DIRS})
	
	add_executable(${PROJECT_NAME}_tests ${SOURCE_TEST})
	add_dependencies(${PROJECT_NAME}_tests ${PROJECT_NAME})

	target_link_libraries(${PROJECT_NAME}_tests PRIVATE GTest::GTest GTest::Main hash_table)

	add_custom_target(run_${PROJECT_NAME}_tests
		COMMENT "Running ${PROJECT_NAME}_tests"
		COMMAND ./${PROJECT_NAME}_tests
	)
	add_dependencies(run_${PROJECT_NAME}_tests ${PROJECT_NAME}_tests)
	
	enable_testing()
endif()