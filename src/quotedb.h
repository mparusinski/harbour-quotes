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
#include "quotecontroller.h"

class QuoteController;

class QuotesReaderThread : public QThread {
    Q_OBJECT
public:
    typedef std::vector<Quote::QuotePtr> ContainerType;

    QuotesReaderThread(QSharedPointer<ContainerType>& quotes,
                       QSharedPointer< std::map<u_int32_t, Quote::QuotePtr> >& quotesByIDs);

    bool readQuotes();

    bool readQuotesFile(QUrl filepath);

    QString readRegularFile(QUrl& pathToFile);

    QString readZFile(QUrl& pathToFile);

    void run() Q_DECL_OVERRIDE;

signals:
    void resultReady();

private:
    QSharedPointer<ContainerType> m_quotes;
    QSharedPointer< std::map<u_int32_t, Quote::QuotePtr> > m_quotesByIDs;
};

class QuoteDB : public QObject {
    Q_OBJECT
public:
    typedef std::vector<Quote::QuotePtr> ContainerType;

    void readQuotes(QuoteController* quoteController);

    QSharedPointer<ContainerType>& getQuotes();

    static QuoteDB* getQuoteDB();

    Quote::QuotePtr getQuoteWithID(const u_int32_t id) const;

    int numQuotes() const;

public slots:
    void quotesReady();

private:
    Q_DISABLE_COPY(QuoteDB)

    QSharedPointer<ContainerType> m_quotes;
    QSharedPointer< std::map<u_int32_t, Quote::QuotePtr> > m_quotesByIDs;
    QuotesReaderThread * m_readerThread;
    QuoteController * m_quoteController;
    static QuoteDB * instance;

    QuoteDB(QObject* parent = 0);
};

#endif  // QUOTEDB_H
