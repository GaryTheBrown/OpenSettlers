set(src_systeminterface
	Display.h
	Events.h
	Fonts.h
	ImageContainer.h
	System.h
)
set(src_systeminterface_SDL2
	SDL2/SDL2Display.cpp
	SDL2/SDL2Display.h
	SDL2/SDL2Events.cpp
	SDL2/SDL2Events.h
	SDL2/SDL2Fonts.cpp
	SDL2/SDL2Fonts.h
	SDL2/SDL2ImageContainer.cpp
	SDL2/SDL2ImageContainer.h
	SDL2/SDL2System.cpp
	SDL2/SDL2System.h
)
set(src_systeminterface ${src_systeminterface} ${src_systeminterface_SDL2})

set(src_systeminterface_OGL21
	OGL21/OGL21Display.cpp
	OGL21/OGL21Display.h
	OGL21/OGL21ImageContainer.cpp
	OGL21/OGL21ImageContainer.h
	OGL21/OGL21System.cpp
	OGL21/OGL21System.h
)
set(src_systeminterface ${src_systeminterface} ${src_systeminterface_OGL21})

add_library(SystemInterface ${src_systeminterface})
target_link_libraries (SystemInterface Functions)
target_link_libraries(SystemInterface ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_link_libraries (SystemInterface ${OPENGL_LIBRARIES})
message ( STATUS "OPENGL_L:" ${OPENGL_LIBRARIES})