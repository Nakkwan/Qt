#include "object.h"

string Object::DisplayItem() {
    string temp = "Object\n";
    temp.append("Label: " + to_string(GetLabel()) + "\n");
    temp.append(QString::fromLocal8Bit("�̸�: ").toStdString() + GetName() + "\n");
    temp.append("Type: " + GetType() + "\n");
    temp.append(QString::fromLocal8Bit("����: ").toStdString() + to_string(GetVolume()) + "\n");
    temp.append(QString::fromLocal8Bit("���� ��¥: ").toStdString() + to_string(GetBuyDate()) + "\n");
    if(O_atri == 1){
        temp.append(QString::fromLocal8Bit("�Һ���: o\n").toStdString());
    }else{
        temp.append(QString::fromLocal8Bit("�Һ���: x\n").toStdString());
    }
    temp.append(QString::fromLocal8Bit("���� ���: ").toStdString() + to_string(GetStorageID()) + QString::fromLocal8Bit("��, ").toStdString() + to_string(GetFloorID()) + QString::fromLocal8Bit("��\n").toStdString());
    temp.append(QString::fromLocal8Bit("����: ").toStdString() + GetPicture());

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
    temp.append(QString::fromLocal8Bit("�̸�: ").toStdString() + GetName() + "\n");
    temp.append("Type: " + GetType() + "\n");
    temp.append(QString::fromLocal8Bit("����: ").toStdString() + to_string(GetVolume()) + "\n");
    temp.append(QString::fromLocal8Bit("���� ��¥: ").toStdString() + to_string(GetBuyDate()) + "\n");
    temp.append(QString::fromLocal8Bit("�������: ").toStdString() + to_string(GetAttribute()) + "\n");
    temp.append(QString::fromLocal8Bit("���� ���: ").toStdString() + to_string(GetStorageID()) + QString::fromLocal8Bit("��, ").toStdString() + to_string(GetFloorID()) + QString::fromLocal8Bit("��\n").toStdString());
    temp.append(QString::fromLocal8Bit("����: ").toStdString() + GetPicture());

    return temp;
}

string Food::OutFile(){
    string temp;
    temp.append(to_string(O_key) + " " + to_string(O_Label) + " " + O_Name + " " + O_Type + " " + to_string(O_Volume) + " "
                + to_string(O_BuyDate) + " " + to_string(O_atri) + " " + to_string(O_StorageID) + " " + to_string(O_FloorID) + " " + O_Picture + "\n");

    return temp;
}
