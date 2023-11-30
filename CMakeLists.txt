cmake_minimum_required(VERSION 3.26)
project(TCMCP_core)

#核心库
set(LIBRARY_NAME tcmcp_core)

#测试单元
set(SqlLiteTest SqlLiteTest)
set(ShenNongTest ShenNongTest)
set(ZhenjiuTest ZhenjiuTest)
set(ShangHanTest ShangHanTest)
set(JinKuiTest JinKuiTest)


message(${LIBRARY_NAME})
execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
message("当前Git分支: ${GIT_BRANCH}")

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
#set(CMAKE_MACOSX_RPATH 1)
#enable_testing()
#set(CMAKE_FIND_LIBRARY_SUFFIXES .dll .so .dylib)
find_package(GTest CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)
message("Found spdlog: ${spdlog_FOUND}")
message("Found GTest: ${GTEST_FOUND}")
message("Found SQLiteCpp: ${SQLiteCpp_FOUND}")

#add_executable(${LIBRARY_NAME} main.cpp)
add_library(${LIBRARY_NAME}
        SHARED
        main.cpp
        tcmcp/shennongbencaojing/tcm.cpp
        tcmcp/shennongbencaojing/tcm.h
        tcmcp/zhenjiudacheng/meridians.cpp
        tcmcp/zhenjiudacheng/meridians.h
        tcmcp/zhenjiudacheng/acupoints.cpp
        tcmcp/zhenjiudacheng/acupoints.h
        tcmcp/shanghanzabinglun/six_stage_diagnosis.cpp
        tcmcp/shanghanzabinglun/six_stage_diagnosis.h
        tcmcp/jinkuiyaolue/prescriptions.cpp
        tcmcp/jinkuiyaolue/prescriptions.h
        tcmcp/huangdineijing/eight_principles_diagnosis.cpp
        tcmcp/huangdineijing/eight_principles_diagnosis.h
)

set(FinallyLibrary
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
        spdlog::spdlog
        SQLiteCpp
)

## 数据库子的test
#add_executable(${SqlLiteTest} ${})

## 针灸test
#add_executable(${ZhenJiuTest} ${ShenNongTestFile})
#
## 神农本草经test
#set(ShenNongTestFile  )
#add_executable(${ShenNongTest} ${ShenNongTestFile})
#
## 伤寒test
#add_executable(${ShangHanTest} ${ShenNongTestFile})
#
## 金匮test
#add_executable(${JinKuiTest} ${ShenNongTestFile})


if (UNIX)
    if (APPLE)
        message("当前是mac")
        target_link_libraries(${LIBRARY_NAME} PUBLIC ${TARGET_LINK_LIBS}
                ${FinallyLibrary}
        )
    elseif (UNIX)
        message("当前是linux")
        target_link_libraries(${LIBRARY_NAME} PUBLIC ${TARGET_LINK_LIBS}
                ${FinallyLibrary}
                bsd
        )
    endif ()
elseif (WIN32)
    message("当前是win32")
    target_link_libraries(${LIBRARY_NAME} PUBLIC ${TARGET_LINK_LIBS}
            ${FinallyLibrary}
    )
endif ()

