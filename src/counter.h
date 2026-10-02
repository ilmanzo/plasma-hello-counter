// SPDX-FileCopyrightText: 2026 Andrea Manzini <ilmanzo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QObject>
#include <QtQml/qqmlregistration.h>

/**
 * The model: it owns the data and knows nothing about how it is shown.
 */
class Counter : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    explicit Counter(QObject *parent = nullptr);

    int count() const;

public Q_SLOTS:
    void increment();
    void reset();

Q_SIGNALS:
    void countChanged();

private:
    int m_count = 0;
};
