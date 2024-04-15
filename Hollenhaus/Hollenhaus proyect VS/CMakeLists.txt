set(PROJECT_NAME HollenhausproyectVS)
add_compile_definitions(_DEBUG)
project(HollenhausproyectVS)

include(vcxproj_list.cmake)

################################################################################
# Target
################################################################################
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

add_executable(${PROJECT_NAME} ${vcxproj_src})
target_include_directories( ${PROJECT_NAME} INTERFACE "src" )
target_include_directories( ${PROJECT_NAME} PUBLIC "src/game" )
target_include_directories( ${PROJECT_NAME} INTERFACE "src/game" )
#target_include_directories( ${PROJECT_NAME} PUBLIC "src/game/components" )
#target_include_directories( ${PROJECT_NAME} PUBLIC "src/game/components/basics" )
#target_include_directories( ${PROJECT_NAME} PUBLIC "src/game/components/managers" )
#target_include_directories( ${PROJECT_NAME} PUBLIC "src/game/factories" )
#target_include_directories( ${PROJECT_NAME} PUBLIC "src/game/gamestates" )
#target_include_directories( ${PROJECT_NAME} PUBLIC "src/utils" )
#target_include_directories( ${PROJECT_NAME} PUBLIC "src/sdlutils" )
#target_include_directories( ${PROJECT_NAME} PUBLIC "src/json" )
target_link_libraries(${PROJECT_NAME} SDL2 SDL2_mixer SDL2_image SDL2_ttf)
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2main)
endif()

target_link_libraries(${PROJECT_NAME} SDL2::SDL2)


target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/game/pch.h>"
)

#use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
#if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
#    use_props(${PROJECT_NAME} Debug   "../Hollenhaus.cmake")
#    use_props(${PROJECT_NAME} Release "../Hollenhaus.cmake")
#elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
#    use_props(${PROJECT_NAME} Debug   "../Hollenhaus.cmake")
#    use_props(${PROJECT_NAME} Release "../Hollenhaus.cmake")
#endif()

set(ROOT_NAMESPACE Practica1TPV)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "SFML_STATIC;"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################

target_compile_options(${PROJECT_NAME} PRIVATE
    -std=c++17
    -W
    -g
)
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /std:c++17
            >
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        string(CONCAT FILE_CL_OPTIONS
            "/Y-"
        )
    endif()
    source_file_compile_options(src/game/GenID.cpp ${FILE_CL_OPTIONS})
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /SUBSYSTEM:CONSOLE
            >
            $<$<CONFIG:Release>:
                /SUBSYSTEM:WINDOWS;
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

