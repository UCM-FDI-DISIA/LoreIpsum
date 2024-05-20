#pragma once
#include "../utils/Singleton.h"
#include <../pchs/pch.h>




namespace Sounds {
	enum MUSIC {
		OFFICE_M,
		BATTLE_P_M,
		BATTLE_T_M,
		SHOP_M,
		CITY_M,
		MAIN_MENU_M
	};

	enum CHANNELS {
		OFFICE_C,
		BATTLE_P_C,
		BATTLE_T_C
	};

	enum SOUND_EFFECTS {
		DOOR_SE,
		CANDLE_SE,
		AMBIENCE_STREET_SE,
		AMBIENCE_OFFICE_SE
	};
}


class SoundManager : public Singleton<SoundManager> {
public:


	SoundManager();

	~SoundManager() override;

	void init();



	// aumenta o disminuye el volumen MASTER
	int Volume(int i);
	void addVolume(int i);
	int getVolume() { return master_volume; };

	// volumen especifico para canales
	void ChannelVolume(Sounds::MUSIC channel, int v);

	void startDynamicMusic(Sounds::MUSIC a, Sounds::MUSIC b);
	void stopDynamicMusic(Sounds::MUSIC a, Sounds::MUSIC b);
	void changeDynamicMusic(Sounds::MUSIC a, Sounds::MUSIC b);

	void startSoundEffect(Sounds::SOUND_EFFECTS a, int reps = 0);
	void stopSoundEffect(Sounds::SOUND_EFFECTS a);

	// ----------
	void startMusic(Sounds::MUSIC M);
	void stopMusic(Sounds::MUSIC m);

	std::vector<std::string> music_names;
	std::vector<std::string> sound_effect_names;
	int master_volume;
};