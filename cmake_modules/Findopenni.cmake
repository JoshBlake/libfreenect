# - Try to find openni
# Once done this will define
#
#  OPENNI_FOUND - system has libusb
#  OPENNI_INCLUDE_DIRS - the libusb include directory
#  OPENNI_LIBRARIES - Link these to use libusb
#  OPENNI_DEFINITIONS - Compiler switches required for using libusb
#
#  Adapted from cmake-modules Google Code project
#
#  Copyright (c) 2006 Andreas Schneider <mail@cynapses.org>
#
#  (Changes for libusb) Copyright (c) 2008 Kyle Machulis <kyle@nonpolynomial.com>
#
# Redistribution and use is allowed according to the terms of the New BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#


if (OPENNI_LIBRARIES AND OPENNI_INCLUDE_DIRS)
  # in cache already
  set(OPENNI_FOUND TRUE)
else (OPENNI_LIBRARIES AND OPENNI_INCLUDE_DIRS)
  find_path(OPENNI_INCLUDE_DIR
    NAMES
      XnUSB.h
    PATHS
      /usr/include
      /usr/local/include
      /opt/local/include
      /sw/include
  )

  find_library(OPENNI_LIBRARY
    NAMES
      openNI.lib
    PATHS
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      /sw/lib
  )

  set(OPENNI_INCLUDE_DIRS
    ${OPENNI_INCLUDE_DIR}
  )
  set(OPENNI_LIBRARIES
    ${OPENNI_LIBRARY}
)

  if (OPENNI_INCLUDE_DIRS AND OPENNI_LIBRARIES)
     set(OPENNI_FOUND TRUE)
  endif (OPENNI_INCLUDE_DIRS AND OPENNI_LIBRARIES)

  if (OPENNI_FOUND)
    if (NOT openni_FIND_QUIETLY)
      message(STATUS "Found OpenNI: ${OPENNI_LIBRARIES}")
    endif (NOT openni_FIND_QUIETLY)
  else (OPENNI_FOUND)
    if (openni_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find OpenNI")
    endif (openni_FIND_REQUIRED)
  endif (OPENNI_FOUND)

  # show the OPENNI_INCLUDE_DIRS and OPENNI_LIBRARIES variables only in the advanced view
  mark_as_advanced(OPENNI_INCLUDE_DIRS OPENNI_LIBRARIES)

endif (OPENNI_LIBRARIES AND OPENNI_INCLUDE_DIRS)