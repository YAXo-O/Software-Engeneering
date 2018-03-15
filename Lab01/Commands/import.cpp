#include "import.h"
#include "../Parsers/gpxparser.h"

Import::Import(const QString &_filename, DBManager &_manager): Command(), filename(_filename), manager(_manager)
{
}

void Import::exec()
{
    GPXParser parser;
    parser.parse(filename, manager);
}

void Import::reject()
{
}
