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
#include <QList>

#include "quote.h"

class QuoteDB : public QObject
{
    Q_OBJECT
public:
    explicit QuoteDB(QObject *parent = 0);

    Quote::QuotePtr nextQuote();

signals:

public slots:

private:
    typedef QList<Quote::QuotePtr> ContainerType;
    ContainerType m_quotes;
    bool m_visitorSet;
    ContainerType::ConstIterator m_visitorIterator;

    bool readQuotesFile(QUrl pathToFile);
};

#endif // QUOTEDB_H
