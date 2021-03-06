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


#include "aac.h"
#include "settings.h"
#include "inputaudiofile.h"


/************************************************

 ************************************************/
OutFormat_Aac::OutFormat_Aac()
{
    mId   = "AAC";
    mExt  = "m4a";
    mName = "AAC";
    mSettingsGroup = "Aac";
}


/************************************************

 ************************************************/
QStringList OutFormat_Aac::encoderArgs(const Track *track, const QString &outFile) const
{
    QStringList args;

    args << settings->programName(encoderProgramName());
    args << "-w"; // Wrap  AAC  data  in  an MP4 container.

    // Quality settings .........................................
    if (settings->value("Aac/UseQuality").toBool())
        args << "-q" << settings->value("Aac/Quality").toString();
    else
        args << "-b" << settings->value("Aac/Bitrate").toString();


    // Tags .....................................................
    // --artist artist
    //     Set artist to artist
    if (!track->artist().isEmpty())        args << "--artist"  << track->artist();

    // --writer writer
    //     Set writer to writer

    // --title title
    //     Set title to title
    if (!track->title().isEmpty())        args << "--title"   << track->title();

    // --genre genre
    //     Set genre to genre
    if (!track->genre().isEmpty())        args << "--genre"   << track->genre();

    // --album album
    //     Set album to album
    if (!track->album().isEmpty())        args << "--album"   << track->album();

    // --compilation
    //     Set compilation

    // --track track
    //     Set track to track in the format “number/total”
    args << "--track" << QString("%1/%2").arg(track->trackNum()).arg(track->trackCount());

    // --disc disc
    //     Set disc to disc in the format “number/total”
    args << "--disc" << QString("%1/%2").arg(track->diskNum()).arg(track->diskCount());

    // --year year
    //     Set year to year
    if (!track->date().isEmpty())   args << "--year"   << track->date();

    // --cover-art file
    //     Set cover art to image in file; supported formats are GIF, JPEG, and PNG.

    // --comment comment
    //     Set comment to comment
    if (!track->comment().isEmpty())   args << "--comment"   << track->comment();


    args << "-o" << outFile;
    args << "-";
    return args;
}


/************************************************

 ************************************************/
QStringList OutFormat_Aac::gainArgs(const QStringList &files) const
{
    Q_UNUSED(files);
    return QStringList();
}


/************************************************

 ************************************************/
QHash<QString, QVariant> OutFormat_Aac::defaultParameters() const
{
    QHash<QString, QVariant> res;
    res.insert("Aac/UseQuality",  true);
    res.insert("Aac/Quality",   100);
    res.insert("Aac/Bitrate", 256);
    return res;
}


/************************************************

 ************************************************/
EncoderConfigPage *OutFormat_Aac::configPage(QWidget *parent) const
{
    return new ConfigPage_Acc(parent);
}


/************************************************

 ************************************************/
ConfigPage_Acc::ConfigPage_Acc(QWidget *parent):
    EncoderConfigPage(parent)
{
    setupUi(this);

    setLossyToolTip(aacQualitySpin);
    aacQualitySlider->setToolTip(aacQualitySpin->toolTip());
    fillBitrateComboBox(aacBitrateCbx,  QList<int>() << 64 << 80 << 128 << 160 << 192 << 224 << 256 << 288 << 320);
}


/************************************************

 ************************************************/
void ConfigPage_Acc::load()
{
    loadWidget("Aac/UseQuality", aacUseQualityCheck);
    loadWidget("Aac/Quality",    aacQualitySpin);
    loadWidget("Aac/Bitrate",    aacBitrateCbx);
}


/************************************************

 ************************************************/
void ConfigPage_Acc::write()
{
    writeWidget("Aac/UseQuality", aacUseQualityCheck);
    writeWidget("Aac/Quality",    aacQualitySpin);
    writeWidget("Aac/Bitrate",    aacBitrateCbx);
}


