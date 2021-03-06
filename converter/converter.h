/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Flacon - audio File Encoder
 * https://github.com/flacon/flacon
 *
 * Copyright: 2012-2013
 *   Alexander Sokoloff <sokoloff.a@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * END_COMMON_COPYRIGHT_HEADER */


#ifndef CONVERTER_H
#define CONVERTER_H

#include "types.h"
#include <QObject>
#include <QDateTime>
#include <QVector>

class DiskPipeline;
class OutFormat;
class Track;

class Converter : public QObject
{
    Q_OBJECT
public:
    explicit Converter(QObject *parent = 0);
    virtual ~Converter();

    bool isRunning();
    static bool canConvert();

    bool showStatistic() const { return mShowStatistic; }
    void setShowStatistic(bool value);

signals:
    void finished();
    void trackProgress(const Track &track, TrackState state, Percent percent);

public slots:
    void start();
    void stop();

private slots:
    void startThread();

private:
    QDateTime mStartTime;
    int mThreadCount;
    QVector<DiskPipeline*> mDiskPiplines;

    bool mShowStatistic;

    bool check(OutFormat *format) const;
    void printStatistic();
};

#endif // CONVERTER_H
