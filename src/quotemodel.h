#ifndef QUOTEMODEL_H
#define QUOTEMODEL_H

#include "quote.h"
#include "quotedb.h"

#include <QAbstractListModel>
#include <QList>
#include <QMap>
#include <QModelIndex>

class QuoteModel : public QAbstractListModel
{
    Q_OBJECT

public:
    typedef QSharedPointer< QListIterator<Quote::QuotePtr> > ModelIteratorPtr;

    enum QuoteRoles {
        QuoteRole = Qt::UserRole + 1,
        PhilosopherRole,
        QuoteIDRole
    };

    virtual ~QuoteModel();

    explicit QuoteModel(QObject *parent = 0);

    void repopulateQuotes();

    void filterUsing(const QString& searchString);

    ModelIteratorPtr getIterToQuote(u_int32_t quoteID) const;

    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    virtual QHash<int, QByteArray> roleNames() const;

private:
    Q_DISABLE_COPY(QuoteModel)

    void clearModel();

    void filterUsingToken(const QString& tokenString);

    QHash<int, QByteArray> m_roles;
    QList<Quote::QuotePtr> m_quotesVisible;
    int m_quoteNum;

};

#endif // QUOTEMODEL_H
