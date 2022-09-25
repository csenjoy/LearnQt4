#Define Global Function to find qt
set(LearnQtVersion "Qt5")

message(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")

message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

set(QT_CMAKE_MODULE_PATH "C:/Qt/Qt5.12.12/5.12.12/mingw73_64/lib")
macro(get_qt_mingw64_path)  
  set(QT_CMAKE_MODULE_PATH "C:/Qt/Qt5.12.12/5.12.12/mingw73_64/lib/cmake")
endmacro(get_qt_mingw64_path)

get_qt_mingw64_path()
message(STATUS "QT_CMAKE_MODULE_PATH: ${QT_CMAKE_MODULE_PATH}")

list(APPEND CMAKE_PREFIX_PATH ${QT_CMAKE_MODULE_PATH})

find_package(${LearnQtVersion} REQUIRED 
    COMPONENTS Core 
               Widgets
)