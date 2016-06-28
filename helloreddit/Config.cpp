#include "Cheat.h"

void CConfig::Setup()
{

	SetupValue( Vars.Legitbot.Aimbot.Enabled, false, strenc( "Legitbot" ), strenc( "Enabled" ) );
	SetupValue( Vars.Legitbot.Aimbot.AlwaysOn, false, strenc( "Legitbot" ), strenc( "AlwaysOn" ) );
	SetupValue( Vars.Legitbot.Aimbot.Key, 0, strenc( "Legitbot" ), strenc( "Key" ) );
	SetupValue( Vars.Legitbot.Aimbot.OnKey, false, strenc( "Legitbot" ), strenc( "OnKey" ) );
	SetupValue( Vars.Legitbot.Aimbot.FriendlyFire, false, strenc( "Legitbot" ), strenc( "FriendlyFire" ) );
	SetupValue( Vars.Legitbot.Aimbot.Hitbox, 6, strenc( "Legitbot" ), strenc( "Hitbox" ) );
	SetupValue( Vars.Legitbot.Aimbot.FOV, 10.f, strenc( "Legitbot" ), strenc( "FOV" ) );
	SetupValue( Vars.Legitbot.Aimbot.Speed, 5.f, strenc( "Legitbot" ), strenc( "Speed" ) );
	SetupValue( Vars.Legitbot.Aimbot.RCS, true, strenc( "Legitbot" ), strenc( "RCS" ) );
	SetupValue( Vars.Legitbot.Aimbot.RCSAmount, 100.f, strenc( "Legitbot" ), strenc( "RCSAmount" ) );

	SetupValue( Vars.Legitbot.Triggerbot.Enabled, false, strenc( "Triggerbot" ), strenc( "Enabled" ) );
	SetupValue( Vars.Legitbot.Triggerbot.AutoFire, false, strenc( "Triggerbot" ), strenc( "AutoFire" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Key, 0, strenc( "Triggerbot" ), strenc( "Key" ) );
	SetupValue( Vars.Legitbot.Triggerbot.HitChance, false, strenc( "Triggerbot" ), strenc( "HitChance" ) );
	SetupValue( Vars.Legitbot.Triggerbot.HitChanceAmt, 60.f, strenc( "Triggerbot" ), strenc( "HitChanceAmt" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Filter.Head, false, strenc( "Triggerbot" ), strenc( "FilterHead" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Filter.Chest, false, strenc( "Triggerbot" ), strenc( "FilterChest" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Filter.Stomach, false, strenc( "Triggerbot" ), strenc( "FilterStomach" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Filter.Arms, false, strenc( "Triggerbot" ), strenc( "FilterArms" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Filter.Legs, false, strenc( "Triggerbot" ), strenc( "FilterLegs" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Filter.Friendly, false, strenc( "Triggerbot" ), strenc( "FilterFriendly" ) );

	SetupValue( Vars.Misc.Bhop, true, strenc( "Misc" ), strenc( "Bhop" ) );
	SetupValue( Vars.Misc.AutoStrafe, false, strenc( "Misc" ), strenc( "AutoStrafe" ) );
	SetupValue( Vars.Misc.Watermark, true, strenc( "Misc" ), strenc( "Watermark" ) );
	SetupValue( Vars.Misc.Ranks, true, strenc( "Misc" ), strenc( "Ranks" ) );
	SetupValue( Vars.Misc.AutoAccept, true, strenc( "Misc" ), strenc( "AutoAccept" ) );
	SetupValue( Vars.Misc.AirStuck, false, strenc( "Misc" ), strenc( "AirStuck" ) );
	SetupValue( Vars.Misc.AirStuckKey, 0, strenc( "Misc" ), strenc( "AirStuckKey" ) );
}

void CConfig::SetupValue( int &value, int def, std::string category, std::string name )
{
	value = def;
	ints.push_back( new ConfigValue<int>( category, name, &value ) );
}

void CConfig::SetupValue( float &value, float def, std::string category, std::string name )
{
	value = def;
	floats.push_back( new ConfigValue<float>( category, name, &value ) );
}

void CConfig::SetupValue( bool &value, bool def, std::string category, std::string name )
{
	value = def;
	bools.push_back( new ConfigValue<bool>( category, name, &value ) );
}

void CConfig::Save()
{
	static TCHAR path[ MAX_PATH ];
	std::string folder, file;

	if( SUCCEEDED( SHGetFolderPath( NULL, CSIDL_APPDATA, NULL, 0, path ) ) )
	{
		folder = std::string( path ) + strenc( "\\lolreesolomon\\" );
		file = std::string( path ) + strenc( "\\lolreesolomon\\lolreesolomon.ini" );
	}

	CreateDirectory( folder.c_str(), NULL );

	for ( auto value : ints )
		WritePrivateProfileString( value->category.c_str(), value->name.c_str(), std::to_string( *value->value ).c_str(), file.c_str() );

	for ( auto value : floats )
		WritePrivateProfileString( value->category.c_str(), value->name.c_str(), std::to_string( *value->value ).c_str(), file.c_str() );

	for ( auto value : bools )
		WritePrivateProfileString( value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str() );
}

void CConfig::Load()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if ( SUCCEEDED( SHGetFolderPath( NULL, CSIDL_APPDATA, NULL, 0, path ) ) )
	{
		folder = std::string( path ) + strenc( "\\lolreesolomon\\" );
		file = std::string( path ) + strenc( "\\lolreesolomon\\lolreesolomon.ini" );
	}

	CreateDirectory( folder.c_str(), NULL );

	char value_l[32] = { '\0' };

	for ( auto value : ints )
	{
		GetPrivateProfileString( value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str() );
		*value->value = atoi( value_l );
	}

	for ( auto value : floats )
	{
		GetPrivateProfileString( value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str() );
		*value->value = atof( value_l );
	}

	for ( auto value : bools )
	{
		GetPrivateProfileString( value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str() );
		*value->value = !strcmp( value_l, "true" );
	}
}

CConfig* Config = new CConfig();
Variables Vars;