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
    enum QuoteRoles {
        QuoteRole = Qt::UserRole + 1,
        PhilosopherRole,
        QuoteIDRole
    };

    virtual ~SearchPageListModel();

    SearchPageListModel(QObject *parent = 0);

    void pushQuote(const Quote::QuotePtr& quote);

    void repopulateQuotes(QuotesDBContainerPtr quotes);

    void filterUsing(const QString& searchString);

    std::list<Quote::QuotePtr>::iterator getIterToQuote(u_int32_t quoteID);

    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    virtual QHash<int, QByteArray> roleNames() const;

    void circularNext(std::list<Quote::QuotePtr>::iterator& iter);

    void circularPrev(std::list<Quote::QuotePtr>::iterator& iter);

    // DEBUG METHOD
    void printAllQuotes() const;

private:
    Q_DISABLE_COPY(SearchPageListModel)

    void clearModel();

    void filterUsingToken(const QString& tokenString);

    QHash<int, QByteArray> m_roles;
    std::list<Quote::QuotePtr> m_quotesVisible;
    std::map<int, Quote::QuotePtr> m_rowsToQuotes;
    int m_quoteNum;

};

#endif // SearchPageListModel_H
