cmake_minimum_required(VERSION 3.20)
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

# --- Fetch FTXUI --------------------------------------------------------------

FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        )

FetchContent_GetProperties(ftxui)
if (NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()

# ------------------------------------------------------------------------------

# --- Fetch PyBind11 --------------------------------------------------------------

FetchContent_Declare(pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11
        )

FetchContent_GetProperties(pybind11)
if (NOT pybind11_POPULATED)
    FetchContent_Populate(pybind11)
    add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()

# ------------------------------------------------------------------------------
project(app_arbore_binar)

set(CMAKE_CXX_STANDARD 17)

add_executable(app_arbore_binar src/main.cpp lib/ArboreBinar.cpp lib/ArboreBinar.h src/utilitare.cpp src/utilitare.h src/componente.h src/componente.cpp src/globale.h)
target_include_directories(app_arbore_binar PRIVATE src)
target_link_libraries(app_arbore_binar
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
        PRIVATE pybind11::embed
        )

set(GCC_COVERAGE_COMPILE_FLAGS "-fvisibility=hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
