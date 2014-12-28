/*
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

QuoteDB::QuoteDB(QObject *parent) :
    QObject(parent)
{
    if (!readQuotesFile(SailfishApp::pathTo("qml/content/quotes_en.json"))) {
        Quote::QuotePtr emptyQuote = Quote::QuotePtr(new Quote("Quote missing", "No philosopher"));
        m_quotes.push_back(emptyQuote);
    }
    m_visitorSet = false;
}

Quote::QuotePtr QuoteDB::nextQuote() {
    if (!m_visitorSet) {
        m_visitorIterator = m_quotes.begin();
        m_visitorSet = true;
    }

    if (m_visitorIterator == m_quotes.end()) {
        // restarting from beginning
        m_visitorIterator = m_quotes.begin();
    }

    Quote::QuotePtr elem = *m_visitorIterator;
    m_visitorIterator++;
    return elem;
}

bool QuoteDB::readQuotesFile(QUrl pathToFile) {
    QString localFile = pathToFile.toLocalFile();
    QFile quotesFile(localFile);
    if (!quotesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Unable to open file " << qPrintable(localFile);
        qDebug() << "Current path is " << QDir::currentPath();
        return false;
    }

    QString fileContent = quotesFile.readAll();
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileContent.toUtf8(), &parseError);
    qWarning() << parseError.errorString();

    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray quotes = jsonObj["quotes"].toArray();

    if (quotes == QJsonArray()) {
        qCritical() << "Malformed JSON file";
        quotesFile.close();
        return false;
    }

    QJsonArray::const_iterator iter;
    for (iter = quotes.constBegin(); iter != quotes.constEnd(); ++iter) {
        const QJsonObject jsonQuoteObj = (*iter).toObject();
        QString quoteText = jsonQuoteObj["quoteText"].toString();
        QString philosopher = jsonQuoteObj["philosopher"].toString();

        qDebug() << philosopher;

        Quote::QuotePtr quote(new Quote(philosopher, quoteText));
        m_quotes.push_back(quote);
    }

    quotesFile.close();
    return true;
}
