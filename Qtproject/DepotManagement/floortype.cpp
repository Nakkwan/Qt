#include "floortype.h"

int FloorType::GetLabel() const {
    return F_Label;
}
string FloorType::GetType()const {
    return F_Type;
}
int FloorType::GetLength() const {
    return F_ItemNum;
}


void FloorType::SetLabel(int inlabel){
    F_Label = inlabel;
}
void FloorType::SetType(string intype){
    F_Type = intype;
}

void FloorType::MakeEmpty(){
    SimpleList.MakeEmpty();
    F_ItemNum = 0;
}
int FloorType::AddItem(SimpleItemType& data){
    if(SimpleList.Add(data)){
        F_ItemNum++;
        return 1;
    }
    return 0;
}
int FloorType::DeleteItem(SimpleItemType& data){
    if(SimpleList.Delete(data)){
        F_ItemNum--;
        return 1;
    }

    return 0;
}
int FloorType::UpdateItem(SimpleItemType& data){
    if(SimpleList.Replace(data)){
        return 1;
    }

    return 0;
}
int FloorType::GetItem(SimpleItemType& data){
    if(SimpleList.Delete(data)){
        return 1;
    }

    return 0;
}

string FloorType::Display(){
    string temp;
    string L = "Floor: " + to_string(GetLabel()) + "\n";
    string T = "Type: " + GetType();
    temp.append(L);
    temp.append(T);

    return temp;
}

void FloorType::Reset(){
    F_curPointer = -1;
}

int FloorType::GetNextSimpleItem(SimpleItemType& data){
    F_curPointer = SimpleList.GetNextItem(data);
    return F_curPointer;
}

string FloorType::OutFile(){
    string temp;
    temp.append(to_string(F_Label) + " " + F_Type + "\n");

    return temp;
}
