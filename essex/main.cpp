#define _USE_MATH_DEFINES
#include <graphics.h>
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <time.h>
#include <dshow.h>

#pragma comment(lib, "MSIMG32.lib")
#pragma comment(lib, "strmiids.lib")
#pragma warning(disable:4996)

#define RGBA(r,g,b,a) ((COLORREF)(((a)&0xFF)<<24 | ((r)&0xFF)<<16 | ((g)&0xFF)<<8 | ((b)&0xFF)))

#define SCREEN_W 1280
#define SCREEN_H 960
#define MAP_W 5120
#define MAP_H 2880
#define NEWMAP_W 2560
#define NEWMAP_H 1440

#define PORTAL1_X 614
#define PORTAL1_Y 478
#define PORTAL2_X 1262
#define PORTAL2_Y 2828
#define BRONZE_RING_WORLD_X 5035
#define BRONZE_RING_WORLD_Y 2686
#define PORTAL_SIZE 120
#define PORTAL_RANGE 80
#define FOREST_PORTAL_X 419
#define FOREST_PORTAL_Y 159
#define FOREST_PORTAL_RANGE 80
#define MOUNTAIN_SPAWN_X 2380
#define MOUNTAIN_SPAWN_Y 374
#define MOUNTAIN_PORTAL_X 2259
#define MOUNTAIN_PORTAL_Y 374
#define MOUNTAIN_PORTAL_RANGE 80
#define ICE_SPAWN_X 1280
#define ICE_SPAWN_Y 720
#define ICE_PORTAL_RANGE 80
#define FOREST_BOSS_TRIGGER_X 1360
#define FOREST_BOSS_TRIGGER_Y 826
#define FOREST_BOSS_TRIGGER_RANGE 80
#define MOUNTAIN_BOSS_TRIGGER_X 474
#define MOUNTAIN_BOSS_TRIGGER_Y 464
#define MOUNTAIN_BOSS_TRIGGER_RANGE 80
#define SHOP_TRIGGER_X 2700
#define SHOP_TRIGGER_Y 2167
#define SHOP_TRIGGER_RANGE 120
#define FOOD_SPAWN_X 2468
#define FOOD_SPAWN_Y 646

#define FOREST_BOSS_X 1280
#define FOREST_BOSS_Y 720
#define FOREST_BOSS_MAX_HP 300
#define FOREST_BOSS_BULLET_MAX_DISTANCE 450.0f
#define FOREST_BOSS_RADIUS 35
#define FOREST_BOSS_MOVE_SPEED 0.75f
#define FOREST_BOSS_MOVE_INTERVAL 60

#define BULLET_RADIUS 28
#define BULLET_SPEED 5.0f
#define BULLET_MAX_DISTANCE 900.0f
#define SHIELD_BALL_RADIUS 28
#define SHIELD_BASE_DAMAGE 20
#define ROOT_WIDTH 800
#define ROOT_HEIGHT 480
#define ROOT_WARNING_TIME 2000
#define ROOT_DISPLAY_TIME 500
#define ROOT_ATTACK_DAMAGE 50

#define MONSTER_COUNT 12
#define MONSTER_SPEED 1.2f
#define PLAYER_MOVE_COLLIDE_RADIUS 0
#define MONSTER_RADIUS 14
#define MONSTER_MAX_HP 80
#define MONSTER_SCALE 0.1f
#define MONSTER_COLLIDE_DAMAGE 5
#define FOREST_MONSTER_COUNT 15
#define FOREST_MONSTER_SPEED 1.2f
#define FOREST_MONSTER_RADIUS 14
#define FOREST_MONSTER_MAX_HP 40
#define FOREST_MONSTER_COLLIDE_DAMAGE 5
#define MOUNTAIN_MONSTER_COUNT 15
#define MOUNTAIN_MONSTER_SPEED 1.2f
#define MOUNTAIN_MONSTER_RADIUS 14
#define MOUNTAIN_MONSTER_MAX_HP 45
#define MOUNTAIN_MONSTER_COLLIDE_DAMAGE 5
#define MONSTER_CONTACT_DAMAGE_INTERVAL 2.0f

#define ICE_SERVANT_MAX_HP 60
#define ICE_SERVANT_SPEED 1.2f
#define ICE_SERVANT_RADIUS 14
#define ICE_SERVANT_SCALE 0.1f
#define ICE_SERVANT_SHOOT_INTERVAL 120
#define ICE_SERVANT_BULLET_SPEED 7.0f
#define ICE_SERVANT_BULLET_DAMAGE 20
#define ICE_SERVANT_COLLIDE_DAMAGE 8
#define ICE_SERVANT_GOLD_REWARD 15
#define SLOW_DURATION 300

#define BASE_MAX_HP 200
#define BASE_MAX_MP 100
#define BASE_MELEE_DAMAGE 5
#define LEVEL_DAMAGE_REDUCE_PCT_PER_LEVEL 5
#define LEVEL_DAMAGE_REDUCE_MAX_PCT 95
#define BOSS_DAMAGE_PER_REINCARNATION 20
#define MELEE_COOLDOWN 0.1f
#define ATTACK_RADIUS 90
#define ATTACK_DURATION 0.1f
#define SWORD_WAVE_COOLDOWN 1.0f
#define MAX_SWORD_WAVES 3
#define MIN_CHARGE_TIME 0.5f
#define MAX_CHARGE_TIME 2.0f
#define BASE_WAVE_DAMAGE 10
#define BASE_WAVE_MAX_DAMAGE 20
#define WAVE_COST_MP 50
#define MP_REGEN_RATE 5.0f
#define MAIN_SPAWN_X 2370.f
#define MAIN_SPAWN_Y 1970.f
#define BOSS_FAIL_HP 50.f
#define HP_PERIODIC_REFILL_INTERVAL_FRAMES (1 * 60 * 60)
#define WAVE_SCALE 0.09f
#define WAVE_COLLIDE_RADIUS 80
#define BOSS_BULLET_DAMAGE 30
#define AIM_CIRCLE_RADIUS 160.0f

#define STONE_BOSS_X 474
#define STONE_BOSS_Y 464
#define STONE_BOSS_MAX_HP 1000
#define STONE_BOSS_RADIUS 40
#define STONE_BOSS_NORMAL_WEAPON_DEF 100
#define STONE_BOSS_ATTACK_DAMAGE 10
#define STONE_BOSS_PICKAXE_BONUS 100
#define ICE_BOSS_X 1280
#define ICE_BOSS_Y 600
#define ICE_BOSS_MAX_HP 1600
#define ICE_BOSS_RADIUS 45
#define ICE_BOSS_MOVE_SPEED 0.5f
#define ICE_BOSS_WAVE_SPEED 12.0f
#define ICE_BOSS_WAVE_DAMAGE 40
#define ICE_BOSS_WAVE_RANGE 700
#define ICE_BOSS_WAVE_INTERVAL 150
#define ICE_BOSS_WAVE_INTERVAL_PHASE2 120
#define ICE_BOSS_SERVANT_SUMMON_INTERVAL 600
#define ICE_BOSS_SERVANT_MAX_COUNT 5
#define ICE_BOSS_SPIKE_INTERVAL 300
#define ICE_BOSS_SPIKE_WARNING_TIME 48
#define ICE_BOSS_SPIKE_DAMAGE 50
#define ICE_BOSS_FREEZE_AURA_RADIUS 150
#define ICE_MAP_DARKNESS_DOT_PER_SEC 10
#define ICE_WAVE_GROUNDED_FRAMES (10 * 60)

#define PLAYER_WALK_SPEED 7.5f
#define PLAYER_CHARGE_WALK_SPEED 3.f
#define PLAYER_FLY_SPEED 15.f

#define MAX_EQUIP_INST 24
#define MAX_WORLD_ITEMS 60
#define MAX_BOSS_BULLETS 80
#define MAX_BOSS_WAVES 40
#define MAX_PLAYER_WAVES 8
#define MAX_ICE_SPIKES 24
#define ANCIENT_BOOK_MAX_LINES 64
#define ANCIENT_BOOK_LINE_CHARS 220

#define EQUIP_SLOT_COUNT 7
#define MAT_IRON 0
#define MAT_WOOD 1
#define MAT_HERB 2
#define CONS_FOOD 0
#define CONS_POTION 1
#define CRAFT_RECIPE_COUNT 3
#define SHOP_POTION_GOLD_COST 50
#define FLIGHT_POTION_SECONDS 30
#define FLIGHT_POTION_FRAMES (FLIGHT_POTION_SECONDS * 60)
#define INVENTORY_PAGE_COUNT 4
#define CONSUM_SLOT_COUNT 2
#define MATERIAL_SLOT_COUNT 3

#define MAX_SAVE_SLOTS 20
#define SAVE_SLOTS_PER_COLUMN 10
#define SAVE_SLOT_LINE_H 38
#define SAVE_SLOT_LIST_TOP 110
#define AUTO_SAVE_INTERVAL_FRAMES 1800
#define MAP_RESOURCE_REFRESH_FRAMES (5 * 60 * 60)
#define BOSS_FIGHT_TIME_LIMIT_FRAMES (3 * 60 * 60)
#define BOSS_FIGHT_ESC_WITHDRAW_FRAMES (90 * 60)
#define FOREST_BOSS_POISON_DOT_PER_SEC 20
#define BRONZE_RING_PICKUP_RANGE (PORTAL_SIZE + 60)
#define SAVE_FORMAT_VERSION 3
#define MAX_RANKING 10
#define MANAGE_PASSWORD "essex2521102"

#define MINIMAP_FULL_W 512
#define MINIMAP_FULL_H 384

#define DIALOG_Y (SCREEN_H * 2 / 3)
#define DIALOG_H (SCREEN_H / 3)
#define DIALOG_FONT_SIZE 32
#define DIALOG_SPEAKER_FONT_SIZE 36
#define DIALOG_SPEAKER_COLOR RGB(0, 0, 0)
#define DIALOG_TEXT_COLOR RGB(30, 30, 30)
#define DIALOG_TIP_FONT_SIZE 20
#define DIALOG_TEXT_MARGIN_X 40
#define DIALOG_TEXT_MARGIN_Y 18
#define DIALOG_LINE_HEIGHT 46
#define DIALOG_CHAR_W_CJK 32
#define DIALOG_CHAR_W_ASC 16

#define ANCIENT_BOOK_MARGIN_X 48
#define ANCIENT_BOOK_MARGIN_Y 88
#define ANCIENT_BOOK_FONT_SIZE 24
#define ANCIENT_BOOK_INTRO_FONT_SIZE 22
#define ANCIENT_BOOK_LINE_HEIGHT 36
#define ANCIENT_BOOK_TITLE_FONT_SIZE 40
#define ANCIENT_BOOK_TEXT_COLOR RGB(220, 215, 200)
#define ANCIENT_BOOK_INTRO_COLOR RGB(160, 140, 90)

struct DialogLine {
    const wchar_t* speaker;
    const wchar_t* content;
};

enum MapType { MAP_MAIN, MAP_FOREST, MAP_MOUNTAIN, MAP_ICE };
enum ItemType { ITEM_WOOD, ITEM_HERB, ITEM_IRON, ITEM_FOOD, ITEM_BRONZE_RING };

struct User { char username[20]; char password[20]; };
struct RankingEntry {
    char username[20];
    int level;
    int reincarnationCycle;
    char gameTime[30];
    bool isValid;
};
struct SaveSlotData {
    bool isValid;
    char username[20];
    char saveTime[30];
    int playerLevel;
    int reincarnationCycle;
    int playerGold;
    float playerHp, playerMaxHp;
    float playerMp, playerMaxMp;
    float playerX, playerY;
    int currentMap;
    bool bossDefeated[3];
    int materialCounts[MATERIAL_SLOT_COUNT];
    int consumCounts[CONSUM_SLOT_COUNT];
    int gameState;
    int bossType;
    int equipCounts[EQUIP_SLOT_COUNT];
    int equippedWeapon;
    int equippedArmor;
    int equippedRing;
    int equippedWeaponInst;
    int equippedArmorInst;
    short equipInstN[EQUIP_SLOT_COUNT];
    short equipInstDur[EQUIP_SLOT_COUNT][24];
    bool bronzeRingWaveUnlocked;
    bool bronzeRingWorldActive;
    float bronzeRingX;
    float bronzeRingY;
    int saveFormatVersion;
};
struct WorldItem { float x, y; int type; bool active; };
struct Character {
    float x, y; int direction; int frame; float animTimer; float attackTimer;
    float meleeCooldown; bool isMoving; int radius; float displayScale;
    float hp, maxHp; float mp, maxMp; int slowTimer;
};
struct Monster {
    float x, y; float hp, maxHp; float speed; int dirX, dirY;
    float moveTimer; int radius; bool active;
};
struct SwordWave {
    float x, y, vx, vy, traveled, range; int damage; bool active; int imageDir;
};
struct BossBullet { float x, y, vx, vy, traveled; bool active; int damage; };
struct ForestBoss {
    float x, y, hp, maxHp; int phase; bool isAlive;
    float moveDirX, moveDirY; int moveTimer, shootTimer, shootInterval;
    int burstCount, burstRemain, damage;
    BossBullet bullets[MAX_BOSS_BULLETS];
    int bulletCount;
    bool shieldActive; float shieldAngle, shieldRadius;
    float shieldRadiusMin, shieldRadiusMax, shieldRadiusSpeed, shieldRotateSpeed;
    int shieldDamage;
    bool rootActive, rootWarning; int rootTimer, rootX, rootY, rootCooldown;
};
struct StoneBoss {
    float x, y, hp, maxHp; int phase; bool isAlive;
    int shootTimer, shootInterval, burstCount, burstRemain, damage;
    BossBullet bullets[MAX_BOSS_BULLETS];
    int bulletCount;
};
struct IceSpike { float x, y; int warningTimer; bool active, warning; };
struct IceServant {
    float x, y, hp, maxHp, speed; int dirX, dirY, moveTimer, shootTimer, radius;
    bool active;
    BossBullet bullets[MAX_BOSS_BULLETS];
    int bulletCount;
};
struct IceBoss {
    float x, y, hp, maxHp; int phase, direction; bool isAlive;
    float moveDirX, moveDirY; int moveTimer, waveShootTimer, waveShootInterval;
    int waveBurstRemain, summonTimer, summonInterval;
    IceSpike iceSpikes[MAX_ICE_SPIKES];
    int iceSpikeCount;
    SwordWave waves[MAX_BOSS_WAVES];
    int waveCount;
    bool freezeAuraActive;
};
struct MirrorBoss {
    float x, y, hp, maxHp, mp, maxMp;
    int direction, frame, radius;
    float animTimer, attackTimer, meleeCooldown, waveCooldown, displayScale;
    bool isMoving, isAlive;
    SwordWave waves[MAX_BOSS_WAVES];
    int waveCount;
};

#define MIRROR_WAVE_BURST_COUNT 3
#define MIRROR_WAVE_COOLDOWN_FRAMES 120
#define MIRROR_BOSS_MOVE_SPEED 5.f
#define MIRROR_REVEAL_FRAMES 150

static const bool GOD_MODE = true;

MapType currentMap = MAP_MAIN;
RankingEntry rankingList[MAX_RANKING];
char currentUsername[20] = "";
int playerLevel = 1;
int reincarnationCycle = 0;
bool gameRunning = true;
char currentMusic[50] = "";
bool musicEnabled = true;
static bool g_finalMusicActive = false;

#define MUSIC_LOGIN   "login"
#define MUSIC_MANAGE  "manage"
#define MUSIC_NORMAL  "normal"
#define MUSIC_FIGHT   "fight"
#define MUSIC_BOSS    "boss"
#define MUSIC_FINAL   "final"
#define MUSIC_RANKING "ranking"

IMAGE bigmap, smallmap, maskImg, exchangeImg, forestMapImg, forestMaskImg, mountainMapImg, mountainMaskImg;
IMAGE iceMapImg, iceMaskImg, monsterImg, iceMonsterImg;
IMAGE img_walk[4][3], img_sword_atk[4], swordWaveImgs[4];
IMAGE forestBossImg, stoneBossImg, bossBulletImg, bossShieldImg, bossRootImg, bossWarningImg;
IMAGE iceBossImgs[4], iceWaveImgs[4], iceSpikeImg;
IMAGE bagBg, coinImg, woodImg, herbImg, ironOreImg, foodImg;
IMAGE equipImg[EQUIP_SLOT_COUNT], consumImg[CONSUM_SLOT_COUNT], materialImg[MATERIAL_SLOT_COUNT];
IMAGE imgLoginBg;

DWORD* maskPixels = NULL; int maskWidth = 0, maskHeight = 0;
DWORD* forestMaskPixels = NULL; int forestMaskWidth = 0, forestMaskHeight = 0;
DWORD* mountainMaskPixels = NULL; int mountainMaskWidth = 0, mountainMaskHeight = 0;
DWORD* iceMaskPixels = NULL; int iceMaskWidth = 0, iceMaskHeight = 0;

int cameraX = 0, cameraY = 0;
bool showFullMinimap = false, showCollisionOverlay = false, flyMode = false;
int gameState = 0, bossType = 0;
bool bossDefeated[3] = { false, false, false };
int invincibleTimer = 0, playerGold = 0;
float monsterContactDamageCd = 0.f;
bool foodItemActive = true;
int foodRespawnTimer = 0;
bool bronzeRingWorldActive = true;
bool g_bronzeRingWaveUnlocked = false;
static float bronzeRingWorldX = (float)BRONZE_RING_WORLD_X;
static float bronzeRingWorldY = (float)BRONZE_RING_WORLD_Y;
static int g_bronzeRingPickupToast = 0;
static int g_mainMapRefreshTimer = MAP_RESOURCE_REFRESH_FRAMES;
static int g_forestMapRefreshTimer = MAP_RESOURCE_REFRESH_FRAMES;
static int g_mountainMapRefreshTimer = MAP_RESOURCE_REFRESH_FRAMES;
static float g_flyOrbitAngle = 0.f;
static int g_autoSaveCounter = 0;
bool inShop = false;
int shopRefreshTimer = 0;
int woodExchangeLimit = 100, ironExchangeLimit = 100, herbExchangeLimit = 100;
bool showInventory = false;
int currentPage = 0;
int selectedSlotEquip = 0, selectedSlotConsum = 0, selectedSlotMaterial = 0;
struct SlotRect { int x, y, w, h; } slotRects[3][8];

enum EquipId {
    EQ_PICKAXE = 0,
    EQ_IRON_SWORD = 1,
    EQ_ENDLESS_SWORD = 2,
    EQ_STEEL_ARMOR = 3,
    EQ_DIAMOND_ARMOR = 4,
    EQ_BRONZE_RING = 5,
    EQ_SOUL_RING = 6
};
const TCHAR* equipNames[EQUIP_SLOT_COUNT] = {
    L"\u788E\u5CA9\u5DE8\u9550", L"\u94C1\u5251", L"\u65E0\u5C3D\u4E4B\u5251",
    L"\u94A2\u7532", L"\u94BB\u77F3\u5723\u9484", L"\u9752\u94DC\u6212\u6307", L"\u9547\u7075\u6212"
};
const TCHAR* equipDescs[EQUIP_SLOT_COUNT] = {
    L"\u5408\u6210\u53F0\u5236\u9020\uFF1B\u7834\u575A\u5CA9\u3001\u5BF9\u5CA9\u7532Boss\u7279\u653B+100\uFF1B\u653B+20\uFF1B\u8010\u4E4540\uFF1B\u914D\u9752\u94DC\u6212\u53EF\u8FDC\u7A0B\u5251\u6C14",
    L"\u5408\u6210\u53F0\u5236\u9020\uFF1B\u653B\u51FB+20",
    L"\u6BD2\u57DF\u9738\u4E3B\u6389\u843D\uFF1B\u653B\u51FB+50\uFF1B\u5251\u6C14\u6539\u4E3A\u4E09\u9053",
    L"\u5408\u6210\u53F0\u5236\u9020\uFF1B\u9632\u5FA1+10",
    L"\u5CA9\u7532\u5B88\u62A4\u8005\u6389\u843D\uFF1B\u9632\u5FA1+45\uFF1B\u514D\u75AB\u6BD2\u57DF\u6BD2\u4F24",
    L"\u4E3B\u5730\u56FE\u4E1C\u5357\u8896\u62FE\u53D6\uFF1B\u653B\u51FB+8\uFF1B\u89E3\u9501\u788E\u5CA9\u9550\u8FDC\u7A0B\u5251\u6C14",
    L"\u68EE\u6797\u9738\u4E3B\u6389\u843D\uFF1B\u653B\u51FB+18\uFF1B\u51CF\u8F7B18%\u4F24\u5BB3\uFF1B\u88C5\u5907\u540E\u6CD5\u529B\u65E0\u9650\uFF1B\u88C5\u5907\u540E\u514D\u53D7\u51B0\u5DDD\u9B54\u6C14"
};
int equipAtk[EQUIP_SLOT_COUNT] = { 20, 20, 50, 0, 0, 8, 18 };
int equipDef[EQUIP_SLOT_COUNT] = { 0, 0, 0, 10, 45, 0, 0 };
int equipCounts[EQUIP_SLOT_COUNT] = { 0, 0, 0, 0, 0, 0, 0 };
int equipDurStack[EQUIP_SLOT_COUNT][MAX_EQUIP_INST];
int equipDurCount[EQUIP_SLOT_COUNT];
int equippedWeapon = EQ_IRON_SWORD;
int equippedArmor = -1;
int equippedRing = -1;
int equippedWeaponInst = 0;
int equippedArmorInst = -1;
const TCHAR* equipImages[EQUIP_SLOT_COUNT] = {
    L"pic/giant_pickaxe.png", L"pic/sword.png", L"pic/epic_sword.png",
    L"pic/armor.png", L"pic/diamond_armor.png", L"pic/ring.png", L"pic/soul_ring.png"
};
bool equipImgLoaded[EQUIP_SLOT_COUNT] = { false };
bool showStatsPanel = false;
bool showAncientBook = false;
static int g_ancientBookScroll = 0;
int shopTab = 0;
bool g_bossInfoOpen = false;
int g_bossInfoType = -1;
const TCHAR* consumNames[CONSUM_SLOT_COUNT] = { L"\u98DF\u7269", L"\u9B54\u6CD5\u836F\u6C34" };
const TCHAR* consumDescs[CONSUM_SLOT_COUNT] = { L"\u6062\u590D15\u70B9\u751F\u547D\u503C", L"\u83B7\u5F9730\u79D2\u98DE\u884C\u65F6\u95F4\uFF08\u53EF\u53E0\u52A0\uFF0C\u4EC5\u98DE\u884C\u65F6\u6D88\u8017\uFF09" };
int consumValues[CONSUM_SLOT_COUNT] = { 15, FLIGHT_POTION_SECONDS };
int consumCounts[CONSUM_SLOT_COUNT] = { 0, 0 };
const TCHAR* consumImages[CONSUM_SLOT_COUNT] = { L"pic/food.png", L"pic/magic_potion.png" };
bool consumImgLoaded[CONSUM_SLOT_COUNT] = { false };
const TCHAR* materialNames[MATERIAL_SLOT_COUNT] = { L"\u94C1\u77FF", L"\u6728\u6750", L"\u836F\u8349" };
const TCHAR* materialDescs[MATERIAL_SLOT_COUNT] = { L"\u7528\u4E8E\u94F8\u9020\u88C5\u5907\u7684\u94C1\u77FF\u77F3", L"\u4FEE\u590D\u5EFA\u7B51\u7684\u57FA\u7840\u6750\u6599", L"\u914D\u5236\u836F\u5242\u7684\u539F\u6750\u6599" };
int materialValues[MATERIAL_SLOT_COUNT] = { 5, 3, 8 };
int materialCounts[MATERIAL_SLOT_COUNT] = { 0, 0, 0 };
const TCHAR* materialImages[MATERIAL_SLOT_COUNT] = { L"pic/iron_ore.png", L"pic/wood.png", L"pic/herb.png" };
bool materialImgLoaded[MATERIAL_SLOT_COUNT] = { false };

WorldItem worldItems[MAX_WORLD_ITEMS];
int worldItemCount;
Character player;
Monster monsters[MONSTER_COUNT];
Monster forestMonsters[FOREST_MONSTER_COUNT];
Monster mountainMonsters[MOUNTAIN_MONSTER_COUNT];
SwordWave swordWaves[MAX_PLAYER_WAVES];
int swordWaveCount;
IceServant iceServants[ICE_BOSS_SERVANT_MAX_COUNT];
int iceServantCount;
ForestBoss forestBoss;
StoneBoss stoneBoss;
IceBoss iceBoss;
MirrorBoss mirrorBoss;
bool isCharging = false;
float chargeTimer = 0.0f, lastWaveTime = 0.0f;
float aimWorldX = 1.0f, aimWorldY = 0.0f;
bool hasAim = true;
int g_mouseX = 0, g_mouseY = 0;
bool isPaused = false;

void drawSprite(IMAGE* img, int x, int y, float scaleX, float scaleY);
void putimageAlpha(int x, int y, int dw, int dh, IMAGE* src, int srcX, int srcY);
int getDirectionIndexForAngle(float dirX, float dirY);
void updateRootAttack();
void drawRootAttack();
bool login_menu();
bool RunOpeningDialog();
static bool RunIceBossPreFightDialog();
static bool RunIceBossMirrorRevealDialog();
static bool RunReincarnationEndingDialog();
static bool TryHandleMirrorBossDefeat();
static bool g_pendingMirrorRevealDialog = false;
static bool g_pendingReincarnationEndingDialog = false;
static bool g_mirrorBossDefeatHandled = false;
static void RunAncientBookIntro();
void applyBossPhaseOnMelee();
void initForestBoss();
void initStoneBoss();
void initIceBoss();
void initMirrorBoss(float spawnX, float spawnY);
void updateMirrorBoss();
void updateMirrorBossWaves();
void drawMirrorBoss(int sx, int sy);
void BeginMirrorBossFight();
void startup();
void show();
void updateWithoutInput();
void updateWithInput();
void drawBossTriggerHints();
void drawShopTriggerHint();
static bool IsReturnKeyEdge();
static void ResetReturnKeyEdge();
static bool HandleWorldReturnKey();
static bool InMountainBossTriggerZone();
static bool InForestBossTriggerZone();
void generateWorldItems();
static void InitBronzeRingWorldPosition();
static void PickupBronzeRingWorldItem();
static float BronzeRingDistToPlayer();
static void SyncBronzeRingWorldState();
static void ResetBronzeRingQuestForNewGame();
static bool ShouldShowBronzeRingWorld();
static bool TryPickupBronzeRingOnInteract();
static bool BronzeRingInPickupRange();
void AutoSaveGame();
static void SaveBossFightSnapshot();
static void FailBossFight();
static void FailBossFightTimeout();
static bool CanWithdrawFromBossFight();
static void WithdrawFromBossFight();
static void ClearForestBossPoisonState();
static void drawBossFightTimer();
static const TCHAR* GetBossDisplayName(int bt);
void drawFlyModeOrbit(int psx, int psy);

static bool g_meleeKeyDown = false;
static bool g_lastM = false, g_lastZ = false;
static bool g_flyKeyDown = false;
static bool g_eKeyDown = false;
static int g_rebirthOverlayTimer = 0;
static int g_mirrorRevealTimer = 0;
static bool g_skipOpeningDialog = false;

static IGraphBuilder* g_pBgmGraph = NULL;
static IMediaControl* g_pBgmControl = NULL;
static IMediaEventEx* g_pBgmEvent = NULL;
static IMediaSeeking* g_pBgmSeek = NULL;
static IBasicAudio* g_pBgmAudio = NULL;
static bool g_bgmComInited = false;

static void BgmEnsureCom() {
    if (!g_bgmComInited) {
        CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
        g_bgmComInited = true;
    }
}

static void BgmReleaseGraph() {
    if (g_pBgmControl) { g_pBgmControl->Stop(); g_pBgmControl->Release(); g_pBgmControl = NULL; }
    if (g_pBgmAudio) { g_pBgmAudio->Release(); g_pBgmAudio = NULL; }
    if (g_pBgmSeek) { g_pBgmSeek->Release(); g_pBgmSeek = NULL; }
    if (g_pBgmEvent) { g_pBgmEvent->Release(); g_pBgmEvent = NULL; }
    if (g_pBgmGraph) { g_pBgmGraph->Release(); g_pBgmGraph = NULL; }
}

static bool MusicResolveMp3Path(const char* trackName, char* outPath, int outSize) {
    const char* patterns[] = { "music/%s.mp3", "music\\%s.mp3" };
    char rel[128];
    for (int i = 0; i < 2; i++) {
        sprintf(rel, patterns[i], trackName);
        DWORD n = GetFullPathNameA(rel, outSize, outPath, NULL);
        if (n > 0 && n < (DWORD)outSize) {
            FILE* f = fopen(outPath, "rb");
            if (f) { fclose(f); return true; }
        }
    }
    return false;
}

static bool BgmPlayMp3File(const char* fullPathA) {
    WCHAR wpath[MAX_PATH];
    if (MultiByteToWideChar(CP_ACP, 0, fullPathA, -1, wpath, MAX_PATH) <= 0) return false;
    BgmEnsureCom();
    BgmReleaseGraph();
    HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder, (void**)&g_pBgmGraph);
    if (FAILED(hr) || !g_pBgmGraph) return false;
    hr = g_pBgmGraph->RenderFile(wpath, NULL);
    if (FAILED(hr)) { BgmReleaseGraph(); return false; }
    g_pBgmGraph->QueryInterface(IID_IMediaControl, (void**)&g_pBgmControl);
    g_pBgmGraph->QueryInterface(IID_IMediaEventEx, (void**)&g_pBgmEvent);
    g_pBgmGraph->QueryInterface(IID_IMediaSeeking, (void**)&g_pBgmSeek);
    g_pBgmGraph->QueryInterface(IID_IBasicAudio, (void**)&g_pBgmAudio);
    if (g_pBgmEvent) {
        HWND hwnd = GetHWnd();
        if (hwnd) g_pBgmEvent->SetNotifyWindow((OAHWND)hwnd, WM_APP + 200, 0);
    }
    if (g_pBgmAudio) g_pBgmAudio->put_Volume(-150);
    if (g_pBgmControl) g_pBgmControl->Run();
    return g_pBgmControl != NULL;
}

