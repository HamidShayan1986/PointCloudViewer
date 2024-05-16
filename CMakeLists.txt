##########################################################################
cmake_minimum_required(VERSION 3.22)

set(programName PointCloudViewer)

project(${programName})
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
#SET(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
##########################################################################
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package (Qt5OpenGL REQUIRED)
find_package (Qt5Gui REQUIRED)
find_package (Qt5Network REQUIRED)

find_package(OpenGL)
find_package(GLUT)

set(CMAKE_AUTOMOC ON) # handle the Qt moc preprocessor automatically
##########################################################################

set(installDir "${CMAKE_CURRENT_BINARY_DIR}")


set(IncludePath
    ./.

    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Network_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
    )


set(LibFiles
    GL

    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Network
    Qt5::OpenGL
    )

set(LibPath
    ./.
    )


set(CppFiles
    ./Camera.cpp 
    ./PointCloud.cpp 
    ./ShaderPrograms.cpp 
    ./ViewerWidget.cpp 
    ./main.cpp 
    ./MainWindow.cpp
    )

set (MocHeaderFiles
    ./Camera.h 
    ./MainWindow.h 
    ./PointCloud.h 
    ./ShaderPrograms.h 
    ./ViewerWidget.h
    )

set(UiFiles
    ./MainWindow.ui
    )

set(ResFiles
    ./Resource/Shader/CommonShaders.qrc
    )


# using Qt meta-system (precompiler)
QT5_ADD_RESOURCES( RES_SOURCES ${ResFiles} )
QT5_WRAP_UI( UI_HEADERS ${UiFiles} )
QT5_WRAP_CPP( MOC_SRCS ${MocHeaderFiles} )


#add "./icon.rc" to target -> set target icon
#add WIN32 -> Skip showing console window
add_executable(${programName} ${CppFiles} ${MocHeaderFiles}  ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )
target_include_directories(${programName} PUBLIC "." ${IncludePath})
target_link_directories(${programName} PUBLIC "." ${LibPath})

target_link_libraries (${programName}  ${LibFiles})

install(TARGETS ${programName} DESTINATION "${installDir}")
#################################################

