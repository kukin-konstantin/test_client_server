cmake_minimum_required(VERSION 3.0)
project(test_task)

if(MSVC)
    set(BOOST_ROOT "C:\\local\\boost_1_73_0")
    set(Boost_USE_STATIC_LIBS   ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
endif()

FIND_PACKAGE( Boost 1.66.0 REQUIRED system date_time regex)

set(HEADERS
    common/command.h
    common/get_color_command.h
    common/set_color_command.h
    common/get_state_command.h
    common/set_state_command.h
    common/get_rate_command.h
    common/set_rate_command.h
    common/led.h
)

set(SOURCES
    common/command.cpp
)

set(HEADERS_CLIENT
	client/client.h
	)

set(SOURCES_CLIENT
	client/main.cpp
	)

set(HEADERS_SERVER
	server/server.h
    server/session.h
	)

set(SOURCES_SERVER
	server/main.cpp
    server/session.cpp
	)

include_directories(./)

include_directories( ${Boost_INCLUDE_DIR} )

    
add_executable(client ${HEADERS} ${HEADERS_CLIENT} ${SOURCES} ${SOURCES_CLIENT})
target_link_libraries(client ${Boost_LIBRARIES} )

add_executable(server ${HEADERS} ${HEADERS_SERVER} ${SOURCES} ${SOURCES_SERVER})
target_link_libraries(server ${Boost_LIBRARIES} )
