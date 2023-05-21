cmake_minimum_required(VERSION 3.25)
project(SDiZO_Projekt_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(SDiZO_Projekt_2 main.cpp data/FileData.cpp data/FileData.h structures/PriorityQueue.cpp structures/PriorityQueue.h structures/Set.cpp structures/Set.h interfaces/ShortestPathMenu.cpp interfaces/ShortestPathMenu.h graphs/UndirectedGraph.cpp graphs/UndirectedGraph.h graphs/DirectedGraph.cpp graphs/DirectedGraph.h graphs/Graph.cpp graphs/Graph.h interfaces/MSTMenu.cpp interfaces/MSTMenu.h interfaces/GraphRepresentations.cpp interfaces/GraphRepresentations.h data/TimeTests.cpp data/TimeTests.h)
