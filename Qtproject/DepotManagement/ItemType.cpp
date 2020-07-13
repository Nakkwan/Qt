#include "ItemType.h"

int ItemType::GetKey() const{
    return O_key;
}
string ItemType::GetName() const {
	return O_Name;
}
int ItemType::GetBuyDate() const {
	return O_BuyDate;
}
int ItemType::GetLabel() const {
	return O_Label;
}
string ItemType::GetType() const {
	return O_Type;
}
int ItemType::GetVolume() const {
	return O_Volume;
}
int ItemType::GetStorageID() const {
    return O_StorageID;
}
int ItemType::GetFloorID() const {
    return O_FloorID;
}
string ItemType::GetPicture() const {
	return O_Picture;
}
void ItemType::SetName(string inName) {
	O_Name = inName;
}
void ItemType::SetBuyDate(int inDate) {
	O_BuyDate = inDate;
}
void ItemType::SetType(string inType) {
	O_Type = inType;
}
void ItemType::SetLabel(int inLabel) {
	O_Label = inLabel;
}
void ItemType::SetVolume(int inVolume) {
	O_Volume = inVolume;
}
void ItemType::SetPicture(string inPic) {
	O_Picture = inPic;
}

void ItemType::SetStorageID(int id) {
    O_StorageID = id;
}
void ItemType::SetFloorID(int id) {
    O_FloorID = id;
}


void ItemType::SetRecordByItem(const ItemType& data) {
    *this = data;
}	


int ItemType::GetAttribute() const{
    return O_atri;
}

void ItemType::SetAttribute(int inattr){
    O_atri = inattr;
}

string ItemType::DisplayItem(){
    string temp;
    temp.append("Label: " + to_string(GetLabel()) + "\n");
    temp.append("이름: " + GetName() + "\n");
    temp.append("Type: " + GetType() + "\n");
    temp.append("개수: " + to_string(GetVolume()) + "\n");
    temp.append("구입 날짜: " + to_string(GetBuyDate()) + "\n");
    temp.append("보관 장소: " + to_string(GetStorageID()) + "번, " + to_string(GetFloorID()) + "층\n");
    temp.append("사진: " + GetPicture());

    return temp;
}

string ItemType::OutFile(){
    string temp;
    temp.append(to_string(O_key) + " " + to_string(O_Label) + " " + O_Name + " " + O_Type + " " + to_string(O_Volume) + " "
                + to_string(O_BuyDate) + " " + to_string(O_atri) + " " + to_string(O_StorageID) + " " + to_string(O_FloorID) + " " + O_Picture + "\n");

    return temp;
}


