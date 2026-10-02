/*
 * SPDX-FileCopyrightText: 2026 Andrea Manzini <ilmanzo@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

import QtQuick
import QtQuick.Layouts
import org.kde.kirigami as Kirigami
import org.kde.plasma.components as PlasmaComponents
import org.kde.plasma.plasmoid
import org.opensuse.hellocounter

PlasmoidItem {
    id: root

    // The model, created once per widget instance
    Counter {
        id: counter
    }

    // View 1: the tooltip shown when hovering the tray icon
    toolTipMainText: i18n("Hello counter")
    toolTipSubText: i18np("%1 click", "%1 clicks", counter.count)

    // View 2: the popup
    fullRepresentation: ColumnLayout {
        Layout.minimumWidth: Kirigami.Units.gridUnit * 12
        Layout.minimumHeight: Kirigami.Units.gridUnit * 5
        spacing: Kirigami.Units.largeSpacing

        Kirigami.Heading {
            Layout.alignment: Qt.AlignHCenter
            text: i18np("%1 click", "%1 clicks", counter.count)
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            // The controller: turns user input into calls on the model
            PlasmaComponents.Button {
                icon.name: "list-add"
                text: i18n("Click me")
                onClicked: counter.increment()
            }

            PlasmaComponents.Button {
                icon.name: "edit-reset"
                text: i18n("Reset")
                enabled: counter.count > 0
                onClicked: counter.reset()
            }
        }
    }
}
