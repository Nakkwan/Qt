#ifndef STORAGETYPE_H
#define STORAGETYPE_H

#include "pch.h"

class StorageType
{
private:
    int S_Label;
    int S_Floor;
    string S_Type;
    int S_curPointer;
    SortedList<FloorType> FloorList;
public:
    StorageType(){
        S_Label = -1;
        S_Floor = 0;
        S_Type = "None";
        S_curPointer = -1;
    }
    StorageType(int n){
        S_Label = -1;
        S_Floor = n;
        S_curPointer = -1;
        S_Type = "None";
        SetFloor(n);
    }
    ~StorageType(){}

    /*
    @brief: Get Label od storage
    @pre: Set label
    @post: none
    @return: Label of storage
    */
    int GetLabel() const;

    /*
    @brief: Get Type od storage
    @pre: Set Type
    @post: none
    @return: Type of storage
    */
    string GetType() const;

    /*
    @brief: Get number of Floor od storage
    @pre: Set Floor
    @post: none
    @return: number of Floor of storage
    */
    int GetFloor() const;

    /*
    @brief: Set label of storage
    @pre: none
    @post: Set label
    */
    void SetLabel(int inlabel);

    /*
    @brief: Set Type of storage
    @pre: none
    @post: Set Type
    */
    void SetType(string intype);

    /*
    @brief: Set number of Floor of storage
    @pre: none
    @post: Set number of Floor
    */
    void SetFloor(int infloor);

    /*
    @brief: Add floortype in floorList
    @pre: none
    @post: Add Floor to floorList
    @return: if success, return 1, otherwise, return 0
    */
    int AddFloor(FloorType& data);

    /*
    @brief: Delete floortype in floorList
    @pre: none
    @post: Delete Floor in floorList
    @return: if success, return 1, otherwise, return 0
    */
    int DeleteFloor(FloorType& data);

    /*
    @brief: Update floortype in floorList
    @pre: none
    @post: Update Floor in floorList
    @return: if success, return 1, otherwise, return 0
    */
    int UpdateFloor(FloorType& data);

    /*
    @brief: Get floortype in floorList
    @pre: none
    @post: Get Floor of floorList
    @return: if success, return 1, otherwise, return 0
    */
    int GetFloor(FloorType& data);

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
    int GetNextFloor(FloorType& data);

    /*
    @brief: Display info of Storage
    @pre: Set Storage
    @post: none
    @return: info of Storage(string)
    */
    string Display();

    /*
    @brief: outfile info of Storage
    @pre: Set Storage
    @post: none
    @return: info of Storage(string)
    */
    string OutFile();

    bool operator==(const StorageType& data){
        if(S_Label == data.GetLabel()){
            return true;
        }
        return false;
    }

    bool operator>(const StorageType& data){
        if(S_Label > data.GetLabel()){
            return true;
        }
        return false;
    }

    bool operator<(const StorageType& data){
        if(S_Label < data.GetLabel()){
            return true;
        }
        return false;
    }

    void operator=(const StorageType& data){
        S_Label = data.GetLabel();
        S_Floor = data.GetFloor();
        S_Type = data.GetType();
        FloorList = data.FloorList;
    }
};

#endif // STORAGETYPE_H
