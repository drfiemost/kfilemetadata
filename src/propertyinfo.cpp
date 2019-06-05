/*
 * This file is part of the KFileMetaData project
 * Copyright (C) 2014  Vishesh Handa <me@vhanda.in>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) version 3, or any
 * later version accepted by the membership of KDE e.V. (or its
 * successor approved by the membership of KDE e.V.), which shall
 * act as a proxy defined in Section 6 of version 3 of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "propertyinfo.h"

#include <KLocalizedString>

#include "formatstrings_p.h"

using namespace KFileMetaData;

class Q_DECL_HIDDEN PropertyInfo::Private
{
public:
    Property::Property prop;
    QString name;
    QString displayName;
    QVariant::Type valueType;
    bool shouldBeIndexed;
    QString (*formatAsString)(const QVariant& value) = nullptr;
};

PropertyInfo::PropertyInfo()
    : d(new Private)
{
    d->prop = Property::Empty;
    d->name = QStringLiteral("empty");
    d->valueType = QVariant::Invalid;
    d->shouldBeIndexed = false;
    d->formatAsString = &FormatStrings::toStringFunction;
}

PropertyInfo::PropertyInfo(Property::Property property)
    : d(new Private)
{
    d->prop = property;
    d->shouldBeIndexed = true;
    d->formatAsString = &FormatStrings::toStringFunction;

    switch (property) {
        case Property::Album:
            d->name = QStringLiteral("album");
            d->displayName = i18nc("@label music album", "Album");
            d->valueType = QVariant::String;
            break;

        case Property::AlbumArtist:
            d->name = QStringLiteral("albumArtist");
            d->displayName = i18nc("@label", "Album Artist");
            d->valueType = QVariant::String;
            break;

        case Property::Artist:
            d->name = QStringLiteral("artist");
            d->displayName = i18nc("@label", "Artist");
            d->valueType = QVariant::String;
            break;

        case Property::AspectRatio:
            d->name = QStringLiteral("aspectRatio");
            d->displayName = i18nc("@label", "Aspect Ratio");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatAspectRatio;
            break;

        case Property::Author:
            d->name = QStringLiteral("author");
            d->displayName = i18nc("@label", "Author");
            d->valueType = QVariant::String;
            break;

        case Property::BitRate:
            d->name = QStringLiteral("bitRate");
            d->displayName = i18nc("@label", "Bitrate");
            d->valueType = QVariant::Int;
            d->formatAsString = &FormatStrings::formatBitRate;
            break;

        case Property::Channels:
            d->name = QStringLiteral("channels");
            d->displayName = i18nc("@label", "Channels");
            d->valueType = QVariant::Int;
            break;

        case Property::Comment:
            d->name = QStringLiteral("comment");
            d->displayName = i18nc("@label", "Comment");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::Description:
            d->name = QStringLiteral("description");
            d->displayName = i18nc("@label", "Description");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::Composer:
            d->name = QStringLiteral("composer");
            d->displayName = i18nc("@label", "Composer");
            d->valueType = QVariant::String;
            break;

        case Property::Copyright:
            d->name = QStringLiteral("copyright");
            d->displayName = i18nc("@label", "Copyright");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::CreationDate:
            d->name = QStringLiteral("creationDate");
            d->displayName = i18nc("@label", "Creation Date");
            d->valueType = QVariant::DateTime;
            d->formatAsString = &FormatStrings::formatDate;
            break;

        case Property::Duration:
            d->name = QStringLiteral("duration");
            d->displayName = i18nc("@label", "Duration");
            d->valueType = QVariant::Int;
            d->formatAsString = &FormatStrings::formatDuration;
            break;

        case Property::Empty:
            d->name = QStringLiteral("empty");
            d->valueType = QVariant::Invalid;
            break;

        case Property::FrameRate:
            d->name = QStringLiteral("frameRate");
            d->displayName = i18nc("@label", "Frame Rate");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatAsFrameRate;
            break;

        case Property::Generator:
            d->name = QStringLiteral("generator");
            d->displayName = i18nc("@label", "Document Generated By");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::Genre:
            d->name = QStringLiteral("genre");
            d->displayName = i18nc("@label music genre", "Genre");
            d->valueType = QVariant::String;
            break;

        case Property::Height:
            d->name = QStringLiteral("height");
            d->displayName = i18nc("@label", "Height");
            d->valueType = QVariant::Int;
            break;

        case Property::ImageDateTime:
            d->name = QStringLiteral("imageDateTime");
            d->displayName = i18nc("@label EXIF", "Image Date Time");
            d->valueType = QVariant::DateTime;
            d->formatAsString = &FormatStrings::formatDate;
            break;

        case Property::ImageMake:
            d->name = QStringLiteral("imageMake");
            d->displayName = i18nc("@label EXIF", "Image Make");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::ImageModel:
            d->name = QStringLiteral("imageModel");
            d->displayName = i18nc("@label EXIF", "Image Model");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::ImageOrientation:
            d->name = QStringLiteral("imageOrientation");
            d->displayName = i18nc("@label EXIF", "Image Orientation");
            d->valueType = QVariant::Int;
            d->formatAsString = &FormatStrings::formatOrientationValue;
            break;

        case Property::Keywords:
            d->name = QStringLiteral("keywords");
            d->displayName = i18nc("@label", "Keywords");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::Language:
            d->name = QStringLiteral("language");
            d->displayName = i18nc("@label", "Language");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::LineCount:
            d->name = QStringLiteral("lineCount");
            d->displayName = i18nc("@label number of lines", "Line Count");
            d->valueType = QVariant::Int;
            break;

        case Property::Lyricist:
            d->name = QStringLiteral("lyricist");
            d->displayName = i18nc("@label", "Lyricist");
            d->valueType = QVariant::String;
            break;

        case Property::PageCount:
            d->name = QStringLiteral("pageCount");
            d->displayName = i18nc("@label", "Page Count");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoApertureValue:
            d->name = QStringLiteral("photoApertureValue");
            d->displayName = i18nc("@label EXIF", "Photo Aperture Value");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatAsFNumber;
            break;

        case Property::PhotoDateTimeOriginal:
            d->name = QStringLiteral("photoDateTimeOriginal");
            d->displayName = i18nc("@label EXIF", "Photo Original Date Time");
            d->valueType = QVariant::DateTime;
            d->formatAsString = &FormatStrings::formatDate;
            break;

        case Property::PhotoExposureBiasValue:
            d->name = QStringLiteral("photoExposureBiasValue");
            d->displayName = i18nc("@label EXIF", "Photo Exposure Bias");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatDouble;
            break;

        case Property::PhotoExposureTime:
            d->name = QStringLiteral("photoExposureTime");
            d->displayName = i18nc("@label EXIF", "Photo Exposure Time");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatPhotoTime;
            break;

        case Property::PhotoFlash:
            d->name = QStringLiteral("photoFlash");
            d->displayName = i18nc("@label EXIF", "Photo Flash");
            d->valueType = QVariant::Int;
            d->formatAsString = &FormatStrings::formatPhotoFlashValue;
            break;

        case Property::PhotoFNumber:
            d->name = QStringLiteral("photoFNumber");
            d->displayName = i18nc("@label EXIF", "Photo F Number");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatAsFNumber;
            break;

        case Property::PhotoFocalLength:
            d->name = QStringLiteral("photoFocalLength");
            d->displayName = i18nc("@label EXIF", "Photo Focal Length");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatDouble;
            break;

        case Property::PhotoFocalLengthIn35mmFilm:
            d->name = QStringLiteral("photoFocalLengthIn35mmFilm");
            d->displayName = i18nc("@label EXIF", "Photo Focal Length 35mm");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatDouble;
            break;

        case Property::PhotoGpsLatitude:
            d->name = QStringLiteral("photoGpsLatitude");
            d->displayName = i18nc("@label EXIF", "Photo GPS Latitude");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatAsDegree;
            break;

        case Property::PhotoGpsLongitude:
            d->name = QStringLiteral("photoGpsLongitude");
            d->displayName = i18nc("@label EXIF", "Photo GPS Longitude");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatAsDegree;
            break;

        case Property::PhotoGpsAltitude:
            d->name = QStringLiteral("photoGpsAltitude");
            d->displayName = i18nc("@label EXIF", "Photo GPS Altitude");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatAsMeter;
            break;

        case Property::PhotoISOSpeedRatings:
            d->name = QStringLiteral("photoISOSpeedRatings");
            d->displayName = i18nc("@label EXIF", "Photo ISO Speed Rating");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoMeteringMode:
            d->name = QStringLiteral("photoMeteringMode");
            d->displayName = i18nc("@label EXIF", "Photo Metering Mode");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoPixelXDimension:
            d->name = QStringLiteral("photoPixelXDimension");
            d->displayName = i18nc("@label EXIF", "Photo X Dimension");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoPixelYDimension:
            d->name = QStringLiteral("photoPixelYDimension");
            d->displayName = i18nc("@label EXIF", "Photo Y Dimension");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoSaturation:
            d->name = QStringLiteral("photoSaturation");
            d->displayName = i18nc("@label EXIF", "Photo Saturation");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoSharpness:
            d->name = QStringLiteral("photoSharpness");
            d->displayName = i18nc("@label EXIF", "Photo Sharpness");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoWhiteBalance:
            d->name = QStringLiteral("photoWhiteBalance");
            d->displayName = i18nc("@label EXIF", "Photo White Balance");
            d->valueType = QVariant::Int;
            break;

        case Property::Publisher:
            d->name = QStringLiteral("publisher");
            d->displayName = i18nc("@label", "Publisher");
            d->valueType = QVariant::String;
            break;

        case Property::Label:
            d->name = QStringLiteral("label");
            d->displayName = i18nc("@label", "Label");
            d->valueType = QVariant::String;
            break;

        case Property::ReleaseYear:
            d->name = QStringLiteral("releaseYear");
            d->displayName = i18nc("@label", "Release Year");
            d->valueType = QVariant::Int;
            break;

        case Property::SampleRate:
            d->name = QStringLiteral("sampleRate");
            d->displayName = i18nc("@label", "Sample Rate");
            d->valueType = QVariant::Int;
            d->formatAsString = &FormatStrings::formatSampleRate;
            break;

        case Property::Subject:
            d->name = QStringLiteral("subject");
            d->displayName = i18nc("@label", "Subject");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::Title:
            d->name = QStringLiteral("title");
            d->displayName = i18nc("@label", "Title");
            d->valueType = QVariant::String;
            break;

        case Property::TrackNumber:
            d->name = QStringLiteral("trackNumber");
            d->displayName = i18nc("@label music track number", "Track Number");
            d->valueType = QVariant::Int;
            break;

        case Property::DiscNumber:
            d->name = QStringLiteral("discNumber");
            d->displayName = i18nc("@label music disc number", "Disc Number");
            d->valueType = QVariant::Int;
            break;

        case Property::Location:
            d->name = QStringLiteral("location");
            d->displayName = i18nc("@label", "Location");
            d->valueType = QVariant::String;
            break;

        case Property::Performer:
            d->name = QStringLiteral("performer");
            d->displayName = i18nc("@label", "Performer");
            d->valueType = QVariant::String;
            break;

        case Property::Ensemble:
            d->name = QStringLiteral("ensemble");
            d->displayName = i18nc("@label", "Ensemble");
            d->valueType = QVariant::String;
            break;

        case Property::Arranger:
            d->name = QStringLiteral("arranger");
            d->displayName = i18nc("@label", "Arranger");
            d->valueType = QVariant::String;
            break;

        case Property::Conductor:
            d->name = QStringLiteral("conductor");
            d->displayName = i18nc("@label", "Conductor");
            d->valueType = QVariant::String;
            break;

        case Property::Compilation:
            d->name = QStringLiteral("compilation");
            d->displayName = i18nc("@label", "Compilation");
            d->valueType = QVariant::String;
            break;

        case Property::License:
            d->name = QStringLiteral("license");
            d->displayName = i18nc("@label", "License");
            d->valueType = QVariant::String;
            break;

        case Property::Lyrics:
            d->name = QStringLiteral("lyrics");
            d->displayName = i18nc("@label", "Lyrics");
            d->valueType = QVariant::String;
            break;

        case Property::Opus:
            d->name = QStringLiteral("opus");
            d->displayName = i18nc("@label", "Opus");
            d->valueType = QVariant::Int;
            break;

        case Property::Rating:
            d->name = QStringLiteral("embeddedRating");
            d->displayName = i18nc("@label", "Rating");
            d->valueType = QVariant::Int;
            break;

        case Property::ReplayGainAlbumPeak:
            d->name = QStringLiteral("replayGainAlbumPeak");
            d->displayName = i18nc("@label", "Replay Gain Album Peak");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatDouble;
            break;

        case Property::ReplayGainAlbumGain:
            d->name = QStringLiteral("replayGainAlbumGain");
            d->displayName = i18nc("@label", "Replay Gain Album Gain");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatDouble;
            break;

        case Property::ReplayGainTrackPeak:
            d->name = QStringLiteral("replayGainTrackPeak");
            d->displayName = i18nc("@label", "Replay Gain Track Peak");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatDouble;
            break;

        case Property::ReplayGainTrackGain:
            d->name = QStringLiteral("replayGainTrackGain");
            d->displayName = i18nc("@label", "Replay Gain Track Gain");
            d->valueType = QVariant::Double;
            d->formatAsString = &FormatStrings::formatDouble;
            break;

        case Property::Width:
            d->name = QStringLiteral("width");
            d->displayName = i18nc("@label", "Width");
            d->valueType = QVariant::Int;
            break;

        case Property::WordCount:
            d->name = QStringLiteral("wordCount");
            d->displayName = i18nc("@label number of words", "Word Count");
            d->valueType = QVariant::Int;
            break;

        case Property::TranslationUnitsTotal:
            d->name = QStringLiteral("translationUnitsTotal");
            d->displayName = i18nc("@label number of translatable strings",
                                   "Translatable Units");
            d->valueType = QVariant::Int;
            d->shouldBeIndexed = false;
            break;

        case Property::TranslationUnitsWithTranslation:
            d->name = QStringLiteral("translationUnitsWithTranslation");
            d->displayName = i18nc("@label number of translated strings", "Translations");
            d->valueType = QVariant::Int;
            d->shouldBeIndexed = false;
            break;

        case Property::TranslationUnitsWithDraftTranslation:
            d->name = QStringLiteral("translationUnitsWithDraftTranslation");
            d->displayName = i18nc("@label number of fuzzy translated strings",
                                   "Draft Translations");
            d->valueType = QVariant::Int;
            d->shouldBeIndexed = false;
            break;

        case Property::TranslationLastAuthor:
            d->name = QStringLiteral("translationLastAuthor");
            d->displayName = i18nc("@label translation author", "Author");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::TranslationLastUpDate:
            d->name = QStringLiteral("translationLastUpDate");
            d->displayName = i18nc("@label translations last update", "Last Update");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            d->formatAsString = &FormatStrings::formatDate;
            break;

        case Property::TranslationTemplateDate:
            d->name = QStringLiteral("translationTemplateDate");
            d->displayName = i18nc("@label date of template creation8", "Template Creation");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            d->formatAsString = &FormatStrings::formatDate;
            break;

        case Property::OriginUrl:
            d->name = QStringLiteral("originUrl");
            d->displayName = i18nc("@label the URL a file was originally downloaded from", "Downloaded From");
            d->valueType = QVariant::Url;
            d->shouldBeIndexed = false;
            break;

        case Property::OriginEmailSubject:
            d->name = QStringLiteral("originEmailSubject");
            d->displayName = i18nc("@label the subject of an email this file was attached to", "E-Mail Attachment Subject");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::OriginEmailSender:
            d->name = QStringLiteral("originEmailSender");
            d->displayName = i18nc("@label the sender of an email this file was attached to", "E-Mail Attachment Sender");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::OriginEmailMessageId:
            d->name = QStringLiteral("originEmailMessageId");
            d->displayName = i18nc("@label the message ID of an email this file was attached to", "E-Mail Attachment Message ID");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::PropertyCount: // To silence the compiler.
            break;

        // NOTE: new properties must also be added to ::fromName()
    }

    if (d->valueType == QVariant::Int || d->valueType == QVariant::DateTime ||
        d->valueType == QVariant::Double)
    {
        d->shouldBeIndexed = false;
    }
}

PropertyInfo::PropertyInfo(const PropertyInfo& pi)
    : d(new Private(*pi.d))
{
}

PropertyInfo::~PropertyInfo()
{
    delete d;
}

PropertyInfo& PropertyInfo::operator=(const PropertyInfo& rhs)
{
    *d = *rhs.d;
    return *this;
}

bool PropertyInfo::operator==(const PropertyInfo& rhs) const
{
    return d->name == rhs.d->name && d->displayName == rhs.d->displayName &&
           d->prop == rhs.d->prop && d->shouldBeIndexed == rhs.d->shouldBeIndexed;
}

QString PropertyInfo::displayName() const
{
    return d->displayName;
}

QString PropertyInfo::name() const
{
    return d->name;
}

Property::Property PropertyInfo::property() const
{
    return d->prop;
}

QVariant::Type PropertyInfo::valueType() const
{
    return d->valueType;
}

bool PropertyInfo::shouldBeIndexed() const
{
    return d->shouldBeIndexed;
}

QString PropertyInfo::formatAsDisplayString(const QVariant &value) const
{
    if (value.type() == QVariant::List || value.type() == QVariant::StringList) {
        if (d->valueType == QVariant::String) {
            return QLocale().createSeparatedList(value.toStringList());
        } else {
            QStringList displayList;
            const auto valueList = value.toList();
            for (const auto& entry : valueList) {
                displayList << d->formatAsString(entry);
            }
            return QLocale().createSeparatedList(displayList);
        }
    } else {
        return d->formatAsString(value);
    }
}

PropertyInfo PropertyInfo::fromName(const QString& name)
{
    static QHash<QString, Property::Property> propertyHash = {
        { QStringLiteral("bitrate"), Property::BitRate },
        { QStringLiteral("channels"), Property::Channels },
        { QStringLiteral("duration"), Property::Duration },
        { QStringLiteral("genre"), Property::Genre },
        { QStringLiteral("samplerate"), Property::SampleRate },
        { QStringLiteral("tracknumber"), Property::TrackNumber },
        { QStringLiteral("discnumber"), Property::DiscNumber },
        { QStringLiteral("releaseyear"), Property::ReleaseYear },
        { QStringLiteral("comment"), Property::Comment },
        { QStringLiteral("description"), Property::Description },
        { QStringLiteral("artist"), Property::Artist },
        { QStringLiteral("album"), Property::Album },
        { QStringLiteral("albumartist"), Property::AlbumArtist },
        { QStringLiteral("composer"), Property::Composer },
        { QStringLiteral("lyricist"), Property::Lyricist },
        { QStringLiteral("location"), Property::Location },
        { QStringLiteral("performer"), Property::Performer },
        { QStringLiteral("ensemble"), Property::Ensemble },
        { QStringLiteral("arranger"), Property::Arranger },
        { QStringLiteral("conductor"), Property::Conductor },
        { QStringLiteral("opus"), Property::Opus },
        { QStringLiteral("embeddedrating"), Property::Rating },
        { QStringLiteral("author"), Property::Author },
        { QStringLiteral("title"), Property::Title },
        { QStringLiteral("subject"), Property::Subject },
        { QStringLiteral("generator"), Property::Generator },
        { QStringLiteral("pagecount"), Property::PageCount },
        { QStringLiteral("wordcount"), Property::WordCount },
        { QStringLiteral("linecount"), Property::LineCount },
        { QStringLiteral("language"), Property::Language },
        { QStringLiteral("copyright"), Property::Copyright },
        { QStringLiteral("publisher"), Property::Publisher },
        { QStringLiteral("label"), Property::Label },
        { QStringLiteral("compilation"), Property::Compilation },
        { QStringLiteral("license"), Property::License },
        { QStringLiteral("lyrics"), Property::Lyrics },
        { QStringLiteral("replaygainalbumpeak"), Property::ReplayGainAlbumPeak },
        { QStringLiteral("replaygainalbumgain"), Property::ReplayGainAlbumGain },
        { QStringLiteral("replaygaintrackpeak"), Property::ReplayGainTrackPeak },
        { QStringLiteral("replaygaintrackgain"), Property::ReplayGainTrackGain },
        { QStringLiteral("creationdate"), Property::CreationDate },
        { QStringLiteral("keywords"), Property::Keywords },
        { QStringLiteral("width"), Property::Width },
        { QStringLiteral("height"), Property::Height },
        { QStringLiteral("aspectratio"), Property::AspectRatio },
        { QStringLiteral("framerate"), Property::FrameRate },
        { QStringLiteral("imagemake"), Property::ImageMake },
        { QStringLiteral("imagemodel"), Property::ImageModel },
        { QStringLiteral("imagedatetime"), Property::ImageDateTime },
        { QStringLiteral("imageorientation"), Property::ImageOrientation },
        { QStringLiteral("photoflash"), Property::PhotoFlash },
        { QStringLiteral("photopixelxdimension"), Property::PhotoPixelXDimension },
        { QStringLiteral("photopixelydimension"), Property::PhotoPixelYDimension },
        { QStringLiteral("photodatetimeoriginal"), Property::PhotoDateTimeOriginal },
        { QStringLiteral("photofocallength"), Property::PhotoFocalLength },
        { QStringLiteral("photofocallengthin35mmfilm"), Property::PhotoFocalLengthIn35mmFilm },
        { QStringLiteral("photoexposuretime"), Property::PhotoExposureTime },
        { QStringLiteral("photofnumber"), Property::PhotoFNumber },
        { QStringLiteral("photoaperturevalue"), Property::PhotoApertureValue },
        { QStringLiteral("photoexposurebiasvalue"), Property::PhotoExposureBiasValue },
        { QStringLiteral("photowhitebalance"), Property::PhotoWhiteBalance },
        { QStringLiteral("photometeringmode"), Property::PhotoMeteringMode },
        { QStringLiteral("photoisospeedratings"), Property::PhotoISOSpeedRatings },
        { QStringLiteral("photosaturation"), Property::PhotoSaturation },
        { QStringLiteral("photosharpness"), Property::PhotoSharpness },
        { QStringLiteral("photogpslatitude"), Property::PhotoGpsLatitude },
        { QStringLiteral("photogpslongitude"), Property::PhotoGpsLongitude },
        { QStringLiteral("photogpsaltitude"), Property::PhotoGpsAltitude },
        { QStringLiteral("translationunitstotal"), Property::TranslationUnitsTotal },
        { QStringLiteral("translationunitswithtranslation"), Property::TranslationUnitsWithTranslation },
        { QStringLiteral("translationunitswithdrafttranslation"), Property::TranslationUnitsWithDraftTranslation },
        { QStringLiteral("translationlastauthor"), Property::TranslationLastAuthor },
        { QStringLiteral("translationlastupdate"), Property::TranslationLastUpDate },
        { QStringLiteral("translationtemplatedate"), Property::TranslationTemplateDate },
        { QStringLiteral("originurl"), Property::OriginUrl },
        { QStringLiteral("originemailsubject"), Property::OriginEmailSubject },
        { QStringLiteral("originemailsender"), Property::OriginEmailSender },
        { QStringLiteral("originemailmessageid"), Property::OriginEmailMessageId }
    };

    return PropertyInfo(propertyHash.value(name.toLower()));
}
