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

#ifndef QUOTECONTROLLER_H
#define QUOTECONTROLLER_H

#include <QObject>

#include "quote.h"
#include "quotedb.h"

class QuoteController : public QObject
{
    Q_OBJECT
public:
    explicit QuoteController(QObject *parent = 0);

    Q_INVOKABLE QString getQuoteText() const;

    Q_INVOKABLE QString getPhilosopherText() const;

    Q_INVOKABLE void updateQuote();

signals:

public slots:

private:
    QuoteDB m_quotesDB;
    Quote::QuotePtr m_currentQuote;

};

#endif // QUOTECONTROLLER_H
