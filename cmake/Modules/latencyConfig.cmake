INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_LATENCY latency)

FIND_PATH(
    LATENCY_INCLUDE_DIRS
    NAMES latency/api.h
    HINTS $ENV{LATENCY_DIR}/include
        ${PC_LATENCY_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    LATENCY_LIBRARIES
    NAMES gnuradio-latency
    HINTS $ENV{LATENCY_DIR}/lib
        ${PC_LATENCY_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/latencyTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LATENCY DEFAULT_MSG LATENCY_LIBRARIES LATENCY_INCLUDE_DIRS)
MARK_AS_ADVANCED(LATENCY_LIBRARIES LATENCY_INCLUDE_DIRS)
