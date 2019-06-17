#pragma once
//////action wait times
const static int grassPitWait = 40;//!wait time before the grass pit triggers
const static int pushWait = 40;//!time to run push animation until push happens
const static int sceneTransWait = 30;//!tiem to wait before screen transition is triggered
const static int pressurePlateWait = 40;//!tiem to wait before pressure plate is triggered
//////animation times
const static int walkFrameRate = 12;//!time to wait between each walk step
/////game values
const static int frameRate = 60;//!Frame Rate of the game
const static int headOffsetX = 8;//!how far up the head is to the body of the player
const static int headOffsetY = 0;//!how far left the head is to the body of the player
const static int bodyWidth = 16;//!width of a body sprite
const static int bodyHeight = 16;//!height of a body sprite
const static int interactHeight = 1;//!height of the interact collider for pushing etc.
const static int interactWidth = 1;//!width of the interact collider for pushing etc.
const static int largeBodyWidth = 32;//!width of a large body sprite
const static int largeBodyHeight = 32;//!height of a large body sprite
const static int mapSpriteWidth = 8;//!width of sprites
const static int mapSpriteHeight = 8;//!height of sprites
const static int spriteSheetRow = 10;//!number of sprites per row
////screensizes
const static int mapTileRow = 180;//!number of map tiles per row per scene
const static int mapTileColumn = 90;//!number of map tiles per column per scene
const static int spriteTileRow = 90;//!number of small sprite tiles per row per scene
const static int spriteTileColumn = 45;//!number of small sprite tiles per column per scene
const static int screenWidth = 1440;//!width of screen
const static int screenHeight = 720;//!height of screen
const static int viewWidth = 240;//!width of game view
const static int viewHeight = 120;//!height of game view
const static float basePlayerSpeed = 1;
//////collider types
enum ColliderType
{
	empty = 0,
	map,//map colliders
	player,//the player collider
	rigid,//a collider for something that cant be "pushed", grass rocks pots etc.
	trigg,//for triggers to be flagged such as pressure bads or loading zones
	slow,//anything that slows the player, mud etc.
	damage,//anythign that may damage the player
	bouncy,
	sword,//sword collider swung by the player
	pit,//hole that the player will fall down
	grass,//cuttable grass
	push,//a pushign collider
	changeScene
};
//////states
enum ObjectState
{
	idle,
	walk,
	run,
	pushing,
	weapon,
	item,
	fall,
	swim,
	pushed,
	slashed,
	burned,
	triggered,
	transitioning
};

enum DirectionState
{
	stationary,
	up,
	upLeft,
	upRight,
	down,
	downLeft,
	downRight,
	left,
	right
};
///////attributes
enum ObjectAtrib
{
	none,
	pushable,
	lightLiftable,
	heavyLiftable,
	slashable,
	burnable,
	pitTrap,
	sceneChange,
	completeLavaDungeon,
	completeForestDungeon,
	completeIceDungeon,
	completeGraveyardDungeon
};
///////animation
enum PlayerAnimationState
{
	idleHeadLeft,
	idleHeadRight,
	idleHeadUp,
	idleHeadDown,
	walkBodyLeft2,
	walkBodyLeft1,
	idleBodyLeft,
	idleBodyRight,
	walkBodyRight1,
	walkBodyRight2,
	walkBodyUp2,
	walkBodyUp1,
	idleBodyUp,
	idleBodyDown,
	walkBodyDown1,
	walkBodyDown2
};
////////map entrances
enum MapEntrance
{
	Middle,
	North,
	NorthWest,
	NorthEast,
	East,
	EastNorth,
	EastSouth,
	West,
	WestNorth,
	WestSouth,
	South,
	SouthWest,
	SouthEast
};
////////map names
enum MapName
{
	town,
	forest,
	volcano,
	graveyard,
	ice
};
enum DungeonProgression
{
	N,
	F,
	G,
	V,
	I,
	FG,FV,FI,
	GF,GV,GI,
	VF,VG,VI,
	IF,IG,IV,
	FGV,FGI,FVG,FVI,FIG,FIV,
	GFV,GFI,GVF,GVI,GIF,GIV,
	VFG,VFI,VGF,VGI,VIF,VIG,
	IFG,IFV,IGF,IGV,IVF,IVG
};