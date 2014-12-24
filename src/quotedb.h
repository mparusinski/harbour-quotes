#ifndef QUOTEDB_H
#define QUOTEDB_H

#include <QObject>
#include <QList>

#include "quote.h"

class QuoteDB : public QObject
{
    Q_OBJECT
public:
    explicit QuoteDB(QObject *parent = 0);

    Quote::QuotePtr nextQuote();

signals:

public slots:

private:
    typedef QList<Quote::QuotePtr> ContainerType;
    ContainerType m_quotes;
    bool m_visitorSet;
    ContainerType::ConstIterator m_visitorIterator;
};

#endif // QUOTEDB_H
