#include "stdafx.h"
#include "cEventObjectManager.h"


cEventObjectManager::cEventObjectManager()
{
}


cEventObjectManager::~cEventObjectManager()
{
}

HRESULT cEventObjectManager::Init()
{
	/*
	/	EVENT OBJECT ���� �� ����
	/	cObject_EventObj* newEvent = new cObject_EventObj;
	/	newEvent->Init();
	/	newEvent->setLocalPosition(D3DXVECTOR3(x, 0, z));
	/	vEventObj.push_back(newEvent);
	*/	

	/*
	/	EVENT SOUND ���� �� ����
	/	cObject_Sound* newSoundObj = new cObject_Sound;
	/	string soundName = SOUNDDATA->getSoundKey(SOUND_TYPE_STRUCT_BASEMENT, SOUND_PLAY_TYPE_MOOD_ROOM, 0);
	/	newSoundObj->Init(soundName, 0.5, FALSE, TRUE, D3DXVECTOR3(0, 0, 0));
	/	vEventSound.push_back(newSoundObj);
	*/

	return S_OK;
}

void cEventObjectManager::Release()
{
	for (viEventObj = vEventObj.begin(); viEventObj != vEventObj.end(); ++viEventObj)
	{
		(*viEventObj)->Release();
		SAFE_DELETE((*viEventObj));
		//viEventObj = vEventObj.erase(viEventObj);
	}
	vEventObj.clear();

	for (viEventSound = vEventSound.begin(); viEventSound != vEventSound.end(); ++viEventSound)
	{
		(*viEventSound)->Release();
		SAFE_DELETE((*viEventSound));
		//viEventSound = vEventSound.erase(viEventSound);
	}
	vEventSound.clear();
}

void cEventObjectManager::Update(float timeDelta, D3DXVECTOR3 playerPos)
{
	int size = vEventObj.size();
	for (int i = 0; i < size; i++)
	{
		vEventObj[i]->Update(timeDelta, playerPos);
	}

	size = vEventSound.size();
	for (int i = 0; i < size; i++)
	{
		vEventSound[i]->Update(timeDelta, playerPos);
	}
}

void cEventObjectManager::Render(const cCamera * pCamera, vector<cLight*> lights)
{
	for (int i = 0; i < vEventObj.size(); i++)
	{
		vEventObj[i]->Render(pCamera, lights);
	}

#ifdef _DEBUG
	//char szTemp[128];
	//for (int i = 0; i < vEventSound.size(); i++)
	//{		
	//	sprintf_s(szTemp, "obj[%d] Dis : %.2f", i, vEventSound[i]->FunctionDistance());
	//	DXFONT_MGR->PrintTextOutline(szTemp, WINSIZE_X - 400, 200 + (i * 60), 0xffffff00, 0xff000000);

	//	sprintf_s(szTemp, "obj[%d] Vol : %.2f", i, vEventSound[i]->GetSoundVolume());
	//	DXFONT_MGR->PrintTextOutline(szTemp, WINSIZE_X - 400, 230 + (i * 60), 0xffffff00, 0xff000000);
	//}

#endif // DEBUG

}

void cEventObjectManager::AddSoundObject(string soundName, D3DXVECTOR3 position)
{
	cObject_Sound* newSoundObj = new cObject_Sound;
	newSoundObj->Init(soundName, position);
	vEventSound.push_back(newSoundObj);
}

void cEventObjectManager::AddSoundObject(string soundName, float soundVolume, bool isLoopPlay, bool isEvent, D3DXVECTOR3 position)
{
	cObject_Sound* newSoundObj = new cObject_Sound;
	newSoundObj->Init(soundName, soundVolume, isLoopPlay, isEvent, position);
	vEventSound.push_back(newSoundObj);
}

void cEventObjectManager::AddSoundObject(string soundName, float soundVolume, bool isLoopPlay, bool isEvent, D3DXVECTOR3 position, cBoundBox eventBox)
{
	cObject_Sound* newSoundObj = new cObject_Sound;
	newSoundObj->Init(soundName, soundVolume, isLoopPlay, isEvent, position, eventBox);
	vEventSound.push_back(newSoundObj);
}

void cEventObjectManager::AddEventObject(string objectName, D3DXVECTOR3 position, string poseName)
{
	cObject_EventObj* newEventObj = new cObject_EventObj;
	newEventObj->Init(objectName, position, poseName);
	vEventObj.push_back(newEventObj);
}

void cEventObjectManager::AddEventObject(string objectName, D3DXVECTOR3 position, string poseName, D3DXVECTOR3 eventPos)
{
	cObject_EventObj* newEventObj = new cObject_EventObj;
	newEventObj->Init(objectName, position, poseName, eventPos);
	vEventObj.push_back(newEventObj);
}

void cEventObjectManager::AddEventObject(string objectName, D3DXVECTOR3 position, string poseName, bool isStatic, D3DXVECTOR3 eventPos)
{
	cObject_EventObj* newEventObj = new cObject_EventObj;
	newEventObj->Init(objectName, position, poseName, isStatic, eventPos);
	vEventObj.push_back(newEventObj);
}
