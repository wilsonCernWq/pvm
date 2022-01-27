# ┌──────────────────────────────────────────────────────────────────┐
# │  Global Properties                                               │
# └──────────────────────────────────────────────────────────────────┘
cmake_minimum_required(VERSION 3.3)
project(PVM CXX)

option(INSTALL_DEV_HEADERS "Whether to install PVM headers" OFF)

include(GNUInstallDirs)
include(GenerateExportHeader)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Configure Source Files                                          │
# └──────────────────────────────────────────────────────────────────┘
add_library(PVM SHARED 
  ddsbase.cpp
)

generate_export_header(PVM BASE_NAME PVM)

target_include_directories(PVM 
PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Configure Install                                               │
# └──────────────────────────────────────────────────────────────────┘
# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS PVM EXPORT PVMConfig) # Windows

if(INSTALL_DEV_HEADERS)

  install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pvm_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

  # This makes the project importable from the install directory
  # Put config file in per-project dir (name MUST match), can also
  # just go into 'cmake'.
  install(EXPORT PVMConfig
    NAMESPACE PVM::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pvm
  )

  # This makes the project importable from the build directory
  export(TARGETS PVM
    NAMESPACE PVM::
    FILE ${CMAKE_INSTALL_LIBDIR}/cmake/pvm/PVMConfig.cmake
  )

endif()
