#pragma once
#include "../utils/Singleton.h"



namespace Musics {
	enum MUSIC {
		OFFICE_M,
		BATTLE_M,
		SHOP_M,
		CITY_M
	};
}


class SoundManager : public Singleton<SoundManager> {
public:


	SoundManager();

	~SoundManager() override;

	void init();



	// aumenta o disminuye el volumen MASTER
	void Volume(int i);

	// volumen especifico para canales
	void ChannelVolume(std::string channel, int v);

	// ----------
	void startMusic(Musics::MUSIC M);
	void stopMusic(Musics::MUSIC m);

	std::vector<std::string> music_names;
};
