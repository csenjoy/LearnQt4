project(shapechangingdialog)

include(LearnQtHelpers)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
  PRIVATE main.cc
          SortDialog.h
          SortDialog.cc
)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE ${LearnQtVersion}::Core
          ${LearnQtVersion}::Widgets
)