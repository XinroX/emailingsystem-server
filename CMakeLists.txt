cmake_minimum_required(VERSION 3.14)

project(emailingsystem-server LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Qt5_DIR "/home/mateusz/Qt/5.15.2/gcc_64/lib/cmake/Qt5")
set(QT_DIR "/home/mateusz/Qt/5.15.2/gcc_64/lib/cmake/Qt5")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(AddGitSubmodule)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)
find_package(GTest CONFIG REQUIRED)

set(GMOCK_LIBRARIES /usr/local/lib/libgmock.a	/usr/local/lib/libgmock_main.a)
#set(POSTGRES_LIBRARIES /Applications/Postgres.app/Contents/Versions/14/bin)

set(SOURCE_FILES
    serverservice.h serverservice.cpp
    dbconnection.h dbconnection.cpp
    IDbConnection.h receiver.h
)
add_executable(emailingsystem-server
  ${SOURCE_FILES} main.cpp
  #tests.cpp
)

add_executable(testServer ${SOURCE_FILES} tests.h tests.cpp)

add_git_submodule(external/core)


target_link_libraries(emailingsystem-server Qt${QT_VERSION_MAJOR}::Core Qt5::Sql
    core)

target_link_libraries(testServer Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql
    core GTest::gtest_main ${GMOCK_LIBRARIES})

install(TARGETS emailingsystem-server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
#set(PRECOMPILED_HEADERS_PATH external/core)
#set(PRECOMPILED_HEADERS ${PRECOMPILED_HEADERS_PATH}/message.h)
#target_precompile_headers(emailingsystem-server PUBLIC ${PRECOMPILED_HEADERS})
