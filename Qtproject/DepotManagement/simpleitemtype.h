#ifndef SIMPLEITEMTYPE_H
#define SIMPLEITEMTYPE_H

#include "pch.h"

class SimpleItemType
{
private:
    int S_Label;
    string S_Name;
    string S_Type;
    string S_Photo;
public:
    SimpleItemType();
    SimpleItemType(ItemType* data);
    ~SimpleItemType(){}

    /*
    @brief: Get Label of SimpleItemType
    @pre: Set label
    @post: none
    @return: Label of SimpleItemtype
    */
    int GetLabel() const;

    /*
    @brief: Get Name of SimpleItemType
    @pre: Set Name
    @post: none
    @return: Name of SimpleItemtype
    */
    string GetName() const;

    /*
    @brief: Get Type of SimpleItemType
    @pre: Set Type
    @post: none
    @return: Type of SimpleItemtype
    */
    string GetType() const;

    /*
    @brief: Get Photo Path of SimpleItemType
    @pre: Set Photo Path
    @post: none
    @return: Photo Path of SimpleItemtype
    */
    string GetPhoto() const;

    /*
    @brief: Set Label of SimpleItemType
    @pre: None
    @post: Set Label
    */
    void SetLabel(int inlabel);

    /*
    @brief: Set Name of SimpleItemType
    @pre: None
    @post: Set Name
    */
    void SetName(string inname);

    /*
    @brief: Set Type of SimpleItemType
    @pre: None
    @post: Set Type
    */
    void SetType(string intype);

    /*
    @brief: Set Photo Path of SimpleItemType
    @pre: None
    @post: Set Photo Path
    */
    void SetPhoto(string inphoto);

    /*
    @brief: Display info of SimpleItemType
    @pre: Set SimpleItemType
    @post: none
    @return: info of SimpleItemType(string)
    */
    string DisplayItem();


    bool operator==(const SimpleItemType& data){
        if(S_Label == data.GetLabel()){
            return true;
        }
        return false;
    }

    bool operator>(const SimpleItemType& data){
        if(S_Label > data.GetLabel()){
            return true;
        }
        return false;
    }

    bool operator<(const SimpleItemType& data){
        if(S_Label < data.GetLabel()){
            return true;
        }
        return false;
    }

    void operator=(const SimpleItemType& data){
        S_Label = data.GetLabel();
        S_Type = data.GetType();
        S_Name = data.GetName();
        S_Photo = data.GetPhoto();
    }
};

#endif // SIMPLEITEMTYPE_H