static void MusicPollEvents() {
    if (!g_pBgmEvent || !g_pBgmSeek || !g_pBgmControl) return;
    long evCode = 0;
    LONG_PTR p1 = 0, p2 = 0;
    while (SUCCEEDED(g_pBgmEvent->GetEvent(&evCode, &p1, &p2, 0))) {
        g_pBgmEvent->FreeEventParams(evCode, p1, p2);
        if (evCode == EC_COMPLETE) {
            LONGLONG pos = 0;
            g_pBgmSeek->SetPositions(&pos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
            g_pBgmControl->Run();
        }
    }
}

static void StopMusic() {
    BgmReleaseGraph();
    currentMusic[0] = '\0';
}

static void PlayMusicTrack(const char* trackName) {
    if (!trackName || !trackName[0]) return;
    if (!musicEnabled) {
        if (currentMusic[0]) StopMusic();
        return;
    }
    if (strcmp(currentMusic, trackName) == 0) return;
    char fullPath[MAX_PATH];
    if (!MusicResolveMp3Path(trackName, fullPath, MAX_PATH)) return;
    if (BgmPlayMp3File(fullPath)) {
        strncpy(currentMusic, trackName, sizeof(currentMusic) - 1);
        currentMusic[sizeof(currentMusic) - 1] = '\0';
    }
}

static bool IsBossInRagePhase() {
    if (gameState != 1) return false;
    if (bossType == 0 && forestBoss.isAlive && forestBoss.phase >= 2) return true;
    if (bossType == 1 && stoneBoss.isAlive && stoneBoss.phase >= 2) return true;
    if (bossType == 2 && iceBoss.isAlive && iceBoss.phase >= 2) return true;
    return false;
}

static bool ShouldPlayFinalMusic() {
    if (g_finalMusicActive) return true;
    if (g_pendingMirrorRevealDialog || g_mirrorRevealTimer > 0) return true;
    if (g_rebirthOverlayTimer > 0 && bossType == 3) return true;
    if (gameState == 1 && bossType == 3) return true;
    return false;
}

static void RefreshGameMusic() {
    if (ShouldPlayFinalMusic()) { PlayMusicTrack(MUSIC_FINAL); return; }
    if (gameState == 1) {
        if (IsBossInRagePhase()) PlayMusicTrack(MUSIC_BOSS);
        else PlayMusicTrack(MUSIC_FIGHT);
        return;
    }
    PlayMusicTrack(MUSIC_NORMAL);
}
static bool g_bossLootScreenOpen = false;
static int g_bossLootScreenType = -1;
static int g_bossFightTimerFrames = 0;
static int g_bossFailOverlayTimer = 0;
static int g_hpPeriodicRefillTimer = 0;
static int g_forestBossPoisonTickFc = 0;
static bool g_forestBossPoisoned = false;
static int g_iceDarkDotFc = 0;
static int g_flyGroundedTimer = 0;
static int g_flightTimeBank = 0;
struct BossFightSnapshot {
    bool valid;
    MapType map;
    float x, y, hp, mp;
};
static BossFightSnapshot g_bossSnapshot = { false, MAP_MAIN, 0.f, 0.f, 0.f, 0.f };

bool HasEquip(int id);
bool IsWeaponSlot(int slot);
bool TryEquipSlot(int slot);

static bool EquipHasDurability(int id) {
    return id == EQ_PICKAXE || id == EQ_IRON_SWORD || id == EQ_STEEL_ARMOR;
}
static int EquipMaxDurability(int id) {
    if (id == EQ_PICKAXE) return 40;
    if (id == EQ_IRON_SWORD) return 50;
    if (id == EQ_STEEL_ARMOR) return 20;
    return 0;
}
static int EquipDurSize(int id) {
    if (id < 0 || id >= EQUIP_SLOT_COUNT) return 0;
    return equipDurCount[id];
}
static bool EquipDurEmpty(int id) {
    return EquipDurSize(id) <= 0;
}
static void EquipDurClear(int id) {
    if (id >= 0 && id < EQUIP_SLOT_COUNT) equipDurCount[id] = 0;
}
static void EquipDurPush(int id, int dur) {
    if (id < 0 || id >= EQUIP_SLOT_COUNT) return;
    if (equipDurCount[id] >= MAX_EQUIP_INST) return;
    equipDurStack[id][equipDurCount[id]++] = dur;
}
static void EquipDurPop(int id) {
    if (equipDurCount[id] > 0) equipDurCount[id]--;
}
static void SyncEquipCountFromStack(int id) {
    if (EquipHasDurability(id)) equipCounts[id] = EquipDurSize(id);
}
static void AddEquipItem(int id) {
    if (id < 0 || id >= EQUIP_SLOT_COUNT) return;
    if (EquipHasDurability(id)) {
        EquipDurPush(id, EquipMaxDurability(id));
        SyncEquipCountFromStack(id);
    }
    else {
        equipCounts[id]++;
    }
}
static int FindPreferUsedInstance(int id) {
    if (!EquipHasDurability(id) || EquipDurEmpty(id)) return -1;
    int best = -1, bestDur = 0x7fffffff;
    for (int i = 0; i < EquipDurSize(id); i++) {
        int d = equipDurStack[id][i];
        if (d > 0 && d < bestDur) { bestDur = d; best = i; }
    }
    return best >= 0 ? best : 0;
}
static void RebuildDurStacksFromCounts() {
    for (int id = 0; id < EQUIP_SLOT_COUNT; id++) {
        if (!EquipHasDurability(id)) continue;
        while (EquipDurSize(id) < equipCounts[id])
            EquipDurPush(id, EquipMaxDurability(id));
        while (EquipDurSize(id) > equipCounts[id])
            EquipDurPop(id);
        SyncEquipCountFromStack(id);
    }
}
static void SaveEquipDurToSlot(SaveSlotData& d) {
    for (int i = 0; i < EQUIP_SLOT_COUNT; i++) {
        int n = EquipDurSize(i);
        if (n > MAX_EQUIP_INST) n = MAX_EQUIP_INST;
        d.equipInstN[i] = (short)n;
        for (int j = 0; j < n; j++) d.equipInstDur[i][j] = (short)equipDurStack[i][j];
    }
    d.equippedWeaponInst = equippedWeaponInst;
    d.equippedArmorInst = equippedArmorInst;
}
static void LoadEquipDurFromSlot(const SaveSlotData& d) {
    for (int i = 0; i < EQUIP_SLOT_COUNT; i++) {
        EquipDurClear(i);
        int n = d.equipInstN[i];
        if (n < 0) n = 0;
        if (n > MAX_EQUIP_INST) n = MAX_EQUIP_INST;
        for (int j = 0; j < n; j++) EquipDurPush(i, (int)d.equipInstDur[i][j]);
        if (EquipHasDurability(i)) SyncEquipCountFromStack(i);
    }
    equippedWeaponInst = d.equippedWeaponInst;
    equippedArmorInst = d.equippedArmorInst;
    RebuildDurStacksFromCounts();
}
static void RemoveEquipInstanceAt(int id, int instIdx) {
    if (!EquipHasDurability(id) || instIdx < 0 || instIdx >= EquipDurSize(id)) return;
    for (int i = instIdx; i < EquipDurSize(id) - 1; i++)
        equipDurStack[id][i] = equipDurStack[id][i + 1];
    equipDurCount[id]--;
    SyncEquipCountFromStack(id);
    if (equippedWeapon == id) {
        if (equippedWeaponInst == instIdx) equippedWeaponInst = -1;
        else if (equippedWeaponInst > instIdx) equippedWeaponInst--;
    }
    if (equippedArmor == id) {
        if (equippedArmorInst == instIdx) equippedArmorInst = -1;
        else if (equippedArmorInst > instIdx) equippedArmorInst--;
    }
}
static void SwordWavesClear() { swordWaveCount = 0; }
static int CountActivePlayerWaves() {
    int c = 0;
    for (int i = 0; i < swordWaveCount; i++)
        if (swordWaves[i].active) c++;
    return c;
}
static void BossBulletPoolClear(BossBullet* pool, int& count) { count = 0; }
static bool BossBulletPoolAdd(BossBullet* pool, int& count, const BossBullet& b) {
    if (count >= MAX_BOSS_BULLETS) return false;
    pool[count++] = b;
    return true;
}
static void BossWavePoolClear(SwordWave* pool, int& count) { count = 0; }
static bool BossWavePoolAdd(SwordWave* pool, int& count, const SwordWave& w) {
    if (count >= MAX_BOSS_WAVES) return false;
    pool[count++] = w;
    return true;
}
static void IceSpikePoolClear(IceSpike* pool, int& count) { count = 0; }
static bool IceSpikePoolAdd(IceSpike* pool, int& count, const IceSpike& sp) {
    if (count >= MAX_ICE_SPIKES) return false;
    pool[count++] = sp;
    return true;
}
static void WorldItemsClear() { worldItemCount = 0; }
static bool WorldItemsAdd(const WorldItem& item) {
    if (worldItemCount >= MAX_WORLD_ITEMS) return false;
    worldItems[worldItemCount++] = item;
    return true;
}
static void IceServantsClear() { iceServantCount = 0; }
static bool CanUseSwordWave() {
    return g_bronzeRingWaveUnlocked;
}
static bool IsEquippedEndlessSword() {
    return equippedWeapon == EQ_ENDLESS_SWORD && HasEquip(EQ_ENDLESS_SWORD);
}
static void PushPlayerSwordWave(float baseAng, float angleOffset, int damage, float range) {
    float ang = baseAng + angleOffset;
    float vx = cosf(ang) * 12.f, vy = sinf(ang) * 12.f;
    SwordWave w;
    w.x = player.x; w.y = player.y;
    w.vx = vx; w.vy = vy;
    w.damage = damage;
    w.range = range;
    w.traveled = 0;
    w.active = true;
    w.imageDir = getDirectionIndexForAngle(cosf(ang), sinf(ang));
    if (swordWaveCount < MAX_PLAYER_WAVES) swordWaves[swordWaveCount++] = w;
}
static void TryConsumeWeaponDurOnDamageDealt() {
    if (equippedWeapon != EQ_IRON_SWORD && equippedWeapon != EQ_PICKAXE) return;
    if (!EquipHasDurability(equippedWeapon) || equippedWeaponInst < 0) return;
    if (equippedWeaponInst >= EquipDurSize(equippedWeapon)) return;
    int& d = equipDurStack[equippedWeapon][equippedWeaponInst];
    d--;
    if (d <= 0) {
        int idx = equippedWeaponInst;
        RemoveEquipInstanceAt(equippedWeapon, idx);
        if (!EquipDurEmpty(equippedWeapon)) {
            TryEquipSlot(equippedWeapon);
        }
        else {
            equippedWeapon = -1;
            for (int w = 0; w < EQUIP_SLOT_COUNT; w++) {
                if (IsWeaponSlot(w) && HasEquip(w)) { TryEquipSlot(w); break; }
            }
            if (equippedWeapon < 0) {
                for (int w = 0; w < EQUIP_SLOT_COUNT; w++) {
                    if (IsWeaponSlot(w) && HasEquip(w)) { TryEquipSlot(w); break; }
                }
            }
        }
    }
}
static void ConsumeEquippedArmorDurability() {
    if (equippedArmor != EQ_STEEL_ARMOR || equippedArmorInst < 0) return;
    if (equippedArmorInst >= EquipDurSize(EQ_STEEL_ARMOR)) return;
    int& d = equipDurStack[EQ_STEEL_ARMOR][equippedArmorInst];
    d--;
    if (d <= 0) {
        int idx = equippedArmorInst;
        RemoveEquipInstanceAt(EQ_STEEL_ARMOR, idx);
        if (!EquipDurEmpty(EQ_STEEL_ARMOR)) {
            TryEquipSlot(EQ_STEEL_ARMOR);
        }
        else {
            equippedArmor = -1;
        }
    }
}
static void OpenBossLootScreen(int bt) {
    g_bossLootScreenType = bt;
    g_bossLootScreenOpen = true;
}
static void drawBossLootEquipIcon(int eqId, int x, int y, int sz) {
    if (eqId >= 0 && eqId < EQUIP_SLOT_COUNT && equipImgLoaded[eqId])
        putimageAlpha(x, y, sz, sz, &equipImg[eqId], 0, 0);
    else {
        setfillcolor(RGB(60, 60, 80));
        solidrectangle(x, y, x + sz, y + sz);
    }
}
static const TCHAR* GetBossDisplayName(int bt) {
    if (bt == 0) return L"\u6BD2\u57DF\u9738\u4E3B";
    if (bt == 1) return L"\u5CA9\u7532\u5B88\u62A4\u8005";
    if (bt == 2) return L"\u5DDD\u5DEE\u5B88\u62A4\u8005";
    return L"\u6697\u5F71\u4E4B\u4E3B";
}
static void drawBossLootScreen() {
    const int iconSz = 128;
    const int iconX = 80;
    const int textX = iconX + iconSz + 32;
    setfillcolor(RGB(0, 0, 0));
    solidrectangle(0, 0, SCREEN_W, SCREEN_H);
    settextcolor(RGB(255, 215, 0));
    settextstyle(40, 0, L"\u5FAE\u8F6F\u96C5\u9ED1");
    outtextxy(SCREEN_W / 2 - 100, 70, L"\u6218\u5229\u54C1");
    settextstyle(28, 0, L"\u5FAE\u8F6F\u96C5\u9ED1");
    settextcolor(RGB(255, 120, 120));
    outtextxy(SCREEN_W / 2 - 80, 115, L"\u51FB\u8D25boss");
    settextcolor(RGB(255, 230, 180));
    outtextxy(SCREEN_W / 2 - 100, 150, GetBossDisplayName(g_bossLootScreenType));
    settextstyle(24, 0, L"\u5FAE\u8F6F\u96C5\u9ED1");
    int y = 200, lh = 100;
    if (g_bossLootScreenType == 0) {
        drawBossLootEquipIcon(EQ_ENDLESS_SWORD, iconX, y - 16, iconSz);
        settextcolor(RGB(255, 230, 150));
        outtextxy(textX, y, L"\u3010\u65E0\u5C3D\u4E4B\u5251\u3011"); y += lh;
        settextcolor(WHITE);
        outtextxy(textX, y, L"\u653B\u51FB\u529B +50"); y += lh + 12;
        drawBossLootEquipIcon(EQ_SOUL_RING, iconX, y - 16, iconSz);
        settextcolor(RGB(255, 230, 150));
        outtextxy(textX, y, L"\u3010\u9547\u7075\u6212\u3011"); y += lh;
        settextcolor(WHITE);
        outtextxy(textX, y, L"\u653B\u51FB\u529B +18");
    }
    else if (g_bossLootScreenType == 1) {
        drawBossLootEquipIcon(EQ_DIAMOND_ARMOR, iconX, y - 16, iconSz);
        settextcolor(RGB(255, 230, 150));
        outtextxy(textX, y, L"\u3010\u94BB\u77F3\u5723\u9484\u3011"); y += lh;
        settextcolor(WHITE);
        outtextxy(textX, y, L"\u9632\u5FA1\u529B +45");
    }
    settextcolor(RGB(180, 180, 180));
    settextstyle(20, 0, L"\u5FAE\u8F6F\u96C5\u9ED1");
    outtextxy(SCREEN_W / 2 - 120, SCREEN_H - 80, L"\u6309 Enter \u7EE7\u7EED\u6E38\u620F");
}

// ==================== 装备（剧情向） ====================
static bool IsSoulRingEquipped();
static void SyncSoulRingMpState();

bool HasEquip(int id) {
    if (id < 0 || id >= EQUIP_SLOT_COUNT) return false;
    if (EquipHasDurability(id)) return !EquipDurEmpty(id);
    return equipCounts[id] > 0;
}
void InitStarterEquipment() {
    for (int i = 0; i < EQUIP_SLOT_COUNT; i++) {
        equipCounts[i] = 0;
        EquipDurClear(i);
    }
    AddEquipItem(EQ_IRON_SWORD);
    equippedWeapon = EQ_IRON_SWORD;
    equippedWeaponInst = 0;
    equippedArmor = -1;
    equippedArmorInst = -1;
    equippedRing = -1;
}
void GrantMountainBossLoot() {
    AddEquipItem(EQ_DIAMOND_ARMOR);
    equippedArmor = EQ_DIAMOND_ARMOR;
    equippedArmorInst = -1;
}
void GrantForestBossLoot() {
    AddEquipItem(EQ_ENDLESS_SWORD);
    AddEquipItem(EQ_SOUL_RING);
    equippedWeapon = EQ_ENDLESS_SWORD;
    equippedWeaponInst = -1;
    equippedRing = EQ_SOUL_RING;
    SyncSoulRingMpState();
}
int GetEquippedWeaponAtk() {
    if (equippedWeapon < 0 || equippedWeapon >= EQUIP_SLOT_COUNT || !HasEquip(equippedWeapon)) return 0;
    return equipAtk[equippedWeapon];
}
int GetEquippedArmorDef() {
    if (equippedArmor < 0 || equippedArmor >= EQUIP_SLOT_COUNT || !HasEquip(equippedArmor)) return 0;
    return equipDef[equippedArmor];
}
int GetEquippedRingAtk() {
    if (equippedRing < 0 || equippedRing >= EQUIP_SLOT_COUNT || !HasEquip(equippedRing)) return 0;
    return equipAtk[equippedRing];
}
bool IsWeaponSlot(int slot) {
    return slot == EQ_PICKAXE || slot == EQ_IRON_SWORD || slot == EQ_ENDLESS_SWORD;
}
bool IsArmorSlot(int slot) {
    return slot == EQ_STEEL_ARMOR || slot == EQ_DIAMOND_ARMOR;
}
bool IsRingSlot(int slot) {
    return slot == EQ_BRONZE_RING || slot == EQ_SOUL_RING;
}
static bool IsSoulRingEquipped() {
    return equippedRing == EQ_SOUL_RING && HasEquip(EQ_SOUL_RING);
}
static bool IsIceMapDarknessActive() {
    return currentMap == MAP_ICE && !IsSoulRingEquipped();
}
static void SyncSoulRingMpState() {
    if (IsSoulRingEquipped()) player.mp = player.maxMp;
}
bool TryEquipSlot(int slot) {
    if (slot < 0 || slot >= EQUIP_SLOT_COUNT || !HasEquip(slot)) return false;
    if (IsWeaponSlot(slot)) {
        equippedWeapon = slot;
        equippedWeaponInst = EquipHasDurability(slot) ? FindPreferUsedInstance(slot) : -1;
    }
    else if (IsArmorSlot(slot)) {
        equippedArmor = slot;
        equippedArmorInst = EquipHasDurability(slot) ? FindPreferUsedInstance(slot) : -1;
    }
    else if (IsRingSlot(slot)) {
        equippedRing = slot;
    }
    else return false;
    SyncSoulRingMpState();
    return true;
}
bool IsItemEquipped(int slot) {
    return slot == equippedWeapon || slot == equippedArmor || slot == equippedRing;
}
static int GetLevelDamageReducePct() {
    int pct = playerLevel * LEVEL_DAMAGE_REDUCE_PCT_PER_LEVEL;
    if (pct < 0) pct = 0;
    if (pct > LEVEL_DAMAGE_REDUCE_MAX_PCT) pct = LEVEL_DAMAGE_REDUCE_MAX_PCT;
    return pct;
}
void ApplyPlayerDamage(float rawDmg, bool poisonSource = false) {
    if (invincibleTimer > 0 || rawDmg <= 0) return;
    if (GOD_MODE && player.hp <= 0) return;
    if (gameState == 1 && bossType == 0 && !HasEquip(EQ_DIAMOND_ARMOR))
        g_forestBossPoisoned = true;
    float dmg = rawDmg * 2.f;
    dmg -= GetEquippedArmorDef() * 0.45f;
    if (equippedRing == EQ_SOUL_RING && HasEquip(EQ_SOUL_RING)) dmg *= 0.82f;
    if (poisonSource && !HasEquip(EQ_DIAMOND_ARMOR)) {
        dmg *= 1.75f;
        if (player.slowTimer < 90) player.slowTimer = 90;
    }
    int reducePct = GetLevelDamageReducePct();
    dmg = dmg * (100 - reducePct) / 100.f;
    if (dmg < 1.f) dmg = 1.f;
    player.hp -= dmg;
    ConsumeEquippedArmorDurability();
    if (player.hp < 0) player.hp = 0;
    if (GOD_MODE && player.hp <= 0) player.hp = 0;
}
static int GetBossReincarnationDamageBonus() {
    return reincarnationCycle * BOSS_DAMAGE_PER_REINCARNATION;
}
static float GetBossAttackDamage(float baseDmg) {
    return baseDmg * 0.5f + (float)GetBossReincarnationDamageBonus();
}
static void ApplyBossPlayerDamage(float rawDmg, bool poisonSource = false) {
    ApplyPlayerDamage(GetBossAttackDamage(rawDmg), poisonSource);
}
static bool IsAttackingWithPickaxe() {
    if (equippedWeapon != EQ_PICKAXE || !HasEquip(EQ_PICKAXE)) return false;
    if (equippedWeaponInst >= 0 && equippedWeaponInst < EquipDurSize(EQ_PICKAXE))
        return equipDurStack[EQ_PICKAXE][equippedWeaponInst] > 0;
    return true;
}
int CalcDamageToBoss(int baseDmg, int bt) {
    if (baseDmg < 1) baseDmg = 1;
    if (bt == 1) {
        if (!IsAttackingWithPickaxe()) {
            int dmg = baseDmg - STONE_BOSS_NORMAL_WEAPON_DEF;
            return dmg < 1 ? 1 : dmg;
        }
        return baseDmg + STONE_BOSS_PICKAXE_BONUS;
    }
    if (bt == 2) return baseDmg + 35;
    return baseDmg;
}

// ==================== 等级 / 轮回 / 伤害 ====================
bool IsIceMapNoLevelBonus() { return currentMap == MAP_ICE; }
int GetUpgradeCost(int level) { if (level < 1) level = 1; return 100 + 50 * level * level; }
int GetMeleeBaseDamage() {
    return IsIceMapNoLevelBonus() ? BASE_MELEE_DAMAGE : BASE_MELEE_DAMAGE + (playerLevel - 1) * 2;
}
int GetWaveBaseOnly() {
    return IsIceMapNoLevelBonus() ? BASE_WAVE_DAMAGE : BASE_WAVE_DAMAGE + (playerLevel - 1) * 3;
}
int GetWaveMaxBaseOnly() {
    return IsIceMapNoLevelBonus() ? BASE_WAVE_MAX_DAMAGE : BASE_WAVE_MAX_DAMAGE + (playerLevel - 1) * 3;
}
int GetEquipAttackBonus() {
    return GetEquippedWeaponAtk() + GetEquippedRingAtk();
}
int GetBaseDefense() { return 0; }
int GetEquipDefenseBonus() { return GetEquippedArmorDef(); }
int GetMeleeDamage() {
    return GetMeleeBaseDamage() + GetEquipAttackBonus();
}
int GetWaveBaseDamage() {
    return GetWaveBaseOnly() + GetEquipAttackBonus();
}
int GetWaveMaxDamage() {
    return GetWaveMaxBaseOnly() + GetEquipAttackBonus();
}
void AddToRanking(const char* username, int level, int cycle);
void SaveRanking();
bool TryUpgradeLevel() {
    int cost = GetUpgradeCost(playerLevel);
    if (playerGold < cost) return false;
    playerGold -= cost;
    playerLevel++;
    AddToRanking(currentUsername, playerLevel, reincarnationCycle);
    return true;
}
void generateMonsters();
void generateForestMonsters();
void generateMountainMonsters();
void ClearAllItemsOnRebirth() {
    playerGold = 0;
    for (int i = 0; i < MATERIAL_SLOT_COUNT; i++) materialCounts[i] = 0;
    for (int i = 0; i < CONSUM_SLOT_COUNT; i++) consumCounts[i] = 0;
    for (int i = 0; i < EQUIP_SLOT_COUNT; i++) EquipDurClear(i);
    InitStarterEquipment();
    WorldItemsClear();
    foodItemActive = true;
    foodRespawnTimer = 0;
    ResetBronzeRingQuestForNewGame();
}
void StartNewCycle() {
    reincarnationCycle++;
    ClearAllItemsOnRebirth();
    bossDefeated[0] = bossDefeated[1] = bossDefeated[2] = false;
    currentMap = MAP_MAIN;
    gameState = 0;
    bossType = 0;
    player.x = MAIN_SPAWN_X; player.y = MAIN_SPAWN_Y;
    player.hp = player.maxHp; player.mp = player.maxMp;
    player.slowTimer = 0;
    flyMode = false;
    g_flightTimeBank = 0;
    g_hpPeriodicRefillTimer = 0;
    SwordWavesClear(); IceServantsClear();
    IceSpikePoolClear(iceBoss.iceSpikes, iceBoss.iceSpikeCount);
    BossWavePoolClear(iceBoss.waves, iceBoss.waveCount);
    mirrorBoss.isAlive = false;
    BossWavePoolClear(mirrorBoss.waves, mirrorBoss.waveCount);
    g_mirrorRevealTimer = 0;
    g_pendingMirrorRevealDialog = false;
    g_pendingReincarnationEndingDialog = false;
    g_finalMusicActive = false;
    generateMonsters(); generateForestMonsters(); generateMountainMonsters();
    forestBoss.isAlive = stoneBoss.isAlive = iceBoss.isAlive = false;
    invincibleTimer = 300;
    AddToRanking(currentUsername, playerLevel, reincarnationCycle);
    AutoSaveGame();
    RunOpeningDialog();
    RunAncientBookIntro();
}

bool isWalkable(int x, int y) {
    if (flyMode) return true;
    DWORD* pixels = NULL; int w = 0, h = 0;
    if (currentMap == MAP_MAIN) { pixels = maskPixels; w = maskWidth; h = maskHeight; }
    else if (currentMap == MAP_FOREST) { pixels = forestMaskPixels; w = forestMaskWidth; h = forestMaskHeight; }
    else if (currentMap == MAP_MOUNTAIN) { pixels = mountainMaskPixels; w = mountainMaskWidth; h = mountainMaskHeight; }
    else if (currentMap == MAP_ICE) { pixels = iceMaskPixels; w = iceMaskWidth; h = iceMaskHeight; }
    if (!pixels) return true;
    if (x < 0 || x >= w || y < 0 || y >= h) return false;
    return (pixels[y * w + x] & 0x00FFFFFF) != RGB(0, 0, 0);
}
static bool CanWalkAt(float x, float y, int moveRadius) {
    if (moveRadius <= 0)
        return isWalkable((int)x, (int)y);
    return isWalkable((int)x - moveRadius, (int)y - moveRadius)
        && isWalkable((int)x + moveRadius, (int)y - moveRadius)
        && isWalkable((int)x - moveRadius, (int)y + moveRadius)
        && isWalkable((int)x + moveRadius, (int)y + moveRadius);
}
void tryMove(Character& p, float dx, float dy) {
    float nextX = p.x + dx, nextY = p.y + dy;
    if (CanWalkAt(nextX, nextY, PLAYER_MOVE_COLLIDE_RADIUS)) {
        p.x = nextX; p.y = nextY;
    }
    int br = p.radius;
    float mapW = MAP_W, mapH = MAP_H;
    if (currentMap != MAP_MAIN) { mapW = NEWMAP_W; mapH = NEWMAP_H; }
    if (p.x < br) p.x = (float)br;
    if (p.x > mapW - br) p.x = mapW - br;
    if (p.y < br) p.y = (float)br;
    if (p.y > mapH - br) p.y = mapH - br;
}
void tryMoveBoss(ForestBoss& b, float dx, float dy) {
    b.x += dx; b.y += dy;
    float mapW = (currentMap == MAP_MAIN) ? MAP_W : NEWMAP_W;
    float mapH = (currentMap == MAP_MAIN) ? MAP_H : NEWMAP_H;
    if (b.x < FOREST_BOSS_RADIUS) b.x = FOREST_BOSS_RADIUS;
    if (b.x > mapW - FOREST_BOSS_RADIUS) b.x = mapW - FOREST_BOSS_RADIUS;
    if (b.y < FOREST_BOSS_RADIUS) b.y = FOREST_BOSS_RADIUS;
    if (b.y > mapH - FOREST_BOSS_RADIUS) b.y = mapH - FOREST_BOSS_RADIUS;
}

void generateMonsters() {
    srand((unsigned)time(NULL));
    for (int i = 0; i < MONSTER_COUNT; i++) {
        Monster& m = monsters[i];
        m.active = true; m.maxHp = MONSTER_MAX_HP; m.hp = m.maxHp;
        m.speed = MONSTER_SPEED; m.radius = MONSTER_RADIUS;
        m.dirX = (rand() % 3) - 1; m.dirY = (rand() % 3) - 1;
        if (m.dirX == 0 && m.dirY == 0) m.dirX = 1;
        m.moveTimer = (float)(rand() % 60) / 10.f;
        int tc = 0;
        do { m.x = (float)(rand() % MAP_W); m.y = (float)(rand() % MAP_H); tc++; if (tc > 500) break; } while (!isWalkable((int)m.x, (int)m.y));
    }
}
void generateForestMonsters() {
    for (int i = 0; i < FOREST_MONSTER_COUNT; i++) {
        Monster& m = forestMonsters[i];
        m.active = true; m.maxHp = FOREST_MONSTER_MAX_HP; m.hp = m.maxHp;
        m.speed = FOREST_MONSTER_SPEED; m.radius = FOREST_MONSTER_RADIUS;
        m.dirX = (rand() % 3) - 1; m.dirY = (rand() % 3) - 1;
        if (m.dirX == 0 && m.dirY == 0) m.dirX = 1;
        m.moveTimer = (float)(rand() % 60) / 10.f;
        int tc = 0;
        do { m.x = (float)(rand() % NEWMAP_W); m.y = (float)(rand() % NEWMAP_H); tc++; if (tc > 500) break; } while (!isWalkable((int)m.x, (int)m.y));
    }
}
void generateMountainMonsters() {
    for (int i = 0; i < MOUNTAIN_MONSTER_COUNT; i++) {
        Monster& m = mountainMonsters[i];
        m.active = true; m.maxHp = MOUNTAIN_MONSTER_MAX_HP; m.hp = m.maxHp;
        m.speed = MOUNTAIN_MONSTER_SPEED; m.radius = MOUNTAIN_MONSTER_RADIUS;
        m.dirX = (rand() % 3) - 1; m.dirY = (rand() % 3) - 1;
        if (m.dirX == 0 && m.dirY == 0) m.dirX = 1;
        m.moveTimer = (float)(rand() % 60) / 10.f;
        int tc = 0;
        do { m.x = (float)(rand() % NEWMAP_W); m.y = (float)(rand() % NEWMAP_H); tc++; if (tc > 500) break; } while (!isWalkable((int)m.x, (int)m.y));
    }
}

void updateMonstersGeneric(Monster* ml, int mlCount, float mapW, float mapH) {
    if (gameState == 1) return;
    for (int mi = 0; mi < mlCount; mi++) {
        Monster& m = ml[mi];
        if (!m.active) continue;
        m.moveTimer -= 1.f / 60.f;
        if (m.moveTimer <= 0) {
            m.dirX = (rand() % 3) - 1; m.dirY = (rand() % 3) - 1;
            if (m.dirX == 0 && m.dirY == 0) m.dirX = 1;
            m.moveTimer = 2.f;
        }
        float newX = m.x + m.dirX * m.speed, newY = m.y + m.dirY * m.speed;
        int r = m.radius;
        m.x = newX; m.y = newY;
        if (m.x < r) m.x = (float)r; if (m.x > mapW - r) m.x = mapW - r;
        if (m.y < r) m.y = (float)r; if (m.y > mapH - r) m.y = mapH - r;
        float dx = player.x - m.x, dy = player.y - m.y;
        float damage = MONSTER_COLLIDE_DAMAGE;
        if (currentMap == MAP_FOREST) damage = FOREST_MONSTER_COLLIDE_DAMAGE;
        else if (currentMap == MAP_MOUNTAIN) damage = MOUNTAIN_MONSTER_COLLIDE_DAMAGE;
        if (hypot(dx, dy) < player.radius + m.radius && invincibleTimer <= 0 && gameState == 0
            && monsterContactDamageCd <= 0.f) {
            ApplyPlayerDamage(damage, currentMap == MAP_FOREST);
            monsterContactDamageCd = MONSTER_CONTACT_DAMAGE_INTERVAL;
            if (currentMap != MAP_MAIN) {
                float ang = atan2(dy, dx);
                player.x += cos(ang) * 15; player.y += sin(ang) * 15;
            }
        }
    }
}

static bool SwordWaveHitMonsters(SwordWave& w, Monster* ml, int mlCount) {
    for (int i = 0; i < mlCount; i++) {
        Monster& m = ml[i];
        if (!m.active) continue;
        if (hypot(m.x - w.x, m.y - w.y) < m.radius + WAVE_COLLIDE_RADIUS) {
            m.hp -= w.damage;
            if (m.hp <= 0) { m.active = false; playerGold += 10; }
            return true;
        }
    }
    return false;
}
void updateSwordWaves() {
    for (int wi = 0; wi < swordWaveCount; ) {
        SwordWave& w = swordWaves[wi];
        if (!w.active) {
            swordWaves[wi] = swordWaves[swordWaveCount - 1];
            swordWaveCount--;
            continue;
        }
        w.x += w.vx; w.y += w.vy;
        w.traveled += hypot(w.vx, w.vy);
        if (w.traveled >= w.range) {
            swordWaves[wi] = swordWaves[swordWaveCount - 1];
            swordWaveCount--;
            continue;
        }
        bool hit = false;
        if (gameState == 0) {
            if (currentMap == MAP_MAIN) hit = SwordWaveHitMonsters(w, monsters, MONSTER_COUNT);
            else if (currentMap == MAP_FOREST) hit = SwordWaveHitMonsters(w, forestMonsters, FOREST_MONSTER_COUNT);
            else if (currentMap == MAP_MOUNTAIN) hit = SwordWaveHitMonsters(w, mountainMonsters, MOUNTAIN_MONSTER_COUNT);
        }
        else if (gameState == 1) {
            if (bossType == 0 && forestBoss.isAlive) {
                if (hypot(forestBoss.x - w.x, forestBoss.y - w.y) < FOREST_BOSS_RADIUS + WAVE_COLLIDE_RADIUS) {
                    int bd = CalcDamageToBoss(w.damage, 0);
                    forestBoss.hp -= bd; if (forestBoss.hp < 0) forestBoss.hp = 0;
                    if (forestBoss.hp <= forestBoss.maxHp / 2 && forestBoss.phase == 1) {
                        forestBoss.phase = 2; forestBoss.shootInterval = 30; forestBoss.burstCount = 3;
                        forestBoss.shieldRotateSpeed = 0.1f; forestBoss.shieldRadiusSpeed = 0.02f; forestBoss.shieldDamage = 30;
                    }
                    hit = true;
                }
            }
            else if (bossType == 1 && stoneBoss.isAlive) {
                if (hypot(stoneBoss.x - w.x, stoneBoss.y - w.y) < STONE_BOSS_RADIUS + WAVE_COLLIDE_RADIUS) {
                    int bd = CalcDamageToBoss(w.damage, 1);
                    stoneBoss.hp -= bd; if (stoneBoss.hp < 0) stoneBoss.hp = 0;
                    if (stoneBoss.hp <= stoneBoss.maxHp / 2 && stoneBoss.phase == 1) {
                        stoneBoss.phase = 2; stoneBoss.shootInterval = 30; stoneBoss.burstCount = 3;
                    }
                    hit = true;
                }
            }
            else if (bossType == 2 && iceBoss.isAlive) {
                if (hypot(iceBoss.x - w.x, iceBoss.y - w.y) < ICE_BOSS_RADIUS + WAVE_COLLIDE_RADIUS) {
                    int bd = CalcDamageToBoss(w.damage, 2);
                    iceBoss.hp -= bd; if (iceBoss.hp < 0) iceBoss.hp = 0;
                    if (iceBoss.hp <= iceBoss.maxHp / 2 && iceBoss.phase == 1) {
                        iceBoss.phase = 2; iceBoss.waveShootInterval = ICE_BOSS_WAVE_INTERVAL_PHASE2;
                        iceBoss.freezeAuraActive = true;
                    }
                    hit = true;
                }
                else {
                    for (int si = 0; si < iceServantCount; si++) {
                        IceServant& s = iceServants[si];
                        if (!s.active) continue;
                        if (hypot(s.x - w.x, s.y - w.y) < s.radius + WAVE_COLLIDE_RADIUS) {
                            s.hp -= w.damage; hit = true; break;
                        }
                    }
                }
            }
            else if (bossType == 3 && mirrorBoss.isAlive && g_mirrorRevealTimer <= 0) {
                if (hypot(mirrorBoss.x - w.x, mirrorBoss.y - w.y) < mirrorBoss.radius + WAVE_COLLIDE_RADIUS) {
                    mirrorBoss.hp -= (float)w.damage;
                    if (mirrorBoss.hp < 0) mirrorBoss.hp = 0;
                    hit = true;
                }
            }
        }
        if (hit) {
            TryConsumeWeaponDurOnDamageDealt();
            swordWaves[wi] = swordWaves[swordWaveCount - 1];
            swordWaveCount--;
        }
        else wi++;
    }
}

void drawMonster(Monster& m, int sx, int sy) {
    if (monsterImg.getwidth() > 0) drawSprite(&monsterImg, sx, sy, MONSTER_SCALE, MONSTER_SCALE);
    else { setfillcolor(RGB(180, 60, 60)); solidcircle(sx, sy, m.radius); }
    int barW = 40, barH = 6, barX = sx - barW / 2, barY = sy - m.radius - 8;
    setfillcolor(RGB(0, 0, 0)); solidrectangle(barX, barY, barX + barW, barY + barH);
    setfillcolor(RGB(255, 0, 0)); solidrectangle(barX, barY, barX + (int)(barW * m.hp / m.maxHp), barY + barH);
}
void drawSwordWave(SwordWave& w, int sx, int sy) {
    if (w.imageDir >= 0 && w.imageDir < 4 && swordWaveImgs[w.imageDir].getwidth() > 0)
        drawSprite(&swordWaveImgs[w.imageDir], sx, sy, WAVE_SCALE, WAVE_SCALE);
    else { setfillcolor(RGB(255, 200, 100)); solidcircle(sx, sy, WAVE_COLLIDE_RADIUS); }
}
void drawPlayerUI() {
    int barW = 250, barH = 28, barX = 20, barY = 20;
    setfillcolor(RGB(40, 40, 40)); solidrectangle(barX, barY, barX + barW, barY + barH);
    setfillcolor(RGB(220, 50, 50)); solidrectangle(barX, barY, barX + (int)(barW * player.hp / player.maxHp), barY + barH);
    setlinecolor(RGB(200, 200, 200)); rectangle(barX, barY, barX + barW, barY + barH);
    settextcolor(WHITE); settextstyle(18, 0, _T("\u9ED1\u4F53"));
    TCHAR t[32]; _stprintf_s(t, L"HP: %.0f/%.0f", player.hp, player.maxHp); outtextxy(barX + 8, barY + 4, t);
    int mpY = barY + barH + 8;
    setfillcolor(RGB(40, 40, 40)); solidrectangle(barX, mpY, barX + barW, mpY + barH);
    if (IsSoulRingEquipped()) {
        setfillcolor(RGB(120, 180, 255));
        solidrectangle(barX, mpY, barX + barW, mpY + barH);
        _stprintf_s(t, L"MP: \u221E");
    }
    else {
        setfillcolor(RGB(50, 100, 220));
        solidrectangle(barX, mpY, barX + (int)(barW * player.mp / player.maxMp), mpY + barH);
        _stprintf_s(t, L"MP: %.0f/%.0f", player.mp, player.maxMp);
    }
    rectangle(barX, mpY, barX + barW, mpY + barH);
    outtextxy(barX + 8, mpY + 4, t);
    TCHAR lv[64]; _stprintf_s(lv, L"Lv.%d  \u8F6E\u56DE:%d", playerLevel, reincarnationCycle);
    outtextxy(barX, mpY + barH + 8, lv);
}
void drawStatsPanel() {
    setfillcolor(RGBA(0, 0, 0, 210)); solidrectangle(0, 0, SCREEN_W, SCREEN_H);
    int pw = 520, ph = 420, px = (SCREEN_W - pw) / 2, py = (SCREEN_H - ph) / 2;
    setfillcolor(RGB(35, 32, 48)); solidrectangle(px, py, px + pw, py + ph);
    setlinecolor(RGB(255, 215, 0)); rectangle(px, py, px + pw, py + ph);
    settextcolor(RGB(255, 215, 0)); settextstyle(30, 0, _T("\u9ED1\u4F53"));
    outtextxy(px + pw / 2 - 70, py + 16, L"\u4EBA\u7269\u6570\u503C");
    settextstyle(20, 0, _T("\u9ED1\u4F53"));
    int y = py + 70, lh = 36;
    TCHAR line[128];
    _stprintf_s(line, L"\u57FA\u7840\u653B\u51FB\u529B: %d", GetMeleeBaseDamage());
    settextcolor(WHITE); outtextxy(px + 40, y, line); y += lh;
    _stprintf_s(line, L"\u57FA\u7840\u9632\u5FA1\u529B: %d", GetBaseDefense());
    outtextxy(px + 40, y, line); y += lh;
    _stprintf_s(line, L"\u7B49\u7EA7\u51CF\u4F24: %d%% (\u6BCF\u7EA7+5%%)", GetLevelDamageReducePct());
    settextcolor(RGB(180, 255, 180)); outtextxy(px + 40, y, line); y += lh;
    _stprintf_s(line, L"\u8F6E\u56DE Boss\u653B\u51FB\u52A0\u6210: +%d (\u6BCF\u8F6E+20)", GetBossReincarnationDamageBonus());
    settextcolor(RGB(255, 180, 180)); outtextxy(px + 40, y, line); y += lh;
    int eqAtk = GetEquipAttackBonus(), eqDef = GetEquipDefenseBonus();
    _stprintf_s(line, L"\u88C5\u5907\u653B\u51FB\u529B: +%d", eqAtk);
    settextcolor(RGB(150, 220, 255)); outtextxy(px + 40, y, line); y += lh;
    _stprintf_s(line, L"\u88C5\u5907\u9632\u5FA1\u529B: +%d", eqDef);
    outtextxy(px + 40, y, line); y += lh + 10;
    settextcolor(RGB(255, 230, 150));
    if (eqAtk > 0)
        _stprintf_s(line, L"\u780D\u51FB: %d+%d", GetMeleeBaseDamage(), eqAtk);
    else
        _stprintf_s(line, L"\u780D\u51FB: %d", GetMeleeBaseDamage());
    outtextxy(px + 40, y, line); y += lh;
    if (eqDef > 0)
        _stprintf_s(line, L"\u62A4\u7532: %d+%d", GetBaseDefense(), eqDef);
    else
        _stprintf_s(line, L"\u62A4\u7532: %d", GetBaseDefense());
    settextcolor(RGB(255, 230, 150)); outtextxy(px + 40, y, line); y += lh;
    if (eqAtk > 0)
        _stprintf_s(line, L"\u5251\u6C14(\u57FA\u7840): %d+%d", GetWaveBaseOnly(), eqAtk);
    else
        _stprintf_s(line, L"\u5251\u6C14(\u57FA\u7840): %d", GetWaveBaseOnly());
    outtextxy(px + 40, y, line); y += lh;
    if (eqAtk > 0)
        _stprintf_s(line, L"\u5251\u6C14(\u6EE1\u50A8): %d+%d", GetWaveMaxBaseOnly(), eqAtk);
    else
        _stprintf_s(line, L"\u5251\u6C14(\u6EE1\u50A8): %d", GetWaveMaxBaseOnly());
    outtextxy(px + 40, y, line); y += lh + 8;
    settextcolor(RGB(200, 200, 200)); settextstyle(16, 0, _T("\u9ED1\u4F53"));
    if (equippedWeapon >= 0 && HasEquip(equippedWeapon))
        _stprintf_s(line, L"\u6B66\u5668: %s", equipNames[equippedWeapon]);
    else _tcscpy_s(line, L"\u6B66\u5668: \u65E0");
    outtextxy(px + 40, y, line); y += 28;
    if (equippedArmor >= 0 && HasEquip(equippedArmor))
        _stprintf_s(line, L"\u62A4\u7532: %s", equipNames[equippedArmor]);
    else _tcscpy_s(line, L"\u62A4\u7532: \u65E0");
    outtextxy(px + 40, y, line); y += 28;
    if (equippedRing >= 0 && HasEquip(equippedRing))
        _stprintf_s(line, L"\u6212\u6307: %s", equipNames[equippedRing]);
    else _tcscpy_s(line, L"\u6212\u6307: \u65E0");
    outtextxy(px + 40, y, line);
    settextcolor(RGB(150, 150, 150)); settextstyle(16, 0, _T("\u9ED1\u4F53"));
    outtextxy(px + 40, py + ph - 36, L"C / ESC \u5173\u95ED");
}
static void SaveBossFightSnapshot() {
    g_bossSnapshot.valid = true;
    g_bossSnapshot.map = currentMap;
    g_bossSnapshot.x = player.x;
    g_bossSnapshot.y = player.y;
    g_bossSnapshot.hp = player.hp;
    g_bossSnapshot.mp = player.mp;
}
static void ClearForestBossPoisonState() {
    g_forestBossPoisoned = false;
    g_forestBossPoisonTickFc = 0;
}
static void EndBossFightCommon() {
    gameState = 0;
    g_bossSnapshot.valid = false;
    g_bossFightTimerFrames = 0;
    forestBoss.isAlive = false;
    stoneBoss.isAlive = false;
    iceBoss.isAlive = false;
    mirrorBoss.isAlive = false;
    BossBulletPoolClear(forestBoss.bullets, forestBoss.bulletCount);
    BossBulletPoolClear(stoneBoss.bullets, stoneBoss.bulletCount);
    forestBoss.rootActive = false;
    forestBoss.rootWarning = false;
    SwordWavesClear();
    IceServantsClear();
    IceSpikePoolClear(iceBoss.iceSpikes, iceBoss.iceSpikeCount);
    BossWavePoolClear(iceBoss.waves, iceBoss.waveCount);
    BossWavePoolClear(mirrorBoss.waves, mirrorBoss.waveCount);
    g_mirrorRevealTimer = 0;
    g_pendingMirrorRevealDialog = false;
    g_pendingReincarnationEndingDialog = false;
    g_finalMusicActive = false;
    ClearForestBossPoisonState();
    invincibleTimer = 180;
    RefreshGameMusic();
}
static void RestoreBossFightSnapshotCore() {
    if (g_bossSnapshot.valid) {
        currentMap = g_bossSnapshot.map;
        player.x = g_bossSnapshot.x;
        player.y = g_bossSnapshot.y;
        player.hp = g_bossSnapshot.hp;
        player.mp = g_bossSnapshot.mp;
    }
    EndBossFightCommon();
}
static void FailBossFight() {
    currentMap = MAP_MAIN;
    player.x = MAIN_SPAWN_X;
    player.y = MAIN_SPAWN_Y;
    player.hp = BOSS_FAIL_HP;
    EndBossFightCommon();
    g_bossFailOverlayTimer = 200;
}
static bool CanWithdrawFromBossFight() {
    if (gameState != 1 || !g_bossSnapshot.valid) return false;
    return g_bossFightTimerFrames > BOSS_FIGHT_TIME_LIMIT_FRAMES - BOSS_FIGHT_ESC_WITHDRAW_FRAMES;
}
static void WithdrawFromBossFight() {
    if (!CanWithdrawFromBossFight()) return;
    RestoreBossFightSnapshotCore();
}
static void FailBossFightTimeout() {
    FailBossFight();
}
static void drawBossFightTimer() {
    if (gameState != 1 || g_bossFightTimerFrames <= 0) return;
    int totalSec = (g_bossFightTimerFrames + 59) / 60;
    int min = totalSec / 60;
    int sec = totalSec % 60;
    TCHAR t[32];
    _stprintf_s(t, L"\u5269\u4F59 %d:%02d", min, sec);
    setbkmode(TRANSPARENT);
    settextcolor(g_bossFightTimerFrames < 60 * 60 ? RGB(255, 90, 90) : RGB(255, 215, 0));
    settextstyle(34, 0, _T("\u9ED1\u4F53"));
    outtextxy(SCREEN_W / 2 - 100, 18, t);
    if (CanWithdrawFromBossFight()) {
        settextcolor(RGB(180, 220, 255));
        settextstyle(20, 0, _T("\u9ED1\u4F53"));
        outtextxy(SCREEN_W / 2 - 130, 58, L"ESC \u64A4\u9000\u6311\u6218 (\u8FDB\u6218\u540E1:30\u5185)");
    }
}
void StartBossFight(int bt) {
    g_bossInfoOpen = false;
    SaveBossFightSnapshot();
    ClearForestBossPoisonState();
    gameState = 1; bossType = bt; SwordWavesClear();
    g_bossFightTimerFrames = BOSS_FIGHT_TIME_LIMIT_FRAMES;
    g_hpPeriodicRefillTimer = 0;
    invincibleTimer = 300;
    if (bt == 0) initForestBoss();
    else if (bt == 1) initStoneBoss();
    else if (bt == 2) {
        currentMap = MAP_ICE; player.x = ICE_SPAWN_X; player.y = ICE_SPAWN_Y;
        initIceBoss(); IceServantsClear();
    }
    RefreshGameMusic();
}
void drawBossInfoPanel(int bt) {
    setfillcolor(RGBA(0, 0, 0, 220)); solidrectangle(0, 0, SCREEN_W, SCREEN_H);
    int pw = 640, ph = 480, px = (SCREEN_W - pw) / 2, py = (SCREEN_H - ph) / 2;
    setfillcolor(RGB(40, 25, 35)); solidrectangle(px, py, px + pw, py + ph);
    setlinecolor(RGB(255, 80, 80)); rectangle(px, py, px + pw, py + ph);
    settextcolor(RGB(255, 100, 100)); settextstyle(32, 0, _T("\u9ED1\u4F53"));
    const TCHAR* title = (bt == 0) ? L"\u6BD2\u57DF\u9738\u4E3B" : (bt == 1) ? L"\u5CA9\u7532\u5B88\u62A4\u8005" : L"\u6697\u5F71\u4E4B\u4E3B";
    outtextxy(px + pw / 2 - 80, py + 18, title);
    settextstyle(20, 0, _T("\u9ED1\u4F53")); settextcolor(WHITE);
    int y = py + 75, lh = 32;
    TCHAR line[160];
    if (bt == 0) {
        _stprintf_s(line, L"HP: %d", FOREST_BOSS_MAX_HP); outtextxy(px + 40, y, line); y += lh;
        outtextxy(px + 40, y, L"\u653B\u51FB\u65B9\u5F0F\u4E0E\u4F24\u5BB3:"); y += lh;
        _stprintf_s(line, L"  \u2022 \u7EFF\u8272\u5B50\u5F39: %d", 15); outtextxy(px + 50, y, line); y += lh;
        _stprintf_s(line, L"  \u2022 \u65CB\u8F6C\u62A4\u76FE\u7403: %d (\u4E00\u9636 %d)", forestBoss.phase >= 2 ? 15 : SHIELD_BASE_DAMAGE, SHIELD_BASE_DAMAGE);
        outtextxy(px + 50, y, line); y += lh;
        _stprintf_s(line, L"  \u2022 \u6811\u6839\u9884\u8B66\u653B\u51FB: %d (\u4E8C\u9636)", ROOT_ATTACK_DAMAGE);
        outtextxy(px + 50, y, line); y += lh;
        outtextxy(px + 40, y, L"\u7279\u6027: \u6BD2\u57DF\u73AF\u5883\u4F24\u5BB3\u52A0\u6210(\u65E0\u5723\u7532)");
    }
    else if (bt == 1) {
        _stprintf_s(line, L"HP: %d", STONE_BOSS_MAX_HP); outtextxy(px + 40, y, line); y += lh;
        outtextxy(px + 40, y, L"\u653B\u51FB\u65B9\u5F0F\u4E0E\u4F24\u5BB3:"); y += lh;
        _stprintf_s(line, L"  \u2022 \u7EFF\u8272\u5B50\u5F39: %d", STONE_BOSS_ATTACK_DAMAGE); outtextxy(px + 50, y, line); y += lh;
        _stprintf_s(line, L"  \u2022 \u4E8C\u9636\u4E09\u5411\u5B50\u5F39\u9F50\u5C04"); outtextxy(px + 50, y, line); y += lh;
        outtextxy(px + 40, y, L"\u7279\u6027: \u91CD\u7532\uFF0C\u666E\u901A\u5175\u5668\u9632+100\uFF0C\u788E\u5CA9\u5DE8\u9550\u5BF9Boss\u4F24+100");
    }
    else {
        _stprintf_s(line, L"HP: %d", ICE_BOSS_MAX_HP); outtextxy(px + 40, y, line); y += lh;
        outtextxy(px + 40, y, L"\u653B\u51FB\u65B9\u5F0F\u4E0E\u4F24\u5BB3:"); y += lh;
        _stprintf_s(line, L"  \u2022 \u51B0\u5DDD\u5251\u6C14: %d", ICE_BOSS_WAVE_DAMAGE); outtextxy(px + 50, y, line); y += lh;
        _stprintf_s(line, L"  \u2022 \u51B0\u96C9\u4F1A\u51BB\u7F13: %d", ICE_BOSS_SPIKE_DAMAGE); outtextxy(px + 50, y, line); y += lh;
        _stprintf_s(line, L"  \u2022 \u51B0\u7075\u5F25\u51FB/\u78B0\u649E: %d / %d", ICE_SERVANT_BULLET_DAMAGE, ICE_SERVANT_COLLIDE_DAMAGE);
        outtextxy(px + 50, y, line); y += lh;
        outtextxy(px + 40, y, L"\u7279\u6027: \u51B0\u5DDD\u73AF\u5883\u4F1A\u51BB\u7F13\u73A9\u5BB6");
    }
    if (reincarnationCycle > 0) {
        y += lh;
        settextcolor(RGB(255, 180, 120));
        _stprintf_s(line, L"\u8F6E\u56DE\u52A0\u6210: \u6240\u6709\u653B\u51FB\u4F24\u5BB3 +%d (\u7B2C%d\u8F6E)", GetBossReincarnationDamageBonus(), reincarnationCycle);
        outtextxy(px + 40, y, line);
    }
    settextcolor(RGB(255, 220, 120)); settextstyle(18, 0, _T("\u9ED1\u4F53"));
    outtextxy(px + 40, py + ph - 70, L"Enter \u5F00\u59CB\u6311\u6218    ESC \u8FD4\u56DE");
    outtextxy(px + 40, py + ph - 42, L"\u6218\u6597\u4E2D ESC \u53EF\u64A4\u9000 (\u8FDB\u6218\u540E1:30\u5185)");
}
void handleBossInfoInput() {
    if (IsReturnKeyEdge()) {
        int bt = g_bossInfoType;
        g_bossInfoOpen = false;
        if (bt == 2) {
            RunIceBossPreFightDialog();
            ResetReturnKeyEdge();
            flushmessage(EX_MOUSE | EX_KEY);
        }
        StartBossFight(bt);
        Sleep(200);
    }
    if (GetAsyncKeyState(VK_ESCAPE) & 1) { g_bossInfoOpen = false; g_bossInfoType = -1; Sleep(200); }
}
bool TryCraftRecipe(int id) {
    switch (id) {
    case 0:
        if (materialCounts[MAT_IRON] < 20) return false;
        materialCounts[MAT_IRON] -= 20; AddEquipItem(EQ_IRON_SWORD); return true;
    case 1:
        if (materialCounts[MAT_IRON] < 20 || materialCounts[MAT_WOOD] < 5) return false;
        materialCounts[MAT_IRON] -= 20; materialCounts[MAT_WOOD] -= 5;
        AddEquipItem(EQ_STEEL_ARMOR); return true;
    case 2:
        if (materialCounts[MAT_IRON] < 10 || materialCounts[MAT_WOOD] < 10 || materialCounts[MAT_HERB] < 10) return false;
        materialCounts[MAT_IRON] -= 10; materialCounts[MAT_WOOD] -= 10; materialCounts[MAT_HERB] -= 10;
        AddEquipItem(EQ_PICKAXE); return true;
    default: return false;
    }
}
void drawGoldUI() {
    if (coinImg.getwidth() > 0) drawSprite(&coinImg, SCREEN_W - 170, 110, 0.05f, 0.05f);
    settextcolor(RGB(255, 215, 0)); settextstyle(24, 0, _T("\u9ED1\u4F53"));
    TCHAR t[32]; _stprintf_s(t, L"x %d", playerGold); outtextxy(SCREEN_W - 120, 70, t);
}
void drawFlyModeOrbit(int psx, int psy) {
    if (!flyMode) return;
    const float orbitR = 58.f;
    const int cx = psx, cy = psy - 45;
    const float sc = player.displayScale * 0.25f;
    for (int i = 0; i < 2; i++) {
        float ang = g_flyOrbitAngle + (float)i * 3.14159265f;
        int ox = cx + (int)(cos(ang) * orbitR);
        int oy = cy + (int)(sin(ang) * orbitR);
        if (bossBulletImg.getwidth() > 0)
            drawSprite(&bossBulletImg, ox, oy, sc, sc);
        else {
            setfillcolor(RGB(120, 220, 255));
            solidcircle(ox, oy, (int)(player.radius * 0.3f));
        }
    }
}
void putimageAlpha(int x, int y, int dw, int dh, IMAGE* src, int srcX, int srcY) {
    if (!src || src->getwidth() == 0) return;
    BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    AlphaBlend(GetImageHDC(NULL), x, y, dw, dh, GetImageHDC(src), srcX, srcY, src->getwidth(), src->getheight(), bf);
}
void drawSprite(IMAGE* img, int x, int y, float scaleX, float scaleY) {
    if (!img || img->getwidth() <= 0) return;
    int w = img->getwidth(), h = img->getheight();
    DWORD* dst = GetImageBuffer(), * src = GetImageBuffer(img);
    int drawW = (int)(w * scaleX), drawH = (int)(h * scaleY);
    for (int iy = 0; iy < drawH; iy++)
        for (int ix = 0; ix < drawW; ix++) {
            int sx = (int)(ix / scaleX), sy = (int)(iy / scaleY);
            if (sx >= w) sx = w - 1; if (sy >= h) sy = h - 1;
            DWORD srcP = src[sy * w + sx];
            unsigned char a = (unsigned char)(srcP >> 24);
            if (a > 0) {
                int dx = x + ix - drawW / 2, dy = y + iy - drawH;
                if (dx >= 0 && dx < SCREEN_W && dy >= 0 && dy < SCREEN_H) {
                    if (a == 255) dst[dy * SCREEN_W + dx] = srcP;
                    else {
                        DWORD dstP = dst[dy * SCREEN_W + dx];
                        unsigned char r = (unsigned char)(((srcP >> 16) & 0xff) * a / 255 + ((dstP >> 16) & 0xff) * (255 - a) / 255);
                        unsigned char g = (unsigned char)(((srcP >> 8) & 0xff) * a / 255 + ((dstP >> 8) & 0xff) * (255 - a) / 255);
                        unsigned char b = (unsigned char)((srcP & 0xff) * a / 255 + (dstP & 0xff) * (255 - a) / 255);
                        dst[dy * SCREEN_W + dx] = (r << 16) | (g << 8) | b;
                    }
                }
            }
        }
}

void loadAssets() {
    loadimage(&bigmap, _T("pic/bigmap.png"));
    loadimage(&smallmap, _T("pic/smallmap.png"));
    loadimage(&maskImg, _T("pic/test1.png"));
    loadimage(&forestMapImg, _T("pic/map1.png"));
    loadimage(&forestMaskImg, _T("pic/test3.jpg"));
    loadimage(&mountainMapImg, _T("pic/mountain.png"));
    loadimage(&mountainMaskImg, _T("pic/test2.jpg"));
    loadimage(&iceMapImg, _T("pic/ice_map.png"));
    loadimage(&iceMaskImg, _T("pic/test4.jpg"));
    loadimage(&exchangeImg, _T("pic/exchange.png"));
    loadimage(&monsterImg, _T("pic/monster.png"));
    loadimage(&iceMonsterImg, _T("pic/ice_monster.png"));
    loadimage(&forestBossImg, _T("pic/boss.png"));
    loadimage(&stoneBossImg, _T("pic/stone_boss.png"));
    loadimage(&bossBulletImg, _T("pic/boss_bullet.png"));
    loadimage(&bossShieldImg, _T("pic/boss_shield.png"));
    loadimage(&bossRootImg, _T("pic/boss_root.png"));
    loadimage(&bossWarningImg, _T("pic/boss_warning.png"));
    loadimage(&iceBossImgs[0], _T("pic/ice_boss_down.png"));
    loadimage(&iceBossImgs[1], _T("pic/ice_boss_up.png"));
    loadimage(&iceBossImgs[2], _T("pic/ice_boss_left.png"));
    loadimage(&iceBossImgs[3], _T("pic/ice_boss_right.png"));
    loadimage(&iceWaveImgs[0], _T("pic/ice_wave_down.png"));
    loadimage(&iceWaveImgs[1], _T("pic/ice_wave_up.png"));
    loadimage(&iceWaveImgs[2], _T("pic/ice_wave_left.png"));
    loadimage(&iceWaveImgs[3], _T("pic/ice_wave_right.png"));
    loadimage(&iceSpikeImg, _T("pic/ice_spike.png"));
    loadimage(&swordWaveImgs[0], _T("pic/wave_down.png"));
    loadimage(&swordWaveImgs[1], _T("pic/wave_up.png"));
    loadimage(&swordWaveImgs[2], _T("pic/wave_left.png"));
    loadimage(&swordWaveImgs[3], _T("pic/wave_right.png"));
    if (maskImg.getwidth() > 0) { maskWidth = maskImg.getwidth(); maskHeight = maskImg.getheight(); maskPixels = GetImageBuffer(&maskImg); }
    if (forestMaskImg.getwidth() > 0) { forestMaskWidth = forestMaskImg.getwidth(); forestMaskHeight = forestMaskImg.getheight(); forestMaskPixels = GetImageBuffer(&forestMaskImg); }
    if (mountainMaskImg.getwidth() > 0) { mountainMaskWidth = mountainMaskImg.getwidth(); mountainMaskHeight = mountainMaskImg.getheight(); mountainMaskPixels = GetImageBuffer(&mountainMaskImg); }
    if (iceMaskImg.getwidth() > 0) { iceMaskWidth = iceMaskImg.getwidth(); iceMaskHeight = iceMaskImg.getheight(); iceMaskPixels = GetImageBuffer(&iceMaskImg); }
    const TCHAR* dirs[] = { _T("down"), _T("up"), _T("left"), _T("right") };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) { TCHAR p[100]; _stprintf_s(p, _T("pic/%s_%d.png"), dirs[i], j); loadimage(&img_walk[i][j], p); }
        TCHAR ap[100]; _stprintf_s(ap, _T("pic/sword_%s_attack_1.png"), dirs[i]); loadimage(&img_sword_atk[i], ap);
    }
    loadimage(&imgLoginBg, _T("pic/login.png"), SCREEN_W, SCREEN_H);
}
void loadInventoryImages() {
    loadimage(&bagBg, _T("pic/bag.png"), 850, 650);
    loadimage(&coinImg, _T("pic/coin.png"));
    loadimage(&woodImg, _T("pic/wood.png"));
    loadimage(&herbImg, _T("pic/herb.png"));
    loadimage(&ironOreImg, _T("pic/iron_ore.png"));
    loadimage(&foodImg, _T("pic/food.png"));
    for (int i = 0; i < EQUIP_SLOT_COUNT; i++) {
        loadimage(&equipImg[i], equipImages[i], 56, 56);
        if (equipImg[i].getwidth() == 0 && i == EQ_PICKAXE)
            loadimage(&equipImg[i], _T("pic/sword.png"), 56, 56);
        equipImgLoaded[i] = equipImg[i].getwidth() > 0;
    }
    for (int i = 0; i < CONSUM_SLOT_COUNT; i++) { loadimage(&consumImg[i], consumImages[i], 56, 56); consumImgLoaded[i] = consumImg[i].getwidth() > 0; }
    for (int i = 0; i < MATERIAL_SLOT_COUNT; i++) { loadimage(&materialImg[i], materialImages[i], 56, 56); materialImgLoaded[i] = materialImg[i].getwidth() > 0; }
}
void updateAim() {
    ExMessage msg;
    while (peekmessage(&msg, EX_MOUSE)) if (msg.message == WM_MOUSEMOVE) { g_mouseX = msg.x; g_mouseY = msg.y; }
    float dx = (float)(cameraX + g_mouseX - player.x), dy = (float)(cameraY + g_mouseY - player.y);
    float len = sqrt(dx * dx + dy * dy);
    if (len > 0.001f) { aimWorldX = dx / len; aimWorldY = dy / len; }
    else { aimWorldX = 1.f; aimWorldY = 0.f; }
    hasAim = true;
}
int getDirectionIndexForAngle(float dirX, float dirY) {
    float dotUp = dirY * (-1), dotDown = dirY, dotLeft = dirX * (-1), dotRight = dirX;
    if (dotUp >= dotDown && dotUp >= dotLeft && dotUp >= dotRight) return 1;
    if (dotDown >= dotUp && dotDown >= dotLeft && dotDown >= dotRight) return 0;
    if (dotLeft >= dotUp && dotLeft >= dotDown && dotLeft >= dotRight) return 2;
    return 3;
}
float getDirectionAngle(int direction) {
    switch (direction) { case 0: return M_PI / 2; case 1: return -M_PI / 2; case 2: return M_PI; case 3: return 0; }
                               return 0;
}

