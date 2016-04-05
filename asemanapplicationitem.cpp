#include "asemanapplicationitem.h"

class AsemanApplicationItemPrivate
{
public:
};

AsemanApplicationItem::AsemanApplicationItem() :
    AsemanApplication()
{
    p = new AsemanApplicationItemPrivate;
}

AsemanApplicationItem::~AsemanApplicationItem()
{
    delete p;
}

