#include "stdafx.h"
#include "cSoundData.h"


cSoundData::cSoundData()
{
}


cSoundData::~cSoundData()
{
}

void cSoundData::Init()
{
	totalSoundSize = 0;

	LoadSoundList();
	addSoundList();

	//Get totalSoundSize Function
	//totalSoundSize = GetTotalSoundSize();
}

void cSoundData::Release()
{
	for (iterTotalSound = arrTotalSound.begin(); iterTotalSound != arrTotalSound.end(); ++iterTotalSound)
	{
		SAFE_DELETE(iterTotalSound->second);
	}
}

void cSoundData::LoadSoundList()
{
	vector<string> vTemp = TXTDATA->txtLoad("Database/SoundList.txt");

	string category;
	string part;
	string soundName;

	for (unsigned int i = 0; i < vTemp.size(); i++)
	{
		if (strchr(vTemp[i].c_str(), '#')) continue;

		if (strchr(vTemp[i].c_str(), '*'))
		{
			category = strstr(vTemp[i].c_str(), "*");
			category = category.substr(1, category.size());
			cSoundStruct* newSoundPart = new cSoundStruct;
			newSoundPart->DirectoryHigh = category;
			arrTotalSound.insert(make_pair(category, newSoundPart));
			iterTotalSound = arrTotalSound.begin();
		}

		if (strchr(vTemp[i].c_str(), '-'))
		{
			part = strstr(vTemp[i].c_str(), "-");
			part = part.substr(1, part.size());
			arrTotalSound.find(category)->second->vDirectoryLow.push_back(part);
			arrTotalSound.find(category)->second->arrPartSound.insert(make_pair(part, new tagSoundList));
			arrTotalSound.find(category)->second->iterPartSound = arrTotalSound.find(category)->second->arrPartSound.begin();
		}

		if (strchr(vTemp[i].c_str(), '='))
		{
			soundName = strstr(vTemp[i].c_str(), "=");
			soundName = soundName.substr(1, soundName.size());
			arrTotalSound.find(category)->second->arrPartSound.find(part)->second->arrSound.push_back(soundName);
			arrTotalSound.find(category)->second->arrPartSound.find(part)->second->iterSound =
				arrTotalSound.find(category)->second->arrPartSound.find(part)->second->arrSound.begin();
		}
	}
}

void cSoundData::addSoundList()
{
	for (iterTotalSound = arrTotalSound.begin(); iterTotalSound != arrTotalSound.end(); ++iterTotalSound)
	{
		iterTotalSound->second->SoundMgrAdd();
	}
}

void cSoundData::playSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation)
{
	string category = findSoundCategory(soundType);
	string soundKey = findSoundKey(situation);


	char strNum[10];
	sprintf_s(strNum, "%d", 0);
	string keyCount = strNum;

	string applyKey = category + "_" + soundKey + keyCount;

	if (!SOUNDMANAGER->isPlaySound(applyKey))
	{
		SOUNDMANAGER->play(applyKey, 0.5);
	}
}

void cSoundData::playSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum)
{
	string category = findSoundCategory(soundType);
	string soundKey = findSoundKey(situation);


	char strNum[10];
	sprintf_s(strNum, "%d", soundNum);
	string keyCount = strNum;

	string applyKey = category + "_" + soundKey + keyCount;

	if (!SOUNDMANAGER->isPlaySound(applyKey))
	{
		SOUNDMANAGER->play(applyKey, 0.5);
	}
}

void cSoundData::playSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum, float volume)
{
	string category = findSoundCategory(soundType);
	string soundKey = findSoundKey(situation);


	char strNum[10];
	sprintf_s(strNum, "%d", soundNum);
	string keyCount = strNum;

	string applyKey = category + "_" + soundKey + keyCount;

	if (!SOUNDMANAGER->isPlaySound(applyKey))
	{
		SOUNDMANAGER->play(applyKey, volume);
	}
}

void cSoundData::resumeSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation)
{
	string category = findSoundCategory(soundType);
	string soundKey = findSoundKey(situation);


	char strNum[10];
	sprintf_s(strNum, "%d", 0);
	string keyCount = strNum;

	string applyKey = category + "_" + soundKey + keyCount;

	if (!SOUNDMANAGER->isPauseSound(applyKey))
	{
		SOUNDMANAGER->resume(applyKey);
	}
}

