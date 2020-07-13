#include "simpleitemtype.h"

SimpleItemType::SimpleItemType()
{
    S_Label = -1;
    S_Name = "None";
    S_Type = "None";
    S_Photo = "None";
}

SimpleItemType::SimpleItemType(ItemType* data)
{
    S_Label = data->GetLabel();
    S_Name = data->GetName();
    S_Type = data->GetType();
    S_Photo = data->GetPicture();
}

int SimpleItemType::GetLabel() const{
    return S_Label;
}
string SimpleItemType::GetName() const{
    return S_Name;
}
string SimpleItemType::GetType() const{
    return S_Type;
}
string SimpleItemType::GetPhoto() const{
    return S_Photo;
}

void SimpleItemType::SetLabel(int inlabel){
    S_Label = inlabel;
}
void SimpleItemType::SetName(string inname){
    S_Name = inname;
}
void SimpleItemType::SetType(string intype){
    S_Type = intype;
}
void SimpleItemType::SetPhoto(string inphoto){
    S_Photo = inphoto;
}

string SimpleItemType::DisplayItem(){
    string temp;
    string L = "Label: " + to_string(GetLabel()) + "\n";
    string N = "Name: " + GetName() + "\n";
    string T = "Type: " + GetType() + "\n";
    string P = "Picture: " + GetPhoto();
    temp.append(L);
    temp.append(N);
    temp.append(T);
    temp.append(P);

    return temp;
}

//string SimpleItemType::OutFile(){
//    string temp;
//    temp.append(to_string(S_Label) + " " + S_Name + " " + S_Type + " " + S_Photo + "\n");
//    return temp;
//}
