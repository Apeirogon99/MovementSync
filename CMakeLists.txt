cmake_minimum_required(VERSION 3.20)
project(MovementSync VERSION 1.0.0)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows 설정
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
    add_definitions(-DBOOST_ALL_NO_LIB)
endif()

# 외부 라이브러리 찾기
find_package(SDL2 CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

# =================================================================
# 공용 정적 라이브러리 생성
# =================================================================
add_library(MovementSyncCommon STATIC
    # 헤더 파일들 (Visual Studio 프로젝트에서 보이도록)
    src/Common/AStar/Grid.h
    src/Common/AStar/Node.h
    src/Common/AStar/PathFinding.h

    src/Common/Math/Vector2f.h
    src/Common/Math/Vector2f_NetQuantize.h

    src/Common/Game/Entity.h

    src/Common/Protocol/Message.h
    
    # 소스 파일들
    src/Common/AStar/Grid.cpp
    src/Common/AStar/Node.cpp
    src/Common/AStar/PathFinding.cpp

    src/Common/Math/Vector2f.cpp
    src/Common/Math/Vector2f_NetQuantize.cpp

    src/Common/Game/Entity.cpp

    src/Common/Protocol/Message.cpp
)

# 공용 라이브러리 설정
target_include_directories(MovementSyncCommon PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Visual Studio에서 폴더로 그룹화
set_target_properties(MovementSyncCommon PROPERTIES 
    FOLDER "Core Libraries"
    OUTPUT_NAME "MovementSyncCommon"
)

# =================================================================
# 클라이언트 실행 파일
# =================================================================
add_executable(MovementSyncClient
    # 헤더 파일
    src/Client/World.h

    # 소스 파일
    src/Client/main.cpp

    src/Client/World.cpp
)

# 클라이언트 라이브러리 링크
target_link_libraries(MovementSyncClient PRIVATE 
    MovementSyncCommon      # 공용 라이브러리
    SDL2::SDL2 
    SDL2::SDL2main 
    Boost::system
)

# =================================================================
# 서버 실행 파일  
# =================================================================
add_executable(MovementSyncServer
    src/Server/main.cpp
)

# 서버 라이브러리 링크
target_link_libraries(MovementSyncServer PRIVATE 
    MovementSyncCommon      # 공용 라이브러리
    Boost::system
)

# =================================================================
# Windows 추가 설정
# =================================================================
if(WIN32)
    target_link_libraries(MovementSyncClient PRIVATE ws2_32 wsock32)
    target_link_libraries(MovementSyncServer PRIVATE ws2_32 wsock32)
endif()

# =================================================================
# 빌드 후 처리 (선택사항)
# =================================================================
# Release 빌드 시 실행 파일들을 한 곳에 모으기
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(MovementSyncClient MovementSyncServer PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endif()