void cSoundData::resumeSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum)
{
	string category = findSoundCategory(soundType);
	string soundKey = findSoundKey(situation);


	char strNum[10];
	sprintf_s(strNum, "%d", soundNum);
	string keyCount = strNum;

	string applyKey = category + "_" + soundKey + keyCount;

	if (!SOUNDMANAGER->isPauseSound(applyKey))
	{
		SOUNDMANAGER->resume(applyKey);
	}
}

void cSoundData::resumeSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum, float volume)
{
	string category = findSoundCategory(soundType);
	string soundKey = findSoundKey(situation);


	char strNum[10];
	sprintf_s(strNum, "%d", soundNum);
	string keyCount = strNum;

	string applyKey = category + "_" + soundKey + keyCount;

	if (!SOUNDMANAGER->isPauseSound(applyKey))
	{
		SOUNDMANAGER->resume(applyKey);
	}
}



void cSoundData::stopSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation)
{
	string category = findSoundCategory(soundType);
	string soundKey = findSoundKey(situation);


	char strNum[10];
	sprintf_s(strNum, "%d", 0);
	string keyCount = strNum;

	string applyKey = category + "_" + soundKey + keyCount;

	if (SOUNDMANAGER->isPlaySound(applyKey))
	{
		SOUNDMANAGER->stop(applyKey);
	}
}

void cSoundData::stopSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum)
{
	string category = findSoundCategory(soundType);
	string soundKey = findSoundKey(situation);


	char strNum[10];
	sprintf_s(strNum, "%d", soundNum);
	string keyCount = strNum;

	string applyKey = category + "_" + soundKey + keyCount;

	if (SOUNDMANAGER->isPlaySound(applyKey))
	{
		SOUNDMANAGER->stop(applyKey);
	}
}

void cSoundData::pauseSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation)
{
	string category = findSoundCategory(soundType);
	string soundKey = findSoundKey(situation);


	char strNum[10];
	sprintf_s(strNum, "%d", 0);
	string keyCount = strNum;

	string applyKey = category + "_" + soundKey + keyCount;

	if (SOUNDMANAGER->isPauseSound(applyKey))
	{
		SOUNDMANAGER->pause(applyKey);
	}
}

void cSoundData::pauseSound(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum)
{
	string category = findSoundCategory(soundType);
	string soundKey = findSoundKey(situation);


	char strNum[10];
	sprintf_s(strNum, "%d", soundNum);
	string keyCount = strNum;

	string applyKey = category + "_" + soundKey + keyCount;

	if (SOUNDMANAGER->isPauseSound(applyKey))
	{
		SOUNDMANAGER->pause(applyKey);
	}
}

string cSoundData::findSoundCategory(SoundUtil::SOUND_DATA_TYPE soundType)
{
	string category;
	switch (soundType)
	{
	case SoundUtil::SOUND_TYPE_BGM:
		category = "BGMMusic";
		break;
	case SoundUtil::SOUND_TYPE_MENU:
		category = "MenuSound";
		break;
	case SoundUtil::SOUND_TYPE_PLAYER_EFFECT:
		category = "PLAYERsSound";
		break;
	case SoundUtil::SOUND_TYPE_PLAYER_VOICE:
		category = "PLAYERsVoice";
		break;
	case SoundUtil::SOUND_TYPE_NPC:
		category = "NPCsSound";
		break;
	case SoundUtil::SOUND_TYPE_STRUCT_BASEMENT:
		category = "Basement";
		break;
	case SoundUtil::SOUND_TYPE_STRUCT_FEMALEWARD:
		category = "FemaleWard";
		break;
	case SoundUtil::SOUND_TYPE_STRUCT_COURTYARD:
		category = "Courtyard";
		break;
	case SoundUtil::SOUND_TYPE_CUSTOM:
		category = "CustomBGM";
		break;
	case SoundUtil::SOUND_TYPE_ETC:
		break;
	}

	return category;
}

