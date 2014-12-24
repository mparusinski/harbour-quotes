#ifndef QUOTECONTROLLER_H
#define QUOTECONTROLLER_H

#include <QObject>

#include "quote.h"
#include "quotedb.h"

class QuoteController : public QObject
{
    Q_OBJECT
public:
    explicit QuoteController(QObject *parent = 0);

    Q_INVOKABLE QString getQuoteText() const;

    Q_INVOKABLE QString getPhilosopherText() const;

    Q_INVOKABLE void updateQuote();

signals:

public slots:

private:
    QuoteDB m_quotesDB;
    Quote::QuotePtr m_currentQuote;

};

#endif // QUOTECONTROLLER_H
