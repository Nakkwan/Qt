#include "object.h"

string Object::DisplayItem() {
    string temp = "Object\n";
    temp.append("Label: " + to_string(GetLabel()) + "\n");
    temp.append(QString::fromLocal8Bit("이름: ").toStdString() + GetName() + "\n");
    temp.append("Type: " + GetType() + "\n");
    temp.append(QString::fromLocal8Bit("개수: ").toStdString() + to_string(GetVolume()) + "\n");
    temp.append(QString::fromLocal8Bit("구입 날짜: ").toStdString() + to_string(GetBuyDate()) + "\n");
    if(O_atri == 1){
        temp.append(QString::fromLocal8Bit("소비형: o\n").toStdString());
    }else{
        temp.append(QString::fromLocal8Bit("소비형: x\n").toStdString());
    }
    temp.append(QString::fromLocal8Bit("보관 장소: ").toStdString() + to_string(GetStorageID()) + QString::fromLocal8Bit("번, ").toStdString() + to_string(GetFloorID()) + QString::fromLocal8Bit("층\n").toStdString());
    temp.append(QString::fromLocal8Bit("사진: ").toStdString() + GetPicture());

    return temp;
}

string Object::OutFile(){
    string temp;
    temp.append(to_string(O_key) + " " + to_string(O_Label) + " " + O_Name + " " + O_Type + " " + to_string(O_Volume) + " "
                + to_string(O_BuyDate) + " " + to_string(O_atri) + " " + to_string(O_StorageID) + " " + to_string(O_FloorID) + " " + O_Picture + "\n");

    return temp;
}

string Food::DisplayItem() {
    string temp = "Food\n";
    temp.append("Label: " + to_string(GetLabel()) + "\n");
    temp.append(QString::fromLocal8Bit("이름: ").toStdString() + GetName() + "\n");
    temp.append("Type: " + GetType() + "\n");
    temp.append(QString::fromLocal8Bit("개수: ").toStdString() + to_string(GetVolume()) + "\n");
    temp.append(QString::fromLocal8Bit("구입 날짜: ").toStdString() + to_string(GetBuyDate()) + "\n");
    temp.append(QString::fromLocal8Bit("유통기한: ").toStdString() + to_string(GetAttribute()) + "\n");
    temp.append(QString::fromLocal8Bit("보관 장소: ").toStdString() + to_string(GetStorageID()) + QString::fromLocal8Bit("번, ").toStdString() + to_string(GetFloorID()) + QString::fromLocal8Bit("층\n").toStdString());
    temp.append(QString::fromLocal8Bit("사진: ").toStdString() + GetPicture());

    return temp;
}

string Food::OutFile(){
    string temp;
    temp.append(to_string(O_key) + " " + to_string(O_Label) + " " + O_Name + " " + O_Type + " " + to_string(O_Volume) + " "
                + to_string(O_BuyDate) + " " + to_string(O_atri) + " " + to_string(O_StorageID) + " " + to_string(O_FloorID) + " " + O_Picture + "\n");

    return temp;
}
