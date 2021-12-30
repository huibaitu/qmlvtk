cmake_minimum_required(VERSION 3.12)

Project(qmlvtk)

find_package(VTK REQUIRED)

# if GDCM is not used, please remove the next two lines.
find_package(GDCM REQUIRED)
include(${GDCM_USE_FILE})

find_package(Qt6 COMPONENTS Quick Qml REQUIRED)
set(QT_LIBRARIES Qt6::Quick Qt6::Qml)
set(CMAKE_AUTORCC ON)

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/config.h"
  )

file(GLOB H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB QML_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qml)
file(GLOB QRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)

 add_executable(${PROJECT_NAME} ${H_FILES} ${CPP_FILES} ${QML_FILES} ${QRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${VTK_LIBRARIES} ${QT_LIBRARIES})