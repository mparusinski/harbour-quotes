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

#include <set>
#include <QObject>
#include <QQuickView>

#include "quote.h"
#include "quotedb.h"
#include "quotemodel.h"

class QuoteEngineQMLInterface : public QObject {
    Q_OBJECT
public:
    explicit QuoteEngineQMLInterface(QObject * parent = 0);

    virtual ~QuoteEngineQMLInterface();

    void emitSignalDoneReadingQuotes() const;

signals:
    void doneReadingQuotes() const;

private:

};

class QuoteController : public QObject {
    Q_OBJECT
public:
    void setMainView(const QSharedPointer<QQuickView>& mainView);

    static QuoteController* getQuoteController();

    void addQMLInterface(QuoteEngineQMLInterface* interface);

    void removeQMLInterface(QuoteEngineQMLInterface* interface);

    Q_INVOKABLE void loadQuote(const QString& quoteID);

    Q_INVOKABLE QString getQuote() const;

    Q_INVOKABLE QString getPhilosopher() const;

    Q_INVOKABLE void nextQuote();

    Q_INVOKABLE void prevQuote();

    Q_INVOKABLE void filterUsingSearchString(const QString& searchString);

    Q_INVOKABLE int quoteNumber() const;

    Q_INVOKABLE void readQuotesDB();

    Q_INVOKABLE void setupQuoteModel() const;

    Q_INVOKABLE void buildSearchPageQuoteModel() const;

    void readingQuotesDone() const;

signals:

public slots:

private:
    Q_DISABLE_COPY(QuoteController)

    explicit QuoteController(QObject* parent = 0);

    QSharedPointer<QQuickView> m_mainView;
    Quote::QuotePtr m_currentQuote;
    std::list<Quote::QuotePtr>::iterator m_modelIterator;
    std::set<QuoteEngineQMLInterface*> m_interfaces;

    static QuoteController* instance;
};

#endif // QUOTECONTROLLER_H
