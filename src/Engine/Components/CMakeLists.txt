# Add files in this folder
add_library(lib3 Component.cpp
				Collider.cpp
				Navigator.cpp
				TextureRenderer.cpp
				Transform.cpp)
target_include_directories (lib3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


