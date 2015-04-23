/*
  Copyright 2015 Michal Parusinski <mparusinski@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include "searchpagelistmodel.h"
#include <QDebug>

SearchPageListModel::SearchPageListModel(QObject *parent)
    : QAbstractListModel(parent) {
    m_quotesVisible = QuotesContainerPtr(new QuotesContainerType);
    m_roles[QuoteRole] = "quote";
    m_roles[PhilosopherRole] = "philosopher";
    m_roles[QuoteIDRole] = "quoteID";
    m_quoteNum = 0;
}

SearchPageListModel::~SearchPageListModel() {
}

void SearchPageListModel::repopulateListModel(AuthorsQuotesDBContainerPtr quotes) {
    clearModel();
    int newSize = quotes->size(); 
    beginInsertRows(QModelIndex(), 0, newSize - 1);
    for (AuthorsQuotesDBContainerType::iterator iter = quotes->begin();
            iter != quotes->end(); ++iter) {
        m_quotesVisible->push_back(*iter);
    }
    m_quoteNum = newSize;
    endInsertRows();
}

SearchPageListModel::QuotesContainerType::iterator SearchPageListModel::getIterToQuote(
  u_int32_t quoteID) {
    QuotesContainerType::iterator iter = m_quotesVisible->begin();
    for ( ; iter != m_quotesVisible->end(); ++iter) {
        const Quote::QuotePtr& quote = *iter;
        if (quote->uniqueID() == quoteID) {
            return iter;
        }
    }
    return iter;
}

void SearchPageListModel::clearModel() {
    if (m_quoteNum > 0) {
        beginRemoveRows(QModelIndex(), 0, m_quoteNum - 1);
        m_quotesVisible->clear();
        m_quoteNum = 0;
        endRemoveRows();
    }
}

void SearchPageListModel::filterUsing(const QString& searchString) {
    QStringList tokens = searchString.split(" ", QString::SkipEmptyParts);

    QListIterator<QString> iter(tokens);
    while (iter.hasNext()) {
        QString currentToken = iter.next();
        filterUsingToken(currentToken);
    }
}

void SearchPageListModel::filterUsingToken(const QString& tokenString) {
    int index = -1;
    QuotesContainerPtr newQuotesVisible(new QuotesContainerType);
    for (QuotesContainerType::iterator iter = m_quotesVisible->begin();
         iter != m_quotesVisible->end(); ++iter) {
        const Quote::QuotePtr& elem = *iter;
        index++;
        const QString & quote = elem->quote();
        bool strContained =quote.contains(tokenString, Qt::CaseInsensitive);
        if (!strContained) {
            beginRemoveRows(QModelIndex(), index, index);
            m_quoteNum--;
            endRemoveRows();
            index--;
        } else {
           newQuotesVisible->push_back(elem);
        }
    }
    m_quotesVisible = newQuotesVisible;
}

int SearchPageListModel::rowCount(const QModelIndex &parent) const {
    return m_quoteNum;
}

QVariant SearchPageListModel::data(const QModelIndex &index, int role) const {
    int rowNum = index.row();
    Quote::QuotePtr elem = (*m_quotesVisible)[rowNum];
    if (role == QuoteRole) {
        return QVariant::fromValue(elem->quote());
    } else if (role == PhilosopherRole) {
        return QVariant::fromValue(elem->philosopher());
    } else if (role == QuoteIDRole) {
        u_int32_t quoteID = elem->uniqueID();
        return QVariant::fromValue(QString::number(quoteID));
    } else {
        qWarning() << "UI is trying to access an unknown property of quote";
        return QVariant();
    }
}

QHash<int, QByteArray> SearchPageListModel::roleNames() const {
    return m_roles;
}

void SearchPageListModel::circularNext(
        QuotesContainerType::iterator& iter) {
    ++iter;
    if (iter == m_quotesVisible->end()) {
        iter = m_quotesVisible->begin();
    }
}

void SearchPageListModel::circularPrev(
        QuotesContainerType::iterator& iter) {
    if (iter == m_quotesVisible->begin()) {
        iter = m_quotesVisible->end();
    }
    --iter;
}

