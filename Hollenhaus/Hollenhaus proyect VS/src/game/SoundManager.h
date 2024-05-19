#pragma once
#include "../utils/Singleton.h"
#include <../pchs/pch.h>




namespace Musics {
	enum MUSIC {
		OFFICE_M,
		BATTLE_P_M,
		BATTLE_T_M,
		SHOP_M,
		CITY_M
	};

	enum CHANNELS {
		OFFICE_C,
		BATTLE_P_C,
		BATTLE_T_C
	};
}


class SoundManager : public Singleton<SoundManager> {
public:


	SoundManager();

	~SoundManager() override;

	void init();



	// aumenta o disminuye el volumen MASTER
	int Volume(int i);
	int getVolume() { return master_volume; };

	// volumen especifico para canales
	void ChannelVolume(Musics::MUSIC channel, int v);

	void startDynamicMusic(Musics::MUSIC a, Musics::MUSIC b);
	void stopDynamicMusic(Musics::MUSIC a, Musics::MUSIC b);

	// ----------
	void startMusic(Musics::MUSIC M);
	void stopMusic(Musics::MUSIC m);

	std::vector<std::string> music_names;
	int master_volume;
};