void GetCurrentTimeStr(char* timeStr, int len) { time_t n = time(NULL); strftime(timeStr, len, "%Y-%m-%d %H:%M:%S", localtime(&n)); }
bool reg(const char* name, const char* pwd) {
    FILE* f = fopen("users.dat", "ab+"); if (!f) return false;
    User u; fseek(f, 0, SEEK_SET);
    while (fread(&u, sizeof(User), 1, f)) if (strcmp(u.username, name) == 0) { fclose(f); return false; }
    strcpy(u.username, name); strcpy(u.password, pwd);
    fwrite(&u, sizeof(User), 1, f); fclose(f); return true;
}
bool login(const char* name, const char* pwd) {
    FILE* f = fopen("users.dat", "rb"); if (!f) return false;
    User u;
    while (fread(&u, sizeof(User), 1, f))
        if (strcmp(u.username, name) == 0 && strcmp(u.password, pwd) == 0) { fclose(f); return true; }
    fclose(f); return false;
}
static bool RankingScoreBetter(int cycleA, int levelA, int cycleB, int levelB) {
    if (cycleA != cycleB) return cycleA > cycleB;
    return levelA > levelB;
}
static void RankingSortEntries() {
    for (int i = 0; i < MAX_RANKING - 1; i++)
        for (int j = i + 1; j < MAX_RANKING; j++) {
            if (!rankingList[i].isValid && rankingList[j].isValid) {
                RankingEntry t = rankingList[i]; rankingList[i] = rankingList[j]; rankingList[j] = t;
            }
            else if (rankingList[i].isValid && rankingList[j].isValid &&
                !RankingScoreBetter(rankingList[i].reincarnationCycle, rankingList[i].level,
                    rankingList[j].reincarnationCycle, rankingList[j].level)) {
                RankingEntry t = rankingList[i]; rankingList[i] = rankingList[j]; rankingList[j] = t;
            }
        }
}
static void RankingDeduplicateUsers() {
    for (int i = 0; i < MAX_RANKING; i++) {
        if (!rankingList[i].isValid) continue;
        for (int j = i + 1; j < MAX_RANKING; j++) {
            if (!rankingList[j].isValid) continue;
            if (strcmp(rankingList[i].username, rankingList[j].username) != 0) continue;
            if (RankingScoreBetter(rankingList[j].reincarnationCycle, rankingList[j].level,
                rankingList[i].reincarnationCycle, rankingList[i].level))
                rankingList[i] = rankingList[j];
            rankingList[j].isValid = false;
        }
    }
    RankingEntry compact[MAX_RANKING];
    int n = 0;
    for (int i = 0; i < MAX_RANKING; i++)
        if (rankingList[i].isValid) compact[n++] = rankingList[i];
    for (int i = 0; i < MAX_RANKING; i++) {
        if (i < n) rankingList[i] = compact[i];
        else rankingList[i].isValid = false;
    }
    RankingSortEntries();
}
void LoadRanking() {
    FILE* f = fopen("ranking.dat", "rb");
    if (f) { fread(rankingList, sizeof(RankingEntry), MAX_RANKING, f); fclose(f); }
    else for (int i = 0; i < MAX_RANKING; i++) rankingList[i].isValid = false;
    RankingDeduplicateUsers();
    SaveRanking();
}
void SaveRanking() {
    FILE* f = fopen("ranking.dat", "wb");
    if (f) { fwrite(rankingList, sizeof(RankingEntry), MAX_RANKING, f); fclose(f); }
}
void AddToRanking(const char* username, int level, int cycle) {
    int idx = -1;
    int emptyIdx = -1;
    for (int i = 0; i < MAX_RANKING; i++) {
        if (rankingList[i].isValid && strcmp(rankingList[i].username, username) == 0) {
            idx = i;
            break;
        }
        if (emptyIdx < 0 && !rankingList[i].isValid) emptyIdx = i;
    }
    if (idx >= 0) {
        if (!RankingScoreBetter(cycle, level,
            rankingList[idx].reincarnationCycle, rankingList[idx].level))
            return;
    }
    else if (emptyIdx >= 0) {
        idx = emptyIdx;
    }
    else {
        idx = 0;
        for (int i = 1; i < MAX_RANKING; i++)
            if (!RankingScoreBetter(rankingList[i].reincarnationCycle, rankingList[i].level,
                rankingList[idx].reincarnationCycle, rankingList[idx].level))
                idx = i;
        if (rankingList[idx].isValid && !RankingScoreBetter(cycle, level,
            rankingList[idx].reincarnationCycle, rankingList[idx].level))
            return;
    }
    strcpy(rankingList[idx].username, username);
    rankingList[idx].level = level;
    rankingList[idx].reincarnationCycle = cycle;
    rankingList[idx].isValid = true;
    GetCurrentTimeStr(rankingList[idx].gameTime, 30);
    RankingSortEntries();
    SaveRanking();
}
static void FillSaveSlotData(SaveSlotData& d) {
    memset(&d, 0, sizeof(d));
    d.isValid = true;
    strcpy(d.username, currentUsername);
    GetCurrentTimeStr(d.saveTime, 30);
    d.playerLevel = playerLevel; d.reincarnationCycle = reincarnationCycle;
    d.playerGold = playerGold;
    d.playerHp = player.hp; d.playerMaxHp = player.maxHp;
    d.playerMp = player.mp; d.playerMaxMp = player.maxMp;
    d.playerX = player.x; d.playerY = player.y;
    d.currentMap = (int)currentMap;
    d.bossDefeated[0] = bossDefeated[0]; d.bossDefeated[1] = bossDefeated[1]; d.bossDefeated[2] = bossDefeated[2];
    memcpy(d.materialCounts, materialCounts, sizeof(materialCounts));
    memcpy(d.consumCounts, consumCounts, sizeof(consumCounts));
    memcpy(d.equipCounts, equipCounts, sizeof(equipCounts));
    d.equippedWeapon = equippedWeapon;
    d.equippedArmor = equippedArmor;
    d.equippedRing = equippedRing;
    SaveEquipDurToSlot(d);
    d.gameState = gameState; d.bossType = bossType;
    d.bronzeRingWaveUnlocked = g_bronzeRingWaveUnlocked;
    d.bronzeRingWorldActive = bronzeRingWorldActive;
    d.bronzeRingX = bronzeRingWorldX;
    d.bronzeRingY = bronzeRingWorldY;
    d.saveFormatVersion = SAVE_FORMAT_VERSION;
}
void SaveGameToSlot(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= MAX_SAVE_SLOTS) return;
    SaveSlotData d;
    FillSaveSlotData(d);
    char fn[50]; sprintf(fn, "save_slot_%d.dat", slotIndex);
    FILE* f = fopen(fn, "wb"); if (f) { fwrite(&d, sizeof(d), 1, f); fclose(f); }
}
void AutoSaveGame() {
    if (!currentUsername[0]) return;
    SaveSlotData d;
    FillSaveSlotData(d);
    FILE* f = fopen("save_auto.dat", "wb");
    if (f) { fwrite(&d, sizeof(d), 1, f); fclose(f); }
}
static void TryPeriodicAutoSave() {
    if (inShop || showInventory || g_bossInfoOpen || g_bossLootScreenOpen || showStatsPanel || showAncientBook) return;
    if (!currentUsername[0]) return;
    g_autoSaveCounter++;
    if (g_autoSaveCounter >= AUTO_SAVE_INTERVAL_FRAMES) {
        g_autoSaveCounter = 0;
        AutoSaveGame();
    }
}
bool LoadGameFromSlot(int slotIndex) {
    char fn[50]; sprintf(fn, "save_slot_%d.dat", slotIndex);
    FILE* f = fopen(fn, "rb"); if (!f) return false;
    SaveSlotData d; if (fread(&d, sizeof(d), 1, f) != 1) { fclose(f); return false; }
    fclose(f); if (!d.isValid) return false;
    strcpy(currentUsername, d.username);
    playerLevel = d.playerLevel; reincarnationCycle = d.reincarnationCycle;
    playerGold = d.playerGold;
    player.hp = d.playerHp; player.maxHp = d.playerMaxHp;
    player.mp = d.playerMp; player.maxMp = d.playerMaxMp;
    player.x = d.playerX; player.y = d.playerY;
    currentMap = (MapType)d.currentMap;
    bossDefeated[0] = d.bossDefeated[0]; bossDefeated[1] = d.bossDefeated[1]; bossDefeated[2] = d.bossDefeated[2];
    memcpy(materialCounts, d.materialCounts, sizeof(materialCounts));
    memcpy(consumCounts, d.consumCounts, sizeof(consumCounts));
    memcpy(equipCounts, d.equipCounts, sizeof(equipCounts));
    equippedWeapon = d.equippedWeapon;
    equippedArmor = d.equippedArmor;
    equippedRing = d.equippedRing;
    LoadEquipDurFromSlot(d);
    g_skipOpeningDialog = true;
    {
        bool hasWeapon = false;
        for (int w = 0; w < EQUIP_SLOT_COUNT; w++) {
            if (IsWeaponSlot(w) && HasEquip(w)) { hasWeapon = true; break; }
        }
        if (!hasWeapon) InitStarterEquipment();
        else {
            if (!HasEquip(equippedWeapon) || !IsWeaponSlot(equippedWeapon)) {
                equippedWeapon = -1;
                for (int w = 0; w < EQUIP_SLOT_COUNT; w++) {
                    if (IsWeaponSlot(w) && HasEquip(w)) { TryEquipSlot(w); break; }
                }
            }
            if (equippedArmor >= 0 && (!HasEquip(equippedArmor) || !IsArmorSlot(equippedArmor))) equippedArmor = -1;
            if (equippedRing >= 0 && (!HasEquip(equippedRing) || !IsRingSlot(equippedRing))) equippedRing = -1;
        }
    }
    gameState = d.gameState; bossType = d.bossType;
    if (d.saveFormatVersion >= SAVE_FORMAT_VERSION) {
        g_bronzeRingWaveUnlocked = d.bronzeRingWaveUnlocked;
        bronzeRingWorldActive = !g_bronzeRingWaveUnlocked;
    }
    else {
        g_bronzeRingWaveUnlocked = false;
        bronzeRingWorldActive = true;
    }
    if (bronzeRingWorldActive) InitBronzeRingWorldPosition();
    SyncBronzeRingWorldState();
    SwordWavesClear();
    g_autoSaveCounter = 0;
    SyncSoulRingMpState();
    return true;
}
void DeleteSaveSlot(int slotIndex) {
    char fn[50]; sprintf(fn, "save_slot_%d.dat", slotIndex); remove(fn);
}

static bool ReadSaveSlotData(int slotIndex, SaveSlotData* out) {
    if (!out || slotIndex < 0 || slotIndex >= MAX_SAVE_SLOTS) return false;
    char fn[50]; sprintf(fn, "save_slot_%d.dat", slotIndex);
    FILE* f = fopen(fn, "rb"); if (!f) return false;
    SaveSlotData d;
    if (fread(&d, sizeof(d), 1, f) != 1) { fclose(f); return false; }
    fclose(f);
    if (!d.isValid) return false;
    *out = d;
    return true;
}

static bool PromptSaveLoadPassword(const char* saveUsername) {
    if (!saveUsername || !saveUsername[0]) return false;
    TCHAR wp[50];
    TCHAR title[80];
    _stprintf_s(title, L"\u8BF7\u8F93\u5165\u7528\u6237\u300C%hs\u300D\u7684\u5BC6\u7801", saveUsername);
    InputBox(wp, 50, title, _T(""), NULL, 0, 0, true);
    char cp[20];
    WideCharToMultiByte(CP_ACP, 0, wp, -1, cp, 20, NULL, NULL);
    if (!cp[0]) return false;
    if (login(saveUsername, cp)) return true;
    MessageBox(GetHWnd(), _T("\u5BC6\u7801\u9519\u8BEF\uFF0C\u65E0\u6CD5\u8BFB\u6863"), _T("\u8BFB\u6863"), MB_OK);
    return false;
}

