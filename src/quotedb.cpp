#include "quotedb.h"

QuoteDB::QuoteDB(QObject *parent) :
    QObject(parent)
{
    // TODO: Something smarter
    Quote::QuotePtr firstQuote(new Quote("Frederich Nietzsche", "That which does not kill you makes you stronger"));
    Quote::QuotePtr secondQuote(new Quote("Rene Descartes", "I think therefore I am"));

    m_quotes.push_back(firstQuote);
    m_quotes.push_back(secondQuote);

    m_visitorSet = false;
}

Quote::QuotePtr QuoteDB::nextQuote() {
    if (!m_visitorSet) {
        m_visitorIterator = m_quotes.begin();
        m_visitorSet = true;
    }

    if (m_visitorIterator == m_quotes.end()) {
        // restarting from beginning
        m_visitorIterator = m_quotes.begin();
    }

    Quote::QuotePtr elem = *m_visitorIterator;
    m_visitorIterator++;
    return elem;
}
