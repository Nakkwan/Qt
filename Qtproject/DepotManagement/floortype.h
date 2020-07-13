#ifndef FLOORTYPE_H
#define FLOORTYPE_H

#include "pch.h"


class FloorType
{
private:
    int F_Label;
    string F_Type;
    int F_ItemNum;
    int F_curPointer;
    SortedList<SimpleItemType> SimpleList;
public:
    FloorType(){
        F_Label = -1;
        F_ItemNum = 0;
        F_Type = "None";
        F_curPointer = -1;
    }
    ~FloorType(){}

    /*
    @brief: Get Label of Floor
    @pre: Set Label
    @post: none
    @return: Label of flooe
    */
    int GetLabel() const ;

    /*
    @brief: Get Type of Floor
    @pre: Set Type
    @post: none
    @return: Type of flooe
    */
    string GetType() const;

    /*
    @brief: Get length of SimpleList
    @pre: none
    @post: none
    @return: Length of list
    */
    int GetLength() const;

    /*
    @brief: Set Label of floor
    @pre: none
    @post: Set Label
    */
    void SetLabel(int inlabel);

    /*
    @brief: Set Type of floor
    @pre: none
    @post: Set Type
    */
    void SetType(string intype);

    /*
    @brief: Make List empty
    @pre: none
    @post: SimpleList is empty
    */
    void MakeEmpty();

    /*
    @brief: Add Item in List
    @pre: none
    @post: SimpleItemType is added to SimpleList
    @return: if Success to add, return 1, otherwise, return 0
    */
    int AddItem(SimpleItemType& data);

    /*
    @brief: Delete Item in List
    @pre: none
    @post: SimpleItemType is Delete to SimpleList
    @return: if Success to Delete, return 1, otherwise, return 0
    */
    int DeleteItem(SimpleItemType& data);

    /*
    @brief: Update Item in List
    @pre: none
    @post: Update Item in SimpleList
    @return: if Success to Update, return 1, otherwise, return 0
    */
    int UpdateItem(SimpleItemType& data);

    /*
    @brief: Get SimpleItem from List
    @pre: none
    @post: Item is return by reference
    @return: if Success to Get, return 1, otherwise, return 0
    */
    int GetItem(SimpleItemType& data);

    /*
    @brief: Make List pointer initialize
    @pre: none
    @post: pointer initialize
    */
    void Reset();

    /*
    @brief: Get Next item of List
    @pre: none
    @post: Next item of list is return by reference
    @return: pointer of list
    */
    int GetNextSimpleItem(SimpleItemType& data);

    /*
    @brief: Display info of floor
    @pre: Set Floor
    @post: none
    @return: info of floor(string)
    */
    string Display();

    /*
    @brief: outfile info of floor
    @pre: Set Floor
    @post: none
    @return: info of floor(string)
    */
    string OutFile();

    bool operator==(const FloorType& data){
        if(F_Label == data.GetLabel()){
            return true;
        }
        return false;
    }

    bool operator>(const FloorType& data){
        if(F_Label > data.GetLabel()){
            return true;
        }
        return false;
    }

    bool operator<(const FloorType& data){
        if(F_Label < data.GetLabel()){
            return true;
        }
        return false;
    }

    void operator=(const FloorType& data){
        F_Label = data.GetLabel();
        F_Type = data.GetType();
        F_ItemNum = data.GetLength();
        SimpleList = data.SimpleList;
    }
};

#endif // FLOORTYPE_H