void ShowRankingMenu() {
    bool run = true; LoadRanking();
    char prevMusic[50];
    strcpy(prevMusic, currentMusic);
    PlayMusicTrack(MUSIC_RANKING);
    while (run) {
        cleardevice(); settextstyle(36, 0, _T("\u9ED1\u4F53")); settextcolor(YELLOW);
        outtextxy(SCREEN_W / 2 - 80, 50, _T("\u6392\u884C\u699C"));
        settextstyle(20, 0, _T("\u9ED1\u4F53"));
        settextcolor(LIGHTGREEN);
        outtextxy(200, 90, L"\u7528\u6237"); outtextxy(420, 90, L"\u8F6E\u56DE"); outtextxy(520, 90, L"\u7B49\u7EA7"); outtextxy(650, 90, L"\u65F6\u95F4");
        settextcolor(WHITE);
        for (int i = 0; i < MAX_RANKING; i++) {
            int y = 120 + i * 40;
            TCHAR r[8]; _stprintf_s(r, L"%d", i + 1); outtextxy(100, y, r);
            if (rankingList[i].isValid) {
                TCHAR n[30], lv[16], cy[16], tm[40];
                wsprintf(n, _T("%hs"), rankingList[i].username);
                _stprintf_s(cy, L"%d", rankingList[i].reincarnationCycle);
                _stprintf_s(lv, L"%d", rankingList[i].level);
                wsprintf(tm, _T("%hs"), rankingList[i].gameTime);
                outtextxy(200, y, n); outtextxy(420, y, cy); outtextxy(520, y, lv); outtextxy(650, y, tm);
            }
        }
        outtextxy(SCREEN_W / 2 - 60, SCREEN_H - 60, _T("ESC \u8FD4\u56DE"));
        FlushBatchDraw();
        if (GetAsyncKeyState(VK_ESCAPE) & 1) run = false;
        MusicPollEvents();
        Sleep(20);
    }
    if (musicEnabled && prevMusic[0]) PlayMusicTrack(prevMusic);
    else PlayMusicTrack(MUSIC_LOGIN);
}
static void GetSaveSlotScreenPos(int slotIndex, int* outX, int* outY) {
    int col = slotIndex / SAVE_SLOTS_PER_COLUMN;
    int row = slotIndex % SAVE_SLOTS_PER_COLUMN;
    *outX = 80 + col * 580;
    *outY = SAVE_SLOT_LIST_TOP + row * SAVE_SLOT_LINE_H;
}
static bool FormatSaveSlotText(int slotIndex, TCHAR* buf, int bufChars, bool showCycle) {
    char fn[50]; sprintf(fn, "save_slot_%d.dat", slotIndex);
    FILE* f = fopen(fn, "rb");
    if (f) {
        SaveSlotData s;
        if (fread(&s, sizeof(s), 1, f) == 1 && s.isValid) {
            fclose(f);
            if (showCycle)
                _stprintf_s(buf, bufChars, L"\u69FD%d %hs Lv%d \u8F6E%d", slotIndex + 1, s.username, s.playerLevel, s.reincarnationCycle);
            else
                _stprintf_s(buf, bufChars, L"\u69FD%d %hs Lv%d", slotIndex + 1, s.username, s.playerLevel);
            return true;
        }
        fclose(f);
    }
    _stprintf_s(buf, bufChars, L"\u69FD%d \u7A7A", slotIndex + 1);
    return false;
}
static void DrawSaveSlotList(int sel, bool showCycle) {
    for (int i = 0; i < MAX_SAVE_SLOTS; i++) {
        int x, y;
        GetSaveSlotScreenPos(i, &x, &y);
        settextcolor(i == sel ? LIGHTGREEN : WHITE);
        TCHAR d[300];
        FormatSaveSlotText(i, d, 300, showCycle);
        outtextxy(x, y, d);
    }
}
void ShowSaveMenu() {
    int sel = 0; bool run = true; bool wp = isPaused; isPaused = true;
    while (run) {
        cleardevice(); settextstyle(36, 0, _T("\u9ED1\u4F53")); settextcolor(YELLOW);
        outtextxy(SCREEN_W / 2 - 60, 50, _T("\u5B58\u6863"));
        settextstyle(20, 0, _T("\u9ED1\u4F53"));
        DrawSaveSlotList(sel, true);
        outtextxy(120, SCREEN_H - 110, _T("\u6E38\u620F\u4E2D\u6BCF30\u79D2\u81EA\u52A8\u5B58\u6863\u81F3 save_auto.dat"));
        outtextxy(120, SCREEN_H - 80, _T("Enter\u5B58\u6863 Del\u5220\u9664 ESC\u53D6\u6D88"));
        FlushBatchDraw();
        if (GetAsyncKeyState(VK_UP) & 1) sel = (sel - 1 + MAX_SAVE_SLOTS) % MAX_SAVE_SLOTS;
        if (GetAsyncKeyState(VK_DOWN) & 1) sel = (sel + 1) % MAX_SAVE_SLOTS;
        if (GetAsyncKeyState(VK_RETURN) & 1) { SaveGameToSlot(sel); run = false; }
        if (GetAsyncKeyState(VK_DELETE) & 1) DeleteSaveSlot(sel);
        if (GetAsyncKeyState(VK_ESCAPE) & 1) run = false;
        Sleep(20);
    }
    isPaused = wp;
}
bool ShowLoadMenu() {
    int sel = 0;
    bool run = true;
    bool loaded = false;
    bool wp = isPaused;
    isPaused = true;
    ResetReturnKeyEdge();
    flushmessage(EX_KEY);
    while (run) {
        cleardevice(); settextstyle(36, 0, _T("\u9ED1\u4F53")); settextcolor(YELLOW);
        outtextxy(SCREEN_W / 2 - 60, 50, _T("\u8BFB\u6863"));
        settextstyle(20, 0, _T("\u9ED1\u4F53"));
        DrawSaveSlotList(sel, false);
        {
            FILE* af = fopen("save_auto.dat", "rb");
            if (af) {
                SaveSlotData as; if (fread(&as, sizeof(as), 1, af) == 1 && as.isValid) {
                    settextcolor(RGB(180, 220, 255));
                    outtextxy(120, SCREEN_H - 110, _T("\u81EA\u52A8\u5B58\u6863\u5DF2\u5C31\u7EEA (\u6E38\u620F\u4E2D\u6BCF30\u79D2\u81EA\u52A8\u4FDD\u5B58)"));
                }
                fclose(af);
            }
        }
        outtextxy(120, SCREEN_H - 80, _T("Enter\u8BFB\u6863(\u9700\u9A8C\u8BC1\u8D26\u53F7\u5BC6\u7801) ESC\u53D6\u6D88"));
        FlushBatchDraw();
        if (GetAsyncKeyState(VK_UP) & 1) sel = (sel - 1 + MAX_SAVE_SLOTS) % MAX_SAVE_SLOTS;
        if (GetAsyncKeyState(VK_DOWN) & 1) sel = (sel + 1) % MAX_SAVE_SLOTS;
        if (IsReturnKeyEdge()) {
            SaveSlotData preview;
            if (!ReadSaveSlotData(sel, &preview)) {
                MessageBox(GetHWnd(), _T("\u8BE5\u5B58\u6863\u69FD\u4E3A\u7A7A\u6216\u5DF2\u635F\u574F"), _T("\u8BFB\u6863"), MB_OK);
            }
            else if (PromptSaveLoadPassword(preview.username) && LoadGameFromSlot(sel)) {
                AddToRanking(currentUsername, playerLevel, reincarnationCycle);
                loaded = true;
                run = false;
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 1) run = false;
        Sleep(20);
    }
    isPaused = wp;
    ResetReturnKeyEdge();
    flushmessage(EX_KEY);
    return loaded;
}
int GetAllUsers(char userList[][20]) {
    FILE* f = fopen("users.dat", "rb"); if (!f) return 0;
    User u; int c = 0;
    while (fread(&u, sizeof(User), 1, f) && c < 100) strcpy(userList[c++], u.username);
    fclose(f); return c;
}
void DeleteUser(const char* username) {
    FILE* f = fopen("users.dat", "rb"); FILE* t = fopen("temp.dat", "wb");
    if (!f || !t) return;
    User u; while (fread(&u, sizeof(User), 1, f)) if (strcmp(u.username, username) != 0) fwrite(&u, sizeof(User), 1, t);
    fclose(f); fclose(t); remove("users.dat"); rename("temp.dat", "users.dat");
}
void ShowManageMenu() {
    char prevMusic[50];
    strcpy(prevMusic, currentMusic);
    TCHAR pw[30]; InputBox(pw, 30, _T("\u7BA1\u7406\u5458\u5BC6\u7801"), _T(""), NULL, 0, 0, true);
    char p[30]; WideCharToMultiByte(CP_ACP, 0, pw, -1, p, 30, NULL, NULL);
    if (strcmp(p, MANAGE_PASSWORD) != 0) {
        if (musicEnabled && prevMusic[0]) PlayMusicTrack(prevMusic);
        return;
    }
    PlayMusicTrack(MUSIC_MANAGE);
    char users[100][20]; int cnt = GetAllUsers(users), sel = 0;
    bool run = true;
    while (run) {
        cleardevice(); settextstyle(32, 0, _T("\u9ED1\u4F53")); settextcolor(YELLOW);
        outtextxy(200, 80, _T("\u7528\u6237\u7BA1\u7406"));
        for (int i = 0; i < cnt; i++) {
            settextcolor(i == sel ? LIGHTGREEN : WHITE);
            TCHAR n[30]; wsprintf(n, _T("%hs"), users[i]); outtextxy(250, 150 + i * 40, n);
        }
        FlushBatchDraw();
        if (GetAsyncKeyState(VK_UP) & 1) sel = (sel - 1 + cnt) % cnt;
        if (GetAsyncKeyState(VK_DOWN) & 1) sel = (sel + 1) % cnt;
        if (GetAsyncKeyState(VK_DELETE) & 1 && cnt > 0) { DeleteUser(users[sel]); cnt = GetAllUsers(users); }
        if (GetAsyncKeyState(VK_ESCAPE) & 1) run = false;
        MusicPollEvents();
        Sleep(20);
    }
    if (musicEnabled && prevMusic[0]) PlayMusicTrack(prevMusic);
    else PlayMusicTrack(MUSIC_LOGIN);
}
static void drawOpeningDialogBgBottomThird(IMAGE* img) {
    if (!img || img->getwidth() <= 0 || img->getheight() <= 0) return;
    putimageAlpha(0, DIALOG_Y, SCREEN_W, DIALOG_H, img, 0, 0);
}

static void drawOpeningDialogPanel(const DialogLine* dialog, int dialogCount, int currentLine,
    IMAGE* dialogBg, bool bgLoaded) {
    int dialogX = 0, dialogY = DIALOG_Y, dialogW = SCREEN_W, dialogH = DIALOG_H;

    setfillcolor(RGB(15, 12, 10));
    solidrectangle(0, 0, SCREEN_W, DIALOG_Y);

    if (bgLoaded && dialogBg && dialogBg->getwidth() > 0) {
        drawOpeningDialogBgBottomThird(dialogBg);
    }
    else {
        setfillcolor(RGB(15, 12, 10));
        solidrectangle(0, DIALOG_Y, SCREEN_W, SCREEN_H);
    }

    if (currentLine >= dialogCount) return;

    const DialogLine& line = dialog[currentLine];
    setbkmode(TRANSPARENT);

    int x = dialogX + DIALOG_TEXT_MARGIN_X;
    int y = dialogY + DIALOG_TEXT_MARGIN_Y;

    if (line.speaker && line.speaker[0]) {
        settextstyle(DIALOG_SPEAKER_FONT_SIZE, 0, L"\u5FAE\u8F6F\u96C5\u9ED1");
        settextcolor(DIALOG_SPEAKER_COLOR);
        outtextxy(x, y, line.speaker);
        y += DIALOG_LINE_HEIGHT;
    }

    settextstyle(DIALOG_FONT_SIZE, 0, L"\u5FAE\u8F6F\u96C5\u9ED1");
    settextcolor(DIALOG_TEXT_COLOR);
    const wchar_t* content = line.content;
    size_t pos = 0;
    size_t len = content ? wcslen(content) : 0;
    int maxWidth = dialogW - 2 * DIALOG_TEXT_MARGIN_X;
    while (content && pos < len) {
        int curWidth = 0;
        size_t end = pos;
        while (end < len) {
            wchar_t ch = content[end];
            int chWidth = (ch > 0xFF) ? DIALOG_CHAR_W_CJK : DIALOG_CHAR_W_ASC;
            if (curWidth + chWidth > maxWidth) break;
            curWidth += chWidth;
            end++;
        }
        if (end == pos) end = pos + 1;
        wchar_t lineText[256];
        size_t n = end - pos;
        if (n >= 255) n = 255;
        wcsncpy(lineText, content + pos, n);
        lineText[n] = L'\0';
        outtextxy(x, y, lineText);
        y += DIALOG_LINE_HEIGHT;
        pos = end;
        if (y + DIALOG_LINE_HEIGHT > dialogY + dialogH - DIALOG_TEXT_MARGIN_Y) break;
    }

    settextstyle(DIALOG_TIP_FONT_SIZE, 0, L"\u5FAE\u8F6F\u96C5\u9ED1");
    settextcolor(RGB(180, 180, 180));
    const wchar_t* tip = L"\u25BC \u70B9\u51FB\u7EE7\u7EED \u25BC";
    int tipW = textwidth(tip);
    outtextxy(dialogX + dialogW - tipW - 20, dialogY + dialogH - 25, tip);
}

struct AncientBookLine {
    const wchar_t* text;
    bool introStyle;
    bool gap;
};

static wchar_t g_ancientBookTextPool[ANCIENT_BOOK_MAX_LINES][ANCIENT_BOOK_LINE_CHARS];
static AncientBookLine g_ancientBookLines[ANCIENT_BOOK_MAX_LINES];
static int g_ancientBookLineCount = 0;
static bool g_ancientBookBuilt = false;

static const wchar_t* AncientBookPoolDup(const wchar_t* src, size_t len) {
    if (g_ancientBookLineCount >= ANCIENT_BOOK_MAX_LINES) return L"";
    wchar_t* dst = g_ancientBookTextPool[g_ancientBookLineCount];
    if (len >= ANCIENT_BOOK_LINE_CHARS) len = ANCIENT_BOOK_LINE_CHARS - 1;
    wcsncpy(dst, src, len);
    dst[len] = L'\0';
    return dst;
}

static void AncientBookLinesAppendGap() {
    if (g_ancientBookLineCount < ANCIENT_BOOK_MAX_LINES)
        g_ancientBookLines[g_ancientBookLineCount++] = { L"", false, true };
}

static void WrapTextToAncientBookLines(const wchar_t* text, bool introStyle, int maxWidth) {
    if (!text || !text[0]) {
        AncientBookLinesAppendGap();
        return;
    }
    size_t pos = 0;
    size_t len = wcslen(text);
    while (pos < len && g_ancientBookLineCount < ANCIENT_BOOK_MAX_LINES) {
        int curWidth = 0;
        size_t end = pos;
        while (end < len) {
            wchar_t ch = text[end];
            int chWidth = (ch > 0xFF) ? DIALOG_CHAR_W_CJK : DIALOG_CHAR_W_ASC;
            if (curWidth + chWidth > maxWidth) break;
            curWidth += chWidth;
            end++;
        }
        if (end == pos) end = pos + 1;
        const wchar_t* linePtr = AncientBookPoolDup(text + pos, end - pos);
        g_ancientBookLines[g_ancientBookLineCount++] = { linePtr, introStyle, false };
        pos = end;
    }
}

static void BuildAncientBookLinesOnce() {
    if (g_ancientBookBuilt) return;
    g_ancientBookBuilt = true;
    g_ancientBookLineCount = 0;
    const int maxWidth = SCREEN_W - 2 * ANCIENT_BOOK_MARGIN_X;
    const wchar_t* intro = L"\u4E66\u9875\u6CDB\u9EC4\u7834\u65E7\uFF0C\u8FB9\u89D2\u78E8\u635F\u4E25\u91CD\uFF0C\u5B57\u8FF9\u6DE1\u5374\u6E05\u6670\uFF0C\u4E0D\u77E5\u88AB\u591A\u5C11\u4EBA\u7FFB\u9605\u8FC7\u65E0\u6570\u6B21\uFF0C\u7EB8\u9762\u8426\u7ED5\u7740\u4E00\u4E1D\u5FAE\u5F31\u7684\u5149\u660E\u6C14\u606F\u3002";
    const wchar_t* paragraphs[] = {
        L"\u543E\u4E43\u8FC7\u5F80\u65C5\u4EBA\uFF0C\u7559\u6B64\u4E66\uFF0C\u4E88\u6BCF\u4E00\u4F4D\u4E8E\u6797\u95F4\u5C0F\u5C4B\u82CF\u9192\u7684\u526F\u5BA2\u3002",
        L"\u8FD9\u7247\u5929\u5730\u88AB\u6697\u5F71\u9B54\u6C14\u7B3C\u7F69\uFF0C\u9ED1\u6697\u86CF\u4F0F\u5927\u5730\uFF0C\u751F\u7075\u8499\u96BE\u3002\u4E16\u95F4\u552F\u4E00\u80FD\u523A\u7834\u9634\u973E\u3001\u7EC8\u7ED3\u707E\u60A3\u4E4B\u4EBA\uFF0C\u552F\u6709\u6267\u5251\u524D\u884C\u7684\u4F60\u3002",
        L"\u4F60\u4E8E\u6B64\u95F4\u82CF\u9192\uFF0C\u9057\u5FD8\u524D\u5C18\u8FC7\u5F80\uFF0C\u5FC3\u4E2D\u53EA\u5269\u552F\u4E00\u6267\u5FF5\u2014\u2014\u8E0F\u7834\u9ED1\u6697\uFF0C\u5E73\u606F\u7978\u4E71\u3002",
        L"\u521D\u9192\u65E0\u5175\u5203\u508D\u8EAB\uFF0C\u53EF\u4E8E\u6728\u5C4B\u70BC\u5236\u53F0\u6536\u96C6\u6750\u6599\uFF0C\u5408\u6210\u788E\u5CA9\u5DE8\u9550\u3002\u6B64\u9550\u53EF\u7834\u575A\u5CA9\u3001\u788E\u91CD\u7532\uFF0C\u4E3A\u4F60\u78C1\u5F00\u5C71\u5730\u9669\u8DEF\uFF0C\u662F\u95EF\u8361\u524D\u8DEF\u7684\u521D\u59CB\u6839\u57FA\u3002",
        L"\u4E3B\u5730\u56FE\u4E1C\u5357\u9685\uFF0C\u85CF\u6709\u4E00\u679A\u9752\u94DC\u6212\u6307\u3002\u5F97\u6B64\u6212\u8005\uFF0C\u53EF\u5F15\u7075\u529B\u5FA1\u5668\uFF0C\u89E3\u9501\u788E\u5CA9\u5DE8\u9550\u8FDC\u7A0B\u653B\u4F10\u4E4B\u80FD\uFF0C\u8FDC\u8FD1\u7686\u53EF\u5FA1\u654C\uFF0C\u8865\u8DB3\u8FD1\u6218\u77ED\u677F\u3002",
        L"\u5907\u597D\u5175\u5203\u3001\u5BFB\u5F97\u94DC\u6212\u3001\u4E60\u5F97\u8FDC\u653B\u4E4B\u6CD5\u540E\uFF0C\u4FBF\u53EF\u524D\u5F80\u9669\u5CED\u5C71\u5730\uFF0C\u51FB\u6E83\u76D8\u8E0D\u4E8E\u6B64\u7684\u5CA9\u7532\u5B88\u62A4\u8005\uFF0C\u83B7\u5F97\u94BB\u77F3\u5723\u94C0\u3002\u6B64\u94C0\u53EF\u9694\u7EDD\u4E16\u95F4\u5267\u6BD2\uFF0C\u662F\u7A7F\u884C\u6BD2\u57DF\u7684\u552F\u4E00\u4F9D\u4E1A\u3002",
        L"\u8EAB\u6279\u5723\u94C0\u6DF1\u5165\u5E7D\u6DF1\u68EE\u6797\uFF0C\u51FB\u8D25\u6BD2\u57DF\u9738\u4E3B\uFF0C\u4FBF\u80FD\u593A\u5F97\u4E24\u4EF6\u81F3\u5B9D\u2014\u2014\u65E0\u5C3D\u4E4B\u5251\u4E0E\u9547\u7075\u6212\u3002",
        L"\u65E0\u5C3D\u4E4B\u5251\u53EF\u65A9\u4E00\u5207\u6697\u5F71\u90AA\u9B54\uFF0C\u9547\u7075\u6212\u53EF\u62B5\u5FA1\u6697\u9ED1\u9B54\u6C14\u4FB5\u8680\u3002",
        L"\u96C6\u9F50\u5168\u90E8\u81F3\u5B9D\uFF0C\u4FBF\u53EF\u8E0F\u5411\u6781\u5BD2\u51B0\u5DDD\uFF0C\u5BFB\u5F97\u9ED1\u6697\u6E90\u5934\uFF0C\u76F4\u9762\u6697\u5F71\u4E4B\u4E3B\u3002",
        L"\u65A9\u9664\u9ED1\u6697\uFF0C\u7EC8\u7ED3\u8BC5\u5492\uFF0C\u4FBF\u662F\u4F60\u552F\u4E00\u7684\u4F7F\u547D\u3002",
        L"\u613F\u5251\u610F\u957F\u5B58\uFF0C\u5149\u660E\u4E0D\u606F\uFF0C\u524D\u8DEF\u867D\u6697\uFF0C\u7EC8\u53EF\u7834\u6653\u3002",
    };
    WrapTextToAncientBookLines(intro, true, maxWidth);
    AncientBookLinesAppendGap();
    for (int pi = 0; pi < (int)(sizeof(paragraphs) / sizeof(paragraphs[0])); pi++) {
        WrapTextToAncientBookLines(paragraphs[pi], false, maxWidth);
        AncientBookLinesAppendGap();
    }
    if (g_ancientBookLineCount > 0 && g_ancientBookLines[g_ancientBookLineCount - 1].gap)
        g_ancientBookLineCount--;
}

static int GetAncientBookLineCount() {
    BuildAncientBookLinesOnce();
    return g_ancientBookLineCount;
}

static void drawAncientBook() {
    setfillcolor(BLACK);
    solidrectangle(0, 0, SCREEN_W, SCREEN_H);
    setbkmode(TRANSPARENT);

    settextstyle(ANCIENT_BOOK_TITLE_FONT_SIZE, 0, L"\u5FAE\u8F6F\u96C5\u9ED1");
    settextcolor(RGB(200, 170, 90));
    const wchar_t* title = L"\u53E4\u8001\u6587\u4E66";
    int titleW = textwidth(title);
    outtextxy((SCREEN_W - titleW) / 2, 24, title);

    int lineCount = GetAncientBookLineCount();
    int yStart = ANCIENT_BOOK_MARGIN_Y;
    int bottomReserve = 44;
    int visibleH = SCREEN_H - yStart - bottomReserve;
    int maxVisible = visibleH / ANCIENT_BOOK_LINE_HEIGHT;
    int maxScroll = lineCount - maxVisible;
    if (maxScroll < 0) maxScroll = 0;
    if (g_ancientBookScroll > maxScroll) g_ancientBookScroll = maxScroll;

    int x = ANCIENT_BOOK_MARGIN_X;
    int y = yStart;
    for (int i = 0; i < maxVisible; i++) {
        int idx = g_ancientBookScroll + i;
        if (idx >= lineCount) break;
        const AncientBookLine& ln = g_ancientBookLines[idx];
        if (ln.gap) {
            y += ANCIENT_BOOK_LINE_HEIGHT / 2;
            continue;
        }
        if (ln.introStyle) {
            settextstyle(ANCIENT_BOOK_INTRO_FONT_SIZE, 0, L"\u5FAE\u8F6F\u96C5\u9ED1");
            settextcolor(ANCIENT_BOOK_INTRO_COLOR);
        }
        else {
            settextstyle(ANCIENT_BOOK_FONT_SIZE, 0, L"\u5FAE\u8F6F\u96C5\u9ED1");
            settextcolor(ANCIENT_BOOK_TEXT_COLOR);
        }
        outtextxy(x, y, ln.text);
        y += ANCIENT_BOOK_LINE_HEIGHT;
    }

    settextstyle(18, 0, L"\u5FAE\u8F6F\u96C5\u9ED1");
    settextcolor(RGB(120, 120, 110));
    const wchar_t* tip = L"\u2191\u2193 \u7FFB\u9875  |  G / ESC \u5173\u95ED";
    int tipW = textwidth(tip);
    outtextxy((SCREEN_W - tipW) / 2, SCREEN_H - 32, tip);
}

static void RunAncientBookIntro() {
    showAncientBook = true;
    g_ancientBookScroll = 0;
    flushmessage(EX_MOUSE | EX_KEY);
    while (showAncientBook) {
        cleardevice();
        drawAncientBook();
        FlushBatchDraw();

        int lineCount = GetAncientBookLineCount();
        int maxVisible = (SCREEN_H - ANCIENT_BOOK_MARGIN_Y - 44) / ANCIENT_BOOK_LINE_HEIGHT;
        int maxScroll = lineCount - maxVisible;
        if (maxScroll < 0) maxScroll = 0;
        if (GetAsyncKeyState(VK_UP) & 1) g_ancientBookScroll = max(0, g_ancientBookScroll - 1);
        if (GetAsyncKeyState(VK_DOWN) & 1) g_ancientBookScroll = min(maxScroll, g_ancientBookScroll + 1);
        if (GetAsyncKeyState(VK_PRIOR) & 1) g_ancientBookScroll = max(0, g_ancientBookScroll - maxVisible);
        if (GetAsyncKeyState(VK_NEXT) & 1) g_ancientBookScroll = min(maxScroll, g_ancientBookScroll + maxVisible);
        if (GetAsyncKeyState('G') & 1 || GetAsyncKeyState(VK_ESCAPE) & 1) {
            showAncientBook = false;
            g_ancientBookScroll = 0;
        }
        Sleep(16);
    }
    flushmessage(EX_MOUSE | EX_KEY);
    Sleep(200);
}

static bool RunDialogSequence(const DialogLine* dialog, int dialogCount, bool allowEscapeCancel) {
    IMAGE dialogBg;
    bool bgLoaded = false;
    const TCHAR* bgPaths[] = { _T("pic/dialog_bg.png"), _T("pic\\dialog_bg.png"), _T("dialog_bg.png") };
    for (int i = 0; i < 3 && !bgLoaded; i++) {
        if (loadimage(&dialogBg, bgPaths[i]) == 0 && dialogBg.getwidth() > 0)
            bgLoaded = true;
    }
    int currentLine = 0;
    flushmessage(EX_MOUSE | EX_KEY);

    while (currentLine < dialogCount) {
        cleardevice();
        drawOpeningDialogPanel(dialog, dialogCount, currentLine, &dialogBg, bgLoaded);
        FlushBatchDraw();

        bool advanced = false;
        while (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) { advanced = true; break; }
        }
        if (allowEscapeCancel && (GetAsyncKeyState(VK_ESCAPE) & 1)) {
            flushmessage(EX_MOUSE | EX_KEY);
            return false;
        }
        if (!advanced && (GetAsyncKeyState(VK_SPACE) & 1 || GetAsyncKeyState(VK_RETURN) & 1))
            advanced = true;
        if (advanced) {
            currentLine++;
            Sleep(100);
        }
        MusicPollEvents();
        Sleep(16);
    }
    flushmessage(EX_MOUSE | EX_KEY);
    return true;
}

bool RunOpeningDialog() {
    PlayMusicTrack(MUSIC_MANAGE);
    static const DialogLine dialog[] = {
        { L"", L"\u610F\u8BC6\u50CF\u662F\u6C89\u5728\u4E00\u7247\u6E29\u6D6E\u7684\u8FF7\u96FE\u91CC\uFF0C\u6D51\u6D51\u5669\u5669\uFF0C\u6CA1\u6709\u8D77\u6B62\uFF0C\u6CA1\u6709\u65F6\u95F4\u6982\u5FF5\u3002\u8033\u8FB9\u9759\u5F97\u5F88\uFF0C\u53EA\u6709\u7A97\u5916\u665A\u98CE\u7A7F\u8FC7\u679D\u53F6\uFF0C\u9001\u6765\u6301\u7EED\u4E0D\u65AD\u7684\u6C99\u6C99\u8F7B\u54CD\uFF0C\u6E29\u67D4\u5374\u964C\u751F\u3002" },
        { L"", L"\u6211\u731B\u5730\u56DE\u795E\uFF0C\u6DF7\u6C8A\u7684\u610F\u8BC6\u8E74\u7136\u6E05\u9192\uFF0C\u89C6\u7EBF\u7F13\u7F13\u805A\u7126\uFF0C\u6620\u5165\u773C\u5E18\u7684\u662F\u8001\u65E7\u5374\u5E72\u51C0\u7684\u6728\u8D28\u5C4B\u9876\uFF0C\u9F3B\u5C16\u7F2B\u7ED5\u7740\u6DE1\u6DE1\u7684\u6728\u5934\u6E05\u9999\u4E0E\u8349\u6728\u6E7F\u6C14\u3002" },
        { L"\u3010\u6211\u3011", L"\u2026\u2026\u8FD9\u91CC\u662F\u54EA\u91CC\uFF1F" },
        { L"", L"\u6211\u7F13\u7F13\u62AC\u624B\uFF0C\u8F7B\u8F7B\u6309\u5728\u53D1\u80C0\u7684\u592A\u9633\u7A74\u4E0A\uFF0C\u4E00\u9635\u7EC6\u788E\u7684\u949D\u611F\u987A\u7740\u6307\u5C16\u832B\u5EF6\u5F00\u6765\u3002\u8111\u6D77\u91CC\u7A7A\u7A7A\u8361\u8361\uFF0C\u4E00\u7247\u7EAF\u767D\uFF0C\u6CA1\u6709\u8FC7\u5F80\u7684\u8BB0\u5FC6\uFF0C\u6CA1\u6709\u8EAB\u4EFD\u7684\u7B54\u6848\uFF0C\u552F\u72EC\u5269\u4E0B\u4E00\u9053\u523B\u5728\u5FC3\u5E95\u3001\u6325\u4E4B\u4E0D\u53BB\u7684\u6A21\u7CCA\u6267\u5FF5\u3002" },
        { L"", L"\u5F80\u524D\u8D70\u3002" },
        { L"", L"\u53BB\u627E\u5230\u4EC0\u4E48\u3002" },
        { L"", L"\u53BB\u7EC8\u7ED3\u4EC0\u4E48\u3002" },
        { L"\u3010\u6211\u3011", L"\u6211\u2026\u2026\u662F\u8C01\uFF1F" },
        { L"", L"\u6211\u6491\u8D77\u8EAB\u5B50\uFF0C\u6162\u6162\u5750\u8D77\u8EAB\uFF0C\u4F4E\u5934\u770B\u5411\u81EA\u5DF1\u7684\u53CC\u624B\u3002\u6307\u5C16\u7EC6\u957F\uFF0C\u5374\u8986\u7740\u4E00\u5C42\u8584\u8584\u7684\u786C\u8307\uFF0C\u638C\u5FC3\u8FD8\u6709\u4E00\u9053\u6D45\u6D45\u7684\u3001\u65E9\u5DF2\u6108\u5408\u7684\u7EC6\u5C0F\u75A4\u75D5\u3002" },
        { L"", L"\u6307\u5C16\u4E0B\u610F\u8BC6\u870F\u7F29\uFF0C\u5FC3\u5E95\u83AB\u540D\u6D8C\u4E0A\u4E00\u9635\u719F\u6089\u7684\u89E6\u611F\uFF0C\u50CF\u662F\u957F\u4E45\u63E1\u7740\u67D0\u6837\u5175\u5668\uFF0C\u53EF\u6211\u5B8C\u5168\u60F3\u4E0D\u8D77\u90A3\u662F\u4EC0\u4E48\uFF0C\u4E5F\u60F3\u4E0D\u8D77\u81EA\u5DF1\u66FE\u505A\u8FC7\u4EC0\u4E48\u3002" },
        { L"\u3010\u6211\u3011", L"\u4E3A\u4EC0\u4E48\u6211\u7684\u624B\u4E0A\u4F1A\u6709\u8307\u2026\u2026\u4E3A\u4EC0\u4E48\u4E00\u60F3\u8D77\u63E1\u5251\u7684\u611F\u89C9\uFF0C\u5FC3\u91CC\u5C31\u4F1A\u83AB\u540D\u53D1\u614C\u3002" },
        { L"", L"\u6728\u5C4B\u7684\u7A97\u6842\u88AB\u98CE\u5439\u5F97\u8F7B\u6643\uFF0C\u6797\u95F4\u7684\u6E05\u98CE\u88F9\u642D\u7740\u8349\u6728\u6E05\u9999\u5439\u5165\u5C4B\u5185\uFF0C\u629A\u5E73\u4E86\u4E9B\u8BB8\u5FC3\u5E95\u7684\u832B\u7136\u3002\u8111\u6D77\u91CC\u7684\u7A7A\u767D\u4F9D\u65E7\u6CA1\u6709\u586B\u8865\uFF0C\u53EF\u90A3\u80A1\u62D7\u52B2\u7684\u6267\u5FF5\uFF0C\u5374\u8D8A\u6765\u8D8A\u6E05\u6670\u3001\u8D8A\u6765\u8D8A\u575A\u5B9A\u3002" },
        { L"\u3010\u6211\u3011", L"\u6211\u597D\u50CF\u2026\u2026\u6709\u5FC5\u987B\u8981\u53BB\u5B8C\u6210\u7684\u4E8B\u3002" },
        { L"", L"\u6211\u6491\u7740\u5E8A\u6CBF\u7AD9\u8D77\u8EAB\uFF0C\u73AF\u987E\u8FD9\u95F4\u7B80\u964B\u7684\u6797\u95F4\u5C0F\u5C4B\u3002\u5C4B\u5185\u6446\u653E\u7740\u4E00\u53F0\u53E4\u6734\u7684\u70BC\u5236\u53F0\uFF0C\u684C\u9762\u5E72\u51C0\u6574\u6D01\uFF0C\u50CF\u662F\u65F6\u5E38\u88AB\u4EBA\u4F7F\u7528\u3002\u5899\u89D2\u7684\u4F4D\u7F6E\uFF0C\u9759\u9759\u9760\u7740\u4E00\u628A\u7C97\u7369\u539A\u91CD\u7684\u788E\u77F3\u5DE8\u956C\uFF0C\u662F\u8FD9\u95F4\u5C0F\u5C4B\u5185\u552F\u4E00\u7684\u5175\u5668\u3002" },
        { L"", L"\u6728\u684C\u4E00\u89D2\uFF0C\u5E73\u653E\u7740\u4E00\u672C\u6CDB\u9EC4\u8001\u65E7\u7684\u6587\u4E66\uFF0C\u8FB9\u89D2\u7834\u635F\u4E0D\u582A\uFF0C\u50CF\u662F\u5386\u7ECF\u4E86\u65E0\u6570\u5C81\u6708\u7684\u7FFB\u9605\u4E0E\u6478\u68C9\u3002" },
        { L"\u3010\u6211\u3011", L"\u8FD9\u91CC\u7684\u4E00\u5207\u2026\u2026\u90FD\u597D\u964C\u751F\u3002" },
        { L"", L"\u98CE\u518D\u6B21\u7A7F\u8FC7\u6797\u95F4\uFF0C\u6811\u53F6\u7B5B\u7B5B\u4F5C\u54CD\uFF0C\u50CF\u662F\u7EC6\u788E\u7684\u4F4E\u8BED\u5728\u8033\u8FB9\u7F2E\u7ED5\uFF0C\u6A21\u7CCA\u4E0D\u6E05\uFF0C\u6293\u4E0D\u4F4F\u5206\u6BEB\u5185\u5BB9\u3002\u8FC7\u5F80\u7684\u8BB0\u5FC6\u4F9D\u65E7\u4E00\u7247\u7A7A\u767D\uFF0C\u53EF\u524D\u884C\u7684\u5FF5\u5934\uFF0C\u5374\u6096\u53D1\u575A\u5B9A\u3002" },
        { L"\u3010\u6211\u3011", L"\u4E0D\u7BA1\u4E86\u3002\u5148\u5F80\u524D\u8D70\u5427\u3002" },
        { L"", L"\u6211\u62AC\u624B\u62FF\u8D77\u684C\u4E0A\u7684\u53E4\u8001\u6587\u4E66\uFF0C\u53C8\u63E1\u7D27\u4E86\u5899\u89D2\u90A3\u628A\u6C89\u7538\u7538\u7684\u94C1\u5251\u3002\u672A\u77E5\u7684\u524D\u8DEF\u85CF\u6EE1\u8FF7\u96FE\uFF0C\u4F46\u5FC3\u5E95\u7684\u6267\u5FF5\uFF0C\u5DF2\u7136\u6307\u5F15\u7740\u6211\uFF0C\u8E0F\u51FA\u7B2C\u4E00\u6B65\u3002" }
    };
    const int dialogCount = (int)(sizeof(dialog) / sizeof(dialog[0]));
    return RunDialogSequence(dialog, dialogCount, false);
}

