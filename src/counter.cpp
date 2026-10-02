// SPDX-FileCopyrightText: 2026 Andrea Manzini <ilmanzo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "counter.h"

Counter::Counter(QObject *parent)
    : QObject(parent)
{
}

int Counter::count() const
{
    return m_count;
}

void Counter::increment()
{
    ++m_count;
    Q_EMIT countChanged();
}

void Counter::reset()
{
    if (m_count == 0) {
        return;
    }

    m_count = 0;
    Q_EMIT countChanged();
}
