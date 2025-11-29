# Auto-locate the Pico SDK. Uses the PICO_SDK_PATH environment variable when available
# and falls back to FetchContent to download a local copy under .pico-sdk/.

if(NOT PICO_SDK_PATH)
    if(DEFINED ENV{PICO_SDK_PATH} AND (NOT "$ENV{PICO_SDK_PATH}" STREQUAL ""))
        set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
    else()
        include(FetchContent)
        set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_LIST_DIR}/.pico-sdk)
        FetchContent_Declare(
            pico_sdk
            GIT_REPOSITORY https://github.com/raspberrypi/pico-sdk.git
            GIT_TAG 2.0.0
            GIT_SUBMODULES_RECURSE TRUE
        )
        FetchContent_Populate(pico_sdk)
        set(PICO_SDK_PATH ${pico_sdk_SOURCE_DIR})
    endif()
endif()

if(NOT EXISTS "${PICO_SDK_PATH}/pico_sdk_init.cmake")
    message(FATAL_ERROR "pico_sdk_init.cmake could not be found. Please set PICO_SDK_PATH or ensure the SDK was fetched correctly.")
endif()

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