static bool RunIceBossPreFightDialog() {
    static const DialogLine dialog[] = {
        { L"", L"\u51B0\u5DDD\u5BD2\u98CE\u51DB\u51BD\uFF0C\u788E\u51B0\u968F\u7740\u72C2\u98CE\u8086\u610F\u98DE\u821E\uFF0C\u523A\u9AA8\u7684\u9B54\u6C14\u7B3C\u7F69\u6574\u7247\u51BB\u571F\u3002\u6211\u6307\u5C16\u7684\u9547\u7075\u6212\u5FAE\u5FAE\u53D1\u70EB\uFF0C\u8270\u96BE\u62B5\u5FA1\u7740\u56DB\u5468\u6D53\u7A20\u7684\u9ED1\u6697\u6C14\u606F\uFF0C\u624B\u4E2D\u65E0\u5C3D\u4E4B\u5251\u7684\u5BD2\u5149\uFF0C\u52C9\u5F3A\u62E8\u5F00\u773C\u524D\u5C42\u5C42\u9ED1\u96FE\u3002" },
        { L"", L"\u7A7F\u8FC7\u6B7B\u5BC2\u7684\u51B0\u5C01\u6797\u5730\uFF0C\u4E00\u5EA7\u5B8F\u4F1F\u7684\u7384\u51B0\u738B\u5EA7\u77D7\u7ACB\u5728\u51B0\u5DDD\u6700\u6DF1\u5904\u3002\u4E00\u9053\u9AD8\u5927\u9ED1\u5F71\u9759\u5750\u5176\u4E0A\uFF0C\u5468\u8EAB\u9ED1\u96FE\u539A\u91CD\u5982\u5E55\uFF0C\u5B8C\u5168\u906E\u853D\u4E86\u9762\u5BB9\uFF0C\u552F\u6709\u6307\u5C16\u4E00\u679A\u6F06\u9ED1\u7684\u6307\u73AF\uFF0C\u5728\u5E7D\u6697\u4E4B\u4E2D\u9759\u9759\u6CDB\u7740\u51B7\u51BD\u6697\u5149\u2014\u2014\u90A3\u662F\u65E0\u5C3D\u4E4B\u6212\u3002" },
        { L"\u3010\u6211\u3011", L"\u810A\u80CC\u7D27\u7EF7\uFF0C\u63E1\u7D27\u5251\u67C4\uFF0C\u773C\u795E\u575A\u5B9A\u3002" },
        { L"\u3010\u6211\u3011", L"\u6697\u5F71\u4E4B\u4E3B\u3002\u6211\u8E0F\u8FC7\u5C71\u5730\u3001\u7A7F\u8D8A\u6BD2\u6797\uFF0C\u96C6\u9F50\u6240\u6709\u81F3\u5B9D\u6765\u5230\u6B64\u5730\u3002\u4ECA\u65E5\uFF0C\u6211\u8981\u5F7B\u5E95\u7EC8\u7ED3\u8FD9\u7247\u4E16\u95F4\u7684\u9ED1\u6697\u8BC5\u5492\u3002" },
        { L"", L"\u738B\u5EA7\u4E0A\u7684\u9ED1\u5F71\u7F13\u7F13\u524D\u503E\uFF0C\u9ED1\u96FE\u5FAE\u5FAE\u6563\u5F00\u4E00\u7EBF\uFF0C\u4E00\u9053\u4F4E\u6C89\u6C99\u54D1\u3001\u9971\u7ECF\u5C81\u6708\u6CA7\u6851\u7684\u58F0\u97F3\u7A7F\u900F\u98CE\u96EA\u3002" },
        { L"\u3010\u6697\u5F71\u4E4B\u4E3B\u3011", L"\u53C8\u4E00\u4F4D\u8D70\u5B8C\u8FD9\u6761\u8DEF\u7684\u5251\u5BA2\u2026\u2026\u6BCF\u4E00\u8F6E\uFF0C\u90FD\u662F\u540C\u6837\u7684\u8A93\u8A00\uFF0C\u540C\u6837\u7684\u5929\u771F\u3002" },
        { L"\u3010\u6211\u3011", L"\u65E0\u8BBA\u4F60\u7ECF\u5386\u8FC7\u4EC0\u4E48\uFF0C\u6211\u90FD\u4F1A\u65A9\u65AD\u9ED1\u6697\uFF0C\u7ED3\u675F\u8FD9\u573A\u707E\u7978\u3002" },
        { L"\u3010\u6697\u5F71\u4E4B\u4E3B\u3011", L"\u4F60\u4EE5\u4E3A\u524D\u884C\u5373\u662F\u5149\u660E\uFF0C\u4F60\u4EE5\u4E3A\u80DC\u5229\u5373\u662F\u89E3\u8131\u3002\u53EF\u60DC\u2026\u2026\u8FD9\u7247\u51B0\u5DDD\uFF0C\u4ECE\u6765\u6CA1\u6709\u771F\u6B63\u7684\u80DC\u5229\u8005\u3002" },
        { L"\u3010\u6211\u3011", L"\u6211\u4E0D\u4FE1\uFF01\u6211\u7684\u5251\uFF0C\u8DB3\u4EE5\u5288\u5F00\u6240\u6709\u865A\u5984\uFF01" },
        { L"\u3010\u6697\u5F71\u4E4B\u4E3B\u3011", L"\u90A3\u5C31\u8BA9\u6211\u770B\u770B\u3002\u8FD9\u4E00\u6B21\u7684\u4F60\uFF0C\u80FD\u4E0D\u80FD\u6253\u7834\u8FD9\u4EFD\u5F80\u590D\u7684\u5BBF\u547D\u3002" },
        { L"", L"\u9ED1\u96FE\u66B4\u6DA8\uFF0C\u6218\u573A\u77AC\u95F4\u5F00\u542F\uFF0C\u51B3\u6218\u4E00\u89E6\u5373\u53D1\u3002" }
    };
    const int dialogCount = (int)(sizeof(dialog) / sizeof(dialog[0]));
    return RunDialogSequence(dialog, dialogCount, false);
}

static bool RunIceBossMirrorRevealDialog() {
    static const DialogLine dialog[] = {
        { L"", L"\u7384\u51B0\u738B\u5EA7\u5728\u5251\u5149\u4E2D\u8F70\u7136\u5D29\u89E3\uFF0C\u5BD2\u98CE\u5377\u8D77\u6B8B\u7559\u7684\u51B0\u5C18\u3002\u90A3\u9053\u9AD1\u5F71\u8EA9\u7AA1\u7740\u5012\u4E0B\uFF0C\u8EAB\u4F53\u5316\u4F5C\u65E0\u6570\u51B0\u6676\u6563\u5165\u98CE\u96EA\u3002" },
        { L"", L"\u7136\u800C\u738B\u5EA7\u4E2D\u592E\uFF0C\u9ED1\u96FE\u518D\u6B21\u7FFB\u6D8C\u3002\u4EBA\u5F62\u4ECE\u96FE\u4E2D\u751F\u51FA\uFF0C\u8F6E\u5ED3\u9010\u6E10\u4E0E\u6211\u76F8\u540C\u2014\u2014\u76F8\u540C\u7684\u8863\u88B9\u3001\u6301\u5251\u7684\u59FF\u6001\uFF0C\u8FDE\u9547\u7075\u6212\u7684\u5FAE\u5149\u90FD\u4E00\u6A21\u4E00\u6837\u3002" },
        { L"\u3010\u6211\u3011", L"\u600E\u4E48\u4F1A\u2026\u2026\u6697\u5F71\u4E4B\u4E3B\u4E0D\u662F\u5DF2\u7ECF\u2026\u2026" },
        { L"\u3010\u955C\u4E2D\u4E4B\u5F71\u3011", L"\u4F60\u4EE5\u4E3A\u6253\u8D25\u7684\uFF0C\u5C31\u662F\u5168\u90E8\u5417\uFF1F" },
        { L"\u3010\u955C\u4E2D\u4E4B\u5F71\u3011", L"\u738B\u5EA7\u4E0A\u7684\u53EA\u662F\u906E\u9762\u7684\u5E01\u5A01\u3002\u771F\u6B63\u7684\u6697\u5F71\u4E4B\u4E3B\uFF0C\u4E00\u76F4\u85CF\u5728\u4F60\u7684\u955C\u50CF\u91CC\u3002" },
        { L"\u3010\u6211\u3011", L"\u4F60\u662F\u2026\u2026\u8C01\uFF1F" },
        { L"\u3010\u955C\u4E2D\u4E4B\u5F71\u3011", L"\u662F\u6240\u6709\u4EE5\u4E3A\u81EA\u5DF1\u8D70\u5230\u7EC8\u70B9\u7684\u5251\u5BA2\u3002\u662F\u6BCF\u4E00\u4E2A\u5728\u51B0\u5DDD\u80DC\u5229\u5374\u672A\u8D70\u51FA\u8F6E\u56DE\u7684\u4F60\u3002" },
        { L"", L"\u5B83\u62AC\u5251\u6307\u5411\u6211\uFF0C\u5251\u950B\u4E0A\u6CA1\u6709\u4E00\u4E1D\u6E29\u5EA6\uFF0C\u5374\u6BD4\u7384\u51B0\u8FD8\u8981\u51B7\u3002\u98CE\u96EA\u4F3C\u4E4E\u505C\u6B62\uFF0C\u6574\u7247\u51B0\u5DDD\u53EA\u5269\u4E0B\u547C\u5438\u4E0E\u5251\u9E23\u3002" },
        { L"\u3010\u6211\u3011", L"\u6697\u5F71\u9732\u51FA\u672C\u4F53\u2026\u2026\u8981\u51FB\u8D25\u7684\u662F\u8FD9\u4E2A\u201C\u6211\u201D\uFF1F" },
        { L"\u3010\u955C\u4E2D\u4E4B\u5F71\u3011", L"\u53EA\u6709\u51FB\u7834\u8FD9\u9762\u955C\u5B50\uFF0C\u624D\u80FD\u8E0F\u4E0A\u4E0B\u4E00\u8F6E\u56DE\u3002\u5426\u5219\uFF0C\u4F60\u4E5F\u5C06\u6C38\u8FDC\u7559\u5728\u8FD9\u91CC\u3002" },
        { L"", L"\u9ED1\u96FE\u6563\u5F00\uFF0C\u955C\u4E2D\u4E4B\u4EBA\u8E0F\u524D\u800C\u4E0A\u3002\u51B0\u5DDD\u6DF1\u5904\uFF0C\u771F\u6B63\u7684\u51B3\u6218\u624D\u521A\u521A\u5F00\u59CB\u3002" }
    };
    const int dialogCount = (int)(sizeof(dialog) / sizeof(dialog[0]));
    return RunDialogSequence(dialog, dialogCount, false);
}

static bool RunReincarnationEndingDialog() {
    PlayMusicTrack(MUSIC_FINAL);
    static const DialogLine dialog[] = {
        { L"", L"\u6211\u538B\u4E0B\u5FC3\u5E95\u7684\u9707\u64BC\u4E0E\u614C\u4E71\uFF0C\u54AC\u7D27\u7259\u5173\u7A33\u4F4F\u5FC3\u795E\uFF0C\u51ED\u7740\u6700\u540E\u7684\u6267\u5FF5\u594B\u529B\u65A9\u51FA\u51B3\u80DC\u4E00\u51FB\u3002" },
        { L"", L"\u5251\u5149\u7A7F\u900F\u9ED1\u6697\u6838\u5FC3\uFF0C\u6697\u5F71\u4E4B\u4E3B\u7684\u8EAB\u8EAF\u7F13\u7F13\u865A\u5316\u3001\u900F\u660E\uFF0C\u6700\u7EC8\u6D88\u878D\u5728\u51DB\u51BD\u7684\u98CE\u96EA\u4E4B\u4E2D\u3002" },
        { L"", L"\u98CE\u96EA\u9AA4\u505C\uFF0C\u5929\u5730\u5BC2\u9759\u3002\u552F\u72EC\u90A3\u679A\u6F06\u9ED1\u6DF1\u9083\u7684\u65E0\u5C3D\u4E4B\u6212\uFF0C\u60AC\u6D6E\u5728\u534A\u7A7A\uFF0C\u9AA4\u7136\u7206\u53D1\u51FA\u6DD8\u5929\u9ED1\u8292\uFF0C\u4EE5\u65E0\u6CD5\u6297\u62D2\u7684\u901F\u5EA6\u671D\u6211\u98DE\u6251\u800C\u6765\uFF0C\u6B7B\u6B7B\u9501\u5728\u6211\u7684\u6307\u5C16\uFF0C\u624E\u6839\u8840\u8089\uFF0C\u518D\u4E5F\u65E0\u6CD5\u6323\u8131\u3002" },
        { L"\u3010\u6211\u3011", L"\uFF08\u60CA\u614C\u6323\u624E\uFF0C\u62FC\u547D\u60F3\u8981\u6458\u4E0B\uFF09" },
        { L"\u3010\u6211\u3011", L"\u7B49\u7B49\uFF01\u8FD9\u662F\u4EC0\u4E48\u4E1C\u897F\uFF1F\u5FEB\u653E\u5F00\u6211\uFF01" },
        { L"", L"\u523A\u9AA8\u9738\u9053\u7684\u9ED1\u6697\u529B\u91CF\u77AC\u95F4\u541E\u6CA1\u81EA\u8EAB\u6240\u6709\u62B5\u5FA1\u5FAE\u5149\uFF0C\u987A\u7740\u6307\u5C16\u75AF\u72C2\u4FB5\u5165\u56DB\u80A2\u767E\u9AB8\uFF0C\u610F\u8BC6\u88AB\u4E0D\u65AD\u6495\u626F\u3001\u6D78\u67D3\u3002\u9ED1\u96FE\u987A\u7740\u8EAB\u4F53\u8513\u5EF6\uFF0C\u6211\u7684\u5723\u94E0\u6E10\u6E10\u53D1\u9ED1\uFF0C\u624B\u4E2D\u795E\u5251\u7F20\u6EE1\u5E7D\u6697\u9B54\u6C14\u3002" },
        { L"\u3010\u6211\u3011", L"\u6211\u660E\u660E\u8D62\u4E86\u2026\u2026\u6211\u660E\u660E\u7EC8\u7ED3\u4E86\u9ED1\u6697\u2026\u2026" },
        { L"\u3010\u6211\u3011", L"\u4E3A\u4EC0\u4E48\u6211\u4F1A\u88AB\u9B54\u6C14\u541E\u566C\u2026\u2026\uFF1F" },
        { L"", L"\u9ED1\u6697\u4FB5\u8680\u6DF1\u5904\uFF0C\u8FC7\u5F80\u6240\u6709\u788E\u7247\u77AC\u95F4\u4E32\u8054\uFF0C\u6211\u7EC8\u4E8E\u5F7B\u5E95\u6D1E\u6089\u4E86\u8FD9\u573A\u8F6E\u56DE\u7684\u5168\u90E8\u771F\u76F8\u3002" },
        { L"\u3010\u6211\u3011", L"\u6211\u61C2\u4E86\u2026\u2026\u7EC8\u4E8E\u61C2\u4E86\u2026\u2026\u90A3\u4E9B\u548C\u6211\u88C5\u5907\u4E00\u6837\u7684\u5251\u5BA2\u2026\u2026\u90A3\u4E9B\u91CD\u590D\u7684\u65C5\u9014\u2026\u2026\u6839\u672C\u4E0D\u662F\u522B\u4EBA\u3002" },
        { L"\u3010\u6211\u3011", L"\u6BCF\u4E00\u4E2A\u6697\u5F71\u4E4B\u4E3B\uFF0C\u90FD\u662F\u6218\u80DC\u9ED1\u6697\u540E\u7684\u2026\u2026\u6211\u81EA\u5DF1\u3002" },
        { L"\u3010\u6211\u3011", L"\u65E0\u5C3D\u4E4B\u6212\u2026\u2026\u6839\u672C\u4E0D\u662F\u7528\u6765\u88AB\u6253\u8D25\u7684\u8BC5\u5492\u9053\u5177\u3002\u5B83\u662F\u7528\u6765\u4F20\u627F\u5BBF\u547D\u7684\u67B7\u9501\u3002\u6218\u80DC\u6697\u5F71\u4E4B\u4E3B\u7684\u4EBA\uFF0C\u5C31\u4F1A\u88AB\u6212\u6307\u9644\u8EAB\uFF0C\u63A5\u66FF\u4ED6\u7684\u4F4D\u7F6E\uFF0C\u9A7B\u5B88\u51B0\u5DDD\uFF0C\u6210\u4E3A\u4E0B\u4E00\u4E2A\u9ED1\u6697\u3002" },
        { L"\u3010\u6211\u3011", L"\u6211\u4EE5\u4E3A\u6211\u5728\u6253\u7834\u8F6E\u56DE\u2026\u2026\u539F\u6765\u6211\u62FC\u5C3D\u5168\u529B\u7684\u80DC\u5229\uFF0C\u53EA\u662F\u5728\u5EF6\u7EED\u8F6E\u56DE\u3002" },
        { L"", L"\u6700\u540E\u4E00\u7F15\u5C5E\u4E8E\u5251\u5BA2\u7684\u5149\u660E\u610F\u8BC6\u5F7B\u5E95\u6C89\u6CA6\u3002" },
        { L"", L"\u51B0\u5DDD\u5BD2\u98CE\u91CD\u65B0\u547C\u5578\u800C\u8D77\uFF0C\u7384\u51B0\u738B\u5EA7\u4E4B\u4E0A\uFF0C\u5168\u65B0\u7684\u6697\u5F71\u4E4B\u4E3B\u7F13\u7F13\u843D\u5EA7\u3002" },
        { L"", L"\u65E0\u5C3D\u8F6E\u56DE\uFF0C\u6084\u7136\u91CD\u542F\u3002" }
    };
    const int dialogCount = (int)(sizeof(dialog) / sizeof(dialog[0]));
    return RunDialogSequence(dialog, dialogCount, false);
}

bool login_menu() {
    loadimage(&imgLoginBg, _T("pic/login.png"), SCREEN_W, SCREEN_H);
    LoadRanking();
    PlayMusicTrack(MUSIC_LOGIN);
    struct Btn { int x, y, w, h, act; const char* txt; };
    Btn btns[] = {
        {SCREEN_W / 2 - 100,200,200,40,1,"1.LOGIN"},
        {SCREEN_W / 2 - 100,250,200,40,2,"2.REGISTER"},
        {SCREEN_W / 2 - 100,300,200,40,3,"3.LOAD"},
        {SCREEN_W / 2 - 100,350,200,40,4,"4.RANK"},
        {SCREEN_W / 2 - 100,400,200,40,5,"5.MANAGE"},
        {SCREEN_W / 2 - 100,450,200,40,6,"6.EXIT"},
    };
    int mode = 0;
    while (true) {
        cleardevice();
        if (imgLoginBg.getwidth() > 0) putimage(0, 0, &imgLoginBg);
        else { setbkcolor(RGB(30, 30, 60)); cleardevice(); }
        settextstyle(32, 0, _T("\u9ED1\u4F53")); settextcolor(YELLOW);
        outtextxy(SCREEN_W / 2 - 100, 120, mode == 0 ? _T("LOGIN SYSTEM") : (mode == 1 ? _T("LOGIN") : _T("REGISTER")));
        if (mode == 0) {
            settextstyle(22, 0, _T("\u9ED1\u4F53"));
            POINT pt; GetCursorPos(&pt); ScreenToClient(GetHWnd(), &pt);
            for (int i = 0; i < 6; i++) {
                bool hov = pt.x >= btns[i].x && pt.x <= btns[i].x + btns[i].w && pt.y >= btns[i].y && pt.y <= btns[i].y + btns[i].h;
                settextcolor(hov ? LIGHTGREEN : WHITE);
                TCHAR tw[40]; wsprintf(tw, _T("%hs"), btns[i].txt);
                outtextxy(btns[i].x, btns[i].y, tw);
            }
            if (MouseHit()) {
                MOUSEMSG m = GetMouseMsg();
                if (m.uMsg == WM_LBUTTONDOWN) {
                    for (int i = 0; i < 6; i++) {
                        if (m.x >= btns[i].x && m.x <= btns[i].x + btns[i].w && m.y >= btns[i].y && m.y <= btns[i].y + btns[i].h) {
                            switch (btns[i].act) {
                            case 6: return false;
                            case 5: ShowManageMenu(); break;
                            case 4: ShowRankingMenu(); break;
                            case 3: if (ShowLoadMenu()) return true; break;
                            case 2: mode = 2; break;
                            case 1: mode = 1; break;
                            }
                        }
                    }
                }
            }
        }
        if ((mode == 1 || mode == 2) && (GetAsyncKeyState(VK_RETURN) & 1)) {
            TCHAR wn[50], wp[50];
            InputBox(wn, 50, _T("\u7528\u6237\u540D"), _T(""), NULL, 0, 0, false);
            InputBox(wp, 50, _T("\u5BC6\u7801"), _T(""), NULL, 0, 0, true);
            char cn[20], cp[20];
            WideCharToMultiByte(CP_ACP, 0, wn, -1, cn, 20, NULL, NULL);
            WideCharToMultiByte(CP_ACP, 0, wp, -1, cp, 20, NULL, NULL);
            if (mode == 2) {
                if (reg(cn, cp)) MessageBox(GetHWnd(), _T("\u6CE8\u518C\u6210\u529F"), _T(""), MB_OK);
                else MessageBox(GetHWnd(), _T("\u7528\u6237\u5DF2\u5B58\u5728"), _T(""), MB_OK);
                mode = 0;
            }
            else if (login(cn, cp)) {
                strcpy(currentUsername, cn);
                AddToRanking(currentUsername, playerLevel, reincarnationCycle);
                return true;
            }
            else MessageBox(GetHWnd(), _T("\u8D26\u53F7\u6216\u5BC6\u7801\u9519\u8BEF"), _T(""), MB_OK);
        }
        if ((mode == 1 || mode == 2) && (GetAsyncKeyState(VK_ESCAPE) & 1)) mode = 0;
        MusicPollEvents();
        FlushBatchDraw();
        Sleep(16);
    }
}

void initForestBoss() {
    forestBoss.x = FOREST_BOSS_X; forestBoss.y = FOREST_BOSS_Y;
    forestBoss.maxHp = FOREST_BOSS_MAX_HP; forestBoss.hp = forestBoss.maxHp;
    forestBoss.phase = 1; forestBoss.isAlive = true;
    forestBoss.moveDirX = (rand() % 3) - 1; forestBoss.moveDirY = (rand() % 3) - 1;
    if (!forestBoss.moveDirX && !forestBoss.moveDirY) forestBoss.moveDirX = 1;
    forestBoss.moveTimer = FOREST_BOSS_MOVE_INTERVAL;
    forestBoss.shootTimer = 0; forestBoss.shootInterval = 60;
    forestBoss.burstCount = 1; forestBoss.burstRemain = 0; forestBoss.damage = BOSS_BULLET_DAMAGE;
    BossBulletPoolClear(forestBoss.bullets, forestBoss.bulletCount); forestBoss.shieldActive = true;
    forestBoss.shieldAngle = 0; forestBoss.shieldRadius = 180;
    forestBoss.shieldRadiusMin = 120; forestBoss.shieldRadiusMax = 300;
    forestBoss.shieldRadiusSpeed = 0.02f; forestBoss.shieldRotateSpeed = 0.0267f;
    forestBoss.shieldDamage = SHIELD_BASE_DAMAGE;
    forestBoss.rootActive = false; forestBoss.rootWarning = false;
    forestBoss.rootTimer = 0; forestBoss.rootCooldown = 0;
}
void initStoneBoss() {
    stoneBoss.x = STONE_BOSS_X; stoneBoss.y = STONE_BOSS_Y;
    stoneBoss.maxHp = STONE_BOSS_MAX_HP; stoneBoss.hp = stoneBoss.maxHp;
    stoneBoss.phase = 1; stoneBoss.isAlive = true;
    stoneBoss.shootTimer = 0; stoneBoss.shootInterval = 50;
    stoneBoss.burstCount = 1; stoneBoss.burstRemain = 0; stoneBoss.damage = STONE_BOSS_ATTACK_DAMAGE;
    BossBulletPoolClear(stoneBoss.bullets, stoneBoss.bulletCount);
}
void initIceBoss() {
    iceBoss.x = ICE_BOSS_X; iceBoss.y = ICE_BOSS_Y;
    iceBoss.maxHp = ICE_BOSS_MAX_HP; iceBoss.hp = iceBoss.maxHp;
    iceBoss.phase = 1; iceBoss.direction = 0; iceBoss.isAlive = true;
    iceBoss.moveDirX = 1; iceBoss.moveDirY = 0; iceBoss.moveTimer = 60;
    iceBoss.waveShootTimer = 0; iceBoss.waveShootInterval = ICE_BOSS_WAVE_INTERVAL;
    iceBoss.waveBurstRemain = 0; iceBoss.summonTimer = 0;
    iceBoss.summonInterval = ICE_BOSS_SERVANT_SUMMON_INTERVAL;
    iceBoss.freezeAuraActive = false;
    IceSpikePoolClear(iceBoss.iceSpikes, iceBoss.iceSpikeCount);
    BossWavePoolClear(iceBoss.waves, iceBoss.waveCount);
    IceServantsClear();
}
void initMirrorBoss(float spawnX, float spawnY) {
    mirrorBoss.x = spawnX;
    mirrorBoss.y = spawnY;
    mirrorBoss.maxHp = player.maxHp * 2.f;
    mirrorBoss.hp = mirrorBoss.maxHp;
    mirrorBoss.maxMp = player.maxMp;
    mirrorBoss.mp = mirrorBoss.maxMp;
    mirrorBoss.direction = 0;
    mirrorBoss.frame = 1;
    mirrorBoss.animTimer = 0;
    mirrorBoss.attackTimer = 0;
    mirrorBoss.meleeCooldown = 0;
    mirrorBoss.waveCooldown = 45;
    mirrorBoss.isMoving = false;
    mirrorBoss.isAlive = true;
    mirrorBoss.displayScale = player.displayScale;
    mirrorBoss.radius = player.radius;
    BossWavePoolClear(mirrorBoss.waves, mirrorBoss.waveCount);
}
void BeginMirrorBossFight() {
    float bx = iceBoss.x, by = iceBoss.y;
    iceBoss.isAlive = false;
    bossDefeated[2] = true;
    BossWavePoolClear(iceBoss.waves, iceBoss.waveCount);
    IceSpikePoolClear(iceBoss.iceSpikes, iceBoss.iceSpikeCount);
    IceServantsClear();
    SwordWavesClear();
    bossType = 3;
    gameState = 1;
    initMirrorBoss(bx, by);
    g_mirrorRevealTimer = 0;
    g_pendingMirrorRevealDialog = true;
    g_finalMusicActive = true;
    PlayMusicTrack(MUSIC_FINAL);
    g_flyGroundedTimer = 0;
    invincibleTimer = 180;
}
static void shootMirrorWave(float angle, int damage) {
    SwordWave w;
    w.x = mirrorBoss.x;
    w.y = mirrorBoss.y;
    w.vx = cosf(angle) * 12.f;
    w.vy = sinf(angle) * 12.f;
    w.traveled = 0;
    w.range = 1000.f;
    w.damage = damage;
    w.active = true;
    w.imageDir = getDirectionIndexForAngle(cosf(angle), sinf(angle));
    BossWavePoolAdd(mirrorBoss.waves, mirrorBoss.waveCount, w);
}
void updateMirrorBossWaves() {
    for (int i = 0; i < mirrorBoss.waveCount; ) {
        SwordWave& w = mirrorBoss.waves[i];
        if (!w.active) {
            mirrorBoss.waves[i] = mirrorBoss.waves[mirrorBoss.waveCount - 1];
            mirrorBoss.waveCount--;
            continue;
        }
        w.x += w.vx;
        w.y += w.vy;
        w.traveled += hypot(w.vx, w.vy);
        if (w.traveled >= w.range) {
            mirrorBoss.waves[i] = mirrorBoss.waves[mirrorBoss.waveCount - 1];
            mirrorBoss.waveCount--;
            continue;
        }
        if (hypot(player.x - w.x, player.y - w.y) < player.radius + WAVE_COLLIDE_RADIUS) {
            ApplyBossPlayerDamage((float)w.damage, false);
            mirrorBoss.waves[i] = mirrorBoss.waves[mirrorBoss.waveCount - 1];
            mirrorBoss.waveCount--;
        }
        else i++;
    }
}
static void tryMoveMirror(float dx, float dy) {
    mirrorBoss.x += dx;
    mirrorBoss.y += dy;
    float mapW = NEWMAP_W, mapH = NEWMAP_H;
    int br = (int)mirrorBoss.radius;
    if (mirrorBoss.x < (float)br) mirrorBoss.x = (float)br;
    if (mirrorBoss.x > mapW - br) mirrorBoss.x = mapW - br;
    if (mirrorBoss.y < (float)br) mirrorBoss.y = (float)br;
    if (mirrorBoss.y > mapH - br) mirrorBoss.y = mapH - br;
}
void updateMirrorBoss() {
    if (!mirrorBoss.isAlive) return;
    mirrorBoss.mp += MP_REGEN_RATE / 60.f;
    if (mirrorBoss.mp > mirrorBoss.maxMp) mirrorBoss.mp = mirrorBoss.maxMp;
    if (mirrorBoss.meleeCooldown > 0) mirrorBoss.meleeCooldown -= 1.f / 60.f;
    if (mirrorBoss.attackTimer > 0) mirrorBoss.attackTimer -= 1.f / 60.f;
    if (mirrorBoss.waveCooldown > 0) mirrorBoss.waveCooldown--;
    mirrorBoss.animTimer += 0.3f;

    float dx = player.x - mirrorBoss.x, dy = player.y - mirrorBoss.y;
    float dist = hypotf(dx, dy);
    mirrorBoss.isMoving = false;
    if (dist > 50.f) {
        float step = MIRROR_BOSS_MOVE_SPEED;
        if (dist > 0.01f) { dx /= dist; dy /= dist; }
        tryMoveMirror(dx * step, dy * step);
        mirrorBoss.isMoving = true;
        if (fabsf(dx) > fabsf(dy)) mirrorBoss.direction = (dx > 0) ? 3 : 2;
        else mirrorBoss.direction = (dy > 0) ? 0 : 1;
    }
    mirrorBoss.frame = mirrorBoss.isMoving ? ((int)mirrorBoss.animTimer % 3) : 1;

    if (dist <= ATTACK_RADIUS && mirrorBoss.meleeCooldown <= 0.f && mirrorBoss.attackTimer <= 0.f) {
        ApplyBossPlayerDamage((float)GetMeleeDamage(), false);
        mirrorBoss.attackTimer = ATTACK_DURATION;
        mirrorBoss.meleeCooldown = MELEE_COOLDOWN * 3.f;
    }
    if (mirrorBoss.waveCooldown <= 0 && dist > 70.f && mirrorBoss.mp >= WAVE_COST_MP) {
        float ang = atan2f(dy, dx);
        int dmg = GetWaveMaxDamage();
        for (int i = 0; i < MIRROR_WAVE_BURST_COUNT; i++) {
            float spread = (float)(i - (MIRROR_WAVE_BURST_COUNT - 1) / 2) * 0.22f;
            shootMirrorWave(ang + spread, dmg);
        }
        mirrorBoss.mp -= (float)WAVE_COST_MP;
        mirrorBoss.waveCooldown = (float)MIRROR_WAVE_COOLDOWN_FRAMES;
        mirrorBoss.attackTimer = ATTACK_DURATION;
    }
}
static void drawBossHpBarWithText(float hp, float maxHp, int barW, int barH, int barX, int barY, COLORREF fillColor) {
    setfillcolor(RGB(40, 40, 40));
    solidrectangle(barX, barY, barX + barW, barY + barH);
    if (maxHp > 0.f) {
        setfillcolor(fillColor);
        int fillW = (int)(barW * hp / maxHp);
        if (fillW < 0) fillW = 0;
        if (fillW > barW) fillW = barW;
        solidrectangle(barX, barY, barX + fillW, barY + barH);
    }
    setlinecolor(RGB(200, 200, 200));
    rectangle(barX, barY, barX + barW, barY + barH);
    settextcolor(WHITE);
    settextstyle(18, 0, _T("\u9ED1\u4F53"));
    TCHAR t[48];
    _stprintf_s(t, L"HP: %.0f/%.0f", hp, maxHp);
    outtextxy(barX + 8, barY + 4, t);
}
static void drawBossRageLabel(int barX, int barY, int barW, int barH) {
    const TCHAR* rage = L"\u72C2\u66B4\u72B6\u6001";
    settextcolor(RGB(255, 100, 0));
    settextstyle(16, 0, _T("\u9ED1\u4F53"));
    outtextxy(barX + barW - textwidth(rage) - 8, barY + (barH - textheight(rage)) / 2, rage);
}
void drawMirrorBoss(int sx, int sy) {
    float curScaleX = mirrorBoss.displayScale, curScaleY = mirrorBoss.displayScale;
    if (!mirrorBoss.isMoving) {
        if (mirrorBoss.attackTimer > 0)
            curScaleY *= (1.f + 0.03f * (float)sin(mirrorBoss.animTimer));
        else {
            float breathe = 1.f + 0.04f * (float)sin(mirrorBoss.animTimer * 0.12f);
            curScaleX *= breathe;
            curScaleY *= breathe;
        }
    }
    IMAGE* cur = (mirrorBoss.attackTimer > 0) ? &img_sword_atk[mirrorBoss.direction]
        : &img_walk[mirrorBoss.direction][mirrorBoss.frame];
    drawSprite(cur, sx, sy, curScaleX, curScaleY);
    int barW = 250, barH = 28, barX = SCREEN_W - barW - 20, barY = 20;
    drawBossHpBarWithText(mirrorBoss.hp, mirrorBoss.maxHp, barW, barH, barX, barY, RGB(200, 50, 80));
    settextcolor(RGB(255, 80, 120)); settextstyle(22, 0, _T("\u9ED1\u4F53"));
    outtextxy(barX, barY - 28, L"\u8F6E\u56DE\u4E4B\u5F71");
}
void shootBullet(float x, float y, float angle, BossBullet* bullets, int& bulletCount, int damage) {
    BossBullet b; b.x = x; b.y = y; b.vx = cos(angle) * BULLET_SPEED; b.vy = sin(angle) * BULLET_SPEED;
    b.traveled = 0; b.active = true; b.damage = damage > 0 ? damage : BOSS_BULLET_DAMAGE;
    BossBulletPoolAdd(bullets, bulletCount, b);
}
void updateBullets(BossBullet* bullets, int& bulletCount, int, bool poisonBullet = false, float maxDistance = BULLET_MAX_DISTANCE) {
    float mapW = (currentMap == MAP_MAIN) ? MAP_W : NEWMAP_W;
    float mapH = (currentMap == MAP_MAIN) ? MAP_H : NEWMAP_H;
    for (int i = 0; i < bulletCount; ) {
        BossBullet& b = bullets[i];
        if (!b.active) {
            bullets[i] = bullets[bulletCount - 1];
            bulletCount--;
            continue;
        }
        b.traveled += hypot(b.vx, b.vy);
        if (b.traveled >= maxDistance) {
            bullets[i] = bullets[bulletCount - 1];
            bulletCount--;
            continue;
        }
        b.x += b.vx; b.y += b.vy;
        if (b.x < 0 || b.x > mapW || b.y < 0 || b.y > mapH) {
            bullets[i] = bullets[bulletCount - 1];
            bulletCount--;
            continue;
        }
        if (hypot(player.x - b.x, player.y - b.y) < player.radius + BULLET_RADIUS) {
            ApplyBossPlayerDamage((float)b.damage, poisonBullet);
            bullets[i] = bullets[bulletCount - 1];
            bulletCount--;
        }
        else i++;
    }
}
void drawBullet(BossBullet& b, int sx, int sy) {
    if (bossBulletImg.getwidth() > 0) drawSprite(&bossBulletImg, sx, sy, 0.1f, 0.1f);
    else { setfillcolor(RGB(0, 255, 0)); solidcircle(sx, sy, BULLET_RADIUS); }
}

