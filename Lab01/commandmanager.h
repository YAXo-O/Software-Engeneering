#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QStack>
#include "Commands/command.h"

class CommandManager
{
public:
    CommandManager() = default;
    ~CommandManager();

    void receive(Command *cmd);
    void undo();
    void redo();
    void repeat();

private:
    QStack<Command *> undoS;
    QStack<Command *> redoS;
};

#endif // COMMANDMANAGER_H
