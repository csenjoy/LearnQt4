project(gotocelldialog)

include(LearnQtHelpers)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
  PROPERTIES AUTOMOC ON
             AUTOUIC ON
             AUTOUIC_SEARCH_PATHS "forms"
)

target_sources(${PROJECT_NAME}
  PRIVATE main.cc
          GoToCellDialog.h
          GoToCellDialog.cc
)

#target ui source
target_sources(${PROJECT_NAME}
  PRIVATE forms/GoToCellDialog.ui
)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE ${LearnQtVersion}::Core
          ${LearnQtVersion}::Widgets
)