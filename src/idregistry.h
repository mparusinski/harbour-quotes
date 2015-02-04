#ifndef IDREGISTRY_H
#define IDREGISTRY_H

#include <QObject>
#include <QSet>

class IDRegistry : public QObject
{
    Q_OBJECT
public:
    static IDRegistry* getRegistry();

    u_int32_t getNextID();

signals:

public slots:

private:
    static IDRegistry * instance;

    explicit IDRegistry(QObject *parent = 0);
    QSet<u_int32_t> m_usedIDs;

};

#endif // IDREGISTRY_H
