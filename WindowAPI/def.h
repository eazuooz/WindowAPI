#pragma once

#define SINGLE(type)\
public:\
	static type& GetInstance()\
	{\
		if (mInstance == nullptr)\
		{\
			mInstance = new type();\
		}\
		return *mInstance;\
	}\
	\
private:\
	static type* mInstance;\
	type();\
	~type();

enum SCENE_TYPE
{
	LOGO,
	START,
	STAGE_01,
	END,
};