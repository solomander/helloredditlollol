#pragma once

struct Variables
{
	Variables()
	{

	}

	struct
	{
		struct
		{
			bool 	Enabled;
			int 	Key;
			bool	OnKey;
			int 	Filter; // will hold flags for team/enemy/etc.
			bool 	RCS;
			float 	RCSAmount;
			float	Speed;
			bool 	VisCheck;
			int 	Hitbox;
			float 	FOV;
			bool 	AlwaysOn;
			bool	FriendlyFire;
		} Aimbot;

		struct
		{
			bool	Enabled;
			bool	AutoFire;
			int		Key;
			bool 	HitChance;
			float	HitChanceAmt;

			struct
			{
				bool Head;
				bool Chest;
				bool Stomach;
				bool Arms;
				bool Legs;
				bool Friendly;
			} Filter;

		} Triggerbot;

	} Legitbot;


	struct
	{
		bool 	Bhop;
		bool 	AutoStrafe;
		bool	ChatSpam;
		int		ChatSpamMode;
		bool	Watermark;
		bool	Ranks;
		bool	AirStuck;
		int		AirStuckKey;
		bool	AutoAccept;
	} Misc;

	struct
	{
		bool	Opened = false;
		int 	Key;
		bool	Ragebot = false;
		bool	Legitbot = false;
		bool	Visual = false;
		bool	Misc = false;
	} Menu;
};

extern Variables Vars;