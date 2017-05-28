set(src_functions
	To.cpp
	To.h
	Timer.cpp
	Timer.h
	iconv.cpp
	iconv.h
	File/Open.cpp
	File/Open.h
	File/DataReader.cpp
	File/DataReader.h
	File/Functions.cpp
	File/Functions.h
	File/Run.cpp
	File/Run.h
	File/Save.cpp
	File/Save.h
	File/TextFile.cpp
	File/TextFile.h
	Audio/WAVData.cpp
	Audio/WAVData.h
	Audio/XMIDIData.cpp
	Audio/XMIDIData.h
	Image/RGBA.cpp
	Image/RGBA.h
	Image/Palette.cpp
	Image/Palette.h
	Image/PaletteData.cpp
	Image/PaletteData.h
	Image/ConvertPALtoRGB.cpp
	Image/ConvertPALtoRGB.h
	Image/FileImage.cpp
	Image/FileImage.h
	Image/Files/BMPv2.cpp
	Image/Files/BMPv4.cpp
	Image/Files/PNG.cpp
	Image/RGBImage.cpp
	Image/RGBImage.h
	Image/PaletteImage.cpp
	Image/PaletteImage.h
)

add_library(Functions ${src_functions})
target_link_libraries (Functions LogSystem)
if(ICONV_FOUND)
	target_link_libraries (Functions ${ICONV_LIBRARIES})
	message ( STATUS "ICONV_L:" ${ICONV_LIBRARIES})
endif(ICONV_FOUND)
if(PNG_FOUND)
	target_link_libraries (Functions ${PNG_LIBRARIES})
	message ( STATUS "PNG_L:" ${PNG_LIBRARIES})
endif(PNG_FOUND)