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

#ifndef QUOTEDB_H
#define QUOTEDB_H

#include <QObject>
#include <QMap>

#include "quote.h"

class QuoteDB : public QObject
{
    Q_OBJECT
public:
    typedef QMap<QString, Quote::QuotePtr> ContainerType;
    typedef QMapIterator<QString, Quote::QuotePtr> ContainerIteratorType;
    typedef QMutableMapIterator<QString, Quote::QuotePtr> ContainerMutableIteratorType;

    Quote::QuotePtr nextQuote();

    ContainerType& getQuotes();

    static QuoteDB* getQuoteDB();

signals:

public slots:

private:
    ContainerType m_quotes;
    bool m_visitorSet;
    ContainerType::ConstIterator m_visitorIterator;
    static QuoteDB * instance;

    QuoteDB(QObject *parent = 0);

    bool readQuotesFile(QUrl pathToFile);
};

#endif // QUOTEDB_H
