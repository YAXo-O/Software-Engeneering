#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
    Command() = default;
    virtual ~Command();

    virtual void exec() = 0;
    virtual void reject() = 0;

    virtual bool isUndoable();
};

#endif // COMMAND_H