void shootBossWave(float angle) {
    SwordWave w; w.x = iceBoss.x; w.y = iceBoss.y;
    w.vx = cos(angle) * ICE_BOSS_WAVE_SPEED; w.vy = sin(angle) * ICE_BOSS_WAVE_SPEED;
    w.traveled = 0; w.range = ICE_BOSS_WAVE_RANGE; w.damage = ICE_BOSS_WAVE_DAMAGE;
    w.active = true; w.imageDir = getDirectionIndexForAngle(cos(angle), sin(angle));
    BossWavePoolAdd(iceBoss.waves, iceBoss.waveCount, w);
}
void updateBossWaves() {
    for (int i = 0; i < iceBoss.waveCount; ) {
        SwordWave& w = iceBoss.waves[i];
        if (!w.active) {
            iceBoss.waves[i] = iceBoss.waves[iceBoss.waveCount - 1];
            iceBoss.waveCount--;
            continue;
        }
        w.x += w.vx; w.y += w.vy; w.traveled += hypot(w.vx, w.vy);
        if (w.traveled >= w.range) {
            iceBoss.waves[i] = iceBoss.waves[iceBoss.waveCount - 1];
            iceBoss.waveCount--;
            continue;
        }
        if (hypot(player.x - w.x, player.y - w.y) < player.radius + WAVE_COLLIDE_RADIUS) {
            if (invincibleTimer <= 0) {
                ApplyBossPlayerDamage((float)w.damage, false);
                player.slowTimer = SLOW_DURATION;
                g_flyGroundedTimer = ICE_WAVE_GROUNDED_FRAMES;
                if (flyMode) flyMode = false;
            }
            iceBoss.waves[i] = iceBoss.waves[iceBoss.waveCount - 1];
            iceBoss.waveCount--;
        }
        else i++;
    }
}
void drawBossWave(SwordWave& w, int sx, int sy) {
    if (w.imageDir >= 0 && w.imageDir < 4 && iceWaveImgs[w.imageDir].getwidth() > 0)
        drawSprite(&iceWaveImgs[w.imageDir], sx, sy, WAVE_SCALE, WAVE_SCALE);
    else { setfillcolor(RGB(100, 200, 255)); solidcircle(sx, sy, WAVE_COLLIDE_RADIUS); }
}
void updateIceServants() {
    for (int si = 0; si < iceServantCount; si++) {
        IceServant& s = iceServants[si];
        if (!s.active) continue;
        s.moveTimer--;
        if (s.moveTimer <= 0) { s.dirX = (rand() % 3) - 1; s.dirY = (rand() % 3) - 1; if (!s.dirX && !s.dirY) s.dirX = 1; s.moveTimer = 120; }
        float nx = s.x + s.dirX * s.speed, ny = s.y + s.dirY * s.speed;
        s.x = nx; s.y = ny;
        int r = s.radius;
        if (s.x < r) s.x = (float)r;
        if (s.x > NEWMAP_W - r) s.x = NEWMAP_W - r;
        if (s.y < r) s.y = (float)r;
        if (s.y > NEWMAP_H - r) s.y = NEWMAP_H - r;
        s.shootTimer--;
        if (s.shootTimer <= 0) {
            shootBullet(s.x, s.y, atan2(player.y - s.y, player.x - s.x), s.bullets, s.bulletCount, ICE_SERVANT_BULLET_DAMAGE);
            s.shootTimer = ICE_SERVANT_SHOOT_INTERVAL;
        }
        updateBullets(s.bullets, s.bulletCount, 0);
        if (hypot(player.x - s.x, player.y - s.y) < player.radius + s.radius
            && invincibleTimer <= 0 && monsterContactDamageCd <= 0.f) {
            ApplyBossPlayerDamage((float)ICE_SERVANT_COLLIDE_DAMAGE, false);
            monsterContactDamageCd = MONSTER_CONTACT_DAMAGE_INTERVAL;
        }
        if (s.hp <= 0) { s.active = false; playerGold += ICE_SERVANT_GOLD_REWARD; }
    }
}
void updateIceSpikes() {
    for (int i = 0; i < iceBoss.iceSpikeCount; ) {
        IceSpike& sp = iceBoss.iceSpikes[i];
        if (!sp.active) {
            iceBoss.iceSpikes[i] = iceBoss.iceSpikes[iceBoss.iceSpikeCount - 1];
            iceBoss.iceSpikeCount--;
            continue;
        }
        if (sp.warning) {
            sp.warningTimer--;
            if (sp.warningTimer <= 0) {
                sp.warning = false;
                if (hypot(player.x - sp.x, player.y - sp.y) < 25) {
                    ApplyBossPlayerDamage((float)ICE_BOSS_SPIKE_DAMAGE, false);
                }
                sp.warningTimer = 10;
            }
        }
        else { sp.warningTimer--; if (sp.warningTimer <= 0) sp.active = false; }
        i++;
    }
}
void drawIceServant(IceServant& s, int sx, int sy) {
    int barOffset = s.radius + 8;
    if (iceMonsterImg.getwidth() > 0) {
        drawSprite(&iceMonsterImg, sx, sy, ICE_SERVANT_SCALE, ICE_SERVANT_SCALE);
        int drawH = (int)(iceMonsterImg.getheight() * ICE_SERVANT_SCALE);
        if (drawH + 8 > barOffset) barOffset = drawH + 8;
    }
    else {
        setfillcolor(RGB(100, 150, 200));
        solidcircle(sx, sy, s.radius);
    }
    int barW = 40, barH = 6, barX = sx - barW / 2, barY = sy - barOffset;
    setfillcolor(RGB(0, 0, 0)); solidrectangle(barX, barY, barX + barW, barY + barH);
    setfillcolor(RGB(255, 0, 0)); solidrectangle(barX, barY, barX + (int)(barW * s.hp / s.maxHp), barY + barH);
}
void drawIceSpikes() {
    for (int i = 0; i < iceBoss.iceSpikeCount; i++) {
        IceSpike& sp = iceBoss.iceSpikes[i];
        int sx = (int)sp.x - cameraX, sy = (int)sp.y - cameraY;
        if (sp.warning) { setfillcolor(RGBA(255, 0, 0, 100)); solidcircle(sx, sy, 20); }
        else if (iceSpikeImg.getwidth() > 0) drawSprite(&iceSpikeImg, sx, sy, 0.1f, 0.1f);
    }
}
void updateForestBoss() {
    if (!forestBoss.isAlive) return;
    forestBoss.moveTimer--;
    if (forestBoss.moveTimer <= 0) {
        forestBoss.moveDirX = (rand() % 3) - 1; forestBoss.moveDirY = (rand() % 3) - 1;
        if (!forestBoss.moveDirX && !forestBoss.moveDirY) forestBoss.moveDirX = 1;
        forestBoss.moveTimer = FOREST_BOSS_MOVE_INTERVAL;
    }
    tryMoveBoss(forestBoss, forestBoss.moveDirX * FOREST_BOSS_MOVE_SPEED, forestBoss.moveDirY * FOREST_BOSS_MOVE_SPEED);
    if (forestBoss.shootTimer <= 0) {
        if (forestBoss.burstRemain <= 0) {
            forestBoss.burstRemain = forestBoss.burstCount;
            float ang = atan2(player.y - forestBoss.y, player.x - forestBoss.x);
            if (forestBoss.burstCount == 1) {
                shootBullet(forestBoss.x, forestBoss.y, ang, forestBoss.bullets, forestBoss.bulletCount, forestBoss.damage);
                forestBoss.burstRemain = 0;
            }
            else {
                shootBullet(forestBoss.x, forestBoss.y, ang, forestBoss.bullets, forestBoss.bulletCount, forestBoss.damage);
                shootBullet(forestBoss.x, forestBoss.y, ang + 0.26f, forestBoss.bullets, forestBoss.bulletCount, forestBoss.damage);
                shootBullet(forestBoss.x, forestBoss.y, ang - 0.26f, forestBoss.bullets, forestBoss.bulletCount, forestBoss.damage);
                forestBoss.burstRemain = 0;
            }
        }
        else forestBoss.burstRemain--;
        forestBoss.shootTimer = forestBoss.shootInterval;
    }
    else forestBoss.shootTimer--;
    if (forestBoss.shieldActive) {
        forestBoss.shieldAngle += forestBoss.shieldRotateSpeed;
        static float t = 0; t += forestBoss.shieldRadiusSpeed;
        forestBoss.shieldRadius = forestBoss.shieldRadiusMin + (sin(t) + 1) / 2 * (forestBoss.shieldRadiusMax - forestBoss.shieldRadiusMin);
    }
    if (forestBoss.phase == 2 && forestBoss.rootCooldown <= 0 && !forestBoss.rootActive) {
        forestBoss.rootX = (int)player.x - ROOT_WIDTH / 2; forestBoss.rootY = (int)player.y - ROOT_HEIGHT / 2;
        if (forestBoss.rootX < 0) forestBoss.rootX = 0;
        if (forestBoss.rootY < 0) forestBoss.rootY = 0;
        if (forestBoss.rootX + ROOT_WIDTH > NEWMAP_W) forestBoss.rootX = NEWMAP_W - ROOT_WIDTH;
        if (forestBoss.rootY + ROOT_HEIGHT > NEWMAP_H) forestBoss.rootY = NEWMAP_H - ROOT_HEIGHT;
        forestBoss.rootActive = true; forestBoss.rootWarning = true;
        forestBoss.rootTimer = ROOT_WARNING_TIME / 16; forestBoss.rootCooldown = 180;
    }
    if (forestBoss.rootCooldown > 0) forestBoss.rootCooldown--;
    updateRootAttack(); updateBullets(forestBoss.bullets, forestBoss.bulletCount, 0, true, FOREST_BOSS_BULLET_MAX_DISTANCE);
}
void updateStoneBoss() {
    if (!stoneBoss.isAlive) return;
    if (stoneBoss.shootTimer <= 0) {
        if (stoneBoss.burstRemain <= 0) {
            stoneBoss.burstRemain = stoneBoss.burstCount;
            float ang = atan2(player.y - stoneBoss.y, player.x - stoneBoss.x);
            if (stoneBoss.burstCount == 1) {
                shootBullet(stoneBoss.x, stoneBoss.y, ang, stoneBoss.bullets, stoneBoss.bulletCount, stoneBoss.damage);
                stoneBoss.burstRemain = 0;
            }
            else {
                shootBullet(stoneBoss.x, stoneBoss.y, ang, stoneBoss.bullets, stoneBoss.bulletCount, stoneBoss.damage);
                shootBullet(stoneBoss.x, stoneBoss.y, ang + 0.26f, stoneBoss.bullets, stoneBoss.bulletCount, stoneBoss.damage);
                shootBullet(stoneBoss.x, stoneBoss.y, ang - 0.26f, stoneBoss.bullets, stoneBoss.bulletCount, stoneBoss.damage);
                stoneBoss.burstRemain = 0;
            }
        }
        else stoneBoss.burstRemain--;
        stoneBoss.shootTimer = stoneBoss.shootInterval;
    }
    else stoneBoss.shootTimer--;
    updateBullets(stoneBoss.bullets, stoneBoss.bulletCount, 0, false);
}
void updateIceBoss() {
    if (!iceBoss.isAlive) return;
    if (iceBoss.hp <= iceBoss.maxHp / 2 && iceBoss.phase == 1) {
        iceBoss.phase = 2; iceBoss.waveShootInterval = ICE_BOSS_WAVE_INTERVAL_PHASE2; iceBoss.freezeAuraActive = true;
    }
    iceBoss.moveTimer--;
    if (iceBoss.moveTimer <= 0) {
        iceBoss.moveDirX = (rand() % 3) - 1; iceBoss.moveDirY = (rand() % 3) - 1;
        if (!iceBoss.moveDirX && !iceBoss.moveDirY) iceBoss.moveDirX = 1;
        iceBoss.moveTimer = 60;
    }
    iceBoss.x += iceBoss.moveDirX * ICE_BOSS_MOVE_SPEED;
    iceBoss.y += iceBoss.moveDirY * ICE_BOSS_MOVE_SPEED;
    if (iceBoss.x < ICE_BOSS_RADIUS) iceBoss.x = ICE_BOSS_RADIUS;
    if (iceBoss.x > NEWMAP_W - ICE_BOSS_RADIUS) iceBoss.x = NEWMAP_W - ICE_BOSS_RADIUS;
    if (iceBoss.y < ICE_BOSS_RADIUS) iceBoss.y = ICE_BOSS_RADIUS;
    if (iceBoss.y > NEWMAP_H - ICE_BOSS_RADIUS) iceBoss.y = NEWMAP_H - ICE_BOSS_RADIUS;
    float dx = player.x - iceBoss.x, dy = player.y - iceBoss.y;
    iceBoss.direction = getDirectionIndexForAngle(dx, dy);
    if (iceBoss.waveShootTimer <= 0) {
        if (iceBoss.waveBurstRemain <= 0) {
            iceBoss.waveBurstRemain = (iceBoss.phase == 1) ? 1 : 3;
            float ang = atan2(dy, dx);
            if (iceBoss.phase == 1) { shootBossWave(ang); iceBoss.waveBurstRemain = 0; }
            else { shootBossWave(ang); shootBossWave(ang + 0.26f); shootBossWave(ang - 0.26f); iceBoss.waveBurstRemain = 0; }
        }
        else iceBoss.waveBurstRemain--;
        iceBoss.waveShootTimer = iceBoss.waveShootInterval;
    }
    else iceBoss.waveShootTimer--;
    if (iceBoss.phase == 2) {
        iceBoss.summonTimer--;
        if (iceBoss.summonTimer <= 0 && iceServantCount < ICE_BOSS_SERVANT_MAX_COUNT) {
            IceServant& s = iceServants[iceServantCount++];
            s.x = iceBoss.x + 50; s.y = iceBoss.y + 50;
            s.hp = s.maxHp = ICE_SERVANT_MAX_HP; s.speed = ICE_SERVANT_SPEED; s.radius = ICE_SERVANT_RADIUS;
            s.dirX = (rand() % 3) - 1; s.dirY = (rand() % 3) - 1;
            if (!s.dirX && !s.dirY) s.dirX = 1;
            s.moveTimer = 60; s.shootTimer = 0; s.active = true;
            s.bulletCount = 0;
            iceBoss.summonTimer = iceBoss.summonInterval;
        }
        static int spikeT = 0; spikeT--;
        if (spikeT <= 0) {
            int spikeCount = 3 + rand() % 3;
            for (int i = 0; i < spikeCount; i++) {
                IceSpike sp; sp.x = player.x + (rand() % 400) - 200; sp.y = player.y + (rand() % 400) - 200;
                if (sp.x < 50) sp.x = 50; if (sp.x > NEWMAP_W - 50) sp.x = NEWMAP_W - 50;
                if (sp.y < 50) sp.y = 50; if (sp.y > NEWMAP_H - 50) sp.y = NEWMAP_H - 50;
                sp.warningTimer = ICE_BOSS_SPIKE_WARNING_TIME; sp.active = true; sp.warning = true;
                IceSpikePoolAdd(iceBoss.iceSpikes, iceBoss.iceSpikeCount, sp);
            }
            spikeT = ICE_BOSS_SPIKE_INTERVAL;
        }
    }
    updateBossWaves(); updateIceServants(); updateIceSpikes();
}
void drawForestBoss(int sx, int sy) {
    if (forestBossImg.getwidth() > 0) drawSprite(&forestBossImg, sx, sy, 0.1f, 0.1f);
    else { setfillcolor(RGB(0, 100, 0)); solidcircle(sx, sy, FOREST_BOSS_RADIUS); }
    int barW = 300, barH = 28, barX = SCREEN_W - barW - 20, barY = 20;
    drawBossHpBarWithText(forestBoss.hp, forestBoss.maxHp, barW, barH, barX, barY, RGB(220, 50, 50));
    settextcolor(RGB(255, 215, 0)); settextstyle(22, 0, _T("\u9ED1\u4F53")); outtextxy(barX, barY - 28, L"\u68EE\u6797\u5B88\u62A4\u8005");
    if (forestBoss.phase == 2) drawBossRageLabel(barX, barY, barW, barH);
}
void drawStoneBoss(int sx, int sy) {
    if (stoneBossImg.getwidth() > 0) drawSprite(&stoneBossImg, sx, sy, 0.1f, 0.1f);
    else { setfillcolor(RGB(100, 100, 100)); solidcircle(sx, sy, STONE_BOSS_RADIUS); }
    int barW = 300, barH = 28, barX = SCREEN_W - barW - 20, barY = 20;
    drawBossHpBarWithText(stoneBoss.hp, stoneBoss.maxHp, barW, barH, barX, barY, RGB(220, 50, 50));
    settextcolor(RGB(255, 215, 0)); settextstyle(22, 0, _T("\u9ED1\u4F53")); outtextxy(barX, barY - 28, L"\u5CA9\u77F3\u5B88\u62A4\u8005");
    if (stoneBoss.phase == 2) drawBossRageLabel(barX, barY, barW, barH);
}
void drawIceBoss(int sx, int sy) {
    if (iceBossImgs[iceBoss.direction].getwidth() > 0) drawSprite(&iceBossImgs[iceBoss.direction], sx, sy, 0.1f, 0.1f);
    else { setfillcolor(RGB(100, 150, 200)); solidcircle(sx, sy, ICE_BOSS_RADIUS); }
    int barW = 350, barH = 28, barX = SCREEN_W - barW - 20, barY = 20;
    drawBossHpBarWithText(iceBoss.hp, iceBoss.maxHp, barW, barH, barX, barY, RGB(100, 150, 255));
    settextcolor(RGB(255, 215, 0)); settextstyle(22, 0, _T("\u9ED1\u4F53")); outtextxy(barX, barY - 28, L"\u5DDD\u5DEE\u5B88\u62A4\u8005");
    if (iceBoss.phase == 2) drawBossRageLabel(barX, barY, barW, barH);
    if (iceBoss.freezeAuraActive) { setfillcolor(RGBA(100, 200, 255, 50)); solidcircle(sx, sy, ICE_BOSS_FREEZE_AURA_RADIUS); }
}
void drawShield(int cx, int cy) {
    if (!forestBoss.shieldActive) return;
    for (int i = 0; i < 3; i++) {
        float ang = forestBoss.shieldAngle + i * 2 * M_PI / 3;
        int bx = cx + (int)(forestBoss.shieldRadius * cos(ang));
        int by = cy + (int)(forestBoss.shieldRadius * sin(ang));
        if (bossShieldImg.getwidth() > 0) drawSprite(&bossShieldImg, bx, by, 0.08f, 0.08f);
        if (hypot(player.x - (forestBoss.x + forestBoss.shieldRadius * cos(ang)), player.y - (forestBoss.y + forestBoss.shieldRadius * sin(ang))) < player.radius + SHIELD_BALL_RADIUS) {
            ApplyBossPlayerDamage((float)forestBoss.shieldDamage, true);
        }
    }
}
void updateRootAttack() {
    if (!forestBoss.rootActive) return;
    if (forestBoss.rootWarning) {
        forestBoss.rootTimer--;
        if (forestBoss.rootTimer <= 0) {
            forestBoss.rootWarning = false; forestBoss.rootTimer = ROOT_DISPLAY_TIME / 16;
            if (player.x >= forestBoss.rootX && player.x <= forestBoss.rootX + ROOT_WIDTH &&
                player.y >= forestBoss.rootY && player.y <= forestBoss.rootY + ROOT_HEIGHT && invincibleTimer <= 0) {
                ApplyBossPlayerDamage((float)ROOT_ATTACK_DAMAGE, true);
            }
        }
    }
    else { forestBoss.rootTimer--; if (forestBoss.rootTimer <= 0) forestBoss.rootActive = false; }
}
void drawRootAttack() {
    if (!forestBoss.rootActive) return;
    int sx = forestBoss.rootX - cameraX, sy = forestBoss.rootY - cameraY;
    if (sx + ROOT_WIDTH < 0 || sx > SCREEN_W || sy + ROOT_HEIGHT < 0 || sy > SCREEN_H) return;
    if (forestBoss.rootWarning) {
        if (bossWarningImg.getwidth() > 0) putimageAlpha(sx, sy, ROOT_WIDTH, ROOT_HEIGHT, &bossWarningImg, 0, 0);
        else { setfillcolor(RGBA(255, 0, 0, 100)); solidrectangle(sx, sy, sx + ROOT_WIDTH, sy + ROOT_HEIGHT); }
    }
    else if (bossRootImg.getwidth() > 0) {
        for (int i = 0; i < (ROOT_WIDTH / 70) + 1; i++)
            putimageAlpha(sx + i * 70, sy, 70, ROOT_HEIGHT, &bossRootImg, 0, 0);
    }
    else { setfillcolor(RGB(139, 69, 19)); solidrectangle(sx, sy, sx + ROOT_WIDTH, sy + ROOT_HEIGHT); }
}
static bool InMountainBossTriggerZone() {
    return fabs(player.x - MOUNTAIN_BOSS_TRIGGER_X) <= MOUNTAIN_BOSS_TRIGGER_RANGE
        && fabs(player.y - MOUNTAIN_BOSS_TRIGGER_Y) <= MOUNTAIN_BOSS_TRIGGER_RANGE;
}
static bool InForestBossTriggerZone() {
    return fabs(player.x - FOREST_BOSS_TRIGGER_X) <= FOREST_BOSS_TRIGGER_RANGE
        && fabs(player.y - FOREST_BOSS_TRIGGER_Y) <= FOREST_BOSS_TRIGGER_RANGE;
}
void drawBossTriggerHints() {
    if (gameState != 0 || g_bossInfoOpen || showFullMinimap) return;
    setbkmode(TRANSPARENT);
    settextcolor(YELLOW);
    settextstyle(22, 0, _T("\u9ED1\u4F53"));
    if (currentMap == MAP_FOREST && !bossDefeated[0] && InForestBossTriggerZone()) {
        outtextxy(SCREEN_W / 2 - 240, SCREEN_H / 2, L"\u6BD2\u57DF\u9738\u4E3B\u5728\u6B64  Enter\u67E5\u770BBoss\u60C5\u62A5");
    }
    else if (currentMap == MAP_MOUNTAIN && !bossDefeated[1] && InMountainBossTriggerZone()) {
        outtextxy(SCREEN_W / 2 - 280, SCREEN_H / 2, L"\u5CA9\u7532\u5B88\u62A4\u8005\u5728\u6B64  Enter\u67E5\u770BBoss\u60C5\u62A5");
        settextstyle(18, 0, _T("\u9ED1\u4F53"));
        outtextxy(SCREEN_W / 2 - 300, SCREEN_H / 2 + 36, L"\u666E\u901A\u5175\u5668\u9632+100\uFF0C\u8BF7\u88C5\u5907\u788E\u5CA9\u5DE8\u9550\u7279\u653B");
    }
}
void drawIcePortalHint() {
    if (gameState != 0 || currentMap != MAP_MOUNTAIN || !bossDefeated[1] || g_bossInfoOpen || showFullMinimap) return;
    if (!InMountainBossTriggerZone()) return;
    setbkmode(TRANSPARENT);
    settextcolor(YELLOW);
    settextstyle(22, 0, _T("\u9ED1\u4F53"));
    outtextxy(SCREEN_W / 2 - 240, SCREEN_H / 2, L"\u6697\u5F71\u4E4B\u4E3B\u5728\u51B0\u5DDD  Enter\u67E5\u770BBoss\u60C5\u62A5");
}
#define SHOP_CRAFT_ICON_SZ 30

static void putShopCraftIcon(IMAGE* img, int x, int y, int sz) {
    if (img && img->getwidth() > 0) {
        int iw = img->getwidth(), ih = img->getheight();
        float scale = (float)sz / (float)(iw > ih ? iw : ih);
        drawSprite(img, x + sz / 2, y + sz, scale, scale);
    }
    else {
        setfillcolor(RGB(70, 60, 50));
        solidrectangle(x, y, x + sz, y + sz);
    }
}
static IMAGE* getMaterialImage(int matType) {
    if (matType >= 0 && matType < MATERIAL_SLOT_COUNT && materialImgLoaded[matType])
        return &materialImg[matType];
    if (matType == MAT_IRON && ironOreImg.getwidth() > 0) return &ironOreImg;
    if (matType == MAT_WOOD && woodImg.getwidth() > 0) return &woodImg;
    if (matType == MAT_HERB && herbImg.getwidth() > 0) return &herbImg;
    return NULL;
}
static int drawCraftMaterialTag(int x, int y, int matType, int count) {
    const TCHAR* matNames[] = { L"\u94C1\u77FF", L"\u6728\u6750", L"\u836F\u8349" };
    if (matType < 0 || matType >= MATERIAL_SLOT_COUNT) return x;
    settextcolor(RGB(180, 210, 230)); settextstyle(16, 0, _T("\u9ED1\u4F53"));
    outtextxy(x, y, matNames[matType]);
    int nx = x + textwidth(matNames[matType]) + 4;
    putShopCraftIcon(getMaterialImage(matType), nx, y - 2, SHOP_CRAFT_ICON_SZ);
    nx += SHOP_CRAFT_ICON_SZ + 4;
    TCHAR cnt[16]; _stprintf_s(cnt, L"x%d", count);
    outtextxy(nx, y, cnt);
    return nx + textwidth(cnt) + 12;
}
static int drawCraftPotionTag(int x, int y, int count) {
    settextcolor(RGB(180, 210, 230)); settextstyle(16, 0, _T("\u9ED1\u4F53"));
    outtextxy(x, y, L"\u9B54\u6CD5\u836F\u6C34");
    int nx = x + textwidth(L"\u9B54\u6CD5\u836F\u6C34") + 4;
    if (consumImgLoaded[CONS_POTION]) putShopCraftIcon(&consumImg[CONS_POTION], nx, y - 2, SHOP_CRAFT_ICON_SZ);
    else putShopCraftIcon(NULL, nx, y - 2, SHOP_CRAFT_ICON_SZ);
    nx += SHOP_CRAFT_ICON_SZ + 4;
    TCHAR cnt[16]; _stprintf_s(cnt, L"x%d", count);
    outtextxy(nx, y, cnt);
    return nx + textwidth(cnt) + 12;
}
static void drawCraftProductHeader(int panelX, int y, int num, int equipId, int consumId, const TCHAR* name, const TCHAR* stat) {
    TCHAR head[80];
    if (stat[0]) _stprintf_s(head, L"%d.%s  %s", num, name, stat);
    else _stprintf_s(head, L"%d.%s", num, name);
    settextcolor(RGB(255, 255, 200)); settextstyle(18, 0, _T("\u9ED1\u4F53"));
    outtextxy(panelX + 36, y, head);
    int iconX = panelX + 36 + textwidth(head) + 8;
    if (equipId >= 0 && equipId < EQUIP_SLOT_COUNT && equipImgLoaded[equipId])
        putShopCraftIcon(&equipImg[equipId], iconX, y - 4, SHOP_CRAFT_ICON_SZ);
    else if (consumId >= 0 && consumId < CONSUM_SLOT_COUNT && consumImgLoaded[consumId])
        putShopCraftIcon(&consumImg[consumId], iconX, y - 4, SHOP_CRAFT_ICON_SZ);
}
static void drawShopCraftTab(int panelX, int yStart, int lineH) {
    const int matYOffset = 28;
    settextcolor(RGB(200, 180, 140)); settextstyle(16, 0, _T("\u9ED1\u4F53"));
    outtextxy(panelX + 36, yStart - 24, L"\u9700\u6C42\u6750\u6599\uFF08\u6587\u5B57+\u56FE\u6807\uFF09\uFF1A");
    drawCraftProductHeader(panelX, yStart, 1, EQ_IRON_SWORD, -1, L"\u94C1\u5251", L"\u653B+20");
    settextcolor(RGB(160, 170, 180)); settextstyle(16, 0, _T("\u9ED1\u4F53"));
    outtextxy(panelX + 52, yStart + matYOffset, L"\u9700");
    int cx = drawCraftMaterialTag(panelX + 82, yStart + matYOffset, MAT_IRON, 20);

    drawCraftProductHeader(panelX, yStart + lineH, 2, EQ_STEEL_ARMOR, -1, L"\u94A2\u7532", L"\u9632+10");
    outtextxy(panelX + 52, yStart + lineH + matYOffset, L"\u9700");
    cx = drawCraftMaterialTag(panelX + 82, yStart + lineH + matYOffset, MAT_IRON, 20);
    outtextxy(cx, yStart + lineH + matYOffset, L"+");
    drawCraftMaterialTag(cx + textwidth(L"+"), yStart + lineH + matYOffset, MAT_WOOD, 5);

    drawCraftProductHeader(panelX, yStart + lineH * 2, 3, EQ_PICKAXE, -1, L"\u788E\u5CA9\u5DE8\u9550", L"\u653B+20");
    outtextxy(panelX + 52, yStart + lineH * 2 + matYOffset, L"\u9700");
    cx = drawCraftMaterialTag(panelX + 82, yStart + lineH * 2 + matYOffset, MAT_IRON, 10);
    outtextxy(cx, yStart + lineH * 2 + matYOffset, L"+");
    cx += textwidth(L"+");
    cx = drawCraftMaterialTag(cx, yStart + lineH * 2 + matYOffset, MAT_WOOD, 10);
    outtextxy(cx, yStart + lineH * 2 + matYOffset, L"+");
    drawCraftMaterialTag(cx + textwidth(L"+"), yStart + lineH * 2 + matYOffset, MAT_HERB, 10);
}

