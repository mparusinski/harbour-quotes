/*
  Copyright 2015 Michal Parusinski <mparusinski@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include "quotedb.h"

#include <sailfishapp.h>

#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QStringList>
#include <QDir>

#include <vector>
#include <zlib.h>

QuoteDB * QuoteDB::instance = NULL;

QuoteDB::QuoteDB(void) {
    m_visitorSet = false;
}

QuoteDB * QuoteDB::getQuoteDB() {
    if (instance == NULL) {
        instance = new QuoteDB;
    }

    return instance;
}

bool QuoteDB::readQuotes() {
    QUrl directoryUrl = SailfishApp::pathTo("qml/content");
    QDir directory(directoryUrl.toLocalFile());
    QStringList nameFilters;
    nameFilters.append("*.json.gz");
    QStringList files = directory.entryList(nameFilters);
    QStringList::Iterator iter;
    for (iter = files.begin(); iter != files.end(); ++iter) {
        const QString& file = *iter;
        QUrl pathToFile = SailfishApp::pathTo("qml/content/" + file);
        if (!readQuotesFile(pathToFile)) {
            return false;
        }
    }
    return true;
}

int QuoteDB::numQuotes() const {
    return m_quotes.size();
}

QString QuoteDB::readZFile(QUrl& pathToFile) {
    QString localFile = pathToFile.toLocalFile();
    gzFile inFileZ = gzopen(localFile.toStdString().c_str(), "rb");
    if (inFileZ == NULL) {
        qCritical() << "Unable to open file " << qPrintable(localFile);
        qDebug() << "Current path is " << QDir::currentPath();
        return "";
    }
    char unzipBuffer[8192];
    int unzippedBytes;
    std::vector<char> unzippedData;
    while (true) {
        unzippedBytes = gzread(inFileZ, unzipBuffer, 8192);
        if (unzippedBytes > 0) {
            for (int i = 0; i < unzippedBytes; i++) {
                unzippedData.push_back(unzipBuffer[i]);
            }
        } else {
            break;
        }
    }
    gzclose(inFileZ);
    return QString::fromUtf8(&unzippedData[0]);
}

QString QuoteDB::readRegularFile(QUrl& pathToFile) {
    QString localFile = pathToFile.toLocalFile();
    QFile quotesFile(localFile);
    if (!quotesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Unable to open file " << qPrintable(localFile);
        qDebug() << "Current path is " << QDir::currentPath();
        return "";
    }

    QString content = quotesFile.readAll();
    quotesFile.close();
    return content;
}

bool QuoteDB::readQuotesFile(QUrl pathToFile) {
    QString fileContent = readZFile(pathToFile);
    QJsonParseError parseError;
    QJsonDocument jsonDoc
      = QJsonDocument::fromJson(fileContent.toUtf8(), &parseError);
    qWarning() << parseError.errorString();

    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray quotes = jsonObj["quotes"].toArray();

    if (quotes == QJsonArray()) {
        qCritical() << "Malformed JSON file";
        return false;
    }

    QJsonArray::const_iterator iter;
    for (iter = quotes.constBegin(); iter != quotes.constEnd(); ++iter) {
        const QJsonObject jsonQuoteObj = (*iter).toObject();
        QString quoteText = jsonQuoteObj["quoteText"].toString();
        QString philosopher = jsonQuoteObj["philosopher"].toString();

        Quote::QuotePtr quote(new Quote(philosopher, quoteText));
        m_quotes.insert(quoteText, quote);  // some way to guarantee sortedness
        m_quotesByIDs.insert(quote->uniqueID(), quote);
    }

    return true;
}

QuoteDB::ContainerType& QuoteDB::getQuotes() {
    return m_quotes;
}

Quote::QuotePtr QuoteDB::getQuoteWithID(u_int32_t id) const {
    QMap<u_int32_t, Quote::QuotePtr>::const_iterator iter
      = m_quotesByIDs.find(id);
    if (iter != m_quotesByIDs.end()) {
        return iter.value();
    } else {
        return Quote::QuotePtr();
    }
}
