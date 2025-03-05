cmake_minimum_required(VERSION 3.28)
project(SATCollision LANGUAGES CXX)

# 실행 파일이 생성될 디렉터리 설정 (bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 리소스 폴더 복사 대상 설정
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")
set(OUTPUT_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB SOURCES "src/*.cpp") 

# 📌 실행 파일 생성
add_executable(main ${SOURCES})

# 📌 빌드 후 resources 폴더를 bin/ 안에 복사
add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${SOURCE_DIR}" "${OUTPUT_DIR}"
)

# 📌 SFML 라이브러리 링크
target_link_libraries(main PRIVATE SFML::Graphics)
