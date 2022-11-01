struct language_mapping fr_mapping =	
	{
		.main_map = {
			"\x1b"/*escape*/,
			"&","é",
			"\x22"/*double quote*/,
			"\x27"/*single quote*/,
			"(","-","è","_","ç","à",")","=",
			"\x7f"/*backspace*/,
			"\x09"/*tab*/,
			"a","z","e","r","t","y","u","i","o","p","^","$",
			"\x0d"/*enter*/,
			STATE_CHANGE_KEY,/*crtl*/
			"q","s","d","f","g","h","j","k","l","m","ù",
			(char *)0,/*² not implemented by our console*/
			STATE_CHANGE_KEY,/*shift left*/
			"*","w","x","c","v","b","n",",",";",":","!",
			STATE_CHANGE_KEY,/*shift right*/
			UNDEF,
			STATE_CHANGE_KEY,/*alt*/
			" ",
			STATE_CHANGE_KEY,/*caps lock*/
	
			UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,
	
			"<"
		},
	
		.shift_map = {
			"\x1b"/*escape*/,
			"1","2","3","4","5","6","7","8","9","0","°","+",
			"\x7f"/*backspace*/,
			"\x09"/*tab*/,
			"A","Z","E","R","T","Y","U","I","O","P",
			UNDEF,/*¨ not implemented by our console*/
			"£",
			"\x0d"/*enter*/,
			STATE_CHANGE_KEY,/*crtl*/
			"Q","S","D","F","G","H","J","K","L","M","%","~",
			STATE_CHANGE_KEY,/*shift left*/
			"µ","W","X","C","V","B","N","?",".","/","§",
			STATE_CHANGE_KEY,/*shift right*/
			UNDEF,
			STATE_CHANGE_KEY,/*alt*/
			" ",
			STATE_CHANGE_KEY,/*caps lock*/
	
			UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,
	
			">"
		},

		.specialKeys = {
			.shift_left = 0x2a,
			.shift_right = 0x36,
			.crtl = 0x1d,
			.alt_gr = 0xe038,
			.cmd = 0xe05b,
			.caps_lock = 0x3a
		}
	};
