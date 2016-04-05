#ifndef ASEMANAPPLICATIONITEM_H
#define ASEMANAPPLICATIONITEM_H

#include "asemanapplication.h"

class AsemanApplicationItemPrivate;
class AsemanApplicationItem : public AsemanApplication
{
    Q_OBJECT
public:
    AsemanApplicationItem();
    ~AsemanApplicationItem();

signals:

public slots:

private:
    AsemanApplicationItemPrivate *p;
};

#endif // ASEMANAPPLICATIONITEM_H
