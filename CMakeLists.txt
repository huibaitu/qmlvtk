cmake_minimum_required(VERSION 3.12)

Project(qmlvtk)

find_package(VTK REQUIRED)

find_package(Qt6
  COMPONENTS Quick Qml
  REQUIRED
  )

set(CMAKE_AUTORCC ON)

file(GLOB cpp_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)


message("${CMAKE_CURRENT_SOURCE_DIR}")

set(qml_files qmlvtk.qml)

foreach (qml_file IN LISTS qml_files)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${qml_file}"
    "${CMAKE_CURRENT_BINARY_DIR}/${qml_file}"
    @ONLY)
endforeach ()

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.qrc"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.qrc"
  COPYONLY)

  add_executable(${PROJECT_NAME} ${cpp_files}
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.qrc"
  )

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  ${VTK_LIBRARIES}
    "Qt6::Quick"
    "Qt6::Qml"
    )