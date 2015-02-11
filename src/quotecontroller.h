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

#ifndef QUOTECONTROLLER_H
#define QUOTECONTROLLER_H

#include <QObject>
#include <QQuickView>

#include "quote.h"
#include "quotedb.h"
#include "quotemodel.h"

class QuoteController : public QObject {
    Q_OBJECT
public:
    typedef QSharedPointer<QuoteModel> QuoteModelPtr;

    explicit QuoteController(const QSharedPointer<QQuickView>& mainView,
      QObject* parent = 0);

    Q_INVOKABLE void loadQuote(const QString& quoteID);

    Q_INVOKABLE QString getQuote() const;

    Q_INVOKABLE QString getPhilosopher() const;

    Q_INVOKABLE void nextQuote();

    Q_INVOKABLE void prevQuote();

    Q_INVOKABLE void filterUsingSearchString(const QString& searchString);

signals:

public slots:

private:
    QSharedPointer<QQuickView> m_mainView;
    Quote::QuotePtr m_currentQuote;
    QuoteModelPtr m_quoteModel;
    QuoteModel::ModelIteratorPtr m_modelIterator;

    void populateModel();
};

#endif // QUOTECONTROLLER_H
