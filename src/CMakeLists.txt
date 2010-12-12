######################################################################################
# Build for main library
######################################################################################

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_C_FLAGS "-Wall")

IF(WIN32)
  include_directories (${OPENNI_INCLUDE_DIRS})
  LIST(APPEND SRC core.c tilt.c cameras.c usb_openni.cpp)
ELSE(WIN32)
  include_directories(${LIBUSB_1_INCLUDE_DIRS})
  LIST(APPEND SRC core.c tilt.c cameras.c usb_libusb10.c)
ENDIF(WIN32)

add_library (freenect SHARED ${SRC})
set_target_properties ( freenect PROPERTIES
  VERSION ${PROJECT_VER}
  SOVERSION ${PROJECT_APIVER})	
install (TARGETS freenect
  DESTINATION "${PROJECT_LIBRARY_INSTALL_DIR}")

add_library (freenectstatic STATIC ${SRC})
set_target_properties (freenectstatic PROPERTIES OUTPUT_NAME freenect)
  SET_TARGET_PROPERTIES (freenect PROPERTIES COMPILE_FLAGS "-g")
IF(UNIX AND NOT APPLE)
  SET_TARGET_PROPERTIES (freenectstatic PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF()
install (TARGETS freenectstatic
  DESTINATION "${PROJECT_LIBRARY_INSTALL_DIR}")

IF(WIN32)
  target_link_libraries (freenect ${OPENNI_LIBRARIES})
  target_link_libraries (freenectstatic ${OPENNI_LIBRARIES})
ELSE(Win32)
  target_link_libraries (freenect ${LIBUSB_LIBRARIES})
  target_link_libraries (freenectstatic ${LIBUSB_LIBRARIES})
ENDIF(WIN32)

# Install the header file
install (FILES "../include/libfreenect.h" "../include/libfreenect.hpp"
  DESTINATION ${PROJECT_INCLUDE_INSTALL_DIR})

IF(UNIX AND NOT APPLE)
  # Produce a pkg-config file for linking against the shared lib
  configure_file ("libfreenect.pc.in" "libfreenect.pc" @ONLY)
  install (FILES "${CMAKE_CURRENT_BINARY_DIR}/libfreenect.pc"
    DESTINATION "${PROJECT_LIBRARY_INSTALL_DIR}/pkgconfig")
ENDIF()
