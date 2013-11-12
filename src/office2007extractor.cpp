/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2013  Vishesh Handa <me@vhanda.in>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "office2007extractor.h"

#include <KDE/KDebug>
#include <KDE/KZip>

#include <QtXml/QDomDocument>
#include <QtXml/QXmlStreamReader>

using namespace KMetaData;

Office2007Extractor::Office2007Extractor(QObject* parent, const QVariantList&): ExtractorPlugin(parent)
{

}


QStringList Office2007Extractor::mimetypes()
{
    QStringList list;
    list << QLatin1String("application/vnd.openxmlformats-officedocument.wordprocessingml.document")
         << QLatin1String("application/vnd.openxmlformats-officedocument.presentationml.presentation")
         << QLatin1String("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

    return list;
}

QVariantMap Office2007Extractor::extract(const QString& fileUrl, const QString& mimeType)
{
    Q_UNUSED(mimeType);
    QVariantMap metadata;

    KZip zip(fileUrl);
    if (!zip.open(QIODevice::ReadOnly)) {
        qWarning() << "Document is not a valid ZIP archive";
        return metadata;
    }

    const KArchiveDirectory* rootDir = zip.directory();
    if (!rootDir) {
        qWarning() << "Invalid document structure (main directory is missing)";
        return metadata;
    }

    const QStringList rootEntries = rootDir->entries();
    if (!rootEntries.contains("docProps")) {
        qWarning() << "Invalid document structure (docProps is missing)";
        return metadata;
    }

    const KArchiveEntry* docPropEntry = rootDir->entry("docProps");
    if (!docPropEntry->isDirectory()) {
        qWarning() << "Invalid document structure (docProps is not a directory)";
        return metadata;
    }

    const KArchiveDirectory* docPropDirectory = dynamic_cast<const KArchiveDirectory*>(docPropEntry);
    const QStringList docPropsEntries = docPropDirectory->entries();

    if (docPropsEntries.contains("core.xml")) {
        QDomDocument coreDoc("core");
        const KArchiveFile* file = static_cast<const KArchiveFile*>(docPropDirectory->entry("core.xml"));
        coreDoc.setContent(file->data());

        QDomElement docElem = coreDoc.documentElement();

        QDomElement elem = docElem.firstChildElement("dc:description");
        if (!elem.isNull()) {
            QString str = elem.text();
            if (!str.isEmpty()) {
                metadata.insert("dc:description", str);
            }
        }

        elem = docElem.firstChildElement("dc:subject");
        if (!elem.isNull()) {
            QString str = elem.text();
            if (!str.isEmpty()) {
                metadata.insert("dc:subject", str);
            }
        }

        elem = docElem.firstChildElement("dc:title");
        if (!elem.isNull()) {
            QString str = elem.text();
            if (!str.isEmpty()) {
                metadata.insert("dc:title", str);
            }
        }

        elem = docElem.firstChildElement("dc:creator");
        if (!elem.isNull()) {
            QString str = elem.text();
            if (!str.isEmpty()) {
                metadata.insert("dc:creator", str);
            }
        }

        elem = docElem.firstChildElement("dc:langauge");
        if (!elem.isNull()) {
            QString str = elem.text();
            if (!str.isEmpty()) {
                metadata.insert("dc:langauge", str);
            }
        }
    }

    if (docPropsEntries.contains("app.xml")) {
        QDomDocument appDoc("app");
        const KArchiveFile* file = static_cast<const KArchiveFile*>(docPropDirectory->entry("app.xml"));
        appDoc.setContent(file->data());

        QDomElement docElem = appDoc.documentElement();

        // According to the ontologies only Documents can have a wordCount and pageCount
        if (mimeType == QLatin1String("application/vnd.openxmlformats-officedocument.wordprocessingml.document")) {
            QDomElement elem = docElem.firstChildElement("Pages");
            if (!elem.isNull()) {
                bool ok = false;
                int pageCount = elem.text().toInt(&ok);
                if (ok) {
                    metadata.insert("pageCount", pageCount);
                }
            }

            elem = docElem.firstChildElement("Words");
            if (!elem.isNull()) {
                bool ok = false;
                int wordCount = elem.text().toInt(&ok);
                if (ok) {
                    metadata.insert("wordCount", wordCount);
                }
            }
        }

        QDomElement elem = docElem.firstChildElement("Application");
        if (!elem.isNull()) {
            QString app = elem.text();
            if (!app.isEmpty()) {
                metadata.insert("generator", app);
            }
        }
    }


    if (rootEntries.contains("word")) {
        const KArchiveEntry* wordEntry = rootDir->entry("word");
        if (!wordEntry->isDirectory()) {
            qWarning() << "Invalid document structure (word is not a directory)";
            return metadata;
        }

        const KArchiveDirectory* wordDirectory = dynamic_cast<const KArchiveDirectory*>(wordEntry);
        const QStringList wordEntries = wordDirectory->entries();

        if (wordEntries.contains("document.xml")) {
            QDomDocument appDoc("document");
            const KArchiveFile* file = static_cast<const KArchiveFile*>(wordDirectory->entry("document.xml"));

            QString plainText;
            QTextStream stream(&plainText);

            extractTextWithTag(file->createDevice(), QLatin1String("w:t"), stream);
            if (!plainText.isEmpty())
                metadata.insert("text", plainText);
        }
    }

    else if (rootEntries.contains("xl")) {
        const KArchiveEntry* xlEntry = rootDir->entry("xl");
        if (!xlEntry->isDirectory()) {
            qWarning() << "Invalid document structure (xl is not a directory)";
            return metadata;
        }

        QString plainText;
        QTextStream stream(&plainText);

        const KArchiveDirectory* xlDirectory = dynamic_cast<const KArchiveDirectory*>(xlEntry);
        extractTextFromFiles(xlDirectory, stream);
        if (!plainText.isEmpty())
            metadata.insert("text", plainText);
    }

    else if (rootEntries.contains("ppt")) {
        const KArchiveEntry* pptEntry = rootDir->entry("ppt");
        if (!pptEntry->isDirectory()) {
            qWarning() << "Invalid document structure (ppt is not a directory)";
            return metadata;
        }

        QString plainText;
        QTextStream stream(&plainText);

        const KArchiveDirectory* pptDirectory = dynamic_cast<const KArchiveDirectory*>(pptEntry);
        extractTextFromFiles(pptDirectory, stream);
        if (!plainText.isEmpty())
            metadata.insert("text", plainText);
    }

    return metadata;
}

void Office2007Extractor::extractAllText(QIODevice* device, QTextStream& stream)
{
    QXmlStreamReader xml(device);

    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isCharacters()) {
            QString str = xml.text().toString();
            stream << str;

            if (!str.at(str.length() - 1).isSpace())
                stream << QLatin1Char(' ');
        }

        if (xml.isEndDocument() || xml.hasError())
            break;
    }
}

