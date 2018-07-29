# Add files in this folder
add_library(lib2 GameObject.cpp
				Scene.cpp
				Texture.cpp
				Updateable.cpp)
target_include_directories (lib2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add subfolder
add_subdirectory(Components)
add_subdirectory(GUI)
add_subdirectory(Managers)
add_subdirectory(Networking)
add_subdirectory(Util)

