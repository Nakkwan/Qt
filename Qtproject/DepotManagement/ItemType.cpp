#include "ItemType.h"

SingleLinkedList<QString> ItemType::O_TypeList;

QString ItemType::GetName() const {
	return O_Name;
}
int ItemType::GetBuyDate() const {
	return O_BuyDate;
}
int ItemType::GetLabel() const {
	return O_Label;
}
QString ItemType::GetType() const {
	return O_Type;
}
int ItemType::GetVolume() const {
	return O_Volume;
}
int ItemType::GetRoomID() const {
	return O_RoomID;
}
int ItemType::GetDrawerID() const {
	return O_DrawerID;
}
int ItemType::GetContainerID() const {
	return O_ContainerID;
}
QString ItemType::GetPicture() const {
	return O_Picture;
}
void ItemType::SetName(QString inName) {
	O_Name = inName;
}
void ItemType::SetBuyDate(int inDate) {
	O_BuyDate = inDate;
}
void ItemType::SetType(QString inType) {
	O_Type = inType;
}
void ItemType::SetLabel(int inLabel) {
	O_Label = inLabel;
}
void ItemType::SetVolume(int inVolume) {
	O_Volume = inVolume;
}
void ItemType::SetPicture(QString inPic) {
	O_Picture = inPic;
}

void ItemType::SetContainerID() {
	O_ContainerID = O_Label / 100;
}
void ItemType::SetDrawerID() {
	O_DrawerID = O_Label / 10000;
}
void ItemType::SetRoomID() {
	O_RoomID = O_Label / 1000000;
}

void ItemType::SetRecord(QString inName, int inDate, QString inType, int inLabel, int inVolume) {
	O_Name = inName;
	O_BuyDate = inDate;
	O_Type = inType;
	O_Label = inLabel;
	O_Volume = inVolume;
	SetContainerID();
	SetDrawerID();
	SetRoomID();
}

void ItemType::SetRecordByItem(const ItemType& data) {
	O_Name = data.GetName();
	O_RoomID = data.GetRoomID();
	O_DrawerID = data.GetDrawerID();
	O_ContainerID = data.GetContainerID();
	O_Label = data.GetLabel();
	O_Type = data.GetType();
	O_BuyDate = data.GetBuyDate();
	O_Volume = data.GetVolume();
	O_Picture = data.GetPicture();
	O_SearchNum = data.GetSearchNum();

}	


bool ItemType::CheckDate(int year, int month, int day) {					//날짜의 유효성 확인
	if ((month % 2 == 1)) //odd month   
	{
		if (month <= 7)
			if (day <= 0 || day > 31) return false;
			else // month > 7   
				if (day <= 0 || day > 30) return false;
	}
	else //even month  
	{
		if (month <= 6) {
			if (month == 2)
			{
				if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) // leap year  
				{
					if (day <= 0 || day > 30) return false;
				}
				else if (day <= 0 || day > 28) return false;

			}
			if (day <= 0 || day > 30) return false;
		}
		else { // month > 6  

			if (day <= 0 || day > 31) return false;
		}
	}
	return true;
}


