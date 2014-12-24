#ifndef QUOTE_H
#define QUOTE_H

#include <QObject>
#include <QString>
#include <QSharedPointer>

class Quote : public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer<Quote> QuotePtr;

    explicit Quote(QObject *parent = 0);

    Quote(QString philosopher, QString quoteText);

    QString getPhilosopher() const;

    QString getQuoteText() const;

signals:

public slots:

private:
    QString m_philosopher;
    QString m_quoteText;

};

#endif // QUOTE_H
