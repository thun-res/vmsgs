#
# Copyright (C) 2026 by Thun Lu. All rights reserved.
#

add_library(vmsgs-bag SHARED bag.cc)
target_link_libraries(vmsgs-bag PRIVATE vmsgs::vmsgs)
set_target_properties(
  vmsgs-bag
  PROPERTIES CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN ON
             VERSION ${PROJECT_VERSION}
             SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

install(
  TARGETS vmsgs-bag
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
