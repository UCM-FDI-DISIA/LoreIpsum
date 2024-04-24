#pragma once
#include "../ComponentUpdate.h"
#include <SDL_net.h>

class TextComponent;

// Este componente necesita dos TextComponent:
//		El primero para renderizar el estado del oponente (Ready/Not-Ready)
//		El segundo para renderizar tu propio estado (Ready/Not-Ready)
class NetPregame : public ComponentUpdate
{
public:
	NetPregame(TextComponent* oponentReadyText, TextComponent* readyButtonText);
	~NetPregame() override;

	void update() override;

	bool GetPlayerReady() { return playerReady; }
	bool GetRivalReady() { return rivalReady; }

	void SetPlayerReady(bool isReady);
	void SetRivalReady(bool isReady);

private:
	// We want to use non-blocking communication, the way to do this is via a socket set.
	SDLNet_SocketSet socketSet;

	// a socket for sending and receiving data
	TCPsocket conn;

	// Referencias a los TextComponent
	TextComponent* _oponentReadyText;
	TextComponent* _readyButtonText;

	// Tu estado y el del rival
	bool playerReady;
	bool rivalReady;

	// Métodos para avisar al oponente de un cambio en nuestro estado
	void SendMsgPlayerReady();
	void SendMsgPlayerNotReady();
};
