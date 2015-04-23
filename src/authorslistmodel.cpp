#include "authorslistmodel.h"

#include <QDebug>

AuthorsListModel::AuthorsListModel(QObject *parent) :
    QAbstractListModel(parent) {
    m_authorsVisible = AuthorsContainerPtr(new AuthorsContainerType);
    m_roles[AuthorsRole] = "author";
    m_authorNum = 0;
}

AuthorsListModel::~AuthorsListModel() {
}

void AuthorsListModel::repopulateListModel(AuthorsDBContainerPtr authors) {
    // TODO: To implement
    clearModel();
    int newSize = authors->size();
    beginInsertRows(QModelIndex(), 0, newSize - 1);
    for (AuthorsDBContainerType::iterator iter = authors->begin();
         iter != authors->end(); ++iter) {
        m_authorsVisible->push_back(*iter);
    }
    m_authorNum = newSize;
    endInsertRows();
}

void AuthorsListModel::clearModel() {
    if (m_authorNum > 0) {
        beginRemoveRows(QModelIndex(), 0, m_authorNum - 1);
        m_authorsVisible->clear();
        m_authorNum = 0;
        endRemoveRows();
    }
}

void AuthorsListModel::filterUsing(const QString& searchString) {
    QStringList tokens = searchString.split(" ", QString::SkipEmptyParts);

    QListIterator<QString> iter(tokens);
    while (iter.hasNext()) {
        QString currentToken = iter.next();
        filterUsingToken(currentToken);
    }
}

void AuthorsListModel::filterUsingToken(const QString& tokenString) {
    int index = -1;
    AuthorsContainerPtr newAuthorsVisible(new AuthorsContainerType);
    for (AuthorsContainerType::iterator iter = m_authorsVisible->begin();
         iter != m_authorsVisible->end(); ++iter) {
        index++;
        const QString & author = *iter;
        bool strContained = author.contains(tokenString, Qt::CaseInsensitive);
        if (!strContained) {
            beginRemoveRows(QModelIndex(), index, index);
            m_authorNum--;
            endRemoveRows();
            index--;
        } else {
           newAuthorsVisible->push_back(author);
        }
    }
    m_authorsVisible = newAuthorsVisible;
}

int AuthorsListModel::rowCount(const QModelIndex &parent) const {
    return m_authorNum;
}

QVariant AuthorsListModel::data(const QModelIndex &index, int role) const {
    int rowNum = index.row();
    const QString& elem = (*m_authorsVisible)[rowNum];
    if (role == AuthorsRole) {
        return QVariant::fromValue(elem);
    } else {
        qWarning() << "UI is trying to access an unknown property";
        return QVariant();
    }
}

QHash<int, QByteArray> AuthorsListModel::roleNames() const {
    return m_roles;
}
