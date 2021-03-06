/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Flacon - audio File Encoder
 * https://github.com/flacon/flacon
 *
 * Copyright: 2018
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


#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include <QDialog>
#include <QList>
#include "tags.h"

class Track;
class TagLineEdit;

namespace Ui {
class TagEditor;
}

class TagEditor : public QDialog
{
    Q_OBJECT

public:
    explicit TagEditor(const QList<Track*> &tracks, QWidget *parent = 0);
    ~TagEditor();

public slots:
    void done(int res) override;

private:
    Ui::TagEditor *ui;
    void addLineEdit(TagId tagId, const QString &label);
    void addTextEdit(TagId tagId, const QString &label);
    void addIntEdit(TagId tagId, const QString &label);
    void addIntEditNumCount(TagId numTagId, TagId cntTagId, const QString &numLabel);
    const QList<Track*> mTracks;
};

#endif // TAGEDITOR_H
