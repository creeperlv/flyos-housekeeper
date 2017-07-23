cmake_minimum_required(VERSION 3.7)
project(flyos_housekeeper)

set(CMAKE_CXX_STANDARD 11)

#qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
#find_package(Qt5Network REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories("/usr/include/libdtk-1.0/DBase")
include_directories("/usr/include/libdtk-1.0/DUtil")
include_directories("/usr/include/libdtk-1.0/DWidget")

set(QRC_FILES styles/styles.qrc
        images/images.qrc)

set(SOURCE_FILES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        SuspensionWidget.cpp
        SuspensionWidget.h
        getInfo.cpp
        getInfo.h

        base/fileUtil.cpp
        base/fileUtil.h)
set(UI_FILES
        widgets/imageItem.cpp
        widgets/imageItem.h
        widgets/rootWidget.cpp
        widgets/rootWidget.h

        widgets/homeWidget.cpp
        widgets/homeWidget.h)

add_executable(flyos-housekeeper ${SOURCE_FILES} ${UI_FILES} ${QRC_FILES})

target_link_libraries(flyos-housekeeper Qt5::Widgets Qt5::Gui Qt5::Core dtkbase dtkwidget)