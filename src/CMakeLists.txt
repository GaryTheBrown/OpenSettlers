set(src_Log
	Log.cpp
	Log.h
	LogSystem/LogSystem.cpp
	LogSystem/LogSystem.h
)
add_library(LogSystem ${src_Log})

add_subdirectory(Functions)

set(src_Config
	ConfigTemplate.h
	ConfigList.cpp
	ConfigList.h
)
add_library(Config ${src_Config})
target_link_libraries (Config Functions LogSystem)

set(src_MenuEvents
	MenuEvents.cpp
	MenuEvents.h
)
add_library(MenuEvents ${src_MenuEvents})

set(src_ReturnData
	ReturnData.cpp
	ReturnData.h
)
add_library(ReturnData ${src_ReturnData})
target_link_libraries (ReturnData Functions MenuEvents)

set(src_StartMenu
	StartMenu.cpp
	StartMenu.h

)
add_library(StartMenu ${src_StartMenu})
target_link_libraries (StartMenu SystemInterface MenuEvents ReturnData OSDataFile GFXInterface)

add_subdirectory(Extractor)
add_subdirectory(SystemInterface)
add_subdirectory(OSDataFile)
add_subdirectory(GFXInterface)
add_subdirectory(Converter)
add_subdirectory(Game)

set(OpenSettlers_src_src
	config.h
	StartupArguments.cpp
	StartupArguments.h
	main.cpp
	main.h
)
add_executable(OpenSettlers ${OpenSettlers_src_src})
target_link_libraries (OpenSettlers LogSystem Config Converter Extractor SystemInterface StartMenu MenuEvents OSDataFile Game ReturnData Functions)