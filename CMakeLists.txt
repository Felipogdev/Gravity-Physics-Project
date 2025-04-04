cmake_minimum_required(VERSION 3.16)
project(GAME LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Diretórios e aqui tu coloca onde tá teu projeto
set(SRC_DIR ${CMAKE_SOURCE_DIR}~/Documents/PhysicsProject/)
#set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Adiciona diretório include
include_directories(${INCLUDE_DIR})

# Dependências
find_package(OpenGL REQUIRED)
#find_package(Assimp REQUIRED)
find_package(GLFW REQUIRED)

# Adiciona arquivos do projeto
file(GLOB SOURCES ${SRC_DIR}/*.cpp)

# Compila executável
add_executable(${PROJECT_NAME} ${SOURCES})

# Linkagem
target_link_libraries(${PROJECT_NAME} PRIVATE 
    OpenGL::GL 
    Assimp::Assimp 
    glfw
)

# Instalação
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
