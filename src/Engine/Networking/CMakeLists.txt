# Add files in this folder
add_library(lib6 NetworkAgent.cpp
				NetworkClient.cpp
				NetworkServer.cpp
				Packet.cpp)
target_include_directories (lib6 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


