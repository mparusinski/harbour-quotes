#ifndef QUOTECONTROLLER_H
#define QUOTECONTROLLER_H

#include <QObject>

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
    QString m_quoteText;
    QString m_philosopherText;
};

#endif // QUOTECONTROLLER_H
