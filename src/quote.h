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

#ifndef QUOTE_H
#define QUOTE_H

#include <QObject>
#include <QString>
#include <QSharedPointer>
#include "quotesidregistry.h"

class QuotesIDRegistry;

class Quote {
public:
    typedef QSharedPointer<Quote> QuotePtr;

    Quote();

    Quote(const QString& philosopher, const QString& quote);

    QString philosopher() const;

    QString quote() const;

    void setID(u_int32_t idNum);

    u_int32_t uniqueID() const;

private:
    Q_DISABLE_COPY(Quote)

    QString m_philosopher;
    QString m_quote;
    u_int32_t m_uniqueID;
};

Quote::QuotePtr getQuoteWithID(u_int32_t idNum);

Quote::QuotePtr createRegisteredQuote(const QString& philosopher, const QString& quote);

void registerQuote(const Quote::QuotePtr& quote);

bool quoteptrCompare(Quote::QuotePtr left, Quote::QuotePtr right);

#endif // QUOTE_H
