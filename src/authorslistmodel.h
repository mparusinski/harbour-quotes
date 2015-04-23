#ifndef AUTHORSLISTMODEL_H
#define AUTHORSLISTMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>

#include "quotedb.h"

class AuthorsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    typedef std::vector<QString> AuthorsContainerType;
    typedef QSharedPointer<AuthorsContainerType> AuthorsContainerPtr;

    enum QuoteRoles {
        AuthorsRole = Qt::UserRole + 1,
    };

    explicit AuthorsListModel(QObject *parent = 0);

    virtual ~AuthorsListModel();

    void repopulateListModel(AuthorsDBContainerPtr quotes);

    void filterUsing(const QString& searchString);

    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    virtual QHash<int, QByteArray> roleNames() const;

private:
    Q_DISABLE_COPY(AuthorsListModel)

    void clearModel();

    void filterUsingToken(const QString& tokenString);

    QHash<int, QByteArray> m_roles;
    AuthorsContainerPtr m_authorsVisible;
    int m_authorNum;

};

#endif // AUTHORSLISTMODEL_H
