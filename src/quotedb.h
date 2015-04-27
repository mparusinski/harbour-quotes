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

#ifndef QUOTEDB_H
#define QUOTEDB_H

#include <QThread>
#include <QSharedPointer>
#include <map>
#include <vector>

#include "quote.h"

typedef std::vector<Quote::QuotePtr> AuthorsQuotesDBContainerType;
typedef QSharedPointer< AuthorsQuotesDBContainerType > AuthorsQuotesDBContainerPtr;
typedef std::map<QString, AuthorsQuotesDBContainerPtr> QuotesDBContainerType;
typedef QSharedPointer< QuotesDBContainerType > QuotesDBContainerPtr;
typedef std::set<QString> AuthorsDBContainerType;
typedef QSharedPointer< AuthorsDBContainerType > AuthorsDBContainerPtr;

class QuotesReaderThread : public QThread {
    Q_OBJECT
public:
    QuotesReaderThread();

    bool readQuotes();

    void run() Q_DECL_OVERRIDE;

    QuotesDBContainerPtr retrieveQuotes() const;

    AuthorsDBContainerPtr retrieveAuthors() const;

signals:
    void quotesRead();

private:   
    bool readQuotesFile(QUrl filepath);

    QString readRegularFile(QUrl& pathToFile);

    QuotesDBContainerPtr m_quotes;
    AuthorsDBContainerPtr m_authors;
};

class QuoteDB : public QObject {
    Q_OBJECT
public:
    QuoteDB(QObject* parent = 0);

    void asyncDBInit();

    QuotesDBContainerPtr getQuotes() const;

    AuthorsDBContainerPtr getAuthors() const;

public slots:
    void threadFinishedReadingQuotes();

signals:
    void quotesRead();

private:
    Q_DISABLE_COPY(QuoteDB)

    QuotesDBContainerPtr m_quotes;
    AuthorsDBContainerPtr m_authors;
    QuotesReaderThread * m_readerThread;
};

#endif  // QUOTEDB_H
