set(SRC
	catch.hpp
	main.cpp
  tagged_type_test.cpp
  type_list_test.cpp
  composed_unit_test.cpp
  number_test.cpp
  su_test.cpp
)

add_executable(tests ${SRC})
target_compile_features(tests PUBLIC cxx_std_17)
target_link_libraries(tests su)