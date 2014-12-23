#include "quotecontroller.h"

QuoteController::QuoteController(QObject *parent) :
    QObject(parent)
{
    m_quoteText = QString("That which does not kill you makes you stronger");
    m_philosopherText = QString("Frederich Nietzsche");
}

QString QuoteController::getQuoteText() const {
    return m_quoteText;
}

QString QuoteController::getPhilosopherText() const {
    return m_philosopherText;
}

void QuoteController::updateQuote()  {
    m_quoteText = QString("I think therefore I am");
    m_philosopherText = QString("Rene Descartes");
}
