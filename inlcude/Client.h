#pragma once

#include <unordered_map>
#include <glm/mat4x4.hpp>
#include <RakPeerInterface.h>
#include "Application.h"
#include "GameObject.h"

class Client : public aie::Application {
public:

	Client();
	virtual ~Client();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	GameObject* getClientGameObject() { return m_localGameObjects[0]; };
	std::vector<GameObject*> getLocalGameObjects() { return m_localGameObjects; }

protected:
	
	virtual void CreateGameObject();
	virtual void setStartPosition();
	virtual void endGame();

	void initialiseClientConnection();
	void handleNetworkMessages();
	
	// Receiving packet logic
	virtual void onSpawnObject(glm::vec3 spawnPos, glm::vec3 spawnVel) { }
	virtual void onStartGame() { } // start game event, override in your game code
	void onSetClientIDPacket(RakNet::Packet* packet);
	void onReceivedClientDataPacket(RakNet::Packet* packet);
	void onDespawnObject(RakNet::Packet* packet);
	// Sending packet logic
	void sendGameObject(GameObject* gameObject);
	void sendSpawnObjectPacket(glm::vec3 spawnPos, glm::vec3 spawnVel);
	void sendStartGamePacket();
	void sendDespawnObjectPacket(int id);

	RakNet::RakPeerInterface* m_pPeerInterface;
	const char* IP = "25.59.116.52";
	const unsigned short PORT = 5456;

	std::vector<GameObject*> m_localGameObjects;
	glm::vec3 m_oldVelocity;
	std::unordered_map<int, GameObject*> m_otherClientGameObjects;

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
	bool m_gameOver = false;
};