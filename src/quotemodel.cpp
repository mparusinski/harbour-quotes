#include "quotemodel.h"

#include <QDebug>

QuoteModel::QuoteModel(QObject *parent)
    : QAbstractListModel(parent)
{
   m_roles[QuoteRole] = "quote";
   m_roles[PhilosopherRole] = "philosopher";
   m_quoteNum = 0;
}

QuoteModel::~QuoteModel()
{

}

void QuoteModel::populateModel(const QList<Quote::QuotePtr>& quotes) {
    int previousSize = m_quoteNum;
    beginRemoveRows(QModelIndex(), 0, previousSize - 1);
    m_quotes.clear();
    m_quoteNum = 0;
    endRemoveRows();

    int newSize = quotes.size();
    beginInsertRows(QModelIndex(), 0, newSize - 1);
    QListIterator<Quote::QuotePtr> iter(quotes);
    while (iter.hasNext()) {
        Quote::QuotePtr elem = iter.next();
        m_quotes.append(elem);
    }
    m_quoteNum = newSize;
    endInsertRows();
}

void QuoteModel::clearModel() {
    int previousSize = m_quoteNum;
    beginRemoveRows(QModelIndex(), 0, previousSize - 1);
    m_quotes.clear();
    m_quoteNum = 0;
    endRemoveRows();
}

void QuoteModel::filterUsing(const QString& searchString) {
    int index = -1;
    QMutableListIterator<Quote::QuotePtr> iter(m_quotes);
    while (iter.hasNext()) {
        Quote::QuotePtr elem = iter.next();
        index++;
        const QString & philosopher = elem->philosopher();
        const QString & quote = elem->quote();
        if (!(philosopher.contains(searchString, Qt::CaseInsensitive) || quote.contains(searchString, Qt::CaseInsensitive))) {
            beginRemoveRows(QModelIndex(), index, index);
            iter.remove();
            m_quoteNum--;
            endRemoveRows();
        }
    }
}

int QuoteModel::rowCount(const QModelIndex &parent) const
{
    return m_quoteNum;
}

QVariant QuoteModel::data(const QModelIndex &index, int role) const
{
    int rowNum = index.row();
    if (role == QuoteRole) {
        return QVariant::fromValue(m_quotes[rowNum]->quote());
    } else if (role == PhilosopherRole) {
        return QVariant::fromValue(m_quotes[rowNum]->philosopher());
    } else {
        qWarning() << "UI is trying to access unknown or unsupported property of quote";
        return QVariant();
    }
}

QHash<int, QByteArray> QuoteModel::roleNames() const
{
    return m_roles;
}
