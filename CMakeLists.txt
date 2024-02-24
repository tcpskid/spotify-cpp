cmake_minimum_required(VERSION 3.22)

project(gen VERSION 1.0 DESCRIPTION "idk something spotify thing")

include_directories(${CMAKE_SOURCE_DIR}/headers)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Boost REQUIRED COMPONENTS system thread)
find_package(OpenSSL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} 
    ${Boost_LIBRARIES} 
    OpenSSL::SSL 
    OpenSSL::Crypto
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
