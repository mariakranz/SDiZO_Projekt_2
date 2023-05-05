cmake_minimum_required(VERSION 3.25)
project(SDiZO_Projekt_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(SDiZO_Projekt_2 main.cpp GraphImpl.cpp GraphImpl.h LinkedList.cpp LinkedList.h FileData.cpp FileData.h PriorityQueue.cpp PriorityQueue.h MST.cpp MST.h)
