cmake_minimum_required(VERSION 3.10)
project(ssutils VERSION 0.5.0 LANGUAGES C)

include(GNUInstallDirs)

set(SSU_ASSETS_DIR "${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_NAME}"
    CACHE PATH "Directory where assets are installed")
set(SSU_TMP_DIR "${CMAKE_INSTALL_PREFIX}/temp" CACHE PATH "Temporary directory")
set(SSU_CACHE_DIR "${CMAKE_INSTALL_PREFIX}/cache" CACHE PATH "Cache directory")
set(SSU_CGI_DIR "${CMAKE_INSTALL_PREFIX}/cgi-bin" CACHE PATH "CGI install directory")

# Third-party static libraries (cgic, md5)
add_subdirectory(external)

foreach(prog yph capture cgictest)
  add_executable(${prog} src/${prog}.c)
  target_link_libraries(${prog} PRIVATE cgic md5)
  target_compile_definitions(${prog} PRIVATE
    ASSETDIR="${SSU_ASSETS_DIR}"
    CACHEDIR="${SSU_CACHE_DIR}"
    TMPDIR="${SSU_TMP_DIR}")
  install(TARGETS ${prog} RUNTIME DESTINATION "${SSU_CGI_DIR}")
endforeach()

install(FILES
  assets/yph0.gif assets/yph1.gif assets/yph2.gif assets/yph3.gif
  assets/yph4.gif assets/yph5.gif assets/sig0.png assets/cgic.html
  DESTINATION "${SSU_ASSETS_DIR}")
