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

void QuoteModel::addQuote(const Quote::QuotePtr& quote)
{
    m_quotes.append(quote);
    m_quoteNum++;
}

void QuoteModel::clearModel() {
    m_quotes.clear();
    m_quoteNum = 0;
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
