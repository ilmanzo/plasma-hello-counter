# SPDX-FileCopyrightText: 2026 Andrea Manzini <ilmanzo@gmail.com>
# SPDX-License-Identifier: GPL-2.0-or-later

cmake_minimum_required(VERSION 3.20)

project(plasma-hello-counter VERSION 0.1.0 LANGUAGES CXX)

find_package(ECM 6.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEClangFormat)
include(ECMQmlModule)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Qml)

# The C++ part: a QML module "org.opensuse.hellocounter" holding the Counter type
add_library(hellocounter)
ecm_add_qml_module(hellocounter URI "org.opensuse.hellocounter" VERSION 1.0 GENERATE_PLUGIN_SOURCE PLUGIN_TARGET hellocounter)
target_sources(hellocounter PRIVATE src/counter.cpp src/counter.h)
target_include_directories(hellocounter PRIVATE src)
target_link_libraries(hellocounter PRIVATE Qt6::Qml)
ecm_finalize_qml_module(hellocounter)

# The QML part: the plasmoid package
install(DIRECTORY package/
    DESTINATION ${KDE_INSTALL_DATADIR}/plasma/plasmoids/org.opensuse.hellocounter
)

# Plasma only searches Qt's own directories for QML modules, so a local install needs QML_IMPORT_PATH
install(CODE "message(STATUS \"Local install? Set QML_IMPORT_PATH=${KDE_INSTALL_FULL_QMLDIR} for Plasma (see README)\")")

if (BUILD_TESTING)
    include(ECMAddTests)
    add_subdirectory(autotests)
endif()

# `cmake --build build --target clang-format` formats the C++ sources with the KDE style
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES src/*.cpp src/*.h autotests/*.cpp)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
