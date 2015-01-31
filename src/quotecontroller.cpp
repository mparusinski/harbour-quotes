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

#include "quotecontroller.h"

#include <QDebug>
#include <QQmlContext>

QuoteController::QuoteController(const QSharedPointer<QQuickView>& mainView, QObject * parent) :
    QObject(parent)
{
    m_mainView = mainView;
    m_currentQuote = QuoteDB::getQuoteDB()->nextQuote();
    m_previousSearchString = "";
    m_quoteModel = QuoteModelPtr(new QuoteModel());
    populateModel();
}

QString QuoteController::getQuote() const {
    return m_currentQuote->quote();
}

QString QuoteController::getPhilosopher() const {
    return m_currentQuote->philosopher();
}

void QuoteController::updateQuote()  {
    m_currentQuote = QuoteDB::getQuoteDB()->nextQuote();
}

void QuoteController::filterUsingSearchString(const QString& searchString) {
    // perhaps do something smart like santization, creating a regexp, ...
//    QString trimmedSearchString = searchString.trimmed();

//    if (m_previousSearchString != trimmedSearchString) { // skip if the same
//        if (trimmedSearchString == "") { // revert to default
//            m_quoteModel->populateModel(m_quotesDB.quotesList());
//        } else {
//            m_quoteModel->filterUsing(trimmedSearchString);
//        }
//        m_previousSearchString = trimmedSearchString;
//    }
}

void QuoteController::populateModel() {
    QQmlContext * rootCtx = m_mainView->rootContext();
    rootCtx->setContextProperty("quoteModel", &(*m_quoteModel)); // I hate this hack
    m_quoteModel->repopulateQuotes();
}

