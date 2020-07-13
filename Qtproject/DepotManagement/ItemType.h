#ifndef __ITEMTYPE_H
#define __ITEMTYPE_H
#include "pch.h"


class ItemType{
public:
	ItemType() {			//constructor
        O_key = -1;
		O_Name = "";				//������ �̸�
		O_BuyDate = -1;				//���� ��¥
		O_Label = -1;				//������ ���� ID
		O_Type = "";				//������ Ÿ��, �뵵
		O_Volume = -1;				//������ ����
		O_SearchNum = -1;			//������ �˻� Ƚ��
        O_StorageID = -1;
        O_FloorID = -1;
		O_Picture = "None";			//������ ���� ������ ���
        O_atri = -1;
	}
	~ItemType() {}	//destructor

    int GetKey() const;

	/*
	@brief: get object name
	@pre: set object name
	@post: none
	@return: object name
	*/
    string GetName() const;

	/*
	@brief: get object writer
	@pre: set buy date
	@post: none
	@return: buy date
	*/
	int GetBuyDate() const;

	/*
	@brief: get unique label
	@pre: set unique label
	@post: none
	@return: unique label
	*/
	int GetLabel() const;

	/*
	@brief: get type of object
	@pre: set type
	@post: none
	@return: type
	*/
    string GetType() const;

	/*
	@brief: get number of object
	@pre: set volume
	@post: none
	@return: volume
	*/
	int GetVolume() const;

	/*
	@brief: get ID of Container
	@pre: set containerID
	@post: none
	@return: containerID
	*/
    int GetStorageID() const;

	/*
	@brief: get ID of Drawer
	@pre: set drawerID
	@post: none
	@return: drawerID
	*/
    int GetFloorID() const;

	/*
	@brief: get picture name(path) of object
	@pre: set picture name(path)
	@post: none
	@return: picture name(path)
	*/
    string GetPicture() const;

	/*
	@brief: set object name
	@pre: none
	@post: assign object name
	@param: object name
	*/
    void SetName(string inName);

	/*
	@brief: set buy date of object
	@pre: none
	@post: assign buy date
	@param: buy date
	*/
	void SetBuyDate(int inDate);

	/*
	@brief: set unique label
	@pre: none
	@post: assign unique label
	@param: label
	*/
	void SetLabel(int inLabel);

	/*
	@brief: set ContainerID
	@pre: none
	@post: assign ContainerID
	*/
    void SetStorageID(int id);

	/*
	@brief: set DrawerID
	@pre: none
	@post: assign DrawerID
	*/
    void SetFloorID(int id);

	/*
	@brief: set type
	@pre: none
	@post: assign type of object
	@param: type
	*/
    void SetType(string inType);

	/*
	@brief: set number of object
	@pre: none
	@post: assign number of object
	@param: object number
	*/
	void SetVolume(int inVolume);

	/*
	@brief: set picture name(path) of object
	@pre: none
	@post: assign picture name(path) of object
	@param: picture name(path) of object
	*/
    void SetPicture(string inPic);

	/*
	@brief: set elememt of ItemType member value
	@pre: none
	@post: assign ItemType
	@param: ItemType for assign member value
	*/
	void SetRecordByItem(const ItemType& data);

	/*
	@brief: �˻�Ƚ���� �ø���.
	@pre: none
	@post: increase O_SearchNum
	*/
	void AddSearchNum() {
		O_SearchNum++;
	}

	/*
	@brief: get searchNum
	@pre: none
	@post: none
	@return: return O_searchNum
	*/
	int GetSearchNum() const {
		return O_SearchNum;
	}

    /*
    @brief: Get Atrribute of item
    @pre: Set atrribute
    @post: none
    @return: Atrribute
    */
    int GetAttribute() const;

    /*
    @brief: Set Atrribute of item
    @pre: none
    @post: Set Atrribute
    */
    void SetAttribute(int inattr);

    /*
    @brief: Display info of item
    @pre: Set item
    @post: none
    @return: info of item(string)
    */
    virtual string DisplayItem();

    /*
    @brief: outfile info of item
    @pre: Set item
    @post: none
    @return: info of item(string)
    */
    virtual string OutFile();

	/*
	@brief: Decide two ItemType is same
	@pre: set unique label of two object
	@post: none
	@param: ItemType to compare
	@return: if same, return 1 if differ, return 0
	*/
    bool operator==(const ItemType& data) {
        if (this->O_Label == data.GetLabel()) {
            return true;
        }
        else {
            return false;
        }
    }

	/*
	@brief: Decide if current itemtype is bigger
	@pre: set unique label of two object
	@post: none
	@param: ItemType for compare
	@return: if bigger, return 1 if smaller, return 0
	*/
	bool operator>(const ItemType& data) {
		if (this->O_Label > data.GetLabel()) {
			return true;
		}
		else {
			return false;
		}
	}

	/*
	@brief: Decide if current itemtype is smaller
	@pre: set unique label of two object
	@post: none
	@param: ItemType for compare
	@return: if smaller, return 1 if bigger, return 0
	*/
	bool operator<(const ItemType& data) {
		if (this->O_Label < data.GetLabel()) {
			return true;
		}
		else {
			return false;
		}
	}


	/*
	@brief: assign data
	@pre: set data to be changed
	@post: member value is replaced by parameter
	*/
    virtual void operator=(const ItemType& data) {
		O_Name = data.GetName();
		O_Label = data.GetLabel();
        O_StorageID = data.GetStorageID();
        O_FloorID = data.GetFloorID();
		O_Type = data.GetType();
		O_BuyDate = data.GetBuyDate();
		O_Volume = data.GetVolume();
		O_Picture = data.GetPicture();
		O_SearchNum = data.GetSearchNum();
        O_key = data.GetKey();
        O_atri = data.GetAttribute();
	}


protected:
    string O_Name;									//������ �̸�
	int O_Label;									//������ ���� ID
	int O_BuyDate;									//������ ���� �ñ�
    string O_Type;									//������ �뵵, Ÿ��
    string O_Picture;								//������ ���� ���
	int O_Volume;									//������ ����
	int O_SearchNum;								//������ �˻� Ƚ��
    int O_StorageID;									//������ ������ ���� ID
    int O_FloorID;									//������ ������ �������� ID
    int O_key;
    int O_atri;
};

#endif
