#pragma once

#include <unordered_map>
#include <chrono>
#include <glm/mat4x4.hpp>
#include "Application.h"
#include "GameObject.h"

/// <summary>
/// Client is one of the main classes implemented in the NetworkingModule, containing all the logic for
/// initialising and managing a networked connection to the Server.exe application, and is the 
/// class from which you should derive your GameClient for whatever game you're making to make 
/// use of the module properly. The class maintains a list of local GameObjects (the first element
/// of which is assumed to be the player object), as well as a map of other-client GameObjects, 
/// all of which are updated and drawn in the corresponding Application override functions. On 
/// startup() the client will establish a RakNet managed connection to the game server using 
/// the member PORT and IP variables (which can be overriden in your derived GameClient), and
/// will then loop through all pending server packets every frame and address them appropriately.
/// The class has event-like functions that are called in response to receiving specific packts,
/// and also has pre-made functions for sending packets to the server (like requesting to start
/// the game or requesting to spawn an object for all other players). Client's are configured to
/// automatically send their GameObject data whenever a change in velocity is detected, and Client's
/// use dead reckoning to update other-client GameObjects in between client data packets.
/// class).
/// </summary>
class Client : public aie::Application {
public:

	Client() { }
	virtual ~Client() { }

	// Standard application functions, can be overriden in derived classes but require base class call-backs somewhere in code
	virtual bool startup();
	virtual void shutdown();
	virtual void update(float deltaTime);
	virtual void draw();

	// Getters
	GameObject* getClientGameObject() { return m_localGameObjects[0]; };
	std::vector<GameObject*> getLocalGameObjects() { return m_localGameObjects; }

protected:
	
	// The network information for the client to connect to
	RakNet::RakPeerInterface* m_pPeerInterface;
	const char* IP = "127.0.0.1"; // Reassign IP member variable with whatever server IP you wish to run on in your game
	const unsigned short PORT = 5456;

	// List of local client objects, and hash map of all other objects in the game
	std::vector<GameObject*> m_localGameObjects;
	std::unordered_map<int, GameObject*> m_otherClientGameObjects;
	glm::vec3 m_oldVelocity; // Used to changed for new client velocities

	// Camera variables
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	// Server ping variables
	std::chrono::steady_clock::time_point m_pingStart;
	std::chrono::steady_clock::time_point m_pingEnd;

	// Standard network handling
	void initialiseClientConnection();
	void handleNetworkMessages();

	// Receiving packet logic
	virtual void onStartGame() { } // Start game event called by the server, override in your game code
	void onSetClientIDPacket(RakNet::Packet* packet); // Called when this client connects to the server, sets ID and start position
	void onReceivedClientDataPacket(RakNet::Packet* packet); // Called when new/updated other-client data is received
	void onDespawnObject(RakNet::Packet* packet); // Despawn object event called by the server
	void onPingResponse();

	// Sending packet logic
	void sendGameObject(GameObject* gameObject); // Sends this game object data to other clients
	void sendStartGamePacket(); // Requests to start the game
	void sendSpawnObjectPacket(glm::vec3 spawnPos, glm::vec3 spawnVel); // Request to spawn server-side object
	void sendDespawnObjectPacket(int id); // Requests to despawn a specific object for all clients and server
	void sendPingQueryPacket(); // Used to query the ping latency of the server

	// Utility functions, override with your own game logic
	virtual void createGameObject();
	virtual void setStartPosition();
	virtual void endGame(bool hasWon);
};