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

#include "internalmodelfacade.h"

#include <sailfishapp.h>
#include <QDebug>
#include <QQmlContext>

InternalModelFacade* InternalModelFacade::instance = NULL;

InternalModelWindow::InternalModelWindow(QObject * parent)
    : QObject(parent) {
    InternalModelFacade::getInternalModelFacade()->addQMLInterface(this);
}

InternalModelWindow::~InternalModelWindow() {
    InternalModelFacade::getInternalModelFacade()->removeQMLInterface(this);
}

void InternalModelWindow::emitSignalDoneReadingQuotes() const {
    emit doneReadingQuotes();
}

void InternalModelFacade::setMainView(const QSharedPointer<QQuickView>& mainView) {
    m_mainView = mainView;
}

InternalModelFacade* InternalModelFacade::getInternalModelFacade() {
    if (instance == NULL) {
        instance = new InternalModelFacade;
    }

    return instance;
}

InternalModelFacade::InternalModelFacade(QObject * parent) : QObject(parent), m_quotesDB(this) {
    // Nothing to do
}

void InternalModelFacade::addQMLInterface(InternalModelWindow* interface) {
    m_interfaces.insert(interface);
}

void InternalModelFacade::removeQMLInterface(InternalModelWindow* interface) {
    m_interfaces.insert(interface);
}

QString InternalModelFacade::getQuote() const {
    return m_currentQuote->quote();
}

QString InternalModelFacade::getPhilosopher() const {
    return m_currentQuote->philosopher();
}

void InternalModelFacade::nextQuote() {
    QuoteModel::getQuoteModel()->circularNext(m_modelIterator);
    m_currentQuote = *m_modelIterator;
}

void InternalModelFacade::prevQuote() {
    QuoteModel::getQuoteModel()->circularPrev(m_modelIterator);
    m_currentQuote = *m_modelIterator;
}

int InternalModelFacade::quoteNumber() const {
    return QuoteModel::getQuoteModel()->rowCount();
}

void InternalModelFacade::filterUsingSearchString(const QString& searchString) {
    // dead stupid
    QuoteModel::getQuoteModel()->repopulateQuotes(m_quotesDB.getQuotes());
    QuoteModel::getQuoteModel()->filterUsing(searchString);
}

void InternalModelFacade::loadQuote(const QString& quoteID) {
    u_int32_t realQuoteID = static_cast<u_int32_t>(quoteID.toLongLong());
    m_currentQuote = getQuoteWithID(realQuoteID);
    m_modelIterator = QuoteModel::getQuoteModel()->getIterToQuote(realQuoteID);
}

void InternalModelFacade::buildSearchPageQuoteModel() const {
    QuoteModel::getQuoteModel()->repopulateQuotes(m_quotesDB.getQuotes());
}

void InternalModelFacade::aynscReadQuotesDB() {
    connect(&m_quotesDB, &QuoteDB::quotesRead, this, &InternalModelFacade::readingQuotesDone);
    m_quotesDB.asyncDBInit();
}

void InternalModelFacade::readingQuotesDone() const {
    qDebug() << "Reading quotes is done";
    for (std::set<InternalModelWindow*>::iterator iter = m_interfaces.begin(); iter != m_interfaces.end(); ++iter) {
        InternalModelWindow* interface = *iter;
        if (interface != NULL) {
            interface->emitSignalDoneReadingQuotes();
        }
    }
}

void InternalModelFacade::setupQuoteModel() const {
    QQmlContext * rootCtx = m_mainView->rootContext();
    rootCtx->setContextProperty("quoteModel", QuoteModel::getQuoteModel());
}
