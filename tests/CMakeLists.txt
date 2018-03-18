set(SRC
	main.cpp
	catch.hpp
)

add_executable(tests ${SRC})
target_compile_features(tests PUBLIC cxx_std_17)
target_link_libraries(tests su)