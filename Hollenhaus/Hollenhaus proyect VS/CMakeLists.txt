set(PROJECT_NAME HollenhausproyectVS)
add_compile_definitions(_DEBUG)
project(HollenhausproyectVS)

#macro(addAllSubDirectory subDir)
#    message("include ./${CMAKE_CURRENT_SOURCE_DIR}/${subDir}")
#    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/${subDir})
#    FILE(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${subDir} ${CMAKE_CURRENT_SOURCE_DIR}/${subDir}/*)
#    foreach(child ${children})
#        if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${subDir}/${child})
#            addAllSubDirectory(${subDir}/${child})
#        endif()
#    endforeach()
#endmacro()

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "src/game/components/Animation.cpp"
    "src/game/components/Animation.h"
)
source_group("" FILES ${no_group_source_files})

set(Archivos_de_encabezado
    "src/game/Data.h"
    "src/game/Dialogue.h"
    "src/game/Game.h"
    "src/game/GameStateMachine.h"
    "src/game/Mouse.h"
    "src/game/Namespaces.h"
)
source_group("Archivos de encabezado" FILES ${Archivos_de_encabezado})

set(Archivos_de_encabezado__Auxiliares
    "pchs/pch_c++_basic.h"
    "pchs/pch_SDL.h"
    "src/game/checkML.h"
    "src/game/pch.h"
)
source_group("Archivos de encabezado\\Auxiliares" FILES ${Archivos_de_encabezado__Auxiliares})

set(Archivos_de_encabezado__Componentes
    "src/game/components/AutoDialogue.h"
    "src/game/components/Button.h"
    "src/game/components/Card.h"
    "src/game/components/Cell.h"
    "src/game/components/ColliderRender.h"
    "src/game/components/DeckComponent.h"
    "src/game/components/DialogueDestroyer.h"
    "src/game/components/DialogueEventCollection.h"
    "src/game/components/DialogueReader.h"
    "src/game/components/Drag.h"
    "src/game/components/DragNoCombat.h"
    "src/game/components/DropDetector.h"
    "src/game/components/DropZone.h"
    "src/game/components/EndTurnButton.h"
    "src/game/components/HandComponent.h"
    "src/game/components/managers/DrawerManager.h"
    "src/game/components/MoveOnClick.h"
    "src/game/components/NextText.h"
    "src/game/components/NPC.h"
    "src/game/components/ShopComponent.h"
    "src/game/components/TypeWriter.h"
    "src/game/EffectCollection.h"
)
source_group("Archivos de encabezado\\Componentes" FILES ${Archivos_de_encabezado__Componentes})

set(Archivos_de_encabezado__Componentes__Basicos
    "src/game/components/basics/BoxCollider.h"
    "src/game/components/basics/SpriteRenderer.h"
    "src/game/components/basics/TextComponent.h"
    "src/game/components/basics/Transform.h"
)
source_group("Archivos de encabezado\\Componentes\\Basicos" FILES ${Archivos_de_encabezado__Componentes__Basicos})

set(Archivos_de_encabezado__ECS
    "src/game/components/Component.h"
    "src/game/components/ComponentRender.h"
    "src/game/components/ComponentUpdate.h"
    "src/game/ecs.h"
    "src/game/Entity.h"
    "src/game/GenID.h"
)
source_group("Archivos de encabezado\\ECS" FILES ${Archivos_de_encabezado__ECS})

set(Archivos_de_encabezado__Factories
    "src/game/factories/BoardFactory.h"
    "src/game/factories/BoardFactory_v0.h"
    "src/game/factories/CardFactory.h"
#    "src/game/factories/CardFactory_v0.h"
    "src/game/factories/CardFactory_v1.h"
    "src/game/factories/DecisionFactory.h"
    "src/game/factories/DecisionFactory_V0.h"
    "src/game/factories/DialogueFactory.h"
    "src/game/factories/DialogueFactory_V0.h"
    "src/game/factories/Factory.h"
    "src/game/factories/FakeCardFactory.h"
#    "src/game/factories/FakeCardFactory_v0.h"
    "src/game/factories/MatchStateUIFactory.h"
    "src/game/factories/MatchStateUIFactory_v0.h"
    "src/game/factories/NPCFactory.h"
    "src/game/factories/NPCFactory_V0.h"
)
source_group("Archivos de encabezado\\Factories" FILES ${Archivos_de_encabezado__Factories})

