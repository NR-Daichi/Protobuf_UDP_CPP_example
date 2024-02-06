cmake_minimum_required(VERSION 3.27)
project(protocol_buffer)
find_package(protobuf CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
add_library(udpConnector udpConnector.cpp udpConnector.h)
add_library(addressbook addressbook.pb.cc addressbook.pb.h)

add_executable(protocol_buffer main.cpp)

target_link_libraries(udpConnector PRIVATE protobuf::libprotobuf)
target_link_libraries(protocol_buffer PUBLIC udpConnector
                        addressbook)