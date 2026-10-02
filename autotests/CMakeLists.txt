# SPDX-FileCopyrightText: 2026 Andrea Manzini <ilmanzo@gmail.com>
# SPDX-License-Identifier: GPL-2.0-or-later

find_package(Qt6 6.5 REQUIRED COMPONENTS Test)

ecm_add_test(countertest.cpp ${CMAKE_SOURCE_DIR}/src/counter.cpp
    TEST_NAME countertest
    LINK_LIBRARIES Qt6::Test Qt6::Qml
)
target_include_directories(countertest PRIVATE ${CMAKE_SOURCE_DIR}/src)
