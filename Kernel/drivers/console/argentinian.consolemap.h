static struct language_mapping ar_mapping =	
	{
		.main_map = {
			"\x1b"/*escape*/,
			"1","2","3","4","5","6","7","8","9","0",
			UNDEF,UNDEF,
			"\x7f"/*backspace*/,
			"\x09"/*tab*/,
			"q","w","e","r","t","y","u","i","o","p",
			UNDEF,UNDEF,
			"\x0d"/*enter*/,
			STATE_CHANGE_KEY,/*crtl*/
			"a","s","d","f","g","h","j","k","l",
			UNDEF,UNDEF,UNDEF,
			STATE_CHANGE_KEY,/*shift left*/
			UNDEF,
			"z","x","c","v","b","n","m",",",".","-",
			STATE_CHANGE_KEY,/*shift right*/
			UNDEF,
			STATE_CHANGE_KEY,/*alt*/
			" ",
			STATE_CHANGE_KEY,/*caps lock*/
	
			UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF
		},
	
		.shift_map = {
			"\x1b"/*escape*/,
			"1","2","3","4","5","6","7","8","9","0",
			UNDEF,UNDEF,
			"\x7f"/*backspace*/,
			"\x09"/*tab*/,
			"Q","W","E","R","T","Y","U","I","O","P",
			UNDEF,UNDEF,
			"\x0d"/*enter*/,
			STATE_CHANGE_KEY,/*crtl*/
			"A","S","D","F","G","H","J","K","L",
			UNDEF,UNDEF,UNDEF,
			STATE_CHANGE_KEY,/*shift left*/
			UNDEF,
			"Z","X","C","V","B","N","M",";",":","_",
			STATE_CHANGE_KEY,/*shift right*/
			UNDEF,
			STATE_CHANGE_KEY,/*alt*/
			" ",
			STATE_CHANGE_KEY,/*caps lock*/
	
			UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF,UNDEF
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
