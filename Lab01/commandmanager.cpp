#include "commandmanager.h"

CommandManager::~CommandManager()
{
    for(auto i : undoS)
        delete i;
    for(auto i : redoS)
        delete i;
}

void CommandManager::Receive(Command *cmd)
{
    cmd->exec();
    if(cmd->isUndoable())
        undoS.append(cmd);
}

void CommandManager::undo()
{
    if(undoS.size())
    {
        Command *cmd = undoS.pop();
        cmd->reject();
        redoS.push_back(cmd);
    }
}

void CommandManager::redo()
{
    if(redoS.size())
    {
        Command *cmd = redoS.pop();
        cmd->exec();
        undoS.push_back(cmd);
    }
}
