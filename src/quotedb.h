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

#include <QObject>
#include <map>
#include <vector>

#include "quote.h"

class QuoteDB {
public:
    typedef std::vector<Quote::QuotePtr> ContainerType;

    bool readQuotes();

    ContainerType& getQuotes();

    static QuoteDB* getQuoteDB();

    Quote::QuotePtr getQuoteWithID(const u_int32_t id) const;

    int numQuotes() const;

private:
    Q_DISABLE_COPY(QuoteDB)

    ContainerType m_quotes;
    bool m_visitorSet;
    std::map<u_int32_t, Quote::QuotePtr> m_quotesByIDs;
    static QuoteDB * instance;

    QuoteDB();

    bool readQuotesFile(QUrl filepath);

    QString readRegularFile(QUrl& pathToFile);

    QString readZFile(QUrl& pathToFile);
};

#endif  // QUOTEDB_H
