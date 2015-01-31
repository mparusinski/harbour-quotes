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

void QuoteModel::repopulateQuotes() {
    clearModel();
    QuoteDB* quoteDB = QuoteDB::getQuoteDB();
    QuoteDB::ContainerType quotes = quoteDB->getQuotes();
    int newSize = quotes.size();
    beginInsertRows(QModelIndex(), 0, newSize - 1);
    QuoteDB::ContainerIteratorType iter(quotes);
    while (iter.hasNext()) {
        iter.next();
        m_quotesVisible.append(iter.value());
    }
    m_quoteNum = newSize;
    endInsertRows();
}

void filterUsing(const QString& searchString);

void QuoteModel::clearModel() {
    if (m_quoteNum > 0) {
        beginRemoveRows(QModelIndex(), 0, m_quoteNum - 1);
        m_quotesVisible.clear();
        m_quoteNum = 0;
        endRemoveRows();
    }
}

void QuoteModel::filterUsing(const QString& searchString) {
//    int index = -1;
//    QuoteDB::ContainerMutableIteratorType iter(m_quotesDB);
//    while (iter.hasNext()) {
//        iter.next();
//        const Quote::QuotePtr& elem = iter.value();
//        index++;
//        const QString & philosopher = elem->philosopher();
//        const QString & quote = elem->quote();
//        if (!(philosopher.contains(searchString, Qt::CaseInsensitive) || quote.contains(searchString, Qt::CaseInsensitive))) {
//            beginRemoveRows(QModelIndex(), index, index);
//            iter.remove();
//            m_quoteNum--;
//            endRemoveRows();
//        }
//    }
}

int QuoteModel::rowCount(const QModelIndex &parent) const
{
    return m_quoteNum;
}

QVariant QuoteModel::data(const QModelIndex &index, int role) const
{
    int rowNum = index.row();
    if (role == QuoteRole) {
        return QVariant::fromValue(m_quotesVisible[rowNum]->quote());
    } else if (role == PhilosopherRole) {
        return QVariant::fromValue(m_quotesVisible[rowNum]->philosopher());
    } else {
        qWarning() << "UI is trying to access unknown or unsupported property of quote";
        return QVariant();
    }
}

QHash<int, QByteArray> QuoteModel::roleNames() const
{
    return m_roles;
}
