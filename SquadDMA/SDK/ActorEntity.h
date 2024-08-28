#pragma once
#include "EngineStructs.h"

class ActorEntity
{
private:
	uint64_t Class = 0;
	uint64_t PlayerState = 0x248; // Pawn -> PlayerState
	uint64_t AcknowledgedPawn = 0x2a8;
	uint64_t RootComponent = 0x138; // Actor -> RootComponent
	uint64_t RelativeLocation = 0x11c; // SceneComponent -> RelativeLocation
	uint32_t EntityID = 0x18;
	uint32_t TeamID = 0x400; // ASQPlayerState -> TeamID
	uint32_t HealthOffset = 0x1df8; // ASQSoldier -> Health
	float Health = 0;
	std::wstring Name = LIT(L"Enemy");
	UEVector UEPosition;
	Vector3 Position;
public:
	ActorEntity(uint64_t address, VMMDLL_SCATTER_HANDLE handle);
	void SetUp1(VMMDLL_SCATTER_HANDLE handle);
	void SetUp2();
	uint64_t GetClass();
	std::wstring GetName();
	Vector3 GetPosition();
	void UpdatePosition(VMMDLL_SCATTER_HANDLE handle);
	void UpdateHealth(VMMDLL_SCATTER_HANDLE handle);
	uint32_t GetEntityID();
	int GetTeamID();
	float GetHealth();
};