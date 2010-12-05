######################################################################################
# Packages needed for examples
######################################################################################

add_executable(glview glview.c)

# Mac just has everything already
if(APPLE)
  set(CMAKE_EXE_LINKER_FLAGS "-framework OpenGL -framework GLUT")
  target_link_libraries(glview freenect)
# Linux, not so much
else()
  find_package(Threads REQUIRED)
  find_package(OpenGL REQUIRED)
  find_package(GLUT REQUIRED)
  SET_TARGET_PROPERTIES (glview PROPERTIES COMPILE_FLAGS "-g")
  include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${USB_INCLUDE_DIRS})
  if (WIN32)
    target_link_libraries(glview freenect ${OPENGL_LIBRARIES} glut32 ${CMAKE_THREAD_LIBS_INIT} m)
  else()
    target_link_libraries(glview freenect ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} m)
  endif()
endif()

install (TARGETS glview
  DESTINATION bin)
