// SPDX-FileCopyrightText: 2026 Andrea Manzini <ilmanzo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "counter.h"

#include <QSignalSpy>
#include <QTest>

class CounterTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void incrementEmitsCountChanged();
    void resetEmitsOnlyWhenCountChanges();
};

void CounterTest::incrementEmitsCountChanged()
{
    Counter counter;
    QSignalSpy spy(&counter, &Counter::countChanged);

    counter.increment();
    counter.increment();

    QCOMPARE(counter.count(), 2);
    QCOMPARE(spy.count(), 2);
}

void CounterTest::resetEmitsOnlyWhenCountChanges()
{
    Counter counter;
    QSignalSpy spy(&counter, &Counter::countChanged);

    counter.reset(); // already 0: nothing to announce
    QCOMPARE(spy.count(), 0);

    counter.increment();
    counter.reset();
    QCOMPARE(counter.count(), 0);
    QCOMPARE(spy.count(), 2);
}

QTEST_GUILESS_MAIN(CounterTest)

#include "countertest.moc"
