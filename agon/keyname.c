
static const char none[]="";

static const char *name[129] =
{
	none,none,none,none,"Left Shift","Left Ctrl","Left Alt","Right Shift","Right Ctrl",
	"Right Alt",none,none,none,none,none,none,none,"Q","3","4","5","F4","8","F7",
	"-","^","Left Arrow","KP 6","KP 7","F11","F12","F10","Sroll Lock",
	"Print Screen","W","E","T","7","I","9","0",none,"Down Arrow","KP 8",
	"KP 9","Break","`",none,"Backspace","1","2","D","R","6","U","O",
	"P","[","Up Arrow","KP +","KP -","KP Enter",,"Insert",
	"Home","Page Up","Caps Lock","A","X","F","Y","J","K","'",":","Enter",
	"KP /","KP Del","KP .","Num Lock","Page Down",none,none,
	"S","C","G","H","N","L",";","]","Delete",none,"KP *",none,"=",none,"_",
	"Tab","Z","Space","V","B","M",",",".","Slash","End","KP 0","KP 1",
	"KP 3",none,none,none,"Esc","F1","F2","F3","F5","F6","F8","F9",none,
	"Right Arrow","KP 4","KP 5","KP 2","Left GUI","Right GUI","App"
};

const char *_keyname (int key)
{
	key = -key;
	if (key < 0 || key > 127)
		return none;

	return name[key];
}
