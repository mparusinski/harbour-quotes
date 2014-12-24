#include "quote.h"

Quote::Quote(QObject *parent) :
    QObject(parent)
{
}

Quote::Quote(QString philosopher, QString quoteText)
{
    m_philosopher = philosopher;
    m_quoteText = quoteText;
}

QString Quote::getPhilosopher() const {
    return m_philosopher;
}

QString Quote::getQuoteText() const {
    return m_quoteText;
}
