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
    m_currentQuote = m_quotesDB.nextQuote();
    populateModel("");
}

QString QuoteController::getQuote() const {
    return m_currentQuote->quote();
}

QString QuoteController::getPhilosopher() const {
    return m_currentQuote->philosopher();
}

void QuoteController::updateQuote()  {
    m_currentQuote = m_quotesDB.nextQuote();
}

void QuoteController::populateModel(const QString& searchString) {
    QList<QObject*>::iterator clearIter;
    for (clearIter = m_searchQuoteModel.begin(); clearIter != m_searchQuoteModel.end(); ++clearIter) {
        QObject* elem = *clearIter;
        delete elem;
    }
    m_searchQuoteModel.clear();
    QList<Quote::QuotePtr>& quotes =  m_quotesDB.quotesList();
    QList<Quote::QuotePtr>::iterator iter;
    if (searchString == "") {
        for (iter = quotes.begin(); iter != quotes.end(); ++iter) {
            Quote::QuotePtr& currQuote = *iter;
            Quote * quoteCopy = new Quote(currQuote->philosopher(), currQuote->quote());
            m_searchQuoteModel.append(quoteCopy);
        }
        QQmlContext * rootCtx = m_mainView->rootContext();
        rootCtx->setContextProperty("quoteModel", QVariant::fromValue(m_searchQuoteModel));
    } else {
        qWarning() << "POPULATING WITH CUSTOM SEARCH STRING NOT SUPPORTED";
    }

}
