cmake_minimum_required(VERSION 3.15)

project("demo-application"
    VERSION 0.2.3
    DESCRIPTION "A project with nested library"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp)


# BLADE-CPP SDK
add_subdirectory(libraries/blade-cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE blade-cpp)

find_package(gRPC CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE c-ares::cares)
include_directories(${CMAKE_BINARY_DIR}/_deps/hedera-sdk-cpp-src/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_HOST_SYSTEM_PROCESSOR}/include)

install(FILES
        ${CMAKE_SOURCE_DIR}/libraries/blade-cpp/assets/mainnet.pb
        ${CMAKE_SOURCE_DIR}/libraries/blade-cpp/assets/previewnet.pb
        ${CMAKE_SOURCE_DIR}/libraries/blade-cpp/assets/testnet.pb
        DESTINATION bin/addressbook)

# /BLADE-CPP SDK


# Install Library & Headers
install(TARGETS ${PROJECT_NAME} 
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
