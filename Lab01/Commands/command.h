#ifndef COMMAND_H
#define COMMAND_H


class Command
{
public:
    Command() = default;
    virtual ~Command();

    virtual void exec() = 0; // Do
    virtual void reject() = 0; // Undo

    virtual bool isUndoable();
};

#endif // COMMAND_H
