#ifndef IMPORT_H
#define IMPORT_H

#include <QString>
#include "command.h"
#include "../dbmanager.h"

class Import : public Command
{
public:
    Import(const QString &filename, DBManager &manager);
    ~Import() override {}

    void exec() override;
    void reject() override;

private:
    const QString filename;
    DBManager &manager;

};

#endif // IMPORT_H
