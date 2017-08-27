set(src_gfxinterface
	GFXItems/GFXBox.cpp
	GFXItems/GFXBox.h
	GFXItems/GFXButton.cpp
	GFXItems/GFXButton.h
	GFXItems/GFXImage.cpp
	GFXItems/GFXImage.h
	GFXItems/GFXItem.cpp
	GFXItems/GFXItem.h
	GFXItems/GFXSpacer.cpp
	GFXItems/GFXSpacer.h
	GFXItems/GFXText.cpp
	GFXItems/GFXText.h
	GFXMenu.cpp
	GFXMenu.h
	GFXLoadingScreen.cpp
	GFXLoadingScreen.h
)
add_library(GFXInterface ${src_gfxinterface})
target_link_libraries (GFXInterface MenuEvents ReturnData Functions SystemInterface OSDataFile)