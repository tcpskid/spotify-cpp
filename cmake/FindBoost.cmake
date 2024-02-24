# Locate the Boost libraries and headers
# The following variables are set if Boost is found:
# BOOST_FOUND - True if Boost is found
# BOOST_INCLUDE_DIRS - The Boost include directories
# BOOST_LIBRARIES - The Boost libraries to link against

find_path(BOOST_INCLUDE_DIRS NAMES boost)
find_library(BOOST_LIBRARIES NAMES boost)

if (BOOST_INCLUDE_DIRS AND BOOST_LIBRARIES)
    set(BOOST_FOUND TRUE)
else()
    set(BOOST_FOUND FALSE)
endif()

# Provide information about Boost to CMake
if (BOOST_FOUND)
    if (NOT BOOST_FIND_QUIETLY)
        message(STATUS "Found Boost: ${BOOST_LIBRARIES}")
    endif()
else()
    if (NOT BOOST_FIND_QUIETLY)
        message(STATUS "Boost library not found")
    endif()
endif()

# Export Boost variables
if (BOOST_FOUND)
    set(BOOST_INCLUDE_DIRS ${BOOST_INCLUDE_DIRS})
    set(BOOST_LIBRARIES ${BOOST_LIBRARIES})
endif()

mark_as_advanced(BOOST_INCLUDE_DIRS BOOST_LIBRARIES)
