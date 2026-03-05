cmake_minimum_required(VERSION 3.16)
project(MeuJogoSFML)

set(CMAKE_CXX_STANDARD 17)

# Caminho para o SFML
set(SFML_DIR "C:/SFML-3.0.2/lib/cmake/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Window)

# Inclui os headers do SFML
include_directories("C:/SFML-3.0.2/include")
include_directories(include)

add_executable(Pong src/main.cpp src/Game.cpp src/Entity.cpp src/Ball.cpp src/Animator.cpp src/Collider.cpp resources.rc)

# target_link_options(Pong PRIVATE "/SUBSYSTEM:WINDOWS" "/ENTRY:mainCRTStartup") #Sem CMD

target_link_options(Pong PRIVATE "/SUBSYSTEM:CONSOLE") #Com CMD


target_link_libraries(Pong SFML::Graphics SFML::Audio SFML::Window)

# Diretório de saída para Release
set_target_properties(Pong PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release
)

# Copiar DLLs do SFML para Release
add_custom_command(TARGET Pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/SFML-3.0.2/bin/sfml-graphics-3.dll"
        "C:/SFML-3.0.2/bin/sfml-window-3.dll"
        "C:/SFML-3.0.2/bin/sfml-system-3.dll"
        "C:/SFML-3.0.2/bin/sfml-audio-3.dll"
		"C:/SFML-3.0.2/bin/sfml-network-3.dll"
        $<TARGET_FILE_DIR:Pong>
)

# Copiar pasta de assets para Release
add_custom_command(TARGET Pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Pong>/assets
)
