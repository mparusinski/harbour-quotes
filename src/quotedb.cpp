#include "quotedb.h"

#include <sailfishapp.h>

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QDir>

QuoteDB::QuoteDB(QObject *parent) :
    QObject(parent)
{
    readQuotesFile(SailfishApp::pathTo("qml/content/quotes_en.txt"));
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

    QTextStream quotesStream(&quotesFile);
    quotesStream.setCodec("UTF-8");
    QString line = quotesStream.readLine();
    while (!line.isNull()) {
        QStringList tokens = line.split(":");
        if (tokens.length() != 2) {
            qCritical() << "File is malformed, line \"" << line << "\" does not have two tokens";
            quotesFile.close();
            return false;
        }
        QString quoteText = tokens[0];
        QString philosopher = tokens[1];
        qDebug() << philosopher;
        Quote::QuotePtr currentQuote(new Quote(philosopher, quoteText));
        m_quotes.push_back(currentQuote);

        line = quotesStream.readLine();
    }

    quotesFile.close();
    return true;
}
