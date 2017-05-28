set(src_game
	GameMenu.cpp
	GameMenu.h
	Game.cpp
	Game.h
)
add_library(Game ${src_game})
target_link_libraries (Game SystemInterface OSDataFile GFXInterface ReturnData)