void drawShopTriggerHint() {
    if (currentMap != MAP_MAIN || gameState != 0 || inShop || showFullMinimap) return;
    float dist = hypot(player.x - SHOP_TRIGGER_X, player.y - SHOP_TRIGGER_Y);
    if (dist <= SHOP_TRIGGER_RANGE) {
        setbkmode(TRANSPARENT);
        settextcolor(RGB(255, 255, 0)); settextstyle(32, 0, _T("\u9ED1\u4F53"));
        outtextxy(SCREEN_W / 2 - 160, SCREEN_H / 2 - 30, L"\u662F\u5426\u8FDB\u5165\u5546\u5E97\uFF1F");
        settextstyle(22, 0, _T("\u9ED1\u4F53"));
        settextcolor(RGB(255, 230, 150));
        outtextxy(SCREEN_W / 2 - 100, SCREEN_H / 2 + 20, L"Enter \u786E\u8BA4");
    }
}
static bool g_returnKeyLastDown = false;
static bool IsReturnKeyEdge() {
    bool down = (GetAsyncKeyState(VK_RETURN) & 0x8000) != 0;
    bool edge = down && !g_returnKeyLastDown;
    g_returnKeyLastDown = down;
    return edge;
}
static void ResetReturnKeyEdge() {
    g_returnKeyLastDown = (GetAsyncKeyState(VK_RETURN) & 0x8000) != 0;
}
static bool HandleWorldReturnKey() {
    if (gameState != 0 || isPaused || showInventory || inShop || g_bossInfoOpen || g_bossLootScreenOpen || showStatsPanel || showAncientBook)
        return false;
    if (!IsReturnKeyEdge()) return false;

    if (currentMap == MAP_MAIN) {
        if (TryPickupBronzeRingOnInteract()) {
            Sleep(200);
            return true;
        }
        float shopD = hypot(player.x - SHOP_TRIGGER_X, player.y - SHOP_TRIGGER_Y);
        if (shopD <= SHOP_TRIGGER_RANGE) {
            inShop = true; shopTab = 0; Sleep(200); return true;
        }
        float d1 = hypot(player.x - PORTAL1_X, player.y - PORTAL1_Y);
        float d2 = hypot(player.x - PORTAL2_X, player.y - PORTAL2_Y);
        if (d1 < PORTAL_RANGE) {
            currentMap = MAP_MOUNTAIN;
            player.x = (float)MOUNTAIN_SPAWN_X; player.y = (float)MOUNTAIN_SPAWN_Y;
            generateWorldItems(); SwordWavesClear(); AutoSaveGame(); Sleep(200); return true;
        }
        if (d2 < PORTAL_RANGE) {
            currentMap = MAP_FOREST;
            player.x = (float)FOREST_PORTAL_X; player.y = (float)FOREST_PORTAL_Y;
            generateWorldItems(); SwordWavesClear(); AutoSaveGame(); Sleep(200); return true;
        }
        return false;
    }
    if (currentMap == MAP_FOREST) {
        if (hypot(player.x - FOREST_PORTAL_X, player.y - FOREST_PORTAL_Y) < FOREST_PORTAL_RANGE) {
            currentMap = MAP_MAIN; player.x = MAIN_SPAWN_X; player.y = MAIN_SPAWN_Y;
            SwordWavesClear(); AutoSaveGame(); Sleep(200); return true;
        }
        if (!bossDefeated[0] && InForestBossTriggerZone()) {
            g_bossInfoOpen = true; g_bossInfoType = 0; Sleep(200); return true;
        }
        return false;
    }
    if (currentMap == MAP_MOUNTAIN) {
        if (!bossDefeated[1] && InMountainBossTriggerZone()) {
            g_bossInfoOpen = true; g_bossInfoType = 1; Sleep(200); return true;
        }
        if (bossDefeated[1] && InMountainBossTriggerZone()) {
            g_bossInfoOpen = true; g_bossInfoType = 2; Sleep(200); return true;
        }
        if (hypot(player.x - MOUNTAIN_PORTAL_X, player.y - MOUNTAIN_PORTAL_Y) < MOUNTAIN_PORTAL_RANGE) {
            currentMap = MAP_MAIN; player.x = MAIN_SPAWN_X; player.y = MAIN_SPAWN_Y;
            SwordWavesClear(); AutoSaveGame(); Sleep(200); return true;
        }
        return false;
    }
    return false;
}
void drawShop() {
    setfillcolor(RGBA(0, 0, 0, 200)); solidrectangle(0, 0, SCREEN_W, SCREEN_H);
    int panelW = 720, panelH = shopTab == 1 ? 540 : 460;
    int panelX = (SCREEN_W - panelW) / 2, panelY = (SCREEN_H - panelH) / 2;
    setfillcolor(RGB(50, 40, 30)); solidrectangle(panelX, panelY, panelX + panelW, panelY + panelH);
    setlinecolor(RGB(255, 215, 0)); rectangle(panelX, panelY, panelX + panelW, panelY + panelH);
    settextcolor(RGB(255, 215, 0)); settextstyle(32, 0, _T("\u9ED1\u4F53"));
    outtextxy(panelX + panelW / 2 - 40, panelY + 16, shopTab == 0 ? L"\u5546\u5E97" : L"\u5408\u6210\u53F0");
    settextstyle(16, 0, _T("\u9ED1\u4F53"));
    settextcolor(shopTab == 0 ? RGB(255, 215, 0) : RGB(150, 140, 120));
    outtextxy(panelX + 30, panelY + 52, L"[\u5151\u6362]");
    settextcolor(shopTab == 1 ? RGB(255, 215, 0) : RGB(150, 140, 120));
    outtextxy(panelX + 120, panelY + 52, L"[\u5408\u6210]");
    TCHAR goldText[64]; _stprintf_s(goldText, L"\u91D1\u5E01:%d  \u94C1:%d \u6728:%d \u8349:%d \u836F\u6C34:%d",
        playerGold, materialCounts[MAT_IRON], materialCounts[MAT_WOOD], materialCounts[MAT_HERB], consumCounts[CONS_POTION]);
    settextcolor(RGB(255, 215, 0)); settextstyle(16, 0, _T("\u9ED1\u4F53"));
    outtextxy(panelX + 280, panelY + 52, goldText);
    int yStart = panelY + 88, lineH = 44;
    settextstyle(18, 0, _T("\u9ED1\u4F53"));
    if (shopTab == 0) {
        settextcolor(RGB(255, 255, 200));
        outtextxy(panelX + 40, yStart, L"1.\u6728\u6750 10\u21921\u91D1");
        TCHAR w[64]; _stprintf_s(w, L"\u62E5\u6709%d \u9650\u5151%d", materialCounts[MAT_WOOD], woodExchangeLimit);
        outtextxy(panelX + 380, yStart, w);
        outtextxy(panelX + 40, yStart + lineH, L"2.\u94C1\u77FF 10\u21921\u91D1");
        TCHAR ir[64]; _stprintf_s(ir, L"\u62E5\u6709%d \u9650\u5151%d", materialCounts[MAT_IRON], ironExchangeLimit);
        outtextxy(panelX + 380, yStart + lineH, ir);
        outtextxy(panelX + 40, yStart + lineH * 2, L"3.\u836F\u8349 10\u21921\u91D1");
        TCHAR hb[64]; _stprintf_s(hb, L"\u62E5\u6709%d \u9650\u5151%d", materialCounts[MAT_HERB], herbExchangeLimit);
        outtextxy(panelX + 380, yStart + lineH * 2, hb);
        outtextxy(panelX + 40, yStart + lineH * 3, L"4.\u9B54\u6CD5\u836F\u6C34 50\u91D1\u21921\u74F6");
        TCHAR pot[64]; _stprintf_s(pot, L"\u62E5\u6709%d\u74F6", consumCounts[CONS_POTION]);
        outtextxy(panelX + 380, yStart + lineH * 3, pot);
        outtextxy(panelX + 40, yStart + lineH * 4, L"5.\u5347\u7EA7");
        TCHAR lv[80]; _stprintf_s(lv, L"\u82B1\u8D39%d\u91D1", GetUpgradeCost(playerLevel));
        outtextxy(panelX + 380, yStart + lineH * 4, lv);
        settextcolor(RGB(150, 150, 150)); settextstyle(15, 0, _T("\u9ED1\u4F53"));
        outtextxy(panelX + 20, panelY + panelH - 38, L"Tab\u5207\u6362 | 1-5\u64CD\u4F5C | ESC/B\u5173\u95ED");
    }
    else {
        drawShopCraftTab(panelX, yStart + 6, 72);
        settextcolor(RGB(150, 150, 150)); settextstyle(15, 0, _T("\u9ED1\u4F53"));
        outtextxy(panelX + 20, panelY + panelH - 38, L"Tab\u5207\u6362 | 1-3\u5408\u6210 | ESC/B\u5173\u95ED");
    }
}
void handleShopInput() {
    static int frameCounter = 0;
    static bool tabDn = false;
    if (GetAsyncKeyState(VK_TAB) & 0x8000) {
        if (!tabDn) { shopTab = 1 - shopTab; tabDn = true; Sleep(120); }
    }
    else tabDn = false;
    frameCounter++;
    if (frameCounter >= 60) {
        frameCounter = 0;
        if (shopRefreshTimer > 0) {
            shopRefreshTimer--;
            if (shopRefreshTimer == 0) woodExchangeLimit = ironExchangeLimit = herbExchangeLimit = 100;
        }
    }
    if (shopTab == 0) {
        if (GetAsyncKeyState('5') & 1) {
            if (TryUpgradeLevel()) MessageBox(GetHWnd(), _T("\u5347\u7EA7\u6210\u529F"), _T(""), MB_OK);
            else MessageBox(GetHWnd(), _T("\u91D1\u5E01\u4E0D\u8DB3"), _T(""), MB_OK);
            Sleep(150);
        }
        if (GetAsyncKeyState('4') & 1) {
            if (playerGold >= SHOP_POTION_GOLD_COST) {
                playerGold -= SHOP_POTION_GOLD_COST;
                consumCounts[CONS_POTION]++;
            }
            else MessageBox(GetHWnd(), _T("\u91D1\u5E01\u4E0D\u8DB3"), _T(""), MB_OK);
            Sleep(150);
        }
        if (GetAsyncKeyState('1') & 1 && woodExchangeLimit > 0 && materialCounts[MAT_WOOD] >= 10) {
            int n = min(woodExchangeLimit, materialCounts[MAT_WOOD] / 10);
            materialCounts[MAT_WOOD] -= n * 10; playerGold += n; woodExchangeLimit -= n; Sleep(150);
        }
        if (GetAsyncKeyState('2') & 1 && ironExchangeLimit > 0 && materialCounts[MAT_IRON] >= 10) {
            int n = min(ironExchangeLimit, materialCounts[MAT_IRON] / 10);
            materialCounts[MAT_IRON] -= n * 10; playerGold += n; ironExchangeLimit -= n; Sleep(150);
        }
        if (GetAsyncKeyState('3') & 1 && herbExchangeLimit > 0 && materialCounts[MAT_HERB] >= 10) {
            int n = min(herbExchangeLimit, materialCounts[MAT_HERB] / 10);
            materialCounts[MAT_HERB] -= n * 10; playerGold += n; herbExchangeLimit -= n; Sleep(150);
        }
    }
    else {
        for (int k = 0; k < CRAFT_RECIPE_COUNT; k++) {
            if (GetAsyncKeyState('1' + k) & 1) {
                if (TryCraftRecipe(k)) MessageBox(GetHWnd(), _T("\u5408\u6210\u6210\u529F"), _T(""), MB_OK);
                else MessageBox(GetHWnd(), _T("\u6750\u6599\u4E0D\u8DB3"), _T(""), MB_OK);
                Sleep(150);
            }
        }
    }
    if (GetAsyncKeyState(VK_ESCAPE) & 1 || GetAsyncKeyState('B') & 1) { inShop = false; shopTab = 0; Sleep(200); }
}
static void InitBronzeRingWorldPosition() {
    const float anchorX = (float)BRONZE_RING_WORLD_X;
    const float anchorY = (float)BRONZE_RING_WORLD_Y;
    float bestX = anchorX, bestY = anchorY, bestScore = 1e9f;
    if (maskPixels && maskWidth > 0 && maskHeight > 0) {
        if (isWalkable((int)anchorX, (int)anchorY)) {
            bronzeRingWorldX = anchorX;
            bronzeRingWorldY = anchorY;
            return;
        }
        for (int ox = -400; ox <= 400; ox += 20) {
            for (int oy = -400; oy <= 400; oy += 20) {
                int tx = (int)(anchorX + ox), ty = (int)(anchorY + oy);
                if (tx < 40 || ty < 40 || tx >= maskWidth - 40 || ty >= maskHeight - 40) continue;
                if (!isWalkable(tx, ty)) continue;
                float d = hypot((float)tx - anchorX, (float)ty - anchorY);
                if (d < bestScore) { bestScore = d; bestX = (float)tx; bestY = (float)ty; }
            }
        }
    }
    bronzeRingWorldX = bestX;
    bronzeRingWorldY = bestY;
}
static void drawBronzeRingWorldPickup() {
    if (!ShouldShowBronzeRingWorld()) return;
    int rx = (int)bronzeRingWorldX - cameraX - PORTAL_SIZE / 2;
    int ry = (int)bronzeRingWorldY - cameraY - PORTAL_SIZE / 2;
    if (rx <= -PORTAL_SIZE || ry <= -PORTAL_SIZE || rx >= SCREEN_W || ry >= SCREEN_H) return;
    if (equipImgLoaded[EQ_BRONZE_RING] && equipImg[EQ_BRONZE_RING].getwidth() > 0)
        putimageAlpha(rx, ry, PORTAL_SIZE, PORTAL_SIZE, &equipImg[EQ_BRONZE_RING], 0, 0);
    else if (bossBulletImg.getwidth() > 0)
        putimageAlpha(rx, ry, PORTAL_SIZE, PORTAL_SIZE, &bossBulletImg, 0, 0);
}
static void SyncBronzeRingWorldState() {
    if (g_bronzeRingWaveUnlocked) bronzeRingWorldActive = false;
}
static void ResetBronzeRingQuestForNewGame() {
    g_bronzeRingWaveUnlocked = false;
    bronzeRingWorldActive = true;
    g_bronzeRingPickupToast = 0;
    InitBronzeRingWorldPosition();
    SyncBronzeRingWorldState();
}
static bool ShouldShowBronzeRingWorld() {
    return bronzeRingWorldActive && !g_bronzeRingWaveUnlocked;
}
static bool WorldItemOverlap(float x, float y) {
    for (int i = 0; i < worldItemCount; i++) {
        if (worldItems[i].active && hypot(worldItems[i].x - x, worldItems[i].y - y) < 100.f) return true;
    }
    return false;
}
static void generateForestWorldItems() {
    WorldItemsClear();
    srand((unsigned)time(NULL));
    for (int i = 0; i < 30; i++) {
        int tc = 0;
        while (tc < 500) {
            int tx = 100 + rand() % (NEWMAP_W - 200), ty = 100 + rand() % (NEWMAP_H - 200);
            if (isWalkable(tx, ty) && !WorldItemOverlap((float)tx, (float)ty)) {
                WorldItemsAdd({ (float)tx, (float)ty, ITEM_WOOD, true }); break;
            }
            tc++;
        }
    }
    for (int i = 0; i < 20; i++) {
        int tc = 0;
        while (tc < 500) {
            int tx = 100 + rand() % (NEWMAP_W - 200), ty = 100 + rand() % (NEWMAP_H - 200);
            if (isWalkable(tx, ty) && !WorldItemOverlap((float)tx, (float)ty)) {
                WorldItemsAdd({ (float)tx, (float)ty, ITEM_HERB, true }); break;
            }
            tc++;
        }
    }
}
static void generateMountainWorldItems() {
    WorldItemsClear();
    srand((unsigned)time(NULL));
    for (int i = 0; i < 25; i++) {
        int tc = 0;
        while (tc < 500) {
            int tx = 100 + rand() % (NEWMAP_W - 200), ty = 100 + rand() % (NEWMAP_H - 200);
            if (isWalkable(tx, ty) && !WorldItemOverlap((float)tx, (float)ty)) {
                WorldItemsAdd({ (float)tx, (float)ty, ITEM_IRON, true }); break;
            }
            tc++;
        }
    }
}
void generateWorldItems() {
    if (currentMap == MAP_FOREST) generateForestWorldItems();
    else if (currentMap == MAP_MOUNTAIN) generateMountainWorldItems();
}
static void PickupBronzeRingWorldItem() {
    if (!ShouldShowBronzeRingWorld()) return;
    if (!HasEquip(EQ_BRONZE_RING)) AddEquipItem(EQ_BRONZE_RING);
    g_bronzeRingWaveUnlocked = true;
    SyncBronzeRingWorldState();
    g_bronzeRingPickupToast = 240;
    AutoSaveGame();
}
static float BronzeRingDistToPlayer() {
    return hypot(player.x - bronzeRingWorldX, player.y - bronzeRingWorldY);
}
static bool BronzeRingInPickupRange() {
    return currentMap == MAP_MAIN && gameState == 0 && ShouldShowBronzeRingWorld()
        && BronzeRingDistToPlayer() <= (float)BRONZE_RING_PICKUP_RANGE;
}
static bool TryPickupBronzeRingOnInteract() {
    if (!BronzeRingInPickupRange()) return false;
    PickupBronzeRingWorldItem();
    return true;
}
static void TryBronzeRingPickupKeys() {
    if (!BronzeRingInPickupRange()) {
        g_eKeyDown = false;
        return;
    }
    if (GetAsyncKeyState('E') & 0x8000) {
        if (!g_eKeyDown) {
            g_eKeyDown = true;
            TryPickupBronzeRingOnInteract();
            Sleep(200);
        }
    }
    else g_eKeyDown = false;
}
void tryPickupItem(float radius) {
    for (int i = 0; i < worldItemCount; i++) {
        WorldItem& item = worldItems[i];
        if (!item.active) continue;
        if (hypot(player.x - item.x, player.y - item.y) <= radius) {
            switch (item.type) {
            case ITEM_WOOD: materialCounts[1]++; break;
            case ITEM_HERB: materialCounts[2]++; break;
            case ITEM_IRON: materialCounts[0]++; break;
            }
            item.active = false;
        }
    }
    if (currentMap == MAP_MAIN && gameState == 0 && foodItemActive) {
        if (hypot(player.x - FOOD_SPAWN_X, player.y - FOOD_SPAWN_Y) <= radius) {
            consumCounts[0]++;
            foodItemActive = false;
            foodRespawnTimer = 1800;
        }
    }
    if (currentMap == MAP_MAIN && gameState == 0 && BronzeRingInPickupRange())
        PickupBronzeRingWorldItem();
}
void respawn() {
    if (GOD_MODE) {
        if (player.hp < 0) player.hp = 0;
        return;
    }
    if (gameState == 1 && player.hp <= 0) {
        FailBossFight();
        return;
    }
    if (gameState != 1) {
        gameState = 0; currentMap = MAP_MAIN;
        player.x = MAIN_SPAWN_X; player.y = MAIN_SPAWN_Y;
        player.hp = player.maxHp; player.mp = player.maxMp;
        SwordWavesClear();
    }
}
static void drawInventoryStatsPage(int bgX, int bgY, int bgW, int bgH) {
    int cx = bgX + 200, cy = bgY + 78, lh = 34;
    TCHAR line[160];
    int bAtk = GetMeleeBaseDamage(), eAtk = GetEquipAttackBonus();
    int bDef = GetBaseDefense(), eDef = GetEquipDefenseBonus();
    int wAtk = GetEquippedWeaponAtk(), rAtk = GetEquippedRingAtk();
    int bWave = GetWaveBaseOnly(), bWaveMax = GetWaveMaxBaseOnly();

    setfillcolor(RGB(40, 35, 28));
    solidrectangle(cx - 12, cy - 8, bgX + bgW - 30, bgY + bgH - 75);

    settextcolor(RGB(255, 215, 0)); settextstyle(22, 0, _T("\u9ED1\u4F53"));
    outtextxy(cx, cy, L"\u3010\u780D\u51FB\u653B\u51FB\u3011"); cy += lh + 4;
    settextstyle(18, 0, _T("\u9ED1\u4F53"));
    _stprintf_s(line, L"  \u57FA\u7840\u653B\u51FB: %d", bAtk);
    settextcolor(WHITE); outtextxy(cx, cy, line); cy += lh;
    _stprintf_s(line, L"  \u88C5\u5907\u653B\u51FB: +%d (\u6B66+%d \u6212+%d)", eAtk, wAtk, rAtk);
    settextcolor(RGB(150, 220, 255)); outtextxy(cx, cy, line); cy += lh;
    if (eAtk > 0) _stprintf_s(line, L"  \u5408\u8BA1: %d+%d", bAtk, eAtk);
    else _stprintf_s(line, L"  \u5408\u8BA1: %d", bAtk);
    settextcolor(RGB(255, 230, 150)); outtextxy(cx, cy, line); cy += lh + 12;

    settextcolor(RGB(255, 215, 0)); settextstyle(22, 0, _T("\u9ED1\u4F53"));
    outtextxy(cx, cy, L"\u3010\u5251\u6C14\u653B\u51FB\u3011"); cy += lh + 4;
    settextstyle(18, 0, _T("\u9ED1\u4F53"));
    _stprintf_s(line, L"  \u57FA\u7840(\u6700\u4F4E): %d", bWave);
    settextcolor(WHITE); outtextxy(cx, cy, line); cy += lh;
    _stprintf_s(line, L"  \u57FA\u7840(\u6EE1\u50A8): %d", bWaveMax);
    outtextxy(cx, cy, line); cy += lh;
    _stprintf_s(line, L"  \u88C5\u5907\u653B\u51FB: +%d", eAtk);
    settextcolor(RGB(150, 220, 255)); outtextxy(cx, cy, line); cy += lh;
    if (eAtk > 0) {
        _stprintf_s(line, L"  \u5408\u8BA1(\u6700\u4F4E): %d+%d", bWave, eAtk);
        settextcolor(RGB(255, 230, 150)); outtextxy(cx, cy, line); cy += lh;
        _stprintf_s(line, L"  \u5408\u8BA1(\u6EE1\u50A8): %d+%d", bWaveMax, eAtk);
        outtextxy(cx, cy, line); cy += lh;
    }
    else {
        _stprintf_s(line, L"  \u5408\u8BA1(\u6700\u4F4E): %d", bWave);
        settextcolor(RGB(255, 230, 150)); outtextxy(cx, cy, line); cy += lh;
        _stprintf_s(line, L"  \u5408\u8BA1(\u6EE1\u50A8): %d", bWaveMax);
        outtextxy(cx, cy, line); cy += lh;
    }
    cy += 8;

    settextcolor(RGB(255, 215, 0)); settextstyle(22, 0, _T("\u9ED1\u4F53"));
    outtextxy(cx, cy, L"\u3010\u9632\u5FA1\u3011"); cy += lh + 4;
    settextstyle(18, 0, _T("\u9ED1\u4F53"));
    _stprintf_s(line, L"  \u57FA\u7840\u9632\u5FA1: %d", bDef);
    settextcolor(WHITE); outtextxy(cx, cy, line); cy += lh;
    _stprintf_s(line, L"  \u88C5\u5907\u9632\u5FA1: +%d", eDef);
    settextcolor(RGB(150, 220, 255)); outtextxy(cx, cy, line); cy += lh;
    if (eDef > 0) _stprintf_s(line, L"  \u5408\u8BA1: %d+%d", bDef, eDef);
    else _stprintf_s(line, L"  \u5408\u8BA1: %d", bDef);
    settextcolor(RGB(255, 230, 150)); outtextxy(cx, cy, line); cy += lh + 8;

    settextcolor(RGB(180, 170, 150)); settextstyle(16, 0, _T("\u9ED1\u4F53"));
    if (equippedWeapon >= 0 && HasEquip(equippedWeapon))
        _stprintf_s(line, L"\u5DF2\u88C5\u5907\u6B66\u5668: %s", equipNames[equippedWeapon]);
    else _tcscpy_s(line, L"\u5DF2\u88C5\u5907\u6B66\u5668: \u65E0");
    outtextxy(cx, cy, line); cy += 26;
    if (equippedArmor >= 0 && HasEquip(equippedArmor))
        _stprintf_s(line, L"\u5DF2\u88C5\u5907\u62A4\u7532: %s", equipNames[equippedArmor]);
    else _tcscpy_s(line, L"\u5DF2\u88C5\u5907\u62A4\u7532: \u65E0");
    outtextxy(cx, cy, line); cy += 26;
    if (equippedRing >= 0 && HasEquip(equippedRing))
        _stprintf_s(line, L"\u5DF2\u88C5\u5907\u6212\u6307: %s", equipNames[equippedRing]);
    else _tcscpy_s(line, L"\u5DF2\u88C5\u5907\u6212\u6307: \u65E0");
    outtextxy(cx, cy, line);
    if (IsIceMapNoLevelBonus()) {
        settextcolor(RGB(200, 120, 120));
        outtextxy(cx, cy + 28, L"\u51B0\u5DDD\u5185\u4EC5\u8BA1\u57FA\u7840\u653B\u51FB(\u65E0\u7B49\u7EA7\u52A0\u6210)");
    }
}

void ShowExitConfirm() {
    bool run = true, wp = isPaused; isPaused = true;
    while (run) {
        setfillcolor(RGB(50, 50, 50));
        solidrectangle(SCREEN_W / 2 - 200, SCREEN_H / 2 - 80, SCREEN_W / 2 + 200, SCREEN_H / 2 + 80);
        settextcolor(YELLOW); settextstyle(24, 0, _T("\u9ED1\u4F53"));
        outtextxy(SCREEN_W / 2 - 80, SCREEN_H / 2 - 40, _T("\u9000\u51FA?"));
        outtextxy(SCREEN_W / 2 - 120, SCREEN_H / 2, _T("N\u5B58\u6863\u9000\u51FA O\u4E0D\u5B58 ESC\u53D6\u6D88"));
        FlushBatchDraw();
        if (GetAsyncKeyState('N') & 1) { SaveGameToSlot(0); run = false; gameRunning = false; }
        if (GetAsyncKeyState('O') & 1) { run = false; gameRunning = false; }
        if (GetAsyncKeyState(VK_ESCAPE) & 1) run = false;
        Sleep(20);
    }
    isPaused = wp;
}
static void drawInventoryTopHints() {
    setbkmode(TRANSPARENT);
    settextcolor(RGB(200, 180, 100)); settextstyle(18, 0, _T("\u9ED1\u4F53"));
    if (currentPage == 0)
        outtextxy(24, 12, L"1/2/3/4\u5207\u9875  Tab\u7FFB\u9875  \u2191\u2193\u9009\u62E9  Enter\u88C5\u5907  B/ESC\u5173\u95ED");
    else if (currentPage == 3)
        outtextxy(24, 12, L"1/2/3/4\u5207\u9875  Tab\u7FFB\u9875  \u5C5E\u6027\u9875\u53EA\u8BFB  B/ESC\u5173\u95ED");
    else
        outtextxy(24, 12, L"1/2/3/4\u5207\u9875  Tab\u7FFB\u9875  \u2191\u2193\u9009\u62E9  Enter\u4F7F\u7528  B/ESC\u5173\u95ED");
    settextstyle(16, 0, _T("\u9ED1\u4F53"));
    const TCHAR* pageHint[] = { L"[\u88C5\u5907]", L"[\u6D88\u8017]", L"[\u6750\u6599]", L"[\u5C5E\u6027]" };
    for (int p = 0; p < INVENTORY_PAGE_COUNT; p++) {
        settextcolor(p == currentPage ? RGB(255, 215, 0) : RGB(120, 110, 90));
        outtextxy(24 + p * 110, 40, pageHint[p]);
    }
}

static void drawEquipSlotStat(int equipId, int x, int y) {
    settextcolor(RGB(160, 150, 130));
    settextstyle(14, 0, _T("\u9ED1\u4F53"));
    if (equipAtk[equipId] > 0) {
        TCHAR statW[32];
        _stprintf_s(statW, L"\u653B\u51FB\u529B +%d", equipAtk[equipId]);
        outtextxy(x, y, statW);
    }
    if (equipDef[equipId] > 0) {
        TCHAR statW[32];
        _stprintf_s(statW, L"\u9632\u5FA1\u529B +%d", equipDef[equipId]);
        outtextxy(x, y + (equipAtk[equipId] > 0 ? 20 : 0), statW);
    }
}

void drawInventory() {
    int bgW = bagBg.getwidth() > 0 ? bagBg.getwidth() : 850;
    int bgH = bagBg.getheight() > 0 ? bagBg.getheight() : 650;
    int bgX = (SCREEN_W - bgW) / 2, bgY = (SCREEN_H - bgH) / 2;
    drawInventoryTopHints();
    if (bagBg.getwidth() > 0) putimage(bgX, bgY, &bagBg);
    else { setfillcolor(RGB(50, 40, 30)); solidrectangle(bgX, bgY, bgX + bgW, bgY + bgH); }
    settextcolor(RGB(255, 215, 0)); settextstyle(32, 0, _T("\u9ED1\u4F53"));
    const TCHAR* titles[] = { L"\u88C5\u5907\u80CC\u5305", L"\u6D88\u8017\u54C1\u80CC\u5305", L"\u6750\u6599\u80CC\u5305", L"\u4EBA\u7269\u5C5E\u6027" };
    if (currentPage < 0) currentPage = 0;
    if (currentPage >= INVENTORY_PAGE_COUNT) currentPage = INVENTORY_PAGE_COUNT - 1;
    if (currentPage == 3) {
        outtextxy(bgX + bgW / 2 - 80, bgY + 20, titles[currentPage]);
        drawInventoryStatsPage(bgX, bgY, bgW, bgH);
        return;
    }
    int slotCount = (currentPage == 0) ? EQUIP_SLOT_COUNT : (currentPage == 1) ? CONSUM_SLOT_COUNT : MATERIAL_SLOT_COUNT;
    int& selected = (currentPage == 0) ? selectedSlotEquip : (currentPage == 1) ? selectedSlotConsum : selectedSlotMaterial;
    int pageIdx = currentPage;
    int slotStartX = bgX + 220, slotHeight = 92, slotMargin = 14, iconSize = 56;
    int slotStartY = bgY + 72;
    if (currentPage == 0) slotStartY -= slotHeight;
    if (currentPage == 0) {
        outtextxy(slotStartX, slotStartY - 42, titles[0]);
    }
    else {
        outtextxy(bgX + bgW / 2 - 80, bgY + 20, titles[currentPage]);
    }
    for (int i = 0; i < slotCount; i++) {
        int slotY = slotStartY + i * (slotHeight + slotMargin);
        bool isSelected = (i == selected);
        slotRects[pageIdx][i] = { slotStartX, slotY, 660, slotHeight };
        setfillcolor(isSelected ? RGB(70, 60, 45) : RGB(35, 30, 22));
        solidrectangle(slotStartX, slotY, slotStartX + 658, slotY + slotHeight);
        setlinecolor(isSelected ? RGB(255, 215, 0) : RGB(150, 130, 100));
        rectangle(slotStartX, slotY, slotStartX + 658, slotY + slotHeight);
        settextcolor(RGB(220, 200, 150)); settextstyle(18, 0, _T("\u9ED1\u4F53"));
        TCHAR idxW[16]; _stprintf_s(idxW, L"%d", i + 1); outtextxy(slotStartX + 10, slotY + 38, idxW);
        int iconX = slotStartX + 110, iconY = slotY + 16;
        if (currentPage == 0 && equipImgLoaded[i]) putimage(iconX, iconY, &equipImg[i]);
        else if (currentPage == 1 && consumImgLoaded[i]) putimage(iconX, iconY, &consumImg[i]);
        else if (currentPage == 2 && materialImgLoaded[i]) putimage(iconX, iconY, &materialImg[i]);
        else { setfillcolor(RGB(100, 80, 60)); solidrectangle(iconX, iconY, iconX + iconSize, iconY + iconSize); }
        settextcolor(RGB(255, 255, 200)); settextstyle(16, 0, _T("\u9ED1\u4F53"));
        const TCHAR* name = (currentPage == 0) ? equipNames[i] : (currentPage == 1) ? consumNames[i] : materialNames[i];
        outtextxy(iconX + 4, iconY + iconSize + 10, name);
        if (currentPage != 0) {
            settextcolor(RGB(160, 150, 130)); settextstyle(14, 0, _T("\u9ED1\u4F53"));
            const TCHAR* desc = (currentPage == 1) ? consumDescs[i] : materialDescs[i];
            outtextxy(slotStartX + 210, slotY + 36, desc);
        }
        if (currentPage == 0) {
            settextcolor(RGB(160, 150, 130)); settextstyle(14, 0, _T("\u9ED1\u4F53"));
            outtextxy(slotStartX + 210, slotY + 20, equipDescs[i]);
            if (!HasEquip(i)) {
                settextcolor(RGB(120, 100, 90)); settextstyle(12, 0, _T("\u9ED1\u4F53"));
                outtextxy(iconX + 4, iconY + iconSize - 16, L"\u672A\u83B7\u5F97");
            }
            else {
                drawEquipSlotStat(i, slotStartX + 210, slotY + 40);
                if (EquipHasDurability(i)) {
                    int showDur = 0;
                    if (IsItemEquipped(i)) {
                        if (i == equippedWeapon && equippedWeaponInst >= 0 && equippedWeaponInst < EquipDurSize(i))
                            showDur = equipDurStack[i][equippedWeaponInst];
                        else if (i == equippedArmor && equippedArmorInst >= 0 && equippedArmorInst < EquipDurSize(i))
                            showDur = equipDurStack[i][equippedArmorInst];
                    }
                    if (showDur <= 0) {
                        for (int k = 0; k < EquipDurSize(i); k++) {
                            int d = equipDurStack[i][k];
                            if (d > 0 && (showDur <= 0 || d < showDur)) showDur = d;
                        }
                    }
                    TCHAR durW[24]; _stprintf_s(durW, L"\u8010\u4E45:%d", showDur);
                    settextcolor(RGB(100, 200, 255)); settextstyle(12, 0, _T("\u9ED1\u4F53"));
                    outtextxy(iconX + iconSize + 6, iconY + 4, durW);
                }
                TCHAR cntW[16]; _stprintf_s(cntW, L"x%d", equipCounts[i]);
                settextcolor(RGB(150, 255, 150)); settextstyle(12, 0, _T("\u9ED1\u4F53"));
                outtextxy(iconX + iconSize + 6, iconY + iconSize - 18, cntW);
                if (IsItemEquipped(i)) {
                    settextcolor(RGB(255, 215, 0));
                    outtextxy(slotStartX + 500, slotY + 38, L"\u5DF2\u88C5\u5907");
                }
            }
        }
        else if (currentPage == 1) {
            TCHAR valW[48];
            _stprintf_s(valW, (i == 1) ? L"\u98DE\u884C+%d\u79D2" : L"\u6062\u590D%dHP", consumValues[i]);
            settextcolor(RGB(100, 200, 255)); settextstyle(12, 0, _T("\u9ED1\u4F53"));
            outtextxy(iconX + iconSize + 6, iconY + 4, valW);
            TCHAR cntW[16]; _stprintf_s(cntW, L"x%d", consumCounts[i]);
            settextcolor(RGB(150, 255, 150));
            outtextxy(iconX + iconSize + 6, iconY + iconSize - 18, cntW);
        }
        else {
            TCHAR cntW[16]; _stprintf_s(cntW, L"x%d", materialCounts[i]);
            settextcolor(RGB(150, 255, 150)); settextstyle(12, 0, _T("\u9ED1\u4F53"));
            outtextxy(iconX + iconSize + 6, iconY + iconSize - 18, cntW);
        }
    }
}
static int inventorySlotCount() {
    if (currentPage == 0) return EQUIP_SLOT_COUNT;
    if (currentPage == 1) return CONSUM_SLOT_COUNT;
    if (currentPage == 2) return MATERIAL_SLOT_COUNT;
    return 0;
}
static int& inventorySelectedSlot() {
    if (currentPage == 0) return selectedSlotEquip;
    if (currentPage == 1) return selectedSlotConsum;
    return selectedSlotMaterial;
}
static void useConsumableAt(int idx) {
    if (idx < 0 || idx >= CONSUM_SLOT_COUNT || consumCounts[idx] <= 0) return;
    if (idx == 0) {
        player.hp += (float)consumValues[0];
        if (player.hp > player.maxHp) player.hp = player.maxHp;
    }
    else {
        g_flightTimeBank += FLIGHT_POTION_FRAMES;
    }
    consumCounts[idx]--;
}
void handleInventoryInput() {
    if (currentPage < 0) currentPage = 0;
    if (currentPage >= INVENTORY_PAGE_COUNT) currentPage = INVENTORY_PAGE_COUNT - 1;

    if (GetAsyncKeyState('1') & 1) { currentPage = 0; Sleep(120); }
    if (GetAsyncKeyState('2') & 1) { currentPage = 1; Sleep(120); }
    if (GetAsyncKeyState('3') & 1) { currentPage = 2; Sleep(120); }
    if (GetAsyncKeyState('4') & 1) { currentPage = 3; Sleep(120); }
    if (GetAsyncKeyState(VK_TAB) & 1) { currentPage = (currentPage + 1) % INVENTORY_PAGE_COUNT; Sleep(120); }

    if (currentPage != 3) {
        int max = inventorySlotCount();
        int& sel = inventorySelectedSlot();
        if (sel < 0) sel = 0;
        if (sel >= max) sel = 0;

        if (GetAsyncKeyState(VK_UP) & 1 || GetAsyncKeyState('W') & 1) {
            sel = (sel - 1 + max) % max;
            Sleep(120);
        }
        if (GetAsyncKeyState(VK_DOWN) & 1 || GetAsyncKeyState('S') & 1) {
            sel = (sel + 1) % max;
            Sleep(120);
        }

        if (GetAsyncKeyState(VK_RETURN) & 1) {
            if (currentPage == 0) {
                if (TryEquipSlot(sel)) Sleep(120);
            }
            else if (currentPage == 1) {
                useConsumableAt(sel);
                Sleep(120);
            }
        }

        static bool lastClick = false;
        bool nowClick = GetAsyncKeyState(VK_LBUTTON) & 0x8000;
        if (nowClick && !lastClick) {
            POINT mouse; GetCursorPos(&mouse); ScreenToClient(GetHWnd(), &mouse);
            int pageIdx = currentPage;
            int slotCount = inventorySlotCount();
            for (int i = 0; i < slotCount; i++) {
                if (mouse.x >= slotRects[pageIdx][i].x && mouse.x <= slotRects[pageIdx][i].x + slotRects[pageIdx][i].w &&
                    mouse.y >= slotRects[pageIdx][i].y && mouse.y <= slotRects[pageIdx][i].y + slotRects[pageIdx][i].h) {
                    if (currentPage == 0) selectedSlotEquip = i;
                    else if (currentPage == 1) selectedSlotConsum = i;
                    else selectedSlotMaterial = i;
                    if (currentPage == 1 && consumCounts[i] > 0) useConsumableAt(i);
                    break;
                }
            }
        }
        lastClick = nowClick;
    }

    if (GetAsyncKeyState(VK_ESCAPE) & 1 || GetAsyncKeyState('B') & 1) {
        showInventory = false;
        currentPage = 0;
        flushmessage(EX_MOUSE | EX_KEY);
        Sleep(200);
    }
}

void startup() {
    initgraph(SCREEN_W, SCREEN_H, EX_MOUSE);
    BeginBatchDraw();
    srand((unsigned)time(NULL));
    if (!login_menu()) { StopMusic(); if (g_bgmComInited) CoUninitialize(); closegraph(); exit(0); }
    if (!g_skipOpeningDialog) {
        RunOpeningDialog();
        RunAncientBookIntro();
    }
    ResetReturnKeyEdge();
    loadAssets();
    loadInventoryImages();
    generateMonsters();
    generateForestMonsters();
    generateMountainMonsters();
    if (!g_skipOpeningDialog) {
        player = { MAIN_SPAWN_X, MAIN_SPAWN_Y, 0, 1, 0, 0, 0, false, 20, 0.1f,
            (float)BASE_MAX_HP, (float)BASE_MAX_HP, (float)BASE_MAX_MP, (float)BASE_MAX_MP, 0 };
        player.displayScale = 0.1f;
        InitStarterEquipment();
        gameState = 0;
        ResetBronzeRingQuestForNewGame();
    }
    else {
        player.displayScale = 0.1f;
        if (EquipHasDurability(equippedWeapon) && HasEquip(equippedWeapon))
            equippedWeaponInst = FindPreferUsedInstance(equippedWeapon);
        if (equippedArmor == EQ_STEEL_ARMOR && HasEquip(EQ_STEEL_ARMOR))
            equippedArmorInst = FindPreferUsedInstance(EQ_STEEL_ARMOR);
        if (!ShouldShowBronzeRingWorld() && bronzeRingWorldX < 100.f)
            InitBronzeRingWorldPosition();
    }
    RefreshGameMusic();
}

void applyBossPhaseOnMelee() {
    if (bossType == 0 && forestBoss.isAlive && forestBoss.hp <= forestBoss.maxHp / 2 && forestBoss.phase == 1) {
        forestBoss.phase = 2; forestBoss.shootInterval = 30; forestBoss.burstCount = 3;
        forestBoss.shieldRotateSpeed = 0.1f; forestBoss.shieldRadiusSpeed = 0.02f; forestBoss.shieldDamage = 30;
    }
    else if (bossType == 1 && stoneBoss.isAlive && stoneBoss.hp <= stoneBoss.maxHp / 2 && stoneBoss.phase == 1) {
        stoneBoss.phase = 2; stoneBoss.shootInterval = 30; stoneBoss.burstCount = 3;
    }
    else if (bossType == 2 && iceBoss.isAlive && iceBoss.hp <= iceBoss.maxHp / 2 && iceBoss.phase == 1) {
        iceBoss.phase = 2; iceBoss.waveShootInterval = ICE_BOSS_WAVE_INTERVAL_PHASE2; iceBoss.freezeAuraActive = true;
    }
    RefreshGameMusic();
}

