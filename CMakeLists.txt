cmake_minimum_required(VERSION 3.22)
project(learning)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/include/)
#add_library(test
#        "${CMAKE_SOURCE_DIR}/src/FileReader.cpp"
#        "${CMAKE_SOURCE_DIR}/src/IFile.cpp"
#        "${CMAKE_SOURCE_DIR}/src/ISocket.cpp"
#        "${CMAKE_SOURCE_DIR}/src/IWorker.cpp"
#        )

#set(Headers
#        "include/definitions.h"
#        "include/FileReader.h"
#        "include/IFile.h"
#        "include/IHandler.h"
#        "include/IObserver.h"
#        "include/ISocket.h"
#        "include/IWorker.h"
#        )
include_directories(${PROJECT_SOURCE_DIR})
set(Src
        "src/FileReader.cpp"
        "src/IFile.cpp"
        "src/ISocket.cpp"
        "src/IWorker.cpp"
        )


file(GLOB SRC
        "src/FileReader.cpp"
        "src/IFile.cpp"
        "src/ISocket.cpp"
        "src/IWorker.cpp"
        "src/FileWriter.cpp"
        )

add_executable(file_transfer main.cpp ${SRC})
