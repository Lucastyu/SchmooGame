cmake_minimum_required(VERSION 3.10)
project(SchmooGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавим определение операционной системы
if(CMAKE_SYSTEM_NAME MATCHES "NetBSD")
    add_definitions(-DNETBSD)
    # Добавим специфичные для NetBSD флаги компиляции, если потребуется
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

option(BUILD_WEB_VERSION "Build web version" OFF)
option(BUILD_TESTS "Build tests" OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CORE_SOURCES
    src/schmoo.cpp
)

# Добавим отдельную цель для NetBSD
if(CMAKE_SYSTEM_NAME MATCHES "NetBSD")
    add_executable(schmoo_netbsd
        ${CORE_SOURCES}
        src/console_main.cpp
    )
else()
    # Остальные цели сборки остаются без изменений
    if(BUILD_TESTS)
        add_executable(schmoo_test
            ${CORE_SOURCES}
            src/test_main.cpp
            src/test_interface.cpp
        )
    endif()

    if(BUILD_WEB_VERSION)
        if(NOT EMSCRIPTEN)
            message(FATAL_ERROR "Emscripten required for web version")
        endif()
        
        add_executable(schmoo_web
            ${CORE_SOURCES}
            src/web_main.cpp
        )
        
        set_target_properties(schmoo_web PROPERTIES
            SUFFIX ".html"
            LINK_FLAGS "
                -s WASM=1 
                -s USE_SDL=2 
                -s EXPORTED_FUNCTIONS=['_main'] 
                -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap']
            "
        )
    else()
        add_executable(schmoo_console
            ${CORE_SOURCES}
            src/console_main.cpp
        )
    endif()
endif()