
#include "customdata.h"

CustomData::CustomData()
{

}

CustomData::CustomData(int intergerArg, int *pointer, const QString &stringArg)
    : m_integer(intergerArg), m_pointer(pointer), m_string(stringArg)
{

}
