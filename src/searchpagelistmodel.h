#ifndef SearchPageListModel_H
#define SearchPageListModel_H

#include "quote.h"
#include "quotedb.h"

#include <QAbstractListModel>
#include <list>
#include <QModelIndex>

class SearchPageListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    typedef std::vector<Quote::QuotePtr> QuotesContainerType;
    typedef QSharedPointer<QuotesContainerType> QuotesContainerPtr;

    enum QuoteRoles {
        QuoteRole = Qt::UserRole + 1,
        PhilosopherRole,
        QuoteIDRole
    };

    explicit SearchPageListModel(QObject *parent = 0);

    virtual ~SearchPageListModel();

    void repopulateListModel(AuthorsQuotesDBContainerPtr quotes);

    void filterUsing(const QString& searchString);

    QuotesContainerType::iterator getIterToQuote(u_int32_t quoteID);

    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    virtual QHash<int, QByteArray> roleNames() const;

    void circularNext(QuotesContainerType::iterator& iter);

    void circularPrev(QuotesContainerType::iterator& iter);

    // DEBUG METHOD
    void printAllQuotes() const;

private:
    Q_DISABLE_COPY(SearchPageListModel)

    void clearModel();

    void filterUsingToken(const QString& tokenString);

    QHash<int, QByteArray> m_roles;
    QuotesContainerPtr m_quotesVisible;
    int m_quoteNum;

};

#endif // SearchPageListModel_H
