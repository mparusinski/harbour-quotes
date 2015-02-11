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

#include <QDebug>
#include <QQmlContext>

QuoteController::QuoteController(const QSharedPointer<QQuickView>& mainView,
                                 QObject * parent) : QObject(parent) {
    m_mainView = mainView;
    m_quoteModel = QuoteModelPtr(new QuoteModel());
    populateModel();
}

QString QuoteController::getQuote() const {
    return m_currentQuote->quote();
}

QString QuoteController::getPhilosopher() const {
    return m_currentQuote->philosopher();
}

void QuoteController::nextQuote()  {
    if (m_modelIterator->hasNext()) {
        m_currentQuote = m_modelIterator->next();
    } else {
        m_modelIterator->toFront();
        m_currentQuote = m_modelIterator->next();
    }
}

void QuoteController::prevQuote()  {
    if (m_modelIterator->hasPrevious()) {
        m_currentQuote = m_modelIterator->previous();
    } else {
        m_modelIterator->toBack();
        m_currentQuote = m_modelIterator->previous();
    }
}

void QuoteController::filterUsingSearchString(const QString& searchString) {
    // dead stupid
    m_quoteModel->repopulateQuotes();
    m_quoteModel->filterUsing(searchString);
}

void QuoteController::populateModel() {
    QQmlContext * rootCtx = m_mainView->rootContext();
    rootCtx->setContextProperty("quoteModel", &(*m_quoteModel));
    m_quoteModel->repopulateQuotes();
}

void QuoteController::loadQuote(const QString& quoteID) {
    u_int32_t realQuoteID = static_cast<u_int32_t>(quoteID.toLongLong());
    m_currentQuote = QuoteDB::getQuoteDB()->getQuoteWithID(realQuoteID);
    m_modelIterator = m_quoteModel->getIterToQuote(realQuoteID);
}
