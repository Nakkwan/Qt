#include "storagetype.h"

int StorageType::GetLabel() const {
    return S_Label;
}
string StorageType::GetType() const{
    return S_Type;
}
int StorageType::GetFloor() const{
    return S_Floor;
}

void StorageType::SetLabel(int inlabel){
    S_Label = inlabel;
}
void StorageType::SetType(string intype){
    S_Type = intype;
}
void StorageType::SetFloor(int infloor){
    for(int i = 0; i < infloor; i++){
        FloorType temp;
        temp.SetLabel(i + 1);
        FloorList.Add(temp);
    }
}

int StorageType::AddFloor(FloorType& data){
    if(FloorList.Add(data)){
        S_Floor++;
        return 1;
    }
    return 0;
}
int StorageType::DeleteFloor(FloorType& data){
    if(FloorList.Delete(data)){
        S_Floor--;
        return 1;
    }
    return 0;
}
int StorageType::UpdateFloor(FloorType& data){
    if(FloorList.Replace(data)){
        return 1;
    }
    return 0;
}
int StorageType::GetFloor(FloorType& data){
    if(FloorList.Get(data)){
        return 1;
    }
    return 0;
}

string StorageType::Display(){
    string temp;
    string L = "Storage Label: " + to_string(GetLabel()) + "\n";
    string T = "Type: " + GetType() + "\n";
    string F = "Number of Floor: " + to_string(GetFloor());

    temp.append(L);
    temp.append(T);
    temp.append(F);

    return temp;
}

void StorageType::Reset(){
    S_curPointer = -1;
}

int StorageType::GetNextFloor(FloorType& data){
    S_curPointer = FloorList.GetNextItem(data);
    return S_curPointer;
}

string StorageType::OutFile(){
    string temp;
    temp.append(to_string(S_Floor) + " " + to_string(S_Label) + " " + S_Type + "\n");
    Reset();
    FloorType flotemp;
    GetNextFloor(flotemp);
    while(S_curPointer != -1){
        temp.append(flotemp.OutFile());
        GetNextFloor(flotemp);
    }

    return temp;
}