string cSoundData::findSoundKey(SoundUtil::SOUND_DATA_PLAY_TYPE situation)
{
	string soundKey;
	switch (situation)
	{
		//MENU & BGM SOUND
	case SoundUtil::SOUND_PLAY_TYPE_MENUBGM:
		soundKey = "MenuBGM";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_MENUEFFECT:
		soundKey = "MenuEffect";
		break;
	case SoundUtil::SOUND_PLAY_GAME_BGM:
		soundKey = "BackgroundMusic";
		break;

		//CUSTOM SOUND
	case SoundUtil::SOUND_PLAY_TYPE_CUSTOM:
		soundKey = "BackgroundMusic";
		break;

		//Courtyard SOUND
	case SoundUtil::SOUND_PLAY_TYPE_RAINY:
		soundKey = "Rainy";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_SMILE:
		soundKey = "Smile";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_GROUND:
		soundKey = "Ground";
		break;

		//PLAYER SOUND
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_WALKING_NORMAL:
		soundKey = "WalkingOnNormal";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_WALKING_WOOD:
		soundKey = "WalkingOnWood";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_WALKING_IRON:
		soundKey = "WalkingOnIron";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_WALKING_SOIL:
		soundKey = "WalkingOnSoil";
		break;

	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_ATTACKED:
		soundKey = "Attacked";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_ATTACKED_RELAX:
		soundKey = "AttackedRelax";
		break;

	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_ROPE:
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_BREATH_ROUGH:
		soundKey = "BreathRough";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_DAED:
		soundKey = "Dead";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_FEAR:
		soundKey = "Fear";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_FEARHIGH:
		soundKey = "FearHigh";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_NERVOUS:
		soundKey = "Nervous";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_PAIN:
		soundKey = "Pain";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_RELAX:
		soundKey = "Relax";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_SCRAG:
		soundKey = "Scrag";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_SURPRISE:
		soundKey = "Surprise";
		break;

	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_TRY_USE_KEY:
		soundKey = "OpenDoorUseKey";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_TRY_OPEN_CABINET:
		soundKey = "TryOpenCabinet";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_TRY_TURN_VALVE:
		soundKey = "TryTurnValve";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_TRY_CLOSE_VALVE:
		soundKey = "CloseValve";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_OPEN_TAPE:
		soundKey = "OpenTape";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_SEARCH_DESK:
		soundKey = "SearchSound";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_PLAYER_TYPEKEYBOARD:
		soundKey = "TypeKeyboard";
		break;

		//CAM SOUND 
	case SoundUtil::SOUND_PLAY_TYPE_CAM_EFFECT:
		soundKey = "CAMEffect";
		break;
	case SOUND_PLAY_TYPE_CAM_OUT:
		soundKey = "TakeOutCam";
		break;
	case SOUND_PLAY_TYPE_CAM_VISION:
		soundKey = "CamTurnOnVision";
		break;

		//NPC SOUND
	case SoundUtil::SOUND_PLAY_TYPE_NPC_SCISSORS:
		soundKey = "Scissors";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_NPC_KNIFE:
		soundKey = "CutBody";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_ATTACK:
		soundKey = "Attack";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_NPC_WALKING_HEAVY:
		soundKey = "WalkingHeavy";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_NPC_WALKING_NORMAL:
		soundKey = "WalkingNormal";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_NPC_WALKING_STAIR:

		break;
	case SoundUtil::SOUND_PLAY_TYPE_NPC_WALKING_IRON:
		soundKey = "WalkingOnIron";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_NPC_WALKING_WATER:
		soundKey = "WalkingOnWater";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_NPC_BREECHING:
		soundKey = "Breeching";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_NPC_TRY_BREECHING:
		soundKey = "TryBreeching";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_NPC_CHAIN:
		soundKey = "Chain";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_NPC_CUTBODY:
		soundKey = "CutBody";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_NPC_TRYOPEN_DOOR:
		soundKey = "TryOpenDoor";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_NPC_OPEN_DOOR:
		soundKey = "OpenDoor";
		break;

		//ROOM SOUND
	case SoundUtil::SOUND_PLAY_TYPE_ROOM_RUN_FAR:
		soundKey = "RoomRunFar";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_ROOM_RUN_CLOSE:
		soundKey = "RoomRun";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_ROOM_SHOWER:
		soundKey = "ShowerRoom";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_HALLWAYRUN_FAR:
		soundKey = "HallWayRun";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_HALLWAYRUN_CLOSE:
		soundKey = "HallWay";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_LOOKEVENT:
		soundKey = "LookEvent";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_THUNDER:
		soundKey = "Thunder";
		break;


	case SoundUtil::SOUND_PLAY_TYPE_MOOD_HALL:	//FemaleWard
		soundKey = "Room";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_MOOD_ROOM:	//Basement
		soundKey = "RoomMood";
		break;


	case SoundUtil::SOUND_PLAY_TYPE_BEND:
		soundKey = "Bend";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_MACHINE_01:	//Basement
		soundKey = "Machine";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_MACHINE_02:	//FemaleWard
		soundKey = "Machine";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_ELECTRIC:	//Basement
		soundKey = "Electric";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_ELECTRIC_NOICE:	//Basement
		soundKey = "ElectricNoice";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_SWITCH:	//Basement
		soundKey = "Switch";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_WATERFALL:		
		break;

	case SoundUtil::SOUND_PLAY_TYPE_CAN:
		soundKey = "Can";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_DOORCLOSE:
		soundKey = "Door";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_FALLOBJECT:
		soundKey = "FallEffect";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_HALLWAYRUN:
		soundKey = "HallWayRun";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_HALLWAY:
		soundKey = "HallWay";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_IRONEFFECT:
		soundKey = "IronEffect";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_ROPE:
		soundKey = "Rope";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_ELEVATOR:
		soundKey = "Elevator";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_ELEVATOR2:
		soundKey = "Elevator2";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_OPENDOOR:
		soundKey = "OpenDoor";
		break;
	case SoundUtil::SOUND_PLAY_TYPE_LOCKDOOR:
		soundKey = "LockDoor";
		break;

	default:
		break;
	}

	return soundKey;
}

