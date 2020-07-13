#ifndef OBJECT_H
#define OBJECT_H

#include"pch.h"


//class for object item
class Object : public ItemType
{
public:
    Object(): ItemType() {
        O_key = 0;
    }

    virtual string DisplayItem() override;
    virtual string OutFile() override;
};


//class for food item
class Food : public ItemType{
public:
    Food(): ItemType(){
        O_key = 1;
    }
    virtual string DisplayItem() override;
    virtual string OutFile() override;
};

#endif // OBJECT_H
