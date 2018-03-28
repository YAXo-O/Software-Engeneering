#ifndef RENAMEROUTE_H
#define RENAMEROUTE_H

#include <QVector>
#include "./command.h"
#include "../dbmanager.h"

class RenameRoute : public Command
{
public:
    RenameRoute(const QString &oldName, const QString &newName, int id, DBManager &manager);
    ~RenameRoute() {}

    void exec() override;
    void reject() override;

private:
    QString oldName, newName;
    DBManager &manager;
    int id;
};

#endif // RENAMEROUTE_H
