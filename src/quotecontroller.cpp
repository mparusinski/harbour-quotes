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

#include "quotecontroller.h"

#include <sailfishapp.h>
#include <QDebug>
#include <QQmlContext>

QuoteController* QuoteController::instance = NULL;

QuoteEngineQMLInterface::QuoteEngineQMLInterface(QObject * parent)
    : QObject(parent) {
    QuoteController::getQuoteController()->addQMLInterface(this);
}

QuoteEngineQMLInterface::~QuoteEngineQMLInterface() {
    QuoteController::getQuoteController()->removeQMLInterface(this);
}

void QuoteEngineQMLInterface::emitSignalDoneReadingQuotes() const {
    emit doneReadingQuotes();
}

void QuoteController::setMainView(const QSharedPointer<QQuickView>& mainView) {
    m_mainView = mainView;
}

QuoteController* QuoteController::getQuoteController() {
    if (instance == NULL) {
        instance = new QuoteController;
    }

    return instance;
}

QuoteController::QuoteController(QObject * parent) : QObject(parent) {
    // Nothing to do
}

void QuoteController::addQMLInterface(QuoteEngineQMLInterface* interface) {
    m_interfaces.insert(interface);
}

void QuoteController::removeQMLInterface(QuoteEngineQMLInterface* interface) {
    m_interfaces.insert(interface);
}

QString QuoteController::getQuote() const {
    return m_currentQuote->quote();
}

QString QuoteController::getPhilosopher() const {
    return m_currentQuote->philosopher();
}

void QuoteController::nextQuote() {
    QuoteModel::getQuoteModel()->circularNext(m_modelIterator);
    m_currentQuote = *m_modelIterator;
}

void QuoteController::prevQuote() {
    QuoteModel::getQuoteModel()->circularPrev(m_modelIterator);
    m_currentQuote = *m_modelIterator;
}

int QuoteController::quoteNumber() const {
    return QuoteModel::getQuoteModel()->rowCount();
}

void QuoteController::filterUsingSearchString(const QString& searchString) {
    // dead stupid
    QuoteModel::getQuoteModel()->repopulateQuotes();
    QuoteModel::getQuoteModel()->filterUsing(searchString);
}

void QuoteController::loadQuote(const QString& quoteID) {
    u_int32_t realQuoteID = static_cast<u_int32_t>(quoteID.toLongLong());
    m_currentQuote = QuoteDB::getQuoteDB()->getQuoteWithID(realQuoteID);
    m_modelIterator = QuoteModel::getQuoteModel()->getIterToQuote(realQuoteID);
    if (m_currentQuote.isNull()) {
        qWarning() << "Quote with id " << quoteID << "not found";
    }
}

void QuoteController::buildSearchPageQuoteModel() const {
    QuoteModel::getQuoteModel()->repopulateQuotes();
}

void QuoteController::readQuotesDB() {
    // Do this in a thread
    QuoteDB::getQuoteDB()->readQuotes(this);
}

void QuoteController::readingQuotesDone() const {
    qDebug() << "Reading quotes is done";
    for (std::set<QuoteEngineQMLInterface*>::iterator iter = m_interfaces.begin(); iter != m_interfaces.end(); ++iter) {
        QuoteEngineQMLInterface* interface = *iter;
        if (interface != NULL) {
            interface->emitSignalDoneReadingQuotes();
        }
    }
}

void QuoteController::setupQuoteModel() const {
    QQmlContext * rootCtx = m_mainView->rootContext();
    rootCtx->setContextProperty("quoteModel", QuoteModel::getQuoteModel());
}
