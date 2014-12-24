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
