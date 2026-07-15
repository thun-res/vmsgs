#
# Copyright (C) 2026 by Thun Lu. All rights reserved.
#

add_library(vmsgs-bag-plugin SHARED bag_plugin.cc)
target_link_libraries(vmsgs-bag-plugin PRIVATE vmsgs::vmsgs)
set_target_properties(
  vmsgs-bag-plugin
  PROPERTIES CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN ON
             VERSION ${PROJECT_VERSION}
             SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

install(
  TARGETS vmsgs-bag-plugin
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
