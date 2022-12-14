cmake_minimum_required(VERSION 3.24)

project(RumblingCounts)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -- Load Allegro 5
include(FetchContent)

FetchContent_Declare(
    allegro5
    GIT_REPOSITORY https://github.com/liballeg/allegro5.git
    GIT_TAG        5.2.8.0
)

FetchContent_GetProperties(allegro5)

if(NOT allegro5_POPULATED)
    FetchContent_Populate(allegro5)

	if (MSVC)
		set(SHARED ON)
	else()
		set(SHARED OFF)
	endif()

    set(WANT_MONOLITH OFF)
	set(WANT_TESTS OFF)
	set(WANT_EXAMPLES OFF)
	set(WANT_DEMO OFF)

    add_subdirectory(${allegro5_SOURCE_DIR} ${allegro5_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

file(COPY ${allegro5_SOURCE_DIR}/addons/font/allegro5/allegro_font.h
	DESTINATION ${allegro5_SOURCE_DIR}/include/allegro5
)
file(COPY ${allegro5_SOURCE_DIR}/addons/image/allegro5/allegro_image.h
	DESTINATION ${allegro5_SOURCE_DIR}/include/allegro5
)
file(COPY ${allegro5_SOURCE_DIR}/addons/primitives/allegro5/allegro_primitives.h
	DESTINATION ${allegro5_SOURCE_DIR}/include/allegro5
)

# -- Executable
FILE(GLOB_RECURSE APP_SOURCES src/*.c bin/main.c)
add_executable(RumblingCounts ${APP_SOURCES})
target_include_directories(RumblingCounts PUBLIC ${allegro5_SOURCE_DIR}/include)
target_include_directories(RumblingCounts PUBLIC ${allegro5_BINARY_DIR}/include)
target_include_directories(RumblingCounts PRIVATE src)
target_link_libraries(
        RumblingCounts 
        LINK_PUBLIC 
        allegro allegro_main allegro_font allegro_primitives allegro_image
    )


# -- Tests
FILE(GLOB_RECURSE TEST_SOURCES src/*.c tests/*.c bin/test.c)
add_executable(RunTests ${TEST_SOURCES})
target_include_directories(RunTests PUBLIC ${allegro5_SOURCE_DIR}/include)
target_include_directories(RunTests PUBLIC ${allegro5_BINARY_DIR}/include)
target_include_directories(RunTests PRIVATE src tests)
target_link_libraries(
        RunTests 
        LINK_PUBLIC 
        allegro allegro_main allegro_font allegro_primitives allegro_image
    )

file(COPY tests/data DESTINATION tests)
