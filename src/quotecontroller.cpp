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

QuoteController::QuoteController(QObject *parent) :
    QObject(parent)
{
    m_currentQuote = m_quotesDB.nextQuote();
}

QString QuoteController::getQuoteText() const {
    return m_currentQuote->getQuoteText();
}

QString QuoteController::getPhilosopherText() const {
    return m_currentQuote->getPhilosopher();
}

void QuoteController::updateQuote()  {
    m_currentQuote = m_quotesDB.nextQuote();
}
