cmake_minimum_required ( VERSION 3.10 )

project ( QtAnnotations )

### Parameters
# CMake
set ( CMAKE_MODULE_PATH         ${PROJECT_SOURCE_DIR}/cmake )
set ( CMAKE_GENERATOR_PLATFORM "x64" CACHE STRING "Target x86 or x64" )
set ( OSG_DIR                  "C:/" CACHE PATH   "OpenSceneGraph root install directory" )


include ( BuildLocation )


### Packages
# find_package ( Qt5Core        REQUIRED ) 
# find_package ( Qt5Gui         REQUIRED ) 
# find_package ( Qt5Widgets     REQUIRED ) 
# find_package ( Qt5OpenGL      REQUIRED ) 
find_package ( Qt5 COMPONENTS Core Gui Widgets OpenGL REQUIRED )

find_package ( OpenSceneGraph REQUIRED osgViewer osgGA osgDB )

find_package ( Threads        REQUIRED ) 
find_package ( OpenGL         REQUIRED )


# Configure Qt
set ( CMAKE_INCLUDE_CURRENT_DIR  ON )
set ( CMAKE_AUTOMOC              ON )
set ( QT_USE_QTOPENGL            TRUE )

add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Gui_DEFINITIONS})
add_definitions(${Qt5OpenGL_DEFINITIONS})


file(GLOB SOURCES src/*.cpp)
# https://stackoverflow.com/questions/37151163/cmake-automoc-with-files-on-different-folders
file(GLOB HEADERS include/*.h)

add_executable ( QtAnnotations 
	${SOURCES}
	${HEADERS}
)

target_link_libraries ( QtAnnotations
	${OPENSCENEGRAPH_LIBRARIES}
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	Qt5::OpenGL
)

target_include_directories ( QtAnnotations
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${OPENSCENEGRAPH_INCLUDE_DIRS}
)

# generate proper GUI program on specified platform
if(WIN32) # Check if we are on Windows
	if(MSVC) # Check if we are using the Visual Studio compiler
		set_target_properties(QtAnnotations PROPERTIES
			WIN32_EXECUTABLE YES
			LINK_FLAGS "/ENTRY:mainCRTStartup"
		)
	elseif(CMAKE_COMPILER_IS_GNUCXX)
			# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
	else()
		message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
	endif(MSVC)
elseif(APPLE)
	set_target_properties( QtAnnotations PROPERTIES
			MACOSX_BUNDLE YES
	)
elseif(UNIX)
	# Nothing special required
else()
	message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
endif(WIN32)


set_property ( TARGET QtAnnotations PROPERTY CXX_STANDARD          11 )
set_property ( TARGET QtAnnotations PROPERTY CXX_STANDARD_REQUIRED ON )


install( TARGETS  QtAnnotations RUNTIME DESTINATION bin )
