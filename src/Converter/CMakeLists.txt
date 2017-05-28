set(src_converter

	Settlers3/Convert.cpp
	Settlers3/Convert.h
	Settlers3/ConvertData.h
	Settlers3/Converter_Landscape.cpp
	Settlers3/Converter_MapObjects.cpp
	Settlers3/SetupData.cpp
	Settlers3/GUI/ConvertGUI.h
	Settlers3/GUI/MenusAndLoadingScreens/Original.cpp
	Settlers3/GUI/MenusAndLoadingScreens/MissionCD.cpp
	Settlers3/GUI/MenusAndLoadingScreens/Amazon.cpp
	Settlers3/GUI/MenusAndLoadingScreens/Gold.cpp

	Converter.cpp
	Converter.h
)
add_library(Converter ${src_converter})
target_link_libraries (Converter LogSystem Functions Extractor OSDataFile)
