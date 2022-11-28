cmake_minimum_required(VERSION 3.12)
project(sms)

set(CMAKE_CXX_STANDARD 14)

IF(WIN32)
    set(JAVA_HOME C:/Program Files/Java/jdk-11.0.14)
    set(JAVA_INCLUDE_PATH2 ${JAVA_HOME}/include/win32)
    link_directories(${JAVA_HOME}/lib)
ELSEIF(APPLE)
    set(JAVA_HOME /Library/Java/JavaVirtualMachines/jdk-11.0.16.jdk/Contents/Home)
    set(JAVA_INCLUDE_PATH2 ${JAVA_HOME}/include/darwin)
    set(INSTALL_LIBDIR /usr/local/lib)
    link_directories(${JAVA_HOME}/lib/server)
ELSE()
    set(JAVA_HOME /usr/lib/jvm/java-11-openjdk)
    set(JAVA_INCLUDE_PATH2 ${JAVA_HOME}/include/linux)
    set(INSTALL_LIBDIR /usr/lib)
    link_directories(${JAVA_HOME}/lib/server)
ENDIF()
set(JAVA_AWT_INCLUDE_PATH ${JAVA_HOME}/include)
set(JAVA_INCLUDE_PATH ${JAVA_HOME}/include)
find_package(JNI REQUIRED)

include_directories(${JAVA_INCLUDE_PATH})
include_directories(${JAVA_INCLUDE_PATH2})

add_library(ump SHARED ump.cpp)
target_link_libraries(ump jvm)

add_executable(sms main.cpp)
target_link_libraries(sms ump)

set_target_properties(ump PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)
install(TARGETS ump
        LIBRARY DESTINATION ${INSTALL_LIBDIR})