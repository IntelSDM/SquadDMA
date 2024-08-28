#pragma once
// ScriptStruct CoreUObject.Vector
struct UEVector {
	float X; 
	float Y;
	float Z;
};
// ScriptStruct CoreUObject.Rotator
struct UERotator {
	float Pitch;
	float Yaw;
	float Roll;
};
struct MinimalViewInfo
{
	struct UEVector Location; // 0x0(0xc)
	struct UERotator Rotation; // 0xC(0xc)
	float FOV; // 0x18(0x4)
};
struct CameraCacheEntry
{
	float Timestamp; // 0x00(0x04)
	char pad_4[0xc]; // 0x04(0x0c)
	MinimalViewInfo POV; // 0x10(0x5e0)
};