set(Archivos_de_encabezado__GameStates
    "src/game/gamestates/AndresState.h"
    "src/game/gamestates/CityState.h"
    "src/game/gamestates/DeckBuildingState.h"
    "src/game/gamestates/GameState.h"
    "src/game/gamestates/JimboState.h"
    "src/game/gamestates/LuisState.h"
    "src/game/gamestates/MainMenuState.h"
    "src/game/gamestates/MatchOverState.h"
    "src/game/gamestates/NievesState.h"
    "src/game/gamestates/OfficeState.h"
    "src/game/gamestates/PaigroState.h"
    "src/game/gamestates/SamuState.h"
    "src/game/gamestates/ShopState.h"
)
source_group("Archivos de encabezado\\GameStates" FILES ${Archivos_de_encabezado__GameStates})

set(Archivos_de_encabezado__Managers
    "src/game/components/managers/BoardManager.h"
    "src/game/components/managers/CardStateManager.h"
    "src/game/components/managers/DragManager.h"
    "src/game/components/managers/IA_manager.h"
    "src/game/components/managers/KeyManager.h"
    "src/game/components/managers/Manager.h"
    "src/game/components/managers/MatchManager.h"
    "src/game/components/managers/PizarraManager.h"
    "src/game/components/managers/PlayerCardsManager.h"
)
source_group("Archivos de encabezado\\Managers" FILES ${Archivos_de_encabezado__Managers})

set(Archivos_de_origen
    "src/game/Data.cpp"
    "src/game/Dialogue.cpp"
    "src/game/Entity.cpp"
    "src/game/Game.cpp"
    "src/game/GameStateMachine.cpp"
    "src/game/main.cpp"
    "src/game/Mouse.cpp"
)
source_group("Archivos de origen" FILES ${Archivos_de_origen})

set(Archivos_de_origen__Auxiliares
    "pchs/pch_c++_basic.cpp"
    "pchs/pch_SDL.cpp"
    "src/game/pch.cpp"
)
source_group("Archivos de origen\\Auxiliares" FILES ${Archivos_de_origen__Auxiliares})

set(Archivos_de_origen__Componentes
    "src/game/components/AutoDialogue.cpp"
    "src/game/components/Button.cpp"
    "src/game/components/Card.cpp"
    "src/game/components/Cell.cpp"
    "src/game/components/ColliderRender.cpp"
    "src/game/components/DeckComponent.cpp"
    "src/game/components/DialogueDestroyer.cpp"
    "src/game/components/DialogueEventCollection.cpp"
    "src/game/components/DialogueReader.cpp"
    "src/game/components/Drag.cpp"
    "src/game/components/DragNoCombat.cpp"
    "src/game/components/DropDetector.cpp"
    "src/game/components/DropZone.cpp"
    "src/game/components/EndTurnButton.cpp"
    "src/game/components/HandComponent.cpp"
    "src/game/components/managers/DrawerManager.cpp"
    "src/game/components/MoveOnClick.cpp"
    "src/game/components/NextText.cpp"
    "src/game/components/NPC.cpp"
    "src/game/components/ShineComponent.cpp"
    "src/game/components/ShopComponent.cpp"
    "src/game/components/TypeWriter.cpp"
    "src/game/EffectCollection.cpp"
    "src/game/GenID.cpp"
)
source_group("Archivos de origen\\Componentes" FILES ${Archivos_de_origen__Componentes})

set(Archivos_de_origen__Componentes__Basicos
    "src/game/components/basics/BoxCollider.cpp"
    "src/game/components/basics/SpriteRenderer.cpp"
    "src/game/components/basics/TextComponent.cpp"
    "src/game/components/basics/Transform.cpp"
)
source_group("Archivos de origen\\Componentes\\Basicos" FILES ${Archivos_de_origen__Componentes__Basicos})

set(Archivos_de_origen__Factories
    "src/game/factories/BoardFactory.cpp"
    "src/game/factories/BoardFactory_v0.cpp"
    "src/game/factories/CardFactory.cpp"
#    "src/game/factories/CardFactory_v0.cpp"
    "src/game/factories/CardFactory_v1.cpp"
    "src/game/factories/DecisionFactory.cpp"
    "src/game/factories/DecisionFactory_V0.cpp"
    "src/game/factories/DialogueFactory.cpp"
    "src/game/factories/DialogueFactory_V0.cpp"
    "src/game/factories/Factory.cpp"
    "src/game/factories/FakeCardFactory_v0.cpp"
    "src/game/factories/MatchStateUIFactory.cpp"
    "src/game/factories/MatchStateUIFactory_v0.cpp"
    "src/game/factories/NPCFactory.cpp"
    "src/game/factories/NPCFactory_V0.cpp"
)
source_group("Archivos de origen\\Factories" FILES ${Archivos_de_origen__Factories})

