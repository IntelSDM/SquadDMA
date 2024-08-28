#include "Pch.h"
#include "Drawing.h"
#include "Globals.h"
#include "Camera.h"
#include "ActorEntity.h"
#include "Engine.h"
#include "PlayerEsp.h"
#include "ConfigUtilities.h"

std::shared_ptr<CheatFunction> UpdatePlayers = std::make_shared<CheatFunction>(10, [] {
	if (!EngineInstance)
		return;
	EngineInstance->UpdatePlayers();
	});

void DrawPlayerEsp()
{
	if (!EngineInstance)
		return;
	for (auto entity : EngineInstance->GetActors())
	{
		if (entity->GetPosition() == Vector3(0, 0, 0))
			continue;
		Vector2 screenpos = Camera::WorldToScreen(EngineInstance->GetCameraCache().POV, entity->GetPosition());
		if (screenpos == Vector2::Zero())
			continue;
		Vector3 campos = Vector3(EngineInstance->GetCameraCache().POV.Location.X, EngineInstance->GetCameraCache().POV.Location.Y, EngineInstance->GetCameraCache().POV.Location.Z);
		float distance = (Vector3::Distance(campos, entity->GetPosition()) / 39.62f) - 6;
		if (distance < 0)
			continue;
		if (entity->GetTeamID() == LocalPlayerTeamID.load())
			continue;
		if(entity->GetHealth() <= 0)
			continue;
		std::wstring wdistance = Configs.Player.Distance ? L"[" + std::to_wstring((int)distance) + L"m]" : L"";
		std::wstring whealth = Configs.Player.Health ? L"[" + std::to_wstring((int)entity->GetHealth()) + L"❤]" : L"";
		std::wstring name = Configs.Player.Name ? entity->GetName() : L"";
		if (distance > Configs.Player.MaxDistance)
			continue;
		DrawText(screenpos.x, screenpos.y, name + wdistance + whealth, LIT("Verdana"), Configs.Player.FontSize, Configs.Player.TextColour, CentreCentre);
	}
	
}