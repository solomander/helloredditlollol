#include "Cheat.h"

CreateMoveFn oCreateMove;
bool __stdcall Hooks::CreateMove( float flInputSampleTime, CUserCmd* cmd )
{
	G::LocalPlayer = U::GetLocalPlayer();
	G::UserCmd = cmd;

	if( cmd->command_number == 0 || !I::Engine->IsInGame() )
		return false;

	if( !G::LocalPlayer || !G::LocalPlayer->GetAlive() )
		return G::Return;

	DWORD* framePointer;
	__asm mov framePointer, ebp;
	*( bool* )( *framePointer - 0x1C ) = G::SendPacket;

	E::LegitBot->Run();

	if( Vars.Misc.Bhop )
		E::Misc->Bunnyhop();

	if( Vars.Misc.AutoStrafe )
		E::Misc->AutoStrafe();

	return false;
}