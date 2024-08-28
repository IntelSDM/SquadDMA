#pragma once
#include "ActorEntity.h"
#include "EngineStructs.h"

// For these offsets just 7 dumper the game and open Engine_Classes
class Engine
{

private:
	uint64_t OwningActorOffset = 0x98; // NetConnection -> OwningActor
	uint64_t MaxPacketOffset = 0xa0; // NetConnection -> MaxPacket
	uint64_t OwningActor;
	uint64_t MaxPacket;
	uint64_t OwningGameInstance = 0x180; // World -> OwningGameInstance
	uint64_t PersistentLevel = 0x30; // World  -> PersistentLevel
	uint64_t GWorld = 0x72aa2e0;
	uint64_t GName = 0x7129580;
	uint64_t LocalPlayers = 0x38; // GameInstance -> LocalPlayers
	uint64_t PlayerController = 0x30; // Player -> PlayerController
	uint64_t AcknowledgedPawn = 0x2a8;
	uint64_t PlayerState = 0x248; // Pawn -> PlayerState
	uint64_t CameraManager = 0x2c0; // PlayerController -> PlayerCameraManager
	uint64_t CameraCachePrivate = 0x0; // PlayerCameraManager -> CameraCachePrivate
	uint64_t CameraCachePrivateOffset = 0x1af0; // PlayerCameraManager -> CameraCachePrivate
	uint64_t TeamID = 0x400;
	CameraCacheEntry CameraEntry; // ScriptStruct Engine.CameraCacheEntry
	MinimalViewInfo CameraViewInfo; // ScriptStruct Engine.MinimalViewInfo
	std::vector<std::shared_ptr<ActorEntity>> Actors;
	std::string ResolveGName(const uint32_t& id);
	std::map<uint32_t, std::string> GNamesMap;

	std::mutex ActorMutex;
public:
	Engine();
	void Cache();
	void UpdatePlayers();
	std::vector<std::shared_ptr<ActorEntity>> GetActors();
	CameraCacheEntry GetCameraCache();
	void RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle);
	uint32_t GetActorSize();

};