project(Spreadsheet)

include(LearnQtHelpers)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
  PROPERTIES AUTOMOC ON
             AUTORCC ON
             AUTOUIC ON
             AUTOUIC_SEARCH_PATHS "ch2_CreatingDialogs/GotoCellDialog/forms;ch2_CreatingDialogs/ShapeChangingDialog/forms" 
)

target_sources(${PROJECT_NAME}
  PRIVATE main.cc
          cell.h
          cell.cc
          mainwindow.h
          mainwindow.cc
          spreadsheet.h
          spreadsheet.cc
          ch2_CreatingDialogs/FindDialog/FindDialog.h
          ch2_CreatingDialogs/FindDialog/FindDialog.cc

          ch2_CreatingDialogs/GotoCellDialog/GotoCellDialog.h
          ch2_CreatingDialogs/GotoCellDialog/GotoCellDialog.cc

          ch2_CreatingDialogs/ShapeChangingDialog/SortDialog.h
          ch2_CreatingDialogs/ShapeChangingDialog/SortDialog.cc
)

target_sources(${PROJECT_NAME}
  PRIVATE ch2_CreatingDialogs/GotoCellDialog/forms/GotoCellDialog.ui
          ch2_CreatingDialogs/ShapeChangingDialog/forms/SortDialog.ui     
)

target_sources(${PROJECT_NAME}
  PRIVATE spreadsheet.qrc
)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE ${LearnQtVersion}::Core
          ${LearnQtVersion}::Widgets
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ch2_CreatingDialogs/FindDialog
         ${CMAKE_CURRENT_SOURCE_DIR}/ch2_CreatingDialogs/GotoCellDialog
         ${CMAKE_CURRENT_SOURCE_DIR}/ch2_CreatingDialogs/ShapeChangingDialog
)