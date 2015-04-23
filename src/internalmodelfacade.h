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

#ifndef InternalModelFacade_H
#define InternalModelFacade_H

#include <set>
#include <QObject>
#include <QQuickView>

#include "quote.h"
#include "quotedb.h"
#include "searchpagelistmodel.h"
#include "authorslistmodel.h"

class InternalModelWindow : public QObject {
    Q_OBJECT
public:
    explicit InternalModelWindow(QObject * parent = 0);

    virtual ~InternalModelWindow();

    void emitSignalDoneReadingQuotes() const;

signals:
    void doneReadingQuotes() const;

private:

};

class InternalModelFacade : public QObject {
    Q_OBJECT
public:
    void setMainView(const QSharedPointer<QQuickView>& mainView);

    static InternalModelFacade* getInternalModelFacade();

    void addQMLInterface(InternalModelWindow* interface);

    void removeQMLInterface(InternalModelWindow* interface);

    Q_INVOKABLE void loadQuote(const QString& quoteID);

    Q_INVOKABLE QString getQuote() const;

    Q_INVOKABLE QString getPhilosopher() const;

    Q_INVOKABLE void nextQuote();

    Q_INVOKABLE void prevQuote();

    Q_INVOKABLE void filterSearchPageUsingSearchString(const QString& searchString);

    Q_INVOKABLE int quoteNumber() const;

    Q_INVOKABLE void aynscReadQuotesDB();

    Q_INVOKABLE void setupSearchPageListModel();

    Q_INVOKABLE void buildSearchPageListModel();

    Q_INVOKABLE void setupAuthorsPageListModel();

    Q_INVOKABLE void buildAuthorsPageListModel();

    Q_INVOKABLE void loadAuthor(const QString& author);

signals:

public slots:
   void readingQuotesDone() const;

private:
    Q_DISABLE_COPY(InternalModelFacade)

    explicit InternalModelFacade(QObject* parent = 0);

    QSharedPointer<QQuickView> m_mainView;
    Quote::QuotePtr m_currentQuote;
    SearchPageListModel::QuotesContainerType::iterator m_modelIterator;
    std::set<InternalModelWindow*> m_interfaces;
    QString m_currentAuthor;
    QuoteDB m_quotesDB;
    SearchPageListModel m_searchPageListModel;
    AuthorsListModel m_authorsPageListModel;

    static InternalModelFacade* instance;
};

#endif // InternalModelFacade_H
