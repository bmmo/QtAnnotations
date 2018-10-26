cmake_minimum_required VERSION 3.1 )

project ( QtAnnotations )

### Parameters
# CMake
set ( CMAKE_MODULE_PATH  ${PROJECT_SOURCE_DIR}/cmake )
set ( CMAKE_CXX_STANDARD  11 )
include ( BuildLocation )


### Packages
find_package ( Qt5Core        REQUIRED ) 
find_package ( Qt5Gui         REQUIRED ) 
find_package ( Qt5Widgets     REQUIRED ) 
find_package ( Qt5OpenGL      REQUIRED ) 

find_package ( OpenSceneGraph REQUIRED osgViewer osgGA osgDB )

find_package ( Threads        REQUIRED ) 
find_package ( OpenGL         REQUIRED )


# Configure Qt
set ( CMAKE_AUTORCC              ON )
set ( CMAKE_INCLUDEC_CURRENT_DIR ON )
set ( QT_USE_QTOPENGL            TRUE )

add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Gui_DEFINITIONS})
add_definitions(${Qt5OpenGL_DEFINITIONS})
add_definitions(${Qt5Xml_DEFINITIONS})


