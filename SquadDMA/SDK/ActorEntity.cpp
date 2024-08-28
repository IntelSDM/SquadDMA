#include "Pch.h"
#include "ActorEntity.h"
#include "Camera.h"
#include "Globals.h"
ActorEntity::ActorEntity(uint64_t address,VMMDLL_SCATTER_HANDLE handle)
{
	Class = address;
	if(!address)
		return;
	 TargetProcess.AddScatterReadRequest(handle,Class + PlayerState,reinterpret_cast<void*>(&PlayerState), sizeof(uint64_t));
	 TargetProcess.AddScatterReadRequest(handle,Class + AcknowledgedPawn, reinterpret_cast<void*>(&AcknowledgedPawn),sizeof(uint64_t));
	 TargetProcess.AddScatterReadRequest(handle, Class + RootComponent, reinterpret_cast<void*>(&RootComponent),sizeof(uint64_t));
	 TargetProcess.AddScatterReadRequest(handle, Class + EntityID, reinterpret_cast<void*>(&EntityID), sizeof(uint32_t));
	
}

void ActorEntity::SetUp1(VMMDLL_SCATTER_HANDLE handle)
{
	if (!Class)
		return;
	if (!RootComponent)
		return;
	TargetProcess.AddScatterReadRequest(handle, PlayerState + TeamID, reinterpret_cast<void*>(&TeamID), sizeof(int));
	TargetProcess.AddScatterReadRequest(handle, Class + HealthOffset, reinterpret_cast<void*>(&Health), sizeof(float));
	TargetProcess.AddScatterReadRequest(handle, RootComponent + RelativeLocation, reinterpret_cast<void*>(&UEPosition), sizeof(UEVector));
}

void ActorEntity::SetUp2()
{

	if (!Class)
		return;
	if (!RootComponent)
		return;
	
		// by this point we should only have our surviors and killers
		Name = L"Player";
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);

}



uint64_t ActorEntity::GetClass()
{
	return Class;
}

std::wstring ActorEntity::GetName()
{
	return Name;
}

Vector3 ActorEntity::GetPosition()
{
	Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
	return Position;
}

void ActorEntity::UpdatePosition(VMMDLL_SCATTER_HANDLE handle)
{
	if (!Class)
		return;
	if (!RootComponent)
		return;
	if (!PlayerState)
		return;
	TargetProcess.AddScatterReadRequest(handle, RootComponent + RelativeLocation, reinterpret_cast<void*>(&UEPosition), sizeof(UEVector));
}
void ActorEntity::UpdateHealth(VMMDLL_SCATTER_HANDLE handle)
{
	if (!Class)
		return;
	if (!RootComponent)
		return;
	if (!PlayerState)
		return;
	TargetProcess.AddScatterReadRequest(handle, Class + HealthOffset, reinterpret_cast<void*>(&Health), sizeof(float));
}

uint32_t ActorEntity::GetEntityID()
{
	return EntityID;
}

int ActorEntity::GetTeamID()
{
	return TeamID;
}

float ActorEntity::GetHealth()
{
	return Health;
}