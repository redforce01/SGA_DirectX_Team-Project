#pragma once
#include "cSingletonBase.h"

struct tagSoundList
{
	vector<string>				arrSound;
	vector<string>::iterator	iterSound;
};

class cSoundStruct
{
public:
	string DirectoryHigh;
	vector<string> vDirectoryLow;

	map<string, tagSoundList*>				arrPartSound;
	map<string, tagSoundList*>::iterator	iterPartSound;

	void SoundMgrAdd();

	cSoundStruct() {};
	~cSoundStruct() {};
};

class cSoundData : public cSingletonBase<cSoundData>
{
private:
	map<string, cSoundStruct*>						arrTotalSound;
	map<string, cSoundStruct*>::iterator			iterTotalSound;

	int totalSoundSize;

public:
	cSoundData();
	~cSoundData();

	void Init();
	void Release();

	void LoadSoundList();
	void addSoundList();

	void playSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation);
	void playSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum);
	void playSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum, float volume);

	void resumeSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation);
	void resumeSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum);
	void resumeSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum, float volume);

	void stopSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation);
	void stopSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum);

	void pauseSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation);
	void pauseSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum);

	string findSoundCategory(SoundUtil::SOUND_DATA_TYPE soundType);
	string findSoundKey(SoundUtil::SOUND_DATA_PLAY_TYPE situation);

	string getSoundKey(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum);

	int GetTotalSoundSize();
};

#define SOUNDDATA cSoundData::GetInstance()