void Office2007Extractor::extractTextFromFiles(const KArchiveDirectory* archiveDir, QTextStream& stream)
{
    const QStringList entries = archiveDir->entries();
    foreach(const QString & entryName, entries) {
        const KArchiveEntry* entry = archiveDir->entry(entryName);
        if (entry->isDirectory()) {
            const KArchiveDirectory* subDir = dynamic_cast<const KArchiveDirectory*>(entry);
            extractTextFromFiles(subDir, stream);
            continue;
        }

        if (!entryName.endsWith(".xml"))
            continue;

        const KArchiveFile* file = static_cast<const KArchiveFile*>(entry);
        extractAllText(file->createDevice(), stream);
    }
}

void Office2007Extractor::extractTextWithTag(QIODevice* device, const QString& tag, QTextStream& stream)
{
    QXmlStreamReader xml(device);
    int size = 0;

    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.qualifiedName().startsWith(tag) && xml.isStartElement()) {
            QString str = xml.readElementText(QXmlStreamReader::IncludeChildElements).simplified();

            if (!str.isEmpty()) {
                stream << str;
                size += str.size();

                if (!str.at(str.length() - 1).isSpace())
                    stream << QLatin1Char(' ');
            }
        }

        if (xml.isEndDocument() || xml.hasError())
            break;
    }
}

KMETADATA_EXPORT_EXTRACTOR(KMetaData::Office2007Extractor, "nepomukoffice2007extractor")
