add_executable(test_utmatrix
	test_main.cpp
			test_tmatrix.cpp
			test_tvector.cpp
)
target_link_libraries(test_utmatrix PUBLIC gtest mp2_library)
#add_test(NAME MyTest COMMADN test_utmatrix)