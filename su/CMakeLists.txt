set(HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/tagged_type.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/type_list.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/su.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/number.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ionumber.hpp
)

add_custom_target(su_headers SOURCES ${HEADERS}) #Trick to show it up in IDE

add_library(su INTERFACE)
target_sources(su INTERFACE ${HEADERS})

target_include_directories(su INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}
)
