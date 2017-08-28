set(src_osdatafile
	APILEVELS.h
	eTypes.h
	FileTypes/FileTypes.cpp
	FileTypes/FileTypes.h
	FileTypes/GameData.cpp
	FileTypes/GameData.h
	FileTypes/Layout/GUIItems/GUIBoxData.cpp
	FileTypes/Layout/GUIItems/GUIBoxData.h
	FileTypes/Layout/GUIItems/GUIBoxDirectoryData.cpp
	FileTypes/Layout/GUIItems/GUIBoxDirectoryData.h
	FileTypes/Layout/GUIItems/GUIButtonData.cpp
	FileTypes/Layout/GUIItems/GUIButtonData.h
	FileTypes/Layout/GUIItems/GUIButtonTypeData.cpp
	FileTypes/Layout/GUIItems/GUIButtonTypeData.h
	FileTypes/Layout/GUIItems/GUIImageData.cpp
	FileTypes/Layout/GUIItems/GUIImageData.h
	FileTypes/Layout/GUIItems/GUIItemData.cpp
	FileTypes/Layout/GUIItems/GUIItemData.h
	FileTypes/Layout/GUIItems/GUIItemNew.cpp
	FileTypes/Layout/GUIItems/GUIItemNew.h
	FileTypes/Layout/GUIItems/GUISpacerData.cpp
	FileTypes/Layout/GUIItems/GUISpacerData.h
	FileTypes/Layout/GUIItems/GUITextData.cpp
	FileTypes/Layout/GUIItems/GUITextData.h
	FileTypes/Layout/GUIItems/GUIVisibilityData.cpp
	FileTypes/Layout/GUIItems/GUIVisibilityData.h
	FileTypes/Layout/GUIItems/ImageData.cpp
	FileTypes/Layout/GUIItems/ImageData.h
	FileTypes/Layout/MenuLayout.cpp
	FileTypes/Layout/MenuLayout.h
	FileTypes/Layout/LoadingScreenLayout.cpp
	FileTypes/Layout/LoadingScreenLayout.h
	FileTypes/GameOptions.cpp
	FileTypes/GameOptions.h
	FileTypes/GameType.cpp
	FileTypes/GameType.h
	FileTypes/MapSetup/MapSetup.cpp
	FileTypes/MapSetup/MapSetup.h
	OSDataFile.cpp
	OSDataFile.h
)

add_library(OSDataFile ${src_osdatafile})

target_link_libraries (OSDataFile Functions LogSystem MenuEvents ReturnData)
if(LIBXML2_FOUND)
	target_link_libraries (OSDataFile ${LIBXML2_LIBRARIES})
	message ( STATUS "LIBXML2_L:" ${LIBXML2_LIBRARIES})
endif(LIBXML2_FOUND)