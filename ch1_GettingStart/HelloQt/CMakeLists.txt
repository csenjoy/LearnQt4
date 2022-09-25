project(helloqt)

include(LearnQtHelpers)

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
  PRIVATE ${LearnQtVersion}::Core
          ${LearnQtVersion}::Widgets
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES AUTOMOC ON
             AUTOUIC ON
             AUTORCC ON
             AUTOUIC_SEARCH_PATHS "forms"
)

target_sources(${PROJECT_NAME}
  PRIVATE main.cc
)
