#ifndef QUOTEMODEL_H
#define QUOTEMODEL_H

#include "quote.h"

#include <QAbstractListModel>
#include <QModelIndex>

class QuoteModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum QuoteRoles {
        QuoteRole = Qt::UserRole + 1,
        PhilosopherRole
    };

    explicit QuoteModel(QObject *parent = 0);

    virtual ~QuoteModel();

    void populateModel(const QList<Quote::QuotePtr>& quotes);

    void clearModel();

    void filterUsing(const QString& searchString);

    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    virtual QHash<int, QByteArray> roleNames() const;

private:
    QHash<int, QByteArray> m_roles;
    QList<Quote::QuotePtr> m_quotes;
    int m_quoteNum;

};

#endif // QUOTEMODEL_H
