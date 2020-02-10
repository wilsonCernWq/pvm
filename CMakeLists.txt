# ┌──────────────────────────────────────────────────────────────────┐
# │  Retrieve Global Properties                                      │
# └──────────────────────────────────────────────────────────────────┘
vidi_global_property_get_lib_output_path(in_LIB_OUTPUT_PATH)
vidi_global_property_get_exe_output_path(in_EXE_OUTPUT_PATH)
vidi_global_property_get_install_incdir(in_INSTALL_INCDIR)
vidi_global_property_get_install_bindir(in_INSTALL_BINDIR)
vidi_global_property_get_install_libdir(in_INSTALL_LIBDIR)
vidi_global_property_get_install_dev_headers(in_INSTALL_DEV_HEADERS)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Configure Source Files                                          │
# └──────────────────────────────────────────────────────────────────┘
add_library(PVM SHARED ddsbase.cpp)

generate_export_header(PVM BASE_NAME PVM)

target_include_directories(PVM PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
target_include_directories(PVM PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
target_include_directories(PVM PUBLIC
  $<INSTALL_INTERFACE:${in_INSTALL_INCDIR}>)

set_target_properties(PVM PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${in_LIB_OUTPUT_PATH}
  LIBRARY_OUTPUT_DIRECTORY ${in_LIB_OUTPUT_PATH}
  RUNTIME_OUTPUT_DIRECTORY ${in_EXE_OUTPUT_PATH})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Configure Install                                               │
# └──────────────────────────────────────────────────────────────────┘
# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS PVM EXPORT PVMConfig
  ARCHIVE  DESTINATION ${in_INSTALL_LIBDIR}
  LIBRARY  DESTINATION ${in_INSTALL_LIBDIR}
  RUNTIME  DESTINATION ${in_INSTALL_BINDIR}) # Windows

if(in_INSTALL_DEV_HEADERS)

  install(DIRECTORY include/ DESTINATION ${in_INSTALL_INCDIR})
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pvm_export.h
    DESTINATION ${in_INSTALL_INCDIR})

  # This makes the project importable from the install directory
  # Put config file in per-project dir (name MUST match), can also
  # just go into 'cmake'.
  install(EXPORT PVMConfig
    NAMESPACE PVM::
    DESTINATION ${in_INSTALL_LIBDIR}/cmake)

  # This makes the project importable from the build directory
  export(TARGETS PVM
    NAMESPACE PVM::
    FILE ${CMAKE_BINARY_DIR}/cmake/PVMConfig.cmake)

  # Register configure files
  set_property(GLOBAL APPEND PROPERTY VIDI_INSTALL_TARGET PVMConfig)

endif()
