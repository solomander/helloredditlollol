#include "Cheat.h"
#include "Menu.h"

void GUI_Init( IDirect3DDevice9* pDevice );

EndSceneFn oEndScene;
long __stdcall Hooks::EndScene( IDirect3DDevice9* pDevice )
{
	if( !G::d3dinit )
		GUI_Init( pDevice );

	H::D3D9->ReHook();

	ImGui::GetIO().MouseDrawCursor = Vars.Menu.Opened;

	ImGui_ImplDX9_NewFrame();

	if( Vars.Menu.Opened )
	{
		int pX, pY;
		I::InputSystem->GetCursorPosition( &pX, &pY );
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos.x = ( float )( pX );
		io.MousePos.y = ( float )( pY );

		ImGui::Begin( charenc( "anime sucks lol" ), &Vars.Menu.Opened, ImVec2( 230, 141 ), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
		{
			ImGui::Checkbox( charenc( "Legitbot Settings" ), &Vars.Menu.Legitbot );
			ImGui::Checkbox( charenc( "Misc Settings" ), &Vars.Menu.Misc );
			ImGui::Separator();
			ImGui::Columns( 2, charenc( "##config-settings" ), false );
			if( ImGui::Button( charenc( "Save Config" ), ImVec2( 93.f, 20.f ) ) ) Config->Save();
			ImGui::NextColumn();
			if( ImGui::Button( charenc( "Load Config" ), ImVec2( 93.f, 20.f ) ) ) Config->Load();
			ImGui::Columns( 1 );
		}
		ImGui::End(); //End main window

		if( Vars.Menu.Legitbot )
		{
			ImGui::Begin( charenc( "Legitbot Settings" ), &Vars.Menu.Legitbot, ImVec2( 300, 500 ), 0.9f, ImGuiWindowFlags_NoCollapse );
			{
				ImGui::Separator();
				ImGui::Text( charenc( "Aimbot" ) );
				ImGui::Separator();
				ImGui::Checkbox( charenc( "Enable Aimbot" ), &Vars.Legitbot.Aimbot.Enabled );
				ImGui::Checkbox( charenc( "Always On" ), &Vars.Legitbot.Aimbot.AlwaysOn );
				ImGui::Combo( charenc( "Aimbot Key" ), &Vars.Legitbot.Aimbot.Key, keyNames, ARRAYSIZE( keyNames ) );
				ImGui::Checkbox( charenc( "Aim on Key" ), &Vars.Legitbot.Aimbot.OnKey );
				ImGui::Checkbox( charenc( "Friendly Fire" ), &Vars.Legitbot.Aimbot.FriendlyFire );
				ImGui::Separator();
				ImGui::Combo( charenc( "Hitbox" ), &Vars.Legitbot.Aimbot.Hitbox, aimBones, ARRAYSIZE( aimBones ) );
				ImGui::SliderFloat( charenc( "FOV" ), &Vars.Legitbot.Aimbot.FOV, 0.1f, 45.f, "%.2f" );
				ImGui::SliderFloat( charenc( "Aim Speed" ), &Vars.Legitbot.Aimbot.Speed, 0.1f, 50.f, "%.2f" );
				ImGui::SliderFloat( charenc( "RCS Amount" ), &Vars.Legitbot.Aimbot.RCSAmount, 1.f, 100.f, "%.0f" );
				ImGui::Checkbox( charenc( "Always on RCS" ), &Vars.Legitbot.Aimbot.RCS );
				ImGui::Separator();

				ImGui::Text( charenc( "Triggerbot" ) );
				ImGui::Separator();
				ImGui::Checkbox( charenc( "Enable Triggerbot" ), &Vars.Legitbot.Triggerbot.Enabled );
				ImGui::Checkbox( charenc( "Auto Fire" ), &Vars.Legitbot.Triggerbot.AutoFire );
				ImGui::Combo( charenc( "Triggerbot Key" ), &Vars.Legitbot.Triggerbot.Key, keyNames, ARRAYSIZE( keyNames ) );
				ImGui::Checkbox( charenc( "Hit Chance" ), &Vars.Legitbot.Triggerbot.HitChance );
				ImGui::SliderFloat( charenc( "Amount" ), &Vars.Legitbot.Triggerbot.HitChanceAmt, 1.f, 100.f, "%.0f" );
				ImGui::Separator();

				ImGui::Text( charenc( "Filter" ) );
				ImGui::Separator();
				ImGui::BeginChild( charenc( "Filter" ), ImVec2( ImGui::GetWindowContentRegionWidth() * 0.5f, 19 * 6 ) );
				{
					ImGui::Selectable( charenc( " Head" ), &Vars.Legitbot.Triggerbot.Filter.Head );
					ImGui::Selectable( charenc( " Chest" ), &Vars.Legitbot.Triggerbot.Filter.Chest );
					ImGui::Selectable( charenc( " Stomach" ), &Vars.Legitbot.Triggerbot.Filter.Stomach );
					ImGui::Selectable( charenc( " Arms" ), &Vars.Legitbot.Triggerbot.Filter.Arms );
					ImGui::Selectable( charenc( " Legs" ), &Vars.Legitbot.Triggerbot.Filter.Legs );
					ImGui::Selectable( charenc( " Friendlies" ), &Vars.Legitbot.Triggerbot.Filter.Friendly );
				}
				ImGui::EndChild();
			}
			ImGui::End(); //End Legitbot window
		}

		if( Vars.Menu.Misc )
		{
			ImGui::Begin( charenc( "Misc Settings" ), &Vars.Menu.Misc, ImVec2( 300, 500 ), 0.9f, ImGuiWindowFlags_NoCollapse );
			{
				ImGui::Separator();
				ImGui::Text( charenc( "Movement" ) );
				ImGui::Separator();
				ImGui::Checkbox( charenc( "Bunny Hop" ), &Vars.Misc.Bhop );
				ImGui::Checkbox( charenc( "Autostrafe" ), &Vars.Misc.AutoStrafe );
				ImGui::Separator();

				ImGui::Text( charenc( "Custom Name" ) );
				ImGui::Separator();
				ImGui::PushItemWidth( 180 );
				static char buf1[ 128 ] = ""; ImGui::InputText( charenc( "##Name" ), buf1, 128 );
				ImGui::SameLine();
				ImGui::PushItemWidth( 50 );
				if( ImGui::Button( charenc( "Change Name" ) ) ) E::Misc->ChangeName( buf1 );
				ImGui::Separator();

				ImGui::Text( charenc( "Chat Spam" ) );
				ImGui::Separator();
				ImGui::PushItemWidth( 180 );
				static char buf2[ 128 ] = ""; ImGui::InputText( charenc( "##File" ), buf2, 128 );
				ImGui::SameLine();
				ImGui::PushItemWidth( 50 );
				if( ImGui::Button( charenc( "Load File" ) ) ) E::Misc->ReadChatspam( buf2 );
				ImGui::PushItemWidth( 180 );
				ImGui::Combo( charenc( "Mode" ), &Vars.Misc.ChatSpamMode, chatspamMode, ARRAYSIZE( chatspamMode ) );
				ImGui::Checkbox( charenc( "ChatSpam" ), &Vars.Misc.ChatSpam );
				ImGui::Separator();
				ImGui::Text( charenc( "Random Shit" ) );
				ImGui::Separator();
				ImGui::Checkbox( charenc( "Ranks" ), &Vars.Misc.Ranks );
				ImGui::Checkbox( charenc( "Auto Accept" ), &Vars.Misc.AutoAccept );
				ImGui::Checkbox( charenc( "Watermark" ), &Vars.Misc.Watermark );
				ImGui::Checkbox( charenc( "AirStuck" ), &Vars.Misc.AirStuck );
				ImGui::Combo( charenc( "AirStuck Key" ), &Vars.Misc.AirStuckKey, keyNames, ARRAYSIZE( keyNames ) );

				ImGui::Separator();
				ImGui::Text( charenc( "Netvar Dump" ) );
				ImGui::Separator();
				ImGui::PushItemWidth( 180 );
				static char buf3[ 128 ] = ""; ImGui::InputText( charenc( "##NetVar" ), buf2, 128 );
				ImGui::SameLine();
				ImGui::PushItemWidth( 50 );
				if( ImGui::Button( charenc( "Save File" ) ) ) NetVarManager->DumpNetvars( buf3 );
			}
			ImGui::End(); //End Misc window
		}
	}

	ImGui::Render();

	return oEndScene( pDevice );
}

ResetFn oReset;
long __stdcall Hooks::Reset( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters )
{
	if( !G::d3dinit )
		return oReset( pDevice, pPresentationParameters );

	ImGui_ImplDX9_InvalidateDeviceObjects();

	auto hr = oReset( pDevice, pPresentationParameters );
	ImGui_ImplDX9_CreateDeviceObjects();


	return hr;
}

void GUI_Init( IDirect3DDevice9* pDevice ) 
{
	ImGui_ImplDX9_Init( G::Window, pDevice );

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ ImGuiCol_Text ] = ImVec4( 0.78f, 0.78f, 0.78f, 1.00f );
	style.Colors[ ImGuiCol_TextDisabled ] = ImVec4( 0.59f, 0.59f, 0.59f, 1.00f );
	style.Colors[ ImGuiCol_WindowBg ] = ImVec4( 0.13f, 0.13f, 0.13f, 1.00f );
	style.Colors[ ImGuiCol_ChildWindowBg ] = ImVec4( 0.11f, 0.11f, 0.11f, 1.00f );
	style.Colors[ ImGuiCol_Border ] = ImVec4( 0.20f, 0.20f, 0.20f, 1.00f );
	style.Colors[ ImGuiCol_FrameBg ] = ImVec4( 0.80f, 0.80f, 0.80f, 0.09f );
	style.Colors[ ImGuiCol_FrameBgHovered ] = ImVec4( 0.39f, 0.39f, 0.39f, 1.00f );
	style.Colors[ ImGuiCol_FrameBgActive ] = ImVec4( 0.04f, 0.04f, 0.04f, 0.88f );
	style.Colors[ ImGuiCol_TitleBg ] = ImVec4( 0.00f, 0.00f, 0.00f, 1.00f );
	style.Colors[ ImGuiCol_TitleBgCollapsed ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.20f );
	style.Colors[ ImGuiCol_TitleBgActive ] = ImVec4( 0.00f, 0.00f, 0.00f, 1.00f );
	style.Colors[ ImGuiCol_MenuBarBg ] = ImVec4( 0.35f, 0.35f, 0.35f, 1.00f );
	style.Colors[ ImGuiCol_ScrollbarBg ] = ImVec4( 0.13f, 0.13f, 0.13f, 1.00f );
	style.Colors[ ImGuiCol_ScrollbarGrab ] = ImVec4( 0.24f, 0.40f, 0.95f, 1.00f );
	style.Colors[ ImGuiCol_ScrollbarGrabHovered ] = ImVec4( 0.24f, 0.40f, 0.95f, 0.59f );
	style.Colors[ ImGuiCol_ScrollbarGrabActive ] = ImVec4( 0.00f, 0.00f, 0.00f, 1.00f );
	style.Colors[ ImGuiCol_SliderGrab ] = ImVec4( 1.00f, 1.00f, 1.00f, 0.59f );
	style.Colors[ ImGuiCol_SliderGrabActive ] = ImVec4( 0.24f, 0.40f, 0.95f, 1.00f );
	style.Colors[ ImGuiCol_Button ] = ImVec4( 0.24f, 0.40f, 0.95f, 1.00f );
	style.Colors[ ImGuiCol_ButtonHovered ] = ImVec4( 0.24f, 0.40f, 0.95f, 0.59f );
	style.Colors[ ImGuiCol_ButtonActive ] = ImVec4( 0.39f, 0.39f, 0.39f, 1.00f );
	style.Colors[ ImGuiCol_Header ] = ImVec4( 0.24f, 0.40f, 0.95f, 1.00f );
	style.Colors[ ImGuiCol_HeaderHovered ] = ImVec4( 0.24f, 0.40f, 0.95f, 0.59f );
	style.Colors[ ImGuiCol_HeaderActive ] = ImVec4( 0.39f, 0.39f, 0.39f, 1.00f );
	style.Colors[ ImGuiCol_ColumnHovered ] = ImVec4( 0.70f, 0.02f, 0.60f, 0.22f );
	style.Colors[ ImGuiCol_CloseButton ] = ImVec4( 0.24f, 0.40f, 0.95f, 1.00f );
	style.Colors[ ImGuiCol_CloseButtonHovered ] = ImVec4( 0.24f, 0.40f, 0.95f, 0.59f );

	style.WindowRounding = 0.f;
	style.FramePadding = ImVec2( 4, 1 );
	style.ScrollbarSize = 10.f;
	style.ScrollbarRounding = 0.f;
	style.GrabMinSize = 5.f;

	G::d3dinit = true;
}