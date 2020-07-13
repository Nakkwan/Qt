#ifndef __ITEMTYPE_H
#define __ITEMTYPE_H
#include "pch.h"


class ItemType{
public:
	ItemType() {			//constructor
        O_key = -1;
		O_Name = "";				//물건의 이름
		O_BuyDate = -1;				//구매 날짜
		O_Label = -1;				//물건의 고유 ID
		O_Type = "";				//물건의 타입, 용도
		O_Volume = -1;				//물건의 개수
		O_SearchNum = -1;			//물건의 검색 횟수
        O_StorageID = -1;
        O_FloorID = -1;
		O_Picture = "None";			//물건의 사진 파일의 경로
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
	@brief: 검색횟수를 늘린다.
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
    string O_Name;									//물건의 이름
	int O_Label;									//물건의 고유 ID
	int O_BuyDate;									//물건의 구매 시기
    string O_Type;									//물건의 용도, 타입
    string O_Picture;								//물건의 사진 경로
	int O_Volume;									//물건의 개수
	int O_SearchNum;								//물건의 검색 횟수
    int O_StorageID;									//물건이 보관된 방의 ID
    int O_FloorID;									//물건이 보관된 수납장의 ID
    int O_key;
    int O_atri;
};

#endif
