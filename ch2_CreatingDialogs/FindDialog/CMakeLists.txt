project(finddialog)

include(LearnQtHelpers)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
  PROPERTIES AUTOMOC ON
)

target_sources(${PROJECT_NAME}
  PRIVATE main.cc
          FindDialog.h
          FindDialog.cc
)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE ${LearnQtVersion}::Core
          ${LearnQtVersion}::Widgets
)