void updateWithoutInput() {
    MusicPollEvents();
    RefreshGameMusic();
    if (g_pendingReincarnationEndingDialog) {
        g_pendingReincarnationEndingDialog = false;
        RunReincarnationEndingDialog();
        ResetReturnKeyEdge();
        flushmessage(EX_MOUSE | EX_KEY);
        g_rebirthOverlayTimer = 150;
        return;
    }
    if (inShop || showInventory || g_rebirthOverlayTimer > 0 || g_bossLootScreenOpen || g_bossInfoOpen || showStatsPanel || showAncientBook) return;

    if (g_bossFailOverlayTimer > 0) g_bossFailOverlayTimer--;

    if (invincibleTimer > 0) invincibleTimer--;
    if (g_bronzeRingPickupToast > 0) g_bronzeRingPickupToast--;
    if (monsterContactDamageCd > 0.f) monsterContactDamageCd -= 1.f / 60.f;
    if (player.slowTimer > 0) player.slowTimer--;
    if (g_flyGroundedTimer > 0) g_flyGroundedTimer--;
    if (!foodItemActive) {
        static int foodFc = 0;
        foodFc++;
        if (foodFc >= 60) {
            foodFc = 0;
            if (foodRespawnTimer > 0) { foodRespawnTimer--; if (foodRespawnTimer == 0) foodItemActive = true; }
        }
    }
    static int shopFc = 0;
    shopFc++;
    if (shopFc >= 60) {
        shopFc = 0;
        if (shopRefreshTimer > 0) { shopRefreshTimer--; if (shopRefreshTimer == 0) woodExchangeLimit = ironExchangeLimit = herbExchangeLimit = 100; }
    }
    if (gameState == 1 && player.hp <= 0) {
        FailBossFight();
        return;
    }
    if (!GOD_MODE && player.hp <= 0) respawn();
    else if (GOD_MODE && player.hp < 0) player.hp = 0;

    if (gameState == 0) {
        g_hpPeriodicRefillTimer++;
        if (g_hpPeriodicRefillTimer >= HP_PERIODIC_REFILL_INTERVAL_FRAMES) {
            g_hpPeriodicRefillTimer = 0;
            player.hp = player.maxHp;
        }
    }

    if (IsSoulRingEquipped()) {
        player.mp = player.maxMp;
    }
    else {
        player.mp += MP_REGEN_RATE / 60.f;
        if (player.mp > player.maxMp) player.mp = player.maxMp;
    }

    if (IsIceMapDarknessActive() && player.hp > 0 && invincibleTimer <= 0) {
        g_iceDarkDotFc++;
        if (g_iceDarkDotFc >= 60) {
            g_iceDarkDotFc = 0;
            player.hp -= (float)ICE_MAP_DARKNESS_DOT_PER_SEC;
            if (player.hp < 0) player.hp = 0;
        }
    }
    else {
        g_iceDarkDotFc = 0;
    }

    if (player.meleeCooldown > 0) player.meleeCooldown -= 1.f / 60.f;
    if (player.attackTimer > 0) player.attackTimer -= 1.f / 60.f;

    if (flyMode) {
        g_flyOrbitAngle += 0.07f;
        player.frame = 1;
        if (g_flightTimeBank > 0) {
            g_flightTimeBank--;
            if (g_flightTimeBank <= 0) {
                g_flightTimeBank = 0;
                flyMode = false;
            }
        }
        else {
            flyMode = false;
        }
    }
    else {
        player.animTimer += 0.3f;
        player.frame = player.isMoving ? ((int)player.animTimer % 3) : 1;
    }
    TryPeriodicAutoSave();

    if (--g_mainMapRefreshTimer <= 0) {
        g_mainMapRefreshTimer = MAP_RESOURCE_REFRESH_FRAMES;
        generateMonsters();
    }
    if (--g_forestMapRefreshTimer <= 0) {
        g_forestMapRefreshTimer = MAP_RESOURCE_REFRESH_FRAMES;
        generateForestMonsters();
        if (currentMap == MAP_FOREST && gameState == 0) generateForestWorldItems();
    }
    if (--g_mountainMapRefreshTimer <= 0) {
        g_mountainMapRefreshTimer = MAP_RESOURCE_REFRESH_FRAMES;
        generateMountainMonsters();
        if (currentMap == MAP_MOUNTAIN && gameState == 0) generateMountainWorldItems();
    }

    if (gameState == 0) {
        if (currentMap == MAP_MAIN) {
            updateMonstersGeneric(monsters, MONSTER_COUNT, MAP_W, MAP_H);
        }
        else if (currentMap == MAP_FOREST) updateMonstersGeneric(forestMonsters, FOREST_MONSTER_COUNT, NEWMAP_W, NEWMAP_H);
        else if (currentMap == MAP_MOUNTAIN) updateMonstersGeneric(mountainMonsters, MOUNTAIN_MONSTER_COUNT, NEWMAP_W, NEWMAP_H);
    }
    else if (gameState == 1) {
        if (g_bossFightTimerFrames > 0) {
            g_bossFightTimerFrames--;
            if (g_bossFightTimerFrames <= 0) FailBossFightTimeout();
        }
        if (bossType == 0 && g_forestBossPoisoned && !HasEquip(EQ_DIAMOND_ARMOR)) {
            g_forestBossPoisonTickFc++;
            if (g_forestBossPoisonTickFc >= 60) {
                g_forestBossPoisonTickFc = 0;
                if (invincibleTimer <= 0 && player.hp > 0) {
                    player.hp -= GetBossAttackDamage((float)FOREST_BOSS_POISON_DOT_PER_SEC);
                    if (player.hp < 0) player.hp = 0;
                }
            }
        }
        if (bossType == 0 && forestBoss.isAlive) {
            updateForestBoss();
            if (forestBoss.hp <= 0) {
                forestBoss.isAlive = false; bossDefeated[0] = true; gameState = 0; playerGold += 2000;
                g_bossSnapshot.valid = false;
                g_bossFightTimerFrames = 0;
                ClearForestBossPoisonState();
                GrantForestBossLoot();
                OpenBossLootScreen(0);
                AutoSaveGame();
            }
        }
        else if (bossType == 1 && stoneBoss.isAlive) {
            updateStoneBoss();
            if (stoneBoss.hp <= 0) {
                stoneBoss.isAlive = false; bossDefeated[1] = true; gameState = 0; playerGold += 1000;
                g_bossSnapshot.valid = false; g_bossFightTimerFrames = 0; ClearForestBossPoisonState();
                GrantMountainBossLoot();
                OpenBossLootScreen(1);
                AutoSaveGame();
            }
        }
        else if (bossType == 2 && iceBoss.isAlive) {
            updateIceBoss();
            if (iceBoss.hp <= 0) BeginMirrorBossFight();
        }
        else if (bossType == 3 && mirrorBoss.isAlive) {
            if (g_pendingMirrorRevealDialog) {
                g_pendingMirrorRevealDialog = false;
                RunIceBossMirrorRevealDialog();
                ResetReturnKeyEdge();
                flushmessage(EX_MOUSE | EX_KEY);
                g_mirrorRevealTimer = MIRROR_REVEAL_FRAMES;
            }
            else if (g_mirrorRevealTimer > 0) {
                g_mirrorRevealTimer--;
            }
            else {
                updateMirrorBoss();
                updateMirrorBossWaves();
            }
            if (mirrorBoss.hp <= 0) {
                mirrorBoss.isAlive = false;
                BossWavePoolClear(mirrorBoss.waves, mirrorBoss.waveCount);
                g_pendingReincarnationEndingDialog = true;
            }
        }
    }
    updateSwordWaves();

    float mapW = (currentMap == MAP_MAIN) ? MAP_W : NEWMAP_W, mapH = (currentMap == MAP_MAIN) ? MAP_H : NEWMAP_H;
    cameraX = (int)player.x - SCREEN_W / 2; cameraY = (int)player.y - SCREEN_H / 2;
    if (cameraX < 0) cameraX = 0; if (cameraY < 0) cameraY = 0;
    if (cameraX > (int)mapW - SCREEN_W) cameraX = (int)mapW - SCREEN_W;
    if (cameraY > (int)mapH - SCREEN_H) cameraY = (int)mapH - SCREEN_H;
    updateAim();
}

void updateWithInput() {
    if (g_bossFailOverlayTimer > 0) return;
    if (g_rebirthOverlayTimer > 0) {
        g_rebirthOverlayTimer--;
        if (g_rebirthOverlayTimer == 0) StartNewCycle();
        return;
    }
    if (g_bossLootScreenOpen) {
        if (GetAsyncKeyState(VK_RETURN) & 1) { g_bossLootScreenOpen = false; Sleep(200); }
        return;
    }
    if (gameState == 1 && (GetAsyncKeyState(VK_ESCAPE) & 1)) {
        if (CanWithdrawFromBossFight()) {
            WithdrawFromBossFight();
            Sleep(200);
            return;
        }
    }
    if (!g_bossInfoOpen) {
        HandleWorldReturnKey();
    }
    else {
        handleBossInfoInput();
        return;
    }
    if (showAncientBook) {
        int lineCount = GetAncientBookLineCount();
        int maxVisible = (SCREEN_H - ANCIENT_BOOK_MARGIN_Y - 44) / ANCIENT_BOOK_LINE_HEIGHT;
        int maxScroll = lineCount - maxVisible;
        if (maxScroll < 0) maxScroll = 0;
        if (GetAsyncKeyState(VK_UP) & 1) g_ancientBookScroll = max(0, g_ancientBookScroll - 1);
        if (GetAsyncKeyState(VK_DOWN) & 1) g_ancientBookScroll = min(maxScroll, g_ancientBookScroll + 1);
        if (GetAsyncKeyState(VK_PRIOR) & 1) g_ancientBookScroll = max(0, g_ancientBookScroll - maxVisible);
        if (GetAsyncKeyState(VK_NEXT) & 1) g_ancientBookScroll = min(maxScroll, g_ancientBookScroll + maxVisible);
        if (GetAsyncKeyState('G') & 1 || GetAsyncKeyState(VK_ESCAPE) & 1) {
            showAncientBook = false;
            g_ancientBookScroll = 0;
            Sleep(200);
        }
        return;
    }
    if (showStatsPanel) {
        if (GetAsyncKeyState('C') & 1 || GetAsyncKeyState(VK_ESCAPE) & 1) { showStatsPanel = false; Sleep(200); }
        return;
    }
    if (inShop) { handleShopInput(); return; }
    if (showInventory) return;

    if (GetAsyncKeyState('M') & 0x8000) { if (!g_lastM) { showFullMinimap = !showFullMinimap; g_lastM = true; } }
    else g_lastM = false;
    if (GetAsyncKeyState('Z') & 0x8000) { if (!g_lastZ) { showCollisionOverlay = !showCollisionOverlay; g_lastZ = true; } }
    else g_lastZ = false;
    if (GetAsyncKeyState('C') & 1) { showStatsPanel = !showStatsPanel; Sleep(200); }
    if (gameState == 0 && GetAsyncKeyState('G') & 1) {
        showAncientBook = !showAncientBook;
        if (showAncientBook) g_ancientBookScroll = 0;
        Sleep(200);
    }
    if (GetAsyncKeyState('B') & 1) {
        showInventory = !showInventory;
        if (showInventory) {
            currentPage = 0;
            flushmessage(EX_MOUSE | EX_KEY);
        }
        Sleep(200);
    }
    if (GetAsyncKeyState('N') & 1) { ShowSaveMenu(); Sleep(200); }
    if (GetAsyncKeyState('J') & 1) { ShowLoadMenu(); Sleep(200); }
    if (GetAsyncKeyState('P') & 1) { isPaused = !isPaused; Sleep(200); }
    if (isPaused && GetAsyncKeyState('O') & 1) { ShowExitConfirm(); Sleep(200); }
    if (GetAsyncKeyState('F') & 0x8000) {
        if (!g_flyKeyDown) {
            if (g_flyGroundedTimer <= 0) {
                if (flyMode) flyMode = false;
                else if (g_flightTimeBank > 0) flyMode = true;
            }
            g_flyKeyDown = true;
        }
    }
    else g_flyKeyDown = false;

    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        if (!g_meleeKeyDown && player.meleeCooldown <= 0 && !isCharging && player.attackTimer <= 0) {
            int md = GetMeleeDamage();
            bool dealtDamage = false;
            if (gameState == 0) {
                Monster* ml = NULL;
                int mlCount = 0;
                if (currentMap == MAP_MAIN) { ml = monsters; mlCount = MONSTER_COUNT; }
                else if (currentMap == MAP_FOREST) { ml = forestMonsters; mlCount = FOREST_MONSTER_COUNT; }
                else if (currentMap == MAP_MOUNTAIN) { ml = mountainMonsters; mlCount = MOUNTAIN_MONSTER_COUNT; }
                if (ml) {
                    for (int mi = 0; mi < mlCount; mi++) {
                        Monster& m = ml[mi];
                        if (!m.active) continue;
                        if (hypot(m.x - player.x, m.y - player.y) > ATTACK_RADIUS) continue;
                        float ang = atan2(m.y - player.y, m.x - player.x), diff = fabs(ang - getDirectionAngle(player.direction));
                        if (diff > M_PI) diff = 2 * M_PI - diff;
                        if (diff <= M_PI / 2) {
                            if (m.hp > 0) dealtDamage = true;
                            m.hp -= md; if (m.hp <= 0) { m.active = false; playerGold += 10; }
                        }
                    }
                }
                tryPickupItem(ATTACK_RADIUS);
            }
            else if (gameState == 1) {
                int bd = CalcDamageToBoss(md, bossType);
                if (bossType == 0 && forestBoss.isAlive) {
                    float dx = forestBoss.x - player.x, dy = forestBoss.y - player.y;
                    if (hypot(dx, dy) <= ATTACK_RADIUS && bd > 0) {
                        dealtDamage = true;
                        forestBoss.hp -= bd; if (forestBoss.hp < 0) forestBoss.hp = 0; applyBossPhaseOnMelee();
                    }
                }
                else if (bossType == 1 && stoneBoss.isAlive) {
                    if (hypot(stoneBoss.x - player.x, stoneBoss.y - player.y) <= ATTACK_RADIUS && bd > 0) {
                        dealtDamage = true;
                        stoneBoss.hp -= bd; if (stoneBoss.hp < 0) stoneBoss.hp = 0; applyBossPhaseOnMelee();
                    }
                }
                else if (bossType == 2) {
                    if (iceBoss.isAlive && hypot(iceBoss.x - player.x, iceBoss.y - player.y) <= ATTACK_RADIUS && bd > 0) {
                        dealtDamage = true;
                        iceBoss.hp -= bd; if (iceBoss.hp < 0) iceBoss.hp = 0; applyBossPhaseOnMelee();
                    }
                    for (int si = 0; si < iceServantCount; si++) {
                        IceServant& s = iceServants[si];
                        if (!s.active) continue;
                        if (hypot(s.x - player.x, s.y - player.y) <= ATTACK_RADIUS && bd > 0) {
                            dealtDamage = true;
                            s.hp -= bd;
                        }
                    }
                }
                else if (bossType == 3 && mirrorBoss.isAlive && g_mirrorRevealTimer <= 0) {
                    if (hypot(mirrorBoss.x - player.x, mirrorBoss.y - player.y) <= ATTACK_RADIUS) {
                        dealtDamage = true;
                        mirrorBoss.hp -= (float)GetMeleeDamage();
                        if (mirrorBoss.hp < 0) mirrorBoss.hp = 0;
                    }
                }
            }
            if (dealtDamage) TryConsumeWeaponDurOnDamageDealt();
            player.meleeCooldown = MELEE_COOLDOWN; player.attackTimer = ATTACK_DURATION; g_meleeKeyDown = true;
        }
    }
    else g_meleeKeyDown = false;

    bool ml = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    if (ml && CanUseSwordWave()) {
        if (!isCharging && player.meleeCooldown <= 0 && player.attackTimer <= 0) { isCharging = true; chargeTimer = 0; }
        if (isCharging) { chargeTimer += 1.f / 60.f; if (chargeTimer > MAX_CHARGE_TIME) chargeTimer = MAX_CHARGE_TIME; }
    }
    else if (isCharging) {
        if (CanUseSwordWave() && chargeTimer >= MIN_CHARGE_TIME
            && (IsSoulRingEquipped() || player.mp >= WAVE_COST_MP)) {
            float now = (float)GetTickCount() / 1000.f;
            int waveCount = IsEquippedEndlessSword() ? 3 : 1;
            if (swordWaveCount + waveCount <= MAX_PLAYER_WAVES && now - lastWaveTime >= SWORD_WAVE_COOLDOWN) {
                float ratio = (chargeTimer - MIN_CHARGE_TIME) / (MAX_CHARGE_TIME - MIN_CHARGE_TIME);
                if (ratio < 0) ratio = 0; if (ratio > 1) ratio = 1;
                int damage = GetWaveBaseDamage() + (int)(ratio * (GetWaveMaxDamage() - GetWaveBaseDamage()));
                float range = 400.f + ratio * 600.f;
                float baseAng = atan2f(aimWorldY, aimWorldX);
                if (IsEquippedEndlessSword()) {
                    PushPlayerSwordWave(baseAng, 0.f, damage, range);
                    PushPlayerSwordWave(baseAng, 0.26f, damage, range);
                    PushPlayerSwordWave(baseAng, -0.26f, damage, range);
                }
                else {
                    PushPlayerSwordWave(baseAng, 0.f, damage, range);
                }
                lastWaveTime = now;
                if (!IsSoulRingEquipped()) player.mp -= WAVE_COST_MP;
            }
        }
        isCharging = false; chargeTimer = 0;
    }

    player.isMoving = false;
    if (player.attackTimer <= 0 && !showFullMinimap && !isPaused) {
        float sp = flyMode ? PLAYER_FLY_SPEED : (isCharging ? PLAYER_CHARGE_WALK_SPEED : PLAYER_WALK_SPEED);
        if (IsIceMapDarknessActive()) sp *= 0.5f;
        if (player.slowTimer > 0) sp *= 0.5f;
        float mx = 0, my = 0;
        if (GetAsyncKeyState('W') & 0x8000) my -= sp;
        if (GetAsyncKeyState('S') & 0x8000) my += sp;
        if (GetAsyncKeyState('A') & 0x8000) mx -= sp;
        if (GetAsyncKeyState('D') & 0x8000) mx += sp;
        if (mx && my) { mx *= 0.7071f; my *= 0.7071f; }
        if (mx || my) {
            tryMove(player, mx, my); player.isMoving = true;
            if (!mx) { if (GetAsyncKeyState('W') & 0x8000) player.direction = 1; if (GetAsyncKeyState('S') & 0x8000) player.direction = 0; }
            else { if (GetAsyncKeyState('D') & 0x8000) player.direction = 3; else if (GetAsyncKeyState('A') & 0x8000) player.direction = 2; }
        }
        TryBronzeRingPickupKeys();
    }

}

void show() {
    cleardevice();
    if (g_bossLootScreenOpen) {
        drawBossLootScreen();
        FlushBatchDraw(); Sleep(16); return;
    }
    if (showAncientBook) {
        drawAncientBook();
        FlushBatchDraw(); Sleep(16); return;
    }
    if (showStatsPanel) {
        drawStatsPanel();
        FlushBatchDraw(); Sleep(16); return;
    }
    if (inShop) { drawShop(); FlushBatchDraw(); Sleep(16); return; }
    if (showInventory) {
        handleInventoryInput();
        drawInventory();
        FlushBatchDraw();
        Sleep(16);
        return;
    }
    if (g_rebirthOverlayTimer > 0) {
        settextcolor(RGB(255, 215, 0)); settextstyle(48, 0, _T("\u9ED1\u4F53"));
        TCHAR msg[64]; _stprintf_s(msg, L"\u7B2C %d \u8F6E\u56DE\u5B8C\u6210!", reincarnationCycle + 1);
        outtextxy(SCREEN_W / 2 - 220, SCREEN_H / 2, msg);
        FlushBatchDraw(); Sleep(16); return;
    }

    if (!showFullMinimap) {
        if (currentMap == MAP_MAIN) putimage(0, 0, SCREEN_W, SCREEN_H, &bigmap, cameraX, cameraY);
        else if (currentMap == MAP_FOREST) putimage(0, 0, SCREEN_W, SCREEN_H, &forestMapImg, cameraX, cameraY);
        else if (currentMap == MAP_MOUNTAIN) putimage(0, 0, SCREEN_W, SCREEN_H, &mountainMapImg, cameraX, cameraY);
        else if (currentMap == MAP_ICE) putimage(0, 0, SCREEN_W, SCREEN_H, &iceMapImg, cameraX, cameraY);

        if (showCollisionOverlay) {
            setfillcolor(RGB(255, 0, 0));
            for (int i = 0; i < SCREEN_W; i += 20) for (int j = 0; j < SCREEN_H; j += 20)
                if (!isWalkable(cameraX + i, cameraY + j)) solidrectangle(i, j, i + 4, j + 4);
        }

        if (gameState == 0) {
            if (currentMap == MAP_MAIN) {
                int d1x = PORTAL1_X - cameraX - PORTAL_SIZE / 2, d1y = PORTAL1_Y - cameraY - PORTAL_SIZE / 2;
                if (d1x > -PORTAL_SIZE && d1y > -PORTAL_SIZE && d1x < SCREEN_W && d1y < SCREEN_H)
                    putimageAlpha(d1x, d1y, PORTAL_SIZE, PORTAL_SIZE, &exchangeImg, 0, 0);
                int d2x = PORTAL2_X - cameraX - PORTAL_SIZE / 2, d2y = PORTAL2_Y - cameraY - PORTAL_SIZE / 2;
                if (d2x > -PORTAL_SIZE && d2y > -PORTAL_SIZE && d2x < SCREEN_W && d2y < SCREEN_H)
                    putimageAlpha(d2x, d2y, PORTAL_SIZE, PORTAL_SIZE, &exchangeImg, 0, 0);
                drawBronzeRingWorldPickup();
            }
            else if (currentMap == MAP_FOREST) {
                int px = FOREST_PORTAL_X - cameraX - PORTAL_SIZE / 2, py = FOREST_PORTAL_Y - cameraY - PORTAL_SIZE / 2;
                if (px > -PORTAL_SIZE && py > -PORTAL_SIZE && px < SCREEN_W && py < SCREEN_H)
                    putimageAlpha(px, py, PORTAL_SIZE, PORTAL_SIZE, &exchangeImg, 0, 0);
                int bx = FOREST_BOSS_TRIGGER_X - cameraX - PORTAL_SIZE / 2, by = FOREST_BOSS_TRIGGER_Y - cameraY - PORTAL_SIZE / 2;
                if (bx > -PORTAL_SIZE && by > -PORTAL_SIZE && bx < SCREEN_W && by < SCREEN_H)
                    putimageAlpha(bx, by, PORTAL_SIZE, PORTAL_SIZE, &exchangeImg, 0, 0);
            }
            else if (currentMap == MAP_MOUNTAIN) {
                int px = MOUNTAIN_PORTAL_X - cameraX - PORTAL_SIZE / 2, py = MOUNTAIN_PORTAL_Y - cameraY - PORTAL_SIZE / 2;
                if (px > -PORTAL_SIZE && py > -PORTAL_SIZE && px < SCREEN_W && py < SCREEN_H)
                    putimageAlpha(px, py, PORTAL_SIZE, PORTAL_SIZE, &exchangeImg, 0, 0);
                int bx = MOUNTAIN_BOSS_TRIGGER_X - cameraX - PORTAL_SIZE / 2, by = MOUNTAIN_BOSS_TRIGGER_Y - cameraY - PORTAL_SIZE / 2;
                if (bx > -PORTAL_SIZE && by > -PORTAL_SIZE && bx < SCREEN_W && by < SCREEN_H)
                    putimageAlpha(bx, by, PORTAL_SIZE, PORTAL_SIZE, &exchangeImg, 0, 0);
            }
        }

        if ((currentMap == MAP_FOREST || currentMap == MAP_MOUNTAIN) && gameState == 0) {
            for (int wi = 0; wi < worldItemCount; wi++) {
                WorldItem& item = worldItems[wi];
                if (!item.active) continue;
                int sx = (int)item.x - cameraX, sy = (int)item.y - cameraY;
                if (sx + 30 > 0 && sx - 30 < SCREEN_W && sy + 30 > 0 && sy - 30 < SCREEN_H) {
                    if (item.type == ITEM_WOOD && woodImg.getwidth() > 0) drawSprite(&woodImg, sx, sy, 0.1f, 0.1f);
                    else if (item.type == ITEM_HERB && herbImg.getwidth() > 0) drawSprite(&herbImg, sx, sy, 0.1f, 0.1f);
                    else if (item.type == ITEM_IRON && ironOreImg.getwidth() > 0) drawSprite(&ironOreImg, sx, sy, 0.1f, 0.1f);
                }
            }
        }
        if (currentMap == MAP_MAIN && gameState == 0 && foodItemActive) {
            int sx = FOOD_SPAWN_X - cameraX, sy = FOOD_SPAWN_Y - cameraY;
            if (sx + 30 > 0 && sx - 30 < SCREEN_W && sy + 30 > 0 && sy - 30 < SCREEN_H && foodImg.getwidth() > 0)
                drawSprite(&foodImg, sx, sy, 0.1f, 0.1f);
        }
        if (currentMap == MAP_MAIN && gameState == 0 && ShouldShowBronzeRingWorld()) {
            float ringDist = BronzeRingDistToPlayer();
            if (ringDist <= BRONZE_RING_PICKUP_RANGE + 220.f) {
                setbkmode(TRANSPARENT);
                settextcolor(ringDist <= BRONZE_RING_PICKUP_RANGE ? RGB(255, 215, 0) : RGB(200, 200, 200));
                settextstyle(18, 0, _T("\u9ED1\u4F53"));
                outtextxy(SCREEN_W / 2 - 240, SCREEN_H - 50,
                    ringDist <= BRONZE_RING_PICKUP_RANGE ? L"\u6309 Enter \u6216 E \u62FE\u53D6\u9752\u94DC\u6212\uFF08\u6216\u8FD1\u8DDD\u79BB\u653B\u51FB\uFF09"
                    : L"\u4E3B\u5730\u56FE\u53F3\u4E0B\u89D2\u6709\u9752\u94DC\u6212\uFF0C\u9760\u8FD1\u540E\u6309 Enter \u6216 E");
            }
        }
        if (g_bronzeRingPickupToast > 0) {
            setbkmode(TRANSPARENT);
            settextcolor(RGB(255, 215, 0));
            settextstyle(22, 0, _T("\u9ED1\u4F53"));
            outtextxy(SCREEN_W / 2 - 180, 90, L"\u5DF2\u83B7\u5F97\u9752\u94DC\u6212\uFF0C\u5251\u6C14\u5DF2\u89E3\u9501\uFF01");
        }

        if (gameState == 0) {
            for (int mi = 0; mi < MONSTER_COUNT; mi++) {
                Monster& m = monsters[mi];
                if (!m.active || currentMap != MAP_MAIN) continue;
                int sx = (int)m.x - cameraX, sy = (int)m.y - cameraY; drawMonster(m, sx, sy);
            }
            for (int mi = 0; mi < FOREST_MONSTER_COUNT; mi++) {
                Monster& m = forestMonsters[mi];
                if (!m.active || currentMap != MAP_FOREST) continue;
                int sx = (int)m.x - cameraX, sy = (int)m.y - cameraY; drawMonster(m, sx, sy);
            }
            for (int mi = 0; mi < MOUNTAIN_MONSTER_COUNT; mi++) {
                Monster& m = mountainMonsters[mi];
                if (!m.active || currentMap != MAP_MOUNTAIN) continue;
                int sx = (int)m.x - cameraX, sy = (int)m.y - cameraY; drawMonster(m, sx, sy);
            }
        }
        if (gameState == 1) {
            if (bossType == 0 && forestBoss.isAlive) {
                int bsx = (int)forestBoss.x - cameraX, bsy = (int)forestBoss.y - cameraY;
                drawForestBoss(bsx, bsy); drawShield(bsx, bsy); drawRootAttack();
                for (int bi = 0; bi < forestBoss.bulletCount; bi++) {
                    BossBullet& b = forestBoss.bullets[bi];
                    drawBullet(b, (int)b.x - cameraX, (int)b.y - cameraY);
                }
            }
            else if (bossType == 1 && stoneBoss.isAlive) {
                int bsx = (int)stoneBoss.x - cameraX, bsy = (int)stoneBoss.y - cameraY;
                drawStoneBoss(bsx, bsy);
                for (int bi = 0; bi < stoneBoss.bulletCount; bi++) {
                    BossBullet& b = stoneBoss.bullets[bi];
                    drawBullet(b, (int)b.x - cameraX, (int)b.y - cameraY);
                }
            }
            else if (bossType == 2 && iceBoss.isAlive) {
                int bsx = (int)iceBoss.x - cameraX, bsy = (int)iceBoss.y - cameraY;
                drawIceBoss(bsx, bsy); drawIceSpikes();
                for (int si = 0; si < iceServantCount; si++) {
                    IceServant& s = iceServants[si];
                    if (!s.active) continue;
                    int ssx = (int)s.x - cameraX, ssy = (int)s.y - cameraY;
                    drawIceServant(s, ssx, ssy);
                    for (int bi = 0; bi < s.bulletCount; bi++) {
                        BossBullet& b = s.bullets[bi];
                        drawBullet(b, (int)b.x - cameraX, (int)b.y - cameraY);
                    }
                }
                for (int wi = 0; wi < iceBoss.waveCount; wi++) {
                    SwordWave& w = iceBoss.waves[wi];
                    drawBossWave(w, (int)w.x - cameraX, (int)w.y - cameraY);
                }
            }
            else if (bossType == 3 && mirrorBoss.isAlive) {
                for (int wi = 0; wi < mirrorBoss.waveCount; wi++) {
                    SwordWave& w = mirrorBoss.waves[wi];
                    drawSwordWave(w, (int)w.x - cameraX, (int)w.y - cameraY);
                }
                int bsx = (int)mirrorBoss.x - cameraX, bsy = (int)mirrorBoss.y - cameraY;
                drawMirrorBoss(bsx, bsy);
            }
        }
        for (int wi = 0; wi < swordWaveCount; wi++) {
            SwordWave& w = swordWaves[wi];
            drawSwordWave(w, (int)w.x - cameraX, (int)w.y - cameraY);
        }
        int psx = (int)player.x - cameraX, psy = (int)player.y - cameraY;
        float curScaleX = player.displayScale, curScaleY = player.displayScale;
        if (!flyMode && !player.isMoving) {
            if (player.attackTimer > 0)
                curScaleY *= (1.f + 0.03f * (float)sin(player.animTimer));
            else {
                float breathe = 1.f + 0.04f * (float)sin(player.animTimer * 0.12f);
                curScaleX *= breathe;
                curScaleY *= breathe;
            }
        }
        IMAGE* cur = NULL;
        if (flyMode) {
            if (player.attackTimer > 0)
                cur = &img_sword_atk[player.direction];
            else
                cur = &img_walk[player.direction][1];
        }
        else if (player.attackTimer > 0) {
            cur = &img_sword_atk[player.direction];
        }
        else {
            cur = &img_walk[player.direction][player.frame];
        }
        drawSprite(cur, psx, psy, curScaleX, curScaleY);
        drawFlyModeOrbit(psx, psy);
        if (isCharging && hasAim && CanUseSwordWave()) {
            setlinestyle(PS_SOLID, 2); setlinecolor(RGB(255, 0, 0));
            circle(psx, psy, (int)AIM_CIRCLE_RADIUS);
            int ax = psx + (int)(aimWorldX * AIM_CIRCLE_RADIUS), ay = psy + (int)(aimWorldY * AIM_CIRCLE_RADIUS);
            setfillcolor(RGB(255, 0, 0)); solidcircle(ax, ay, 6);
            setlinecolor(RGB(255, 255, 0)); line(psx, psy, ax, ay);
        }
        if (isCharging) {
            float cp = chargeTimer / MAX_CHARGE_TIME;
            int barW = 60, barH = 8, barX = psx - barW / 2, barY = psy - player.radius - 15;
            setfillcolor(RGB(0, 0, 0)); solidrectangle(barX - 1, barY - 1, barX + barW + 1, barY + barH + 1);
            setfillcolor(RGB(0, 0, 255)); solidrectangle(barX, barY, barX + (int)(barW * cp), barY + barH);
        }
        drawPlayerUI(); drawGoldUI();
        if (gameState == 1) drawBossFightTimer();
        if (g_bossFailOverlayTimer > 0) {
            setfillcolor(RGBA(0, 0, 0, 160));
            solidrectangle(0, 0, SCREEN_W, SCREEN_H);
            settextcolor(RGB(255, 100, 100));
            settextstyle(36, 0, _T("\u9ED1\u4F53"));
            outtextxy(SCREEN_W / 2 - 200, SCREEN_H / 2 - 40, L"\u6311\u6218\u5931\u8D25");
            settextstyle(24, 0, _T("\u9ED1\u4F53"));
            settextcolor(WHITE);
            outtextxy(SCREEN_W / 2 - 240, SCREEN_H / 2 + 10, L"\u5DF2\u4F20\u9001\u81F3\u51FA\u751F\u70B9\uFF0C\u8840\u91CF\u4E3A 50");
        }
        settextcolor(YELLOW); settextstyle(20, 0, _T("\u9ED1\u4F53"));
        if (g_flyGroundedTimer > 0) {
            settextcolor(RGB(255, 140, 80));
            TCHAR gt[48];
            _stprintf_s(gt, L"\u51FB\u843D\uFF01\u65E0\u6CD5\u98DE\u884C (%d\u79D2)", (g_flyGroundedTimer + 59) / 60);
            outtextxy(20, 118, gt);
        }
        else if (flyMode) {
            settextcolor(RGB(120, 220, 255));
            TCHAR gt[48];
            _stprintf_s(gt, L"\u98DE\u884C\u4E2D %d\u79D2 (F\u5173\u95ED)", (g_flightTimeBank + 59) / 60);
            outtextxy(20, 118, gt);
        }
        else if (g_flightTimeBank > 0) {
            settextcolor(RGB(160, 200, 255));
            TCHAR gt[56];
            _stprintf_s(gt, L"\u50A8\u5907\u98DE\u884C %d\u79D2 (F\u5F00\u542F)", (g_flightTimeBank + 59) / 60);
            outtextxy(20, 118, gt);
        }
        else {
            settextcolor(YELLOW);
            outtextxy(20, 118, L"\u666E\u901A\u884C\u8D70 (\u9B54\u6CD5\u836F\u6C34\u53EF\u83B7\u5F97\u98DE\u884C\u65F6\u95F4)");
        }
        if (IsIceMapDarknessActive()) {
            settextcolor(RGB(180, 200, 255));
            outtextxy(20, 142, L"\u51B0\u5DDD\u9B54\u6C14\uFF1A\u901F\u5EA6\u51CF\u534A\uFF0C\u6BCF\u79D2\u6389\u884010 (\u88C5\u5907\u9547\u7075\u6212\u53EF\u62B5\u5FA1)");
        }
        if (g_mirrorRevealTimer > 0 && bossType == 3) {
            setfillcolor(RGBA(0, 0, 0, 180)); solidrectangle(0, 0, SCREEN_W, SCREEN_H);
            settextcolor(RGB(255, 80, 100)); settextstyle(40, 0, _T("\u9ED1\u4F53"));
            outtextxy(SCREEN_W / 2 - 280, SCREEN_H / 2 - 80, L"\u6697\u5F71\u9732\u51FA\u672C\u4F53\u2026\u2026");
            settextstyle(26, 0, _T("\u9ED1\u4F53"));
            settextcolor(RGB(255, 215, 0));
            outtextxy(SCREEN_W / 2 - 320, SCREEN_H / 2 - 10, L"\u4E0E\u4F60\u76F8\u540C\u7684\u5F71\u5B50\uFF0C\u5251\u6C14\u4E4B\u4E2D\u85CF\u7740\u771F\u6B63\u7684\u8F6E\u56DE");
            settextstyle(20, 0, _T("\u9ED1\u4F53"));
            settextcolor(WHITE);
            outtextxy(SCREEN_W / 2 - 120, SCREEN_H / 2 + 50, L"\u51FB\u8D25\u5B83\u624D\u80FD\u8FDB\u5165\u4E0B\u4E00\u8F6E\u56DE");
        }
        settextcolor(WHITE); settextstyle(16, 0, _T("\u9ED1\u4F53"));
        outtextxy(20, 150, L"N\u5B58 J\u8BFB B\u5305 C\u6570\u503C G\u6587\u4E66 P\u6682\u505C(O\u9000) F\u98DE M\u5730\u56FE Z\u78B0\u649E");
        if (isPaused) {
            settextstyle(50, 0, _T("\u9ED1\u4F53")); settextcolor(YELLOW);
            outtextxy(SCREEN_W / 2 - 80, SCREEN_H / 2 - 80, L"PAUSED");
            settextstyle(20, 0, _T("\u9ED1\u4F53")); settextcolor(WHITE);
            outtextxy(SCREEN_W / 2 - 100, SCREEN_H / 2 - 20, L"\u6309 P \u7EE7\u7EED");
            settextcolor(LIGHTRED);
            outtextxy(SCREEN_W / 2 - 100, SCREEN_H / 2 + 20, L"\u6309 O \u9000\u51FA\u6E38\u620F");
        }
        if (gameState == 0 && currentMap == MAP_MAIN) {
            float d1 = hypot(player.x - PORTAL1_X, player.y - PORTAL1_Y);
            float d2 = hypot(player.x - PORTAL2_X, player.y - PORTAL2_Y);
            if (d1 < PORTAL_RANGE || d2 < PORTAL_RANGE) {
                setbkmode(TRANSPARENT); settextcolor(RGB(255, 255, 0)); settextstyle(36, 0, _T("\u9ED1\u4F53"));
                outtextxy(SCREEN_W / 2 - 180, SCREEN_H / 2, L"\u786E\u5B9A\u8981\u8DF3\u8F6C\u5417\uff1f\u6309\u56DE\u8F66\u786E\u8BA4");
            }
        }
        drawShopTriggerHint();
        drawBossTriggerHints();
        drawIcePortalHint();
    }
    else {
        int ox = (SCREEN_W - MINIMAP_FULL_W) / 2, oy = (SCREEN_H - MINIMAP_FULL_H) / 2;
        putimage(ox, oy, MINIMAP_FULL_W, MINIMAP_FULL_H, &smallmap, 0, 0);
        setfillcolor(RED);
        solidcircle(ox + (int)(player.x / MAP_W * MINIMAP_FULL_W), oy + (int)(player.y / MAP_H * MINIMAP_FULL_H), 6);
        settextcolor(WHITE); outtextxy(20, 20, L"Full Minimap | Press M to Return");
    }
    if (g_bossInfoOpen) drawBossInfoPanel(g_bossInfoType);
    FlushBatchDraw();
    Sleep(16);
}

int main() {
    startup();
    while (1) {
        show();
        updateWithoutInput();
        updateWithInput();
        if (!gameRunning) break;
    }
    EndBatchDraw();
    StopMusic();
    if (g_bgmComInited) CoUninitialize();
    closegraph();
    return 0;
}
