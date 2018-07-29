# Add files in this folder
add_library(lib Ball.cpp
				Counter.cpp
				Game.cpp
				MainMenu.cpp
				Player.cpp
				PlayerAI.cpp
				Scoreboard.cpp
				ScoreBoardNumberDisplay.cpp
				WinAlert.cpp)
target_include_directories (lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add subfolder
add_subdirectory(Engine)


