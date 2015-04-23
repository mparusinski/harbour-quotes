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
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QStringList>
#include <QDir>

#include <zlib.h>
#include <algorithm>

QuotesReaderThread::QuotesReaderThread() {
    m_quotes = QuotesDBContainerPtr(new QuotesDBContainerType);
    m_authors = AuthorsDBContainerPtr(new AuthorsDBContainerType);
}

void QuotesReaderThread::run() {
    readQuotes();
    emit quotesRead();
}

bool QuotesReaderThread::readQuotes() {
    QUrl directoryUrl = SailfishApp::pathTo("./");
    QDir directory(directoryUrl.toLocalFile());
    QStringList nameFilters;
    nameFilters.append("*.json");
    QStringList files = directory.entryList(nameFilters);
    if (files.length() == 0) {
        qCritical() << "No valid JSON file found";
    }
    QStringList::Iterator iter;
    for (iter = files.begin(); iter != files.end(); ++iter) {
        const QString& file = *iter;
        QUrl pathToFile = SailfishApp::pathTo(file);
        if (!readQuotesFile(pathToFile)) {
            return false;
        }
    }
    for (AuthorsDBContainerType::const_iterator iter = m_authors->begin();
            iter != m_authors->end(); ++iter) {
        AuthorsQuotesDBContainerPtr authorsQuotes = (*m_quotes)[*iter];
        std::sort(authorsQuotes->begin(), authorsQuotes->end(), quoteptrCompare);
    }
    return true;
}

QString QuotesReaderThread::readZFile(QUrl& pathToFile) {
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

QString QuotesReaderThread::readRegularFile(QUrl& pathToFile) {
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

bool QuotesReaderThread::readQuotesFile(QUrl pathToFile) {
    QString fileContent = readRegularFile(pathToFile);
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

        Quote::QuotePtr quote = createRegisteredQuote(philosopher, quoteText);

        m_authors->insert(philosopher);
        if (m_quotes->find(philosopher) == m_quotes->end()) {
            (*m_quotes)[philosopher] = AuthorsQuotesDBContainerPtr(new AuthorsQuotesDBContainerType);
        }
        AuthorsQuotesDBContainerPtr authorsQuotes = (*m_quotes)[philosopher];
        authorsQuotes->push_back(quote);
    }

    return true;
}

QuotesDBContainerPtr QuotesReaderThread::retrieveQuotes() const {
    return m_quotes;
}

AuthorsDBContainerPtr QuotesReaderThread::retrieveAuthors() const {
    return m_authors;
}

QuoteDB::QuoteDB(QObject * parent) : QObject(parent) {
    m_readerThread = new QuotesReaderThread();
}

void QuoteDB::asyncDBInit() {
    connect(m_readerThread, &QuotesReaderThread::quotesRead, this, &QuoteDB::threadFinishedReadingQuotes);
    m_readerThread->start();
}

void QuoteDB::threadFinishedReadingQuotes() {
    m_quotes = m_readerThread->retrieveQuotes();
    m_authors = m_readerThread->retrieveAuthors();
    emit quotesRead();
}

QuotesDBContainerPtr QuoteDB::getQuotes() const {
    return m_quotes;
}

AuthorsDBContainerPtr QuoteDB::getAuthors() const {
    return m_authors;
}

