# Options de compilation
cmake_minimum_required(VERSION 3.0)
project(MASTERMIND)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")
set(CMAKE_BUILD_TYPE Debug) # TODO: À enlever
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Documentation (Doxygen)
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Génération de la documentation HTML (requiert doxygen)" ${DOXYGEN_FOUND})

if (BUILD_DOCUMENTATION)
  if (NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen est introuvable.")
  endif()

  set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
  set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  configure_file(${doxyfile_in} ${doxyfile} @ONLY)

  add_custom_target(doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Génération de la documentation doxygen"
    VERBATIM)
endif()

# Documentation (Sphinx)
find_package(Sphinx REQUIRED)

if(NOT DEFINED SPHINX_THEME)
  set(SPHINX_THEME default)
endif()

if(NOT DEFINED SPHINX_THEME_DIR)
  set(SPHINX_THEME_DIR)
endif()

# configured documentation tools and intermediate build results
set(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/sphinx/_build")

# Sphinx cache with pickled ReST documents
set(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/sphinx/_doctrees")

# HTML output directory
set(SPHINX_HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/sphinx/html")

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/sphinx/conf.py.in"
  "${BINARY_BUILD_DIR}/conf.py"
@ONLY)

add_custom_target(doc_sphinx ALL
  ${SPHINX_EXECUTABLE}
  -q -b html
  -c "${BINARY_BUILD_DIR}"
  -d "${SPHINX_CACHE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/sphinx"
  "${SPHINX_HTML_DIR}"
  COMMENT "Génération de la documentation sphinx")

# Modules externes
find_package( PkgConfig REQUIRED )
pkg_check_modules( PKG REQUIRED cpputest sfml-all )
include_directories( ${PKG_INCLUDE_DIRS} )
include_directories ( "${CMAKE_SOURCE_DIR}/include" )

# Éxécutable client
add_executable( client.out src/main_client.cpp
  src/App.cpp
  src/GameStateManager.cpp
  src/MenuState.cpp
  src/JoiningState.cpp
  src/NetworkState.cpp
  src/Button.cpp
  src/TextField.cpp
  src/mastermind.cpp
  src/Pion.cpp
  src/Combinaison.cpp
  src/Plateau.cpp
  src/PionDrawable.cpp
  src/Utils.cpp
  #src/PanelPions.cpp
)

# Éxécutable serveur
add_executable( server.out src/main_server.cpp
  src/Server.cpp
  src/mastermind.cpp
  src/Pion.cpp
  src/Combinaison.cpp
  src/Plateau.cpp
)

# TODO: Tests unitaires
add_executable( main_test.out tests/main_test.cpp
  src/mastermind.cpp
  src/Pion.cpp
  src/Combinaison.cpp
  src/Plateau.cpp
  
  tests/mastermind_test.cpp
  tests/Pion_test.cpp
  tests/Plateau_test.cpp
  tests/Combinaison_test.cpp
)

# Édition des liens
target_link_libraries( client.out ${PKG_LIBRARIES} )
target_link_libraries( server.out ${PKG_LIBRARIES} )
target_link_libraries( main_test.out ${PKG_LIBRARIES} )
