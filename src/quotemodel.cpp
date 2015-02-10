#include "quotemodel.h"

#include <QDebug>

QuoteModel::QuoteModel(QObject *parent)
    : QAbstractListModel(parent)
{
   m_roles[QuoteRole] = "quote";
   m_roles[PhilosopherRole] = "philosopher";
   m_roles[QuoteIDRole] = "quoteID";
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

QuoteModel::ModelIteratorPtr QuoteModel::getIterToQuote(u_int32_t quoteID) const {
    ModelIteratorPtr modelIterator(new QListIterator<Quote::QuotePtr>(m_quotesVisible));
    while (modelIterator->hasNext()) {
        const Quote::QuotePtr& quote = modelIterator->next();
        if (quote->uniqueID() == quoteID) {
            return modelIterator;
        }
    }
}

void QuoteModel::clearModel() {
    if (m_quoteNum > 0) {
        beginRemoveRows(QModelIndex(), 0, m_quoteNum - 1);
        m_quotesVisible.clear();
        m_quoteNum = 0;
        endRemoveRows();
    }
}

void QuoteModel::filterUsing(const QString& searchString) {
    QStringList tokens = searchString.split(" ", QString::SkipEmptyParts);

    QListIterator<QString> iter(tokens);
    while (iter.hasNext()) {
        QString currentToken = iter.next();
        filterUsingToken(currentToken);
    }
}

void QuoteModel::filterUsingToken(const QString& tokenString) {
    int index = -1;
    QMutableListIterator<Quote::QuotePtr> iter(m_quotesVisible);
    while (iter.hasNext()) {
        iter.next();
        const Quote::QuotePtr& elem = iter.value();
        index++;
        const QString & philosopher = elem->philosopher();
        const QString & quote = elem->quote();
        if (!(philosopher.contains(tokenString, Qt::CaseInsensitive) || quote.contains(tokenString, Qt::CaseInsensitive))) {
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
        return QVariant::fromValue(m_quotesVisible[rowNum]->quote());
    } else if (role == PhilosopherRole) {
        return QVariant::fromValue(m_quotesVisible[rowNum]->philosopher());
    } else if (role == QuoteIDRole) {
        u_int32_t quoteID = m_quotesVisible[rowNum]->uniqueID();
        return QVariant::fromValue(QString::number(quoteID));
    } else {
        qWarning() << "UI is trying to access unknown or unsupported property of quote";
        return QVariant();
    }
}

QHash<int, QByteArray> QuoteModel::roleNames() const
{
    return m_roles;
}
