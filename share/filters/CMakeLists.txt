# SPDX-License-Identifier: GPL-2.0-or-later
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/filters.svg.h
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/i18n.py ${CMAKE_CURRENT_SOURCE_DIR}/filters.svg > ${CMAKE_CURRENT_BINARY_DIR}/filters.svg.h
  MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/filters.svg
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/i18n.py
)
set_source_files_properties(${CMAKE_BINARY_DIR}/filters.svg.h PROPERTIES GENERATED TRUE)

add_custom_target(filters_svg_h ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/filters.svg.h)

install(FILES "filters.svg" DESTINATION ${INKSCAPE_SHARE_INSTALL}/filters)