string cSoundData::getSoundKey(SoundUtil::SOUND_DATA_TYPE soundType, SoundUtil::SOUND_DATA_PLAY_TYPE situation, int soundNum)
{
	string category = findSoundCategory(soundType);
	string soundKey = findSoundKey(situation);


	char strNum[10];
	sprintf_s(strNum, "%d", soundNum);
	string keyCount = strNum;

	string applyKey = category + "_" + soundKey + keyCount;

	return applyKey;
}

int cSoundData::GetTotalSoundSize()
{
	int totalSoundSize = 0;
	for (iterTotalSound = arrTotalSound.begin(); iterTotalSound != arrTotalSound.end(); ++iterTotalSound)
	{
		for (iterTotalSound->second->iterPartSound = iterTotalSound->second->arrPartSound.begin();
		iterTotalSound->second->iterPartSound != iterTotalSound->second->arrPartSound.end(); ++iterTotalSound->second->iterPartSound)
		{
			for (int i = 0; i < iterTotalSound->second->iterPartSound->second->arrSound.size(); i++)
			{
				totalSoundSize++;
			}
		}
	}

	return totalSoundSize;
}

void cSoundStruct::SoundMgrAdd()
{
	string soundKey;
	string soundFile;

	char soundKeyBuf[10];
	int soundCount = 0;
	int soundPartNum = 0;

	for (iterPartSound = arrPartSound.begin(); iterPartSound != arrPartSound.end(); ++iterPartSound)
	{
		soundCount = 0;
		int size = iterPartSound->second->arrSound.size();
		for (int i = 0; i < size; i++)
		{
			soundKey = DirectoryHigh;
			soundKey = soundKey.append("_");
			soundKey = soundKey.append(vDirectoryLow[soundPartNum]);
			sprintf_s(soundKeyBuf, "%d", soundCount);
			soundKey = soundKey.append(soundKeyBuf);

			iterPartSound->second[i];
			soundFile = "SoundData";
			soundFile = soundFile.append("/");
			soundFile = soundFile.append(DirectoryHigh);
			soundFile = soundFile.append("/");
			soundFile = soundFile.append(vDirectoryLow[soundPartNum]);
			soundFile = soundFile.append("/");
			soundFile = soundFile.append(iterPartSound->second->arrSound[i]);
			soundFile = soundFile.append(".mp3");

			SOUNDMANAGER->addSound(soundKey, soundFile, FALSE, FALSE);
			soundCount++;
		}
		soundPartNum++;
	}
}
