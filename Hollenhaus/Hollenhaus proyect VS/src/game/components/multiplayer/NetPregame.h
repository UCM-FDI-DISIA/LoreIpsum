#pragma once
#include "../ComponentUpdate.h"
#include <SDL_net.h>

class TextComponent;

// Este componente necesita un TextComponent en su misma entidad
class NetPregame : public ComponentUpdate
{
public:
	NetPregame(TextComponent* oponentReadyText, TextComponent* readyButtonText);
	~NetPregame();

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

	TextComponent* _oponentReadyText;
	TextComponent* _readyButtonText;

	bool playerReady;
	bool rivalReady;

	void SendMsgPlayerReady();
	void SendMsgPlayerNotReady();
};