set(Archivos_de_origen__GameStates
    "src/game/gamestates/AndresState.cpp"
    "src/game/gamestates/CityState.cpp"
    "src/game/gamestates/DeckBuildingState.cpp"
    "src/game/gamestates/GameState.cpp"
    "src/game/gamestates/JimboState.cpp"
    "src/game/gamestates/LuisState.cpp"
    "src/game/gamestates/MainMenuState.cpp"
    "src/game/gamestates/MatchOverState.cpp"
    "src/game/gamestates/NievesState.cpp"
    "src/game/gamestates/OfficeState.cpp"
    "src/game/gamestates/PaigroState.cpp"
    "src/game/gamestates/SamuState.cpp"
    "src/game/gamestates/ShopState.cpp"
)
source_group("Archivos de origen\\GameStates" FILES ${Archivos_de_origen__GameStates})

set(Archivos_de_origen__Managers
    "src/game/components/managers/BoardManager.cpp"
    "src/game/components/managers/CardStateManager.cpp"
    "src/game/components/managers/DragManager.cpp"
    "src/game/components/managers/IA_manager.cpp"
    "src/game/components/managers/KeyManager.cpp"
    "src/game/components/managers/Manager.cpp"
    "src/game/components/managers/MatchManager.cpp"
    "src/game/components/managers/PizarraManager.cpp"
    "src/game/components/managers/PlayerCardsManager.cpp"
)
source_group("Archivos de origen\\Managers" FILES ${Archivos_de_origen__Managers})

set(Resources
    "resources/config/cards.json"
    "resources/config/dialogues.json"
    "resources/config/dialoguesV1.json"
    "resources/config/resources.json"
)
source_group("Resources" FILES ${Resources})

set(Utilidades__JSON
    "src/json/JSON.cpp"
    "src/json/JSON.h"
    "src/json/JSONValue.cpp"
    "src/json/JSONValue.h"
)
source_group("Utilidades\\JSON" FILES ${Utilidades__JSON})

set(Utilidades__SDL_Utils
    "src/sdlutils/Font.h"
    "src/sdlutils/InputHandler.h"
    "src/sdlutils/macros.h"
    "src/sdlutils/Music.h"
    "src/sdlutils/RandomNumberGenerator.h"
    "src/sdlutils/SDLNetUtils.h"
    "src/sdlutils/SDLUtils.cpp"
    "src/sdlutils/SDLUtils.h"
    "src/sdlutils/SoundEffect.cpp"
    "src/sdlutils/SoundEffect.h"
    "src/sdlutils/Texture.cpp"
    "src/sdlutils/Texture.h"
    "src/sdlutils/VirtualTimer.h"
)
source_group("Utilidades\\SDL_Utils" FILES ${Utilidades__SDL_Utils})

set(Utilidades__Utils
    "src/utils/Collisions.cpp"
    "src/utils/Collisions.h"
    "src/utils/DynamicBitSet.h"
    "src/utils/mpl.h"
    "src/utils/ptr_iterator.h"
    "src/utils/Singleton.h"
    "src/utils/Vector2D.cpp"
    "src/utils/Vector2D.h"
)
source_group("Utilidades\\Utils" FILES ${Utilidades__Utils})

set(ALL_FILES
    ${no_group_source_files}
    ${Archivos_de_encabezado}
    ${Archivos_de_encabezado__Auxiliares}
    ${Archivos_de_encabezado__Componentes}
    ${Archivos_de_encabezado__Componentes__Basicos}
    ${Archivos_de_encabezado__ECS}
    ${Archivos_de_encabezado__Factories}
    ${Archivos_de_encabezado__GameStates}
    ${Archivos_de_encabezado__Managers}
    ${Archivos_de_origen}
    ${Archivos_de_origen__Auxiliares}
    ${Archivos_de_origen__Componentes}
    ${Archivos_de_origen__Componentes__Basicos}
    ${Archivos_de_origen__Factories}
    ${Archivos_de_origen__GameStates}
    ${Archivos_de_origen__Managers}
    ${Resources}
    ${Utilidades__JSON}
    ${Utilidades__SDL_Utils}
    ${Utilidades__Utils}
)


################################################################################
# Target
################################################################################
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

add_executable(${PROJECT_NAME} ${ALL_FILES})
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

