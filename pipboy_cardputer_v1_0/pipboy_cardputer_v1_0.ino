/**
 * ╔══════════════════════════════════════════════════════════╗
 * ║          PIP-BOY 3000  TERMINAL  OPERATING  SYSTEM       ║
 * ║              VAULT-TEC  CERTIFIED  v4.3.0                ║
 * ╠══════════════════════════════════════════════════════════╣
 * ║  Target : M5Stack Cardputer Adv (ESP32-S3)              ║
 * ║  Display: ST7789V2  240x135                              ║
 * ║  IDE    : Arduino IDE (ino format)                       ║
 * ╠══════════════════════════════════════════════════════════╣
 * ║  v4.3.0 CHANGELOG:                                      ║
 * ║  - FIX: BtnA(G0) now works globally in ALL modal dialogs ║
 * ║    (edge-trigger latch consumed by loop() before modals)  ║
 * ║  - ENH: Boosted SPECIAL values now CYAN (high contrast)  ║
 * ║    bars remain GOLD for at-a-glance clarity              ║
 * ║  - NEW: Equipment diminishing returns (3 items = 1 pt)   ║
 * ║    Raw bonuses divided: div = max(1,(count+1)/2)         ║
 * ║  - NEW: Equipment aging — C fades, I grows with time     ║
 * ║    Cumulative age / 180 days → C-1 I+1 per tier          ║
 * ║  - CHG: Detail view shows effective bonus + age effects  ║
 * ╠══════════════════════════════════════════════════════════╣
 * ║  v4.2.3 CHANGELOG:                                      ║
 * ║  - CHG:  All 48 icons regenerated at 25x25 px (1-bit)  ║
 * ║  - CHG:  Icon selector grid uses 25x25 cells, 2 rows    ║
 * ║  - CHG:  include → icons_25x25_1bit.h (100 B/icon)      ║
 * ║  - NEW:  Equipment price field + avg daily cost calc    ║
 * ║  - FIX:  Detail view text shifted down, no title overlap  ║
 * ╠══════════════════════════════════════════════════════════╣
 * ║  v4.2.2 CHANGELOG:                                      ║
 * ║  v4.2.1 CHANGELOG:                                      ║
 * ║  - NEW:  48-icon equipment library (line art icons)    ║
 * ║  - CHG:  Icon data moved to external icons_25x25_1bit.h  ║
 * ║  - CHG:  Icon picker scrolls through 48 icons (4/screen) ║
 * ║  - CHG:  Item detail view Y offset raised (-10px)       ║
 * ╠══════════════════════════════════════════════════════════╣
 * ║  v4.2.0 CHANGELOG:                                      ║
 * ║  - NEW:  Equipment SPECIAL stat bonus editor (+/-)       ║
 * ║  - NEW:  Equipment icon library (AirPods Pro/AirPods)    ║
 * ║  - NEW:  Icon picker with golden frame selection         ║
 * ║  - NEW:  Item detail view (name/date/days/icon/bonus)    ║
 * ║  - NEW:  Equipment bonuses auto-apply to SPECIAL bars    ║
 * ║  - CHG:  EQIP up/down selects item, Enter views detail   ║
 * ║  - CHG:  Removed EQIP list submenu (simplified UX)       ║
 * ║  - FIX:  Screenshot SD init (correct SPI2 pins + CS=G12)║
 * ║  - NEW:  Progress bar during screenshot capture          ║
 * ║  - NEW:  EQIP module — equipment tracker (name+date)    ║
 * ║  - NEW:  CTRL+S screenshot to SD card (/picture/*.bmp)  ║
 * ║  - NEW:  6th tab (EQIP) with 40px tab width             ║
 * ║  - NEW:  FN+Backspace delete in equipment list          ║
 * ║  - NEW:  Vault Boy avatar replaced (user thumbs-up img)  ║
 * ║  - NEW:  Profile FN+Backspace delete (no menu option)    ║
 * ║  - NEW:  Profile UPDATE option (overwrites current)      ║
 * ║  - FIX:  Weight history flicker removed (dirty-flag)       ║
 * ║  - FIX:  Lora volume default 50% + persisted in NVS      ║
 * ║  - FIX:  Profile view flicker removed (dirty-flag)       ║
 * ║  - NEW:  DELETE PROFILE option (with confirm)            ║
 * ║  - NEW:  Compact 2-column profile layout                 ║
 * ║  - NEW:  Vault Boy profile entry on STAT (blink select)  ║
 * ║  - NEW:  Profile registration (name/sex/DOB/H/W/date)    ║
 * ║  - NEW:  Latest profile view + weight history sub-menu   ║
 * ║  - FIX:  Arrow keys now use isKeyPressed fallback (;/.)  ║
 * ║  - FIX:  Hint text moved above tab bar (no overlap)      ║
 * ║  - FIX:  enterRecordTime flicker removed (dirty-flag)    ║
 * ║  - FIX:  Arrow-key selection restored (modal guard)      ║
 * ║  - FIX:  g_bootTime now correctly preserves NVS value    ║
 * ║  - FIX:  Keyboard debounce (50ms) prevents double-trigger║
 * ║  - PERF: NVS dirty-flag batching reduces flash wear      ║
 * ║  - PERF: Fixed char buffers replace String in hot paths  ║
 * ║  - PERF: localtime_r() caching reduces CPU overhead      ║
 * ║  - SAFE: Bounds validation on all Preferences loads      ║
 * ║  - ROBUST: Input state machines hardened against noise   ║
 * ╚══════════════════════════════════════════════════════════╝
 *
 * Library dependencies (install via Library Manager):
 *   - M5Cardputer  by M5Stack
 *   - M5Unified    by M5Stack  (auto-installed with M5Cardputer)
 *
 * Board setup:
 *   - Boards Manager URL:
 *     https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index_cn.json
 *   - Board:      Tools → Board → M5Stack → M5Cardputer
 *   - Partition:  Tools → Partition Scheme → Default (1.25MB APP) is fine
 *
 * Controls:
 *   , / ←  → previous screen (left)
 *   / / → / Tab → next screen (right)
 *   ; / ↑  → CAL: move inline cursor up
 *   . / ↓  → CAL: move inline cursor down
 *   - / =  → Volume down/up (LORA)
 *   Enter   → CAL: activate; CAFF: add coffee; MEMO: new memo
 *           → LORA: PTT
 *   ESC/DEL → cancel / exit editor
 *   MEMO:   1-9 → edit memo (ESC save, BS backspace, < > move cursor)
 *           Fn+Backspace (DEL) → delete entire memo
 *
 *   Hardware key mapping:
 *     Arrow ← = FN + , (comma)
 *     Arrow → = FN + / (slash)
 *     Arrow ↑ = FN + ; (semicolon)
 *     Arrow ↓ = FN + . (period)
 */

#include <M5Cardputer.h>
#include <WiFi.h>
#include "time.h"
#include <Preferences.h>
#include "esp_task_wdt.h"
#include <SPI.h>           // v4.1.7: dedicated SPI for SD card
#include <SD.h>             // v4.1.6: screenshot to SD card
#include "FS.h"

// ============================================================
// CONFIGURATION  (config.h merged)
// ============================================================

// --- WIFI ---
// SSID/password are stored in NVS (preferences), entered by the user at runtime.
// No hardcoded credentials in the source.
// --- NTP ---
#define NTP_SERVER  "pool.ntp.org"
#define GMT_OFFSET  (8 * 3600)
#define DST_OFFSET  0

// --- DISPLAY ---
#define SCREEN_W  240
#define SCREEN_H  135

// Pip-Boy color palette (RGB565)
#define PIP_COL_BG       0x0881
#define PIP_COL_GREEN    0x07E0
#define PIP_COL_DIM      0x02C0
#define PIP_COL_GOLD     0xFFE0
#define PIP_COL_CYAN     0x07FF   // boosted SPECIAL value color — high contrast
#define PIP_COL_BAR_BG   0x0100
#define PIP_COL_BORDER   0x0320
#define PIP_COL_SKIN     0x02E0
#define PIP_COL_SUIT     0x0120

// --- S.P.E.C.I.A.L. ---
#define BASE_STR  5
#define BASE_PER  4
#define BASE_END  5
#define BASE_CHA  3
#define BASE_INT  6
#define BASE_AGI  4
#define BASE_LCK  7

// --- CAFFEINE / CALORIE BONUS ---
#define CAFF_BONUS_PER_MG    100
#define CAFF_END_BONUS       2
#define CAFF_END_MAX_BONUS   5
#define CAFF_HALF_LIFE_SEC   (4 * 3600)

#define CAL_BONUS_PER_KCAL   500
#define CAL_STR_BONUS        1
#define CAL_AGI_BONUS        1
#define CAL_MAX_BONUS        3

// --- STORAGE KEYS ---
#define PREFS_NAMESPACE  "pipboy"
#define KEY_CAFF_COUNT   "caff_cnt"
#define KEY_CAFF_BASE    "caff_"
#define KEY_CAL_COUNT    "cal_cnt"
#define KEY_CAL_BASE     "cal_"
#define KEY_MEMO_COUNT   "memo_cnt"
#define KEY_MEMO_BASE    "memo_"
#define KEY_CAL_GOAL     "cal_goal"
#define KEY_LAST_TIME    "last_time"
#define KEY_WIFI_SSID    "wifi_ssid"
#define KEY_WIFI_PASS    "wifi_pass"

// v4.1.3: Personal profile storage
#define KEY_PROF_COUNT   "prof_cnt"
#define KEY_PROF_BASE    "prof_"

// v4.1.5: Lora volume persistence
#define KEY_VOLUME       "lora_vol"

// v4.1.6: Equipment module
#define KEY_EQUIP_COUNT  "eqip_cnt"
#define KEY_EQUIP_BASE   "eqip_"

#define MAX_CAFF_RECORDS  50
#define MAX_CAL_RECORDS   50
#define MAX_MEMOS         20
#define MAX_PROFILES      20
#define MAX_EQUIP         20
#define MEMO_MAX_LEN      128
#define PROF_NAME_LEN     16
#define EQUIP_NAME_LEN    20

// --- KEYBOARD ---
#define KEY_DEBOUNCE_MS       50   // v4.1: prevent double-trigger
#define BATT_READ_INTERVAL_MS 30000
#define NVS_FLUSH_INTERVAL_MS 5000 // v4.1: batch NVS writes every 5s

// ============================================================
// DATA TYPES
// ============================================================

enum Screen : uint8_t { STAT = 0, EQIP = 1, CAL = 2, CAFF = 3, LORA = 4, MEMO = 5 };
#define NUM_SCREENS  6

struct SPCIAL {
    int8_t s, p, e, c, i, a, l;
};

struct CaffRecord {
    time_t  ts;
    int16_t mg;
};

struct CalRecord {
    time_t  ts;
    int16_t kcal;
};

// v4.1.3: Personal profile record
struct ProfileRecord {
    char     name[PROF_NAME_LEN];   // null-terminated
    char     gender;                // 'M' / 'F' / 'O'
    int16_t  birthYear;             // e.g. 1990
    uint8_t  birthMonth;            // 1-12
    uint8_t  birthDay;              // 1-31
    uint8_t  heightCm;              // 100-250
    uint8_t  weightKg;              // 30-200
    time_t   regTs;                 // registration date
};

// v4.1.6: Equipment record (updated v4.2: bonus + icon, v4.2.3: price)
struct EquipRecord {
    char     name[EQUIP_NAME_LEN];  // null-terminated
    time_t   purchaseTs;            // purchase date
    float    price;                 // purchase price (0 = not set)
    SPCIAL   bonus;                 // stat bonuses for SPECIAL
    int8_t   iconIndex;             // -1=no icon, 0+=icon library index
};

// ============================================================
// GLOBAL STATE
// ============================================================

Screen         g_screen     = STAT;
SPCIAL         g_base       = { BASE_STR, BASE_PER, BASE_END,
                                BASE_CHA, BASE_INT, BASE_AGI, BASE_LCK };
SPCIAL         g_current;
CaffRecord     g_caffLog[MAX_CAFF_RECORDS];
int            g_caffCount  = 0;
CalRecord      g_calLog[MAX_CAL_RECORDS];
int            g_calCount   = 0;
char           g_memos[MAX_MEMOS][MEMO_MAX_LEN + 1];
int            g_memoCount  = 0;
int32_t        g_calGoal   = 2200;
bool           g_timeValid = false;
time_t         g_bootTime  = 0;
unsigned long  g_lastClock = 0;
unsigned long  g_lastMetab = 0;
Preferences    g_prefs;
int8_t   g_memoView    = -1;
uint8_t  g_calMenuSel  = 0;

// v4.1.3: Personal profiles + STAT selection state
ProfileRecord  g_profiles[MAX_PROFILES];
int            g_profileCount = 0;
uint8_t        g_statSel      = 0;   // 0 = none, 1 = vault boy selected
unsigned long  g_lastStatBlink = 0;
bool           g_statBlinkOn   = true;

// v4.1.6: Equipment records
EquipRecord    g_equips[MAX_EQUIP];
int            g_equipCount = 0;
bool           g_equipDirty = false;

// v4.2: Equipment inline cursor for item selection
int            g_equipCursor = 0;    // -1 = no selection, 0+ = selected item index

// v4.1.7: Dedicated SPI bus for SD card (display uses SPI3, SD uses SPI2)
// Cardputer SD pins: SCK=GPIO40, MISO=GPIO39, MOSI=GPIO14, CS=GPIO12
static SPIClass g_sdSPI(SPI2_HOST);
static bool     g_sdReady = false;

// === V4.1: Keyboard debounce ===
static unsigned long g_lastKeyTime = 0;

// === V4.1.1: Modal flag — blocks handleNormalKeys during blocking dialogs ===
static bool    g_inModal    = false;

// === V4.2.6: BtnA (G0) global flag — captured in loop() before any processing ===
// wasPressed() is edge-triggered and every M5Cardputer.update() advances _oldPress,
// so the second call (in modal loops) always returns false.  This flag captures
// the press ONCE in loop() and is consumed by handleBtnAHome() in any modal.
static bool    g_btnAHome   = false;

// === V4.2.5: BtnA (G0) exit helper — call from any modal loop to return to STAT ===
// Returns true if G0 was pressed; saves state, clears modal, and redraws STAT.
static void drawStatFull();  // forward-decl: defined at ~L1178
static bool takeScreenshot(); // forward-decl: defined at ~L3453
static bool handleBtnAHome() {
    // v4.2.6: BtnA (G0) → return to STAT
    if (g_btnAHome) {
        g_btnAHome = false;
        g_inModal  = false;
        g_screen   = STAT;
        g_statSel  = 0;
        drawStatFull();
        return true;
    }
    // v4.3.3: Ctrl+S → screenshot (global, works in ALL modal loops)
    // handleBtnAHome() is called after every M5Cardputer.update() in every
    // modal while-loop, so this gives Ctrl+S coverage everywhere.
    //
    // CRITICAL: Do NOT call isChange() here — it is stateful (updates
    // _last_key_size internally) and can only return true ONCE per key
    // event. If we consume it here, the modal loop's own isChange() check
    // will always return false, breaking ALL key handling in the modal.
    //
    // Instead, use stateless APIs:
    //   - isPressed():  returns keyList().size(), no side effects
    //   - keysState():  returns reference to _keys_state_buffer, no side effects
    //   - isKeyPressed(): scans keyList(), no side effects
    // And do our own edge detection via a static flag to avoid retriggering
    // while Ctrl+S is held down.
    static bool s_ctrlSHeld = false;
    bool nowCtrlS = false;
    if (M5Cardputer.Keyboard.isPressed()) {
        Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();
        if (s.ctrl) {
            for (char c : s.word) {
                if (c == 'S' || c == 's') {
                    nowCtrlS = true;
                    break;
                }
            }
        }
    }
    if (nowCtrlS && !s_ctrlSHeld) {
        s_ctrlSHeld = true;
        g_inModal = false;
        takeScreenshot();
        return true;
    }
    if (!nowCtrlS) s_ctrlSHeld = false;
    return false;
}

// === V4.1: NVS dirty flag batching ===
static bool    g_caffDirty  = false;
static bool    g_calDirty   = false;
static bool    g_memoDirty  = false;
static unsigned long g_lastNvsFlush = 0;

// === V4.1: localtime cache (thread-safe localtime_r) ===
static time_t       g_tmCachedTime = 0;
static struct tm    g_tmCached;
static unsigned long g_lastTmFetch = 0;
#define TM_CACHE_MS  1000   // re-fetch at most once per second

// === V2: Audio state ===
// v4.1.5: default 50%, persisted in NVS
uint8_t   g_volume = 50;
static int8_t  g_battLevel    = -2;
static unsigned long g_lastBattRead = 0;

// ============================================================
// VAULT BOY HEAD BITMAP (40×40, 1-bit monochrome, MSB first)
// v4.1.5: updated with user-provided Vault Boy thumbs-up image
// ============================================================
const uint8_t VAULTBOY_HEAD[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x40, 0x00,
    0x00, 0x00, 0x00, 0xB0, 0x00,
    0x00, 0x00, 0x07, 0x08, 0x00,
    0x00, 0x00, 0x78, 0x04, 0x00,
    0x00, 0x00, 0x44, 0xC2, 0x00,
    0x00, 0x00, 0x48, 0x2D, 0x00,
    0x00, 0x00, 0x70, 0x06, 0x00,
    0x00, 0x00, 0x70, 0x42, 0x00,
    0x00, 0x00, 0x40, 0x04, 0x00,
    0x00, 0x00, 0x50, 0x84, 0x00,
    0x07, 0x00, 0x14, 0xC7, 0x00,
    0x09, 0x00, 0x08, 0x07, 0x00,
    0x11, 0x00, 0x8C, 0x02, 0x00,
    0x10, 0x00, 0x00, 0x80, 0x00,
    0x02, 0x00, 0x60, 0xC2, 0x00,
    0x09, 0x00, 0x40, 0x04, 0x00,
    0x7C, 0x80, 0x0C, 0x08, 0x00,
    0x82, 0x40, 0x20, 0x10, 0x00,
    0x70, 0x60, 0x10, 0x3C, 0x00,
    0x5F, 0x38, 0x6C, 0x27, 0x00,
    0x82, 0x3F, 0xE7, 0xC7, 0xC0,
    0x78, 0x7F, 0xF0, 0x0F, 0xE0,
    0x46, 0x3F, 0xFE, 0x3F, 0xF0,
    0x00, 0x3F, 0xFF, 0x3F, 0xF8,
    0x5F, 0x7F, 0xFF, 0x1F, 0xFC,
    0x1F, 0x7F, 0xFF, 0x1F, 0xFE,
    0x00, 0xFF, 0xFF, 0x1F, 0xFE,
    0x00, 0x10, 0xFF, 0x1F, 0xFE,
    0x00, 0x00, 0xFF, 0x0F, 0xFE,
    0x00, 0x00, 0xFF, 0x0F, 0xFE,
    0x00, 0x00, 0xFF, 0x0F, 0xFC,
    0x00, 0x00, 0xFF, 0x0F, 0xFC,
    0x00, 0x00, 0xFF, 0x8C, 0xF8,
    0x00, 0x00, 0x9F, 0x80, 0x30,
    0x00, 0x00, 0x80, 0x00, 0x10,
    0x00, 0x00, 0x80, 0x01, 0x00,
    0x00, 0x00, 0x80, 0x07, 0x20,
    0x00, 0x00, 0xF0, 0x1F, 0xA0,
    0x00, 0x00, 0xFF, 0xFF, 0xC0,
};

// ============================================================
// VAULT BOY FULL BODY BITMAP (55×60, 1-bit monochrome)
// ============================================================
const uint8_t VAULTBOY_FULL[] PROGMEM = {
    0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0E, 0x60, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xF4, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x01, 0xEB, 0x88, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x9F, 0xFC, 0x00, 0x00, 0x00,
    0x00, 0x01, 0xE0, 0x7C, 0x00, 0x00, 0x00,
    0x00, 0x01, 0xE1, 0x9E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x96, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xEB, 0x1E, 0x00, 0x00, 0x00,
    0x0E, 0x01, 0xFB, 0x1C, 0x00, 0x00, 0x00,
    0x1B, 0x01, 0x10, 0x1C, 0x00, 0x00, 0x00,
    0x12, 0x01, 0x10, 0x18, 0x00, 0x00, 0x00,
    0x12, 0x01, 0xC3, 0x0C, 0x00, 0x00, 0x00,
    0x12, 0x01, 0xFF, 0x08, 0x00, 0x00, 0x00,
    0x7B, 0x00, 0xBC, 0x38, 0x00, 0x00, 0x00,
    0xFD, 0x80, 0xD8, 0x60, 0x00, 0x00, 0x00,
    0x82, 0xC0, 0x60, 0xE0, 0x00, 0x00, 0x00,
    0xFE, 0x70, 0xF0, 0xDC, 0x00, 0x00, 0x00,
    0x8E, 0xFF, 0xDF, 0x9E, 0x00, 0x00, 0x00,
    0xF2, 0xFF, 0xE7, 0x3F, 0x80, 0x00, 0x00,
    0xFF, 0xFF, 0xF8, 0x7F, 0xC0, 0x00, 0x00,
    0x87, 0xFF, 0xFC, 0xFF, 0xE0, 0x00, 0x00,
    0xFF, 0xFF, 0xFC, 0x7F, 0xF0, 0x00, 0x00,
    0x7E, 0xFF, 0xFE, 0x7F, 0xF0, 0x00, 0x00,
    0x03, 0xFF, 0xFE, 0x7F, 0xF8, 0x00, 0x00,
    0x00, 0x79, 0xFE, 0x7F, 0xF8, 0x00, 0x00,
    0x00, 0x01, 0xFE, 0x3F, 0xF8, 0x00, 0x00,
    0x00, 0x01, 0xFE, 0x3F, 0xF8, 0x00, 0x00,
    0x00, 0x01, 0xFE, 0x3F, 0xF0, 0x00, 0x00,
    0x00, 0x01, 0xFE, 0x3F, 0xE0, 0x00, 0x00,
    0x00, 0x01, 0xFE, 0x37, 0xE0, 0x00, 0x00,
    0x00, 0x01, 0x3E, 0x00, 0xC0, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x06, 0xC0, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x0F, 0x80, 0x00, 0x00,
    0x00, 0x01, 0xC0, 0x7F, 0x80, 0x00, 0x00,
    0x00, 0x03, 0xFF, 0xFF, 0x80, 0x00, 0x00,
    0x00, 0x03, 0xFF, 0xFE, 0x00, 0x00, 0x00,
    0x00, 0x03, 0xFF, 0xFE, 0x00, 0x00, 0x00,
    0x00, 0x03, 0xFF, 0xFE, 0x00, 0x00, 0x00,
    0x00, 0x03, 0xFF, 0xFE, 0x00, 0x00, 0x00,
    0x00, 0x03, 0xFF, 0xFE, 0x00, 0x00, 0x00,
    0x00, 0x07, 0xFF, 0xFE, 0x00, 0x00, 0x00,
    0x00, 0x07, 0xFF, 0xFE, 0x00, 0x00, 0x00,
    0x00, 0x07, 0xFF, 0xFE, 0x00, 0x00, 0x00,
    0x00, 0x07, 0xFB, 0xFC, 0x00, 0x00, 0x00,
    0x00, 0x0F, 0xFB, 0xFC, 0x00, 0x00, 0x00,
    0x00, 0x0F, 0xFB, 0xFC, 0x00, 0x00, 0x00,
    0x00, 0x0F, 0xF3, 0xFC, 0x00, 0x00, 0x00,
    0x00, 0x1F, 0xF3, 0xF8, 0x00, 0x00, 0x00,
    0x00, 0x1F, 0xE3, 0xF8, 0x00, 0x00, 0x00,
    0x00, 0x1F, 0xE3, 0xFC, 0x00, 0x00, 0x00,
    0x00, 0x1F, 0xC3, 0xFE, 0x00, 0x00, 0x00,
    0x00, 0x1F, 0x81, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x1F, 0x00, 0x0E, 0x00, 0x00, 0x00,
    0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// ============================================================
// EQUIPMENT ICON LIBRARY (15×20, 1-bit monochrome, MSB first)
// 48 icons, 1920 bytes total flash
// ============================================================
#include "icons_25x25_1bit.h"

// Icon library catalog
#define ICON_COUNT 48
struct IconEntry {
    const char*   name;
    const uint8_t* data;
};
static const IconEntry g_iconLib[ICON_COUNT] = {
    {"MacBook",           ICON_MACBOOK},
    {"iPhone",            ICON_IPHONE},
    {"alarm",             ICON_ALARM},
    {"sunglasses",        ICON_SUNGLASSES},
    {"eyeglasses",        ICON_EYEGLASSES},
    {"jacket",            ICON_JACKET},
    {"shoe",              ICON_SHOE},
    {"tshirt",            ICON_TSHIRT},
    {"helmet",            ICON_HELMET},
    {"DJI",               ICON_DJI},
    {"watch",             ICON_WATCH},
    {"tent",              ICON_TENT},
    {"robotic vacuum",    ICON_ROBOT_VACUUM},
    {"projector",         ICON_PROJECTOR},
    {"suitcase",          ICON_SUITCASE},
    {"briefcase",         ICON_BRIEFCASE},
    {"handbag",           ICON_HANDBAG},
    {"duffle",            ICON_DUFFLE},
    {"snowboard",         ICON_SNOWBOARD},
    {"skateboard",        ICON_SKATEBOARD},
    {"tennis",            ICON_TENNIS},
    {"ns",                ICON_NS},
    {"steam",             ICON_STEAM},
    {"Xbox",              ICON_XBOX},
    {"PS",                ICON_PS},
    {"moped",             ICON_MOPED},
    {"scooter",           ICON_SCOOTER},
    {"motorcycle",        ICON_MOTORCYCLE},
    {"bicycle",           ICON_BICYCLE},
    {"appleTV",           ICON_APPLETV},
    {"AirPods1 case",     ICON_AIRPODS1_CASE},
    {"AppleWatch",        ICON_APPLEWATCH},
    {"magic mouse",       ICON_MAGIC_MOUSE},
    {"apple pencil",      ICON_APPLE_PENCIL},
    {"vision pro",        ICON_VISION_PRO},
    {"ipad",              ICON_IPAD},
    {"Mac Studio",        ICON_MAC_STUDIO},
    {"Macmini",           ICON_MACMINI},
    {"AirTag",            ICON_AIRTAG},
    {"keyboard",          ICON_KEYBOARD},
    {"camera",            ICON_CAMERA},
    {"counsel",           ICON_COUNSEL},
    {"car",               ICON_CAR},
    {"HomePod",           ICON_HOMEPOD},
    {"AirPodsPromax",     ICON_AIRPODS_MAX},
    {"AirPods case",      ICON_AIRPODS_CASE},
    {"mouse",             ICON_MOUSE},
    {"Mac Pro",           ICON_MAC_PRO},
};

// Forward declarations
static void addMemo();
static void memoEditor(int index);
static void drawVaultBoy(int x, int y);
static void drawVaultBoyHead(int ox, int oy);
static void setCalGoal();
static void drawStatFull();
static void drawCaffFull();
static void drawCalFull();
static void drawMemoFull();
static void drawLoraFull();
// v4.1.3: profile viewer / registration / weight history
static void viewProfile();
static void registerProfile(bool update = false);
static void viewWeightHistory();
// v4.1.6: equipment module + screenshot
static void drawEqipFull();
static void addEquipment();
static void viewEquipDetail(int index);       // v4.2: single item detail view
static int  selectEquipIcon();                // v4.2: icon picker
static void drawEquipIcon(int ox, int oy, int iconIdx, uint16_t fg, uint16_t bg);
static void saveEquips();
static void flushEquips();
static void loadEquips();
static bool takeScreenshot();

// ============================================================
// HELPER: DRAW TEXT WITH PIP-BOY CRT STYLE
// ============================================================

static void drawTextCenter(int y, const char* text, uint16_t color) {
    auto& d = M5Cardputer.Display;
    d.setFont(&fonts::Font0);
    d.setTextColor(color, PIP_COL_BG);
    int16_t tw = d.textWidth(text);
    d.setCursor((SCREEN_W - tw) / 2, y);
    d.print(text);
}

static void drawTextRight(int xRight, int y, const char* text, uint16_t color) {
    auto& d = M5Cardputer.Display;
    d.setFont(&fonts::Font0);
    d.setTextColor(color, PIP_COL_BG);
    int16_t tw = d.textWidth(text);
    d.setCursor(xRight - tw, y);
    d.print(text);
}

// ============================================================
// SCREEN LAYOUT: BATTERY STATUS ICON
// ============================================================

static void drawBatteryIcon(int xRight, int y, int level) {
    auto& d = M5Cardputer.Display;

    if (level < 0) {
        int px = xRight - 9;
        uint16_t c = PIP_COL_GREEN;
        d.drawRect(px, y, 7, 7, c);
        d.drawFastVLine(px + 1, y - 2, 3, c);
        d.drawFastVLine(px + 5, y - 2, 3, c);
        d.drawFastHLine(px + 7, y + 3, 2, c);
        return;
    }

    uint16_t col = (level <= 20) ? PIP_COL_GOLD : PIP_COL_GREEN;
    uint16_t bg  = PIP_COL_BORDER;

    char pctBuf[6];
    if (level == 0) {
        snprintf(pctBuf, sizeof(pctBuf), "0%%");
    } else {
        snprintf(pctBuf, sizeof(pctBuf), "%d%%", level);
    }
    d.setFont(&fonts::Font0);
    int16_t tw = d.textWidth(pctBuf);

    const int ICON_W = 17;
    const int ICON_H = 7;

    int iconX  = xRight - tw - 2 - ICON_W;
    int textX  = xRight - tw;

    d.setTextColor(col, bg);
    d.setCursor(textX, y);
    d.print(pctBuf);

    d.drawRect(iconX, y, 15, ICON_H, col);
    int tipX = iconX + 15;
    int tipY = y + 2;
    d.fillRect(tipX, tipY, 2, 3, col);
    d.fillRect(iconX + 1, y + 1, 13, ICON_H - 2, bg);

    int segs = level / 25;
    if (level > 0 && segs == 0) segs = 1;
    for (int s = 0; s < segs && s < 4; s++) {
        int sx = iconX + 1 + s * 4;
        if (sx + 3 > iconX + 14) break;
        d.fillRect(sx, y + 1, 3, ICON_H - 2, col);
    }
}

static int readBattLevel() {
    unsigned long now = millis();
    if (g_battLevel == -2 || now - g_lastBattRead >= BATT_READ_INTERVAL_MS) {
        g_battLevel    = M5Cardputer.Power.getBatteryLevel();
        g_lastBattRead = now;
    }
    return g_battLevel;
}

static void updateBatteryDisplay() {
    g_battLevel    = M5Cardputer.Power.getBatteryLevel();
    g_lastBattRead = millis();

    auto& d = M5Cardputer.Display;
    d.fillRect(SCREEN_W - 65, 0, 65, 14, PIP_COL_BORDER);
    drawBatteryIcon(SCREEN_W - 3, 3, g_battLevel);
}

// ============================================================
// SCREEN LAYOUT: HEADER
// ============================================================

static void drawHeader(const char* label) {
    auto& d = M5Cardputer.Display;
    d.fillRect(0, 0, SCREEN_W, 14, PIP_COL_BORDER);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BORDER);
    d.setFont(&fonts::Font0);
    d.setCursor(3, 3);
    d.print(label);

    char dateBuf[10];
    struct tm ti;
    if (g_timeValid && getLocalTime(&ti)) {
        strftime(dateBuf, sizeof(dateBuf), "%m/%d", &ti);
    } else {
        snprintf(dateBuf, sizeof(dateBuf), "--/--");
    }
    d.setFont(&fonts::Font0);
    d.setTextColor(PIP_COL_DIM, PIP_COL_BORDER);
    int16_t dw = d.textWidth(dateBuf);
    d.setCursor((SCREEN_W - dw) / 2, 3);
    d.print(dateBuf);

    int level = readBattLevel();
    drawBatteryIcon(SCREEN_W - 3, 3, level);
}

// ============================================================
// SCREEN LAYOUT: TAB BAR
// ============================================================

static void drawTabBar(Screen active) {
    auto& d = M5Cardputer.Display;
    const int TAB_H = 16;
    const int TAB_Y = SCREEN_H - TAB_H;
    const int TAB_W = SCREEN_W / NUM_SCREENS;
    const char* labels[] = { "STAT", "EQIP", "CAL ", "CAFF", "LORA", "MEMO" };

    d.fillRect(0, TAB_Y, SCREEN_W, TAB_H, PIP_COL_BORDER);

    for (int i = 0; i < NUM_SCREENS; i++) {
        int tx = i * TAB_W;
        bool sel = (i == (int)active);

        if (sel) {
            d.fillRect(tx, TAB_Y, TAB_W, TAB_H, PIP_COL_GREEN);
            d.setTextColor(PIP_COL_BG, PIP_COL_GREEN);
        } else {
            d.setTextColor(PIP_COL_DIM, PIP_COL_BORDER);
        }
        d.setFont(&fonts::Font0);
        int16_t tw = d.textWidth(labels[i]);
        d.setCursor(tx + (TAB_W - tw) / 2, TAB_Y + 3);
        d.print(labels[i]);
    }

    for (int i = 1; i < NUM_SCREENS; i++) {
        d.drawFastVLine(i * TAB_W, TAB_Y, TAB_H, PIP_COL_BG);
    }
}

// ============================================================
// TIME HELPERS (v4.1: localtime_r caching)
// ============================================================

// Thread-safe cached localtime access — avoids repeated mallocs from localtime()
static struct tm* getCachedTm(time_t t) {
    unsigned long now = millis();
    if (t != g_tmCachedTime || now - g_lastTmFetch >= TM_CACHE_MS) {
        localtime_r(&t, &g_tmCached);
        g_tmCachedTime = t;
        g_lastTmFetch  = now;
    }
    return &g_tmCached;
}

static time_t getNow() {
    if (g_timeValid) {
        struct tm ti;
        if (getLocalTime(&ti)) {
            return mktime(&ti);
        }
    }
    return g_bootTime + (millis() / 1000);
}

static void formatTime(char* buf, size_t len, time_t t) {
    struct tm* ti = getCachedTm(t);
    strftime(buf, len, "%H:%M", ti);
}

// ============================================================
// S.P.E.C.I.A.L. & METABOLISM CALCULATIONS
// ============================================================

static int calcTodayCalories() {
    time_t now = getNow();
    struct tm* nti = getCachedTm(now);
    int todayYday = nti->tm_yday;
    int todayYear = nti->tm_year;
    int total = 0;

    for (int i = 0; i < g_calCount; i++) {
        struct tm* rti = getCachedTm(g_calLog[i].ts);
        if (rti->tm_yday == todayYday && rti->tm_year == todayYear) {
            total += g_calLog[i].kcal;
        }
    }
    return total;
}

// v4.1.2: today-only caffeine stats (cups + total mg), resets after midnight
static void calcTodayCaffeine(int* outCups, int* outTotalMg) {
    time_t now = getNow();
    struct tm* nti = getCachedTm(now);
    int todayYday = nti->tm_yday;
    int todayYear = nti->tm_year;
    int cups  = 0;
    int total = 0;

    for (int i = 0; i < g_caffCount; i++) {
        struct tm* rti = getCachedTm(g_caffLog[i].ts);
        if (rti->tm_yday == todayYday && rti->tm_year == todayYear) {
            total += g_caffLog[i].mg;
            cups++;
        }
    }
    if (outCups)    *outCups    = cups;
    if (outTotalMg) *outTotalMg = total;
}

static int calcActiveCaffeine() {
    time_t now = getNow();
    int total = 0;

    for (int i = 0; i < g_caffCount; i++) {
        long elapsed = now - g_caffLog[i].ts;
        if (elapsed <= 0) {
            total += g_caffLog[i].mg;
        } else if (elapsed < CAFF_HALF_LIFE_SEC) {
            total += g_caffLog[i].mg - (g_caffLog[i].mg * elapsed / CAFF_HALF_LIFE_SEC);
        }
    }
    return total;
}

static void calcSpecial() {
    g_current = g_base;

    int activeCaff = calcActiveCaffeine();
    int endBonus = (activeCaff / CAFF_BONUS_PER_MG) * CAFF_END_BONUS;
    if (endBonus > CAFF_END_MAX_BONUS) endBonus = CAFF_END_MAX_BONUS;
    g_current.e += endBonus;

    int todayKcal = calcTodayCalories();
    int calTiers = todayKcal / CAL_BONUS_PER_KCAL;
    int strBonus = calTiers * CAL_STR_BONUS;
    int agiBonus = calTiers * CAL_AGI_BONUS;
    if (strBonus > CAL_MAX_BONUS) strBonus = CAL_MAX_BONUS;
    if (agiBonus > CAL_MAX_BONUS) agiBonus = CAL_MAX_BONUS;
    g_current.s += strBonus;
    g_current.a += agiBonus;

    // v4.2.6: Equipment stat bonuses — fractional accumulation with
    // diminishing returns.  Raw bonuses are summed then divided by a
    // dim-factor: max(1, (count+1)/2).  E.g. 3 items each +1 → 3/2 = +1.
    if (g_equipCount > 0) {
        int div = max(1, (g_equipCount + 1) / 2);
        int sumS = 0, sumP = 0, sumE = 0, sumC = 0, sumI = 0, sumA = 0, sumL = 0;
        for (int i = 0; i < g_equipCount; i++) {
            sumS += g_equips[i].bonus.s;
            sumP += g_equips[i].bonus.p;
            sumE += g_equips[i].bonus.e;
            sumC += g_equips[i].bonus.c;
            sumI += g_equips[i].bonus.i;
            sumA += g_equips[i].bonus.a;
            sumL += g_equips[i].bonus.l;
        }
        g_current.s += sumS / div;
        g_current.p += sumP / div;
        g_current.e += sumE / div;
        g_current.c += sumC / div;
        g_current.i += sumI / div;
        g_current.a += sumA / div;
        g_current.l += sumL / div;

        // v4.2.6: Aging mechanic — equipment ages, Charisma fades but
        // Intelligence grows.  Cumulative age (sum of all items' days)
        // converts at 180 days per point.
        time_t now = getNow();
        long totalAgeDays = 0;
        for (int i = 0; i < g_equipCount; i++) {
            totalAgeDays += (now - g_equips[i].purchaseTs) / 86400L;
        }
        int agePoints = totalAgeDays / 180;
        g_current.c -= agePoints;
        g_current.i += agePoints;
    }
}

// ============================================================
// STORAGE: PREFERENCES PERSISTENCE (v4.1: dirty flag batching)
// ============================================================

// --- Caffeine ---
static void saveCaffLog() {
    g_caffDirty = true;  // v4.1: defer actual write
}

// Flush caffeine log to NVS (called from loop() when dirty)
static void flushCaffLog() {
    if (!g_caffDirty) return;
    g_prefs.putInt(KEY_CAFF_COUNT, g_caffCount);
    for (int i = 0; i < g_caffCount; i++) {
        char key[32];
        snprintf(key, sizeof(key), "%s%d_ts", KEY_CAFF_BASE, i);
        g_prefs.putULong64(key, (uint64_t)g_caffLog[i].ts);
        snprintf(key, sizeof(key), "%s%d_mg", KEY_CAFF_BASE, i);
        g_prefs.putInt(key, g_caffLog[i].mg);
    }
    g_caffDirty = false;
}

static void loadCaffLog() {
    g_caffCount = 0;
    int count = g_prefs.getInt(KEY_CAFF_COUNT, 0);
    // v4.1: bounds validation
    if (count < 0 || count > MAX_CAFF_RECORDS) count = 0;

    for (int i = 0; i < count && i < MAX_CAFF_RECORDS; i++) {
        CaffRecord rec;
        char key[32];
        snprintf(key, sizeof(key), "%s%d_ts", KEY_CAFF_BASE, i);
        rec.ts = (time_t)g_prefs.getULong64(key, 0);
        snprintf(key, sizeof(key), "%s%d_mg", KEY_CAFF_BASE, i);
        rec.mg = g_prefs.getInt(key, 0);
        if (rec.ts > 0 && rec.mg > 0) {
            g_caffLog[g_caffCount++] = rec;
        }
    }
}

// --- Calories ---
static void saveCalLog() {
    g_calDirty = true;
}

static void flushCalLog() {
    if (!g_calDirty) return;
    g_prefs.putInt(KEY_CAL_COUNT, g_calCount);
    for (int i = 0; i < g_calCount; i++) {
        char key[32];
        snprintf(key, sizeof(key), "%s%d_ts", KEY_CAL_BASE, i);
        g_prefs.putULong64(key, (uint64_t)g_calLog[i].ts);
        snprintf(key, sizeof(key), "%s%d_kcal", KEY_CAL_BASE, i);
        g_prefs.putInt(key, g_calLog[i].kcal);
    }
    g_calDirty = false;
}

static void loadCalLog() {
    g_calCount = 0;
    int count = g_prefs.getInt(KEY_CAL_COUNT, 0);
    // v4.1: bounds validation
    if (count < 0 || count > MAX_CAL_RECORDS) count = 0;

    for (int i = 0; i < count && i < MAX_CAL_RECORDS; i++) {
        CalRecord rec;
        char key[32];
        snprintf(key, sizeof(key), "%s%d_ts", KEY_CAL_BASE, i);
        rec.ts = (time_t)g_prefs.getULong64(key, 0);
        snprintf(key, sizeof(key), "%s%d_kcal", KEY_CAL_BASE, i);
        rec.kcal = g_prefs.getInt(key, 0);
        if (rec.ts > 0 && rec.kcal > 0) {
            g_calLog[g_calCount++] = rec;
        }
    }
}

// --- Memos ---
static void saveMemos() {
    g_memoDirty = true;
}

// v4.1.3: --- Personal Profiles ---
static bool g_profDirty = false;

static void saveProfiles() {
    g_profDirty = true;
}

static void flushProfiles() {
    if (!g_profDirty) return;
    g_prefs.putInt(KEY_PROF_COUNT, g_profileCount);
    for (int i = 0; i < g_profileCount; i++) {
        char key[32];
        snprintf(key, sizeof(key), "%s%d_name",   KEY_PROF_BASE, i);
        g_prefs.putString(key, g_profiles[i].name);
        snprintf(key, sizeof(key), "%s%d_gender", KEY_PROF_BASE, i);
        g_prefs.putChar(key, g_profiles[i].gender);
        snprintf(key, sizeof(key), "%s%d_byr",    KEY_PROF_BASE, i);
        g_prefs.putInt(key, g_profiles[i].birthYear);
        snprintf(key, sizeof(key), "%s%d_bmo",    KEY_PROF_BASE, i);
        g_prefs.putUChar(key, g_profiles[i].birthMonth);
        snprintf(key, sizeof(key), "%s%d_bday",   KEY_PROF_BASE, i);
        g_prefs.putUChar(key, g_profiles[i].birthDay);
        snprintf(key, sizeof(key), "%s%d_h",      KEY_PROF_BASE, i);
        g_prefs.putUChar(key, g_profiles[i].heightCm);
        snprintf(key, sizeof(key), "%s%d_w",      KEY_PROF_BASE, i);
        g_prefs.putUChar(key, g_profiles[i].weightKg);
        snprintf(key, sizeof(key), "%s%d_ts",     KEY_PROF_BASE, i);
        g_prefs.putULong64(key, (uint64_t)g_profiles[i].regTs);
    }
    g_profDirty = false;
}

static void loadProfiles() {
    g_profileCount = 0;
    int count = g_prefs.getInt(KEY_PROF_COUNT, 0);
    if (count < 0 || count > MAX_PROFILES) count = 0;

    for (int i = 0; i < count && i < MAX_PROFILES; i++) {
        ProfileRecord rec;
        memset(&rec, 0, sizeof(rec));
        char key[32];
        snprintf(key, sizeof(key), "%s%d_name",   KEY_PROF_BASE, i);
        String nm = g_prefs.getString(key, "");
        strncpy(rec.name, nm.c_str(), PROF_NAME_LEN - 1);
        rec.name[PROF_NAME_LEN - 1] = '\0';

        snprintf(key, sizeof(key), "%s%d_gender", KEY_PROF_BASE, i);
        rec.gender = g_prefs.getChar(key, 'M');
        if (rec.gender != 'M' && rec.gender != 'F' && rec.gender != 'O')
            rec.gender = 'M';

        snprintf(key, sizeof(key), "%s%d_byr",    KEY_PROF_BASE, i);
        rec.birthYear = (int16_t)g_prefs.getInt(key, 1990);

        snprintf(key, sizeof(key), "%s%d_bmo",    KEY_PROF_BASE, i);
        rec.birthMonth = g_prefs.getUChar(key, 1);

        snprintf(key, sizeof(key), "%s%d_bday",   KEY_PROF_BASE, i);
        rec.birthDay = g_prefs.getUChar(key, 1);

        snprintf(key, sizeof(key), "%s%d_h",      KEY_PROF_BASE, i);
        rec.heightCm = g_prefs.getUChar(key, 170);

        snprintf(key, sizeof(key), "%s%d_w",      KEY_PROF_BASE, i);
        rec.weightKg = g_prefs.getUChar(key, 65);

        snprintf(key, sizeof(key), "%s%d_ts",     KEY_PROF_BASE, i);
        rec.regTs = (time_t)g_prefs.getULong64(key, 0);

        // validate essential fields
        if (rec.name[0] != '\0' && rec.birthYear > 1900 && rec.regTs > 0) {
            g_profiles[g_profileCount++] = rec;
        }
    }
}

static void flushMemos() {
    if (!g_memoDirty) return;
    g_prefs.putInt(KEY_MEMO_COUNT, g_memoCount);
    for (int i = 0; i < g_memoCount; i++) {
        char key[32];
        snprintf(key, sizeof(key), "%s%d", KEY_MEMO_BASE, i);
        g_prefs.putString(key, g_memos[i]);
    }
    g_memoDirty = false;
}

static void loadMemos() {
    g_memoCount = 0;
    int count = g_prefs.getInt(KEY_MEMO_COUNT, 0);
    // v4.1: bounds validation
    if (count < 0 || count > MAX_MEMOS) count = 0;

    for (int i = 0; i < count && i < MAX_MEMOS; i++) {
        char key[32];
        snprintf(key, sizeof(key), "%s%d", KEY_MEMO_BASE, i);
        String s = g_prefs.getString(key, "");
        if (s.length() > 0) {
            strncpy(g_memos[g_memoCount], s.c_str(), MEMO_MAX_LEN);
            g_memos[g_memoCount][MEMO_MAX_LEN] = '\0';
            g_memoCount++;
        }
    }
}

// v4.1: flush all dirty NVS writes immediately (critical moments)
static void flushAllNvs() {
    flushCaffLog();
    flushCalLog();
    flushMemos();
    flushProfiles();
    flushEquips();
}

// v4.1.5: volume persistence
static void flushVolume() {
    g_prefs.putUChar(KEY_VOLUME, g_volume);
}

// ============================================================
// v4.1.6: EQUIPMENT STORAGE
// ============================================================

static void saveEquips() {
    g_equipDirty = true;
}

static void flushEquips() {
    if (!g_equipDirty) return;
    g_prefs.putInt(KEY_EQUIP_COUNT, g_equipCount);
    for (int i = 0; i < g_equipCount; i++) {
        char key[32];
        snprintf(key, sizeof(key), "%s%d_name", KEY_EQUIP_BASE, i);
        g_prefs.putString(key, g_equips[i].name);
        snprintf(key, sizeof(key), "%s%d_ts", KEY_EQUIP_BASE, i);
        g_prefs.putULong64(key, (uint64_t)g_equips[i].purchaseTs);
        // v4.2.3: price
        snprintf(key, sizeof(key), "%s%d_price", KEY_EQUIP_BASE, i);
        g_prefs.putFloat(key, g_equips[i].price);
        // v4.2: bonus as packed string
        snprintf(key, sizeof(key), "%s%d_bonus", KEY_EQUIP_BASE, i);
        char bstr[32];
        snprintf(bstr, sizeof(bstr), "%d,%d,%d,%d,%d,%d,%d",
            g_equips[i].bonus.s, g_equips[i].bonus.p, g_equips[i].bonus.e,
            g_equips[i].bonus.c, g_equips[i].bonus.i, g_equips[i].bonus.a,
            g_equips[i].bonus.l);
        g_prefs.putString(key, bstr);
        // v4.2: icon index
        snprintf(key, sizeof(key), "%s%d_icon", KEY_EQUIP_BASE, i);
        g_prefs.putChar(key, g_equips[i].iconIndex);
    }
    g_equipDirty = false;
}

static void loadEquips() {
    g_equipCount = 0;
    int count = g_prefs.getInt(KEY_EQUIP_COUNT, 0);
    if (count < 0 || count > MAX_EQUIP) count = 0;

    for (int i = 0; i < count && i < MAX_EQUIP; i++) {
        EquipRecord rec;
        memset(&rec, 0, sizeof(rec));
        char key[32];
        snprintf(key, sizeof(key), "%s%d_name", KEY_EQUIP_BASE, i);
        String nm = g_prefs.getString(key, "");
        strncpy(rec.name, nm.c_str(), EQUIP_NAME_LEN - 1);
        rec.name[EQUIP_NAME_LEN - 1] = '\0';

        snprintf(key, sizeof(key), "%s%d_ts", KEY_EQUIP_BASE, i);
        rec.purchaseTs = (time_t)g_prefs.getULong64(key, 0);

        // v4.2.3: load price
        snprintf(key, sizeof(key), "%s%d_price", KEY_EQUIP_BASE, i);
        rec.price = g_prefs.getFloat(key, 0.0f);

        // v4.2: load bonus
        snprintf(key, sizeof(key), "%s%d_bonus", KEY_EQUIP_BASE, i);
        String bstr = g_prefs.getString(key, "");
        if (bstr.length() > 0) {
            int vals[7] = {0};
            sscanf(bstr.c_str(), "%d,%d,%d,%d,%d,%d,%d",
                &vals[0], &vals[1], &vals[2], &vals[3],
                &vals[4], &vals[5], &vals[6]);
            rec.bonus.s = vals[0]; rec.bonus.p = vals[1]; rec.bonus.e = vals[2];
            rec.bonus.c = vals[3]; rec.bonus.i = vals[4]; rec.bonus.a = vals[5];
            rec.bonus.l = vals[6];
        }

        // v4.2: load icon
        snprintf(key, sizeof(key), "%s%d_icon", KEY_EQUIP_BASE, i);
        rec.iconIndex = g_prefs.getChar(key, -1);

        if (rec.name[0] != '\0' && rec.purchaseTs > 0) {
            g_equips[g_equipCount++] = rec;
        }
    }
}

static void loadData() {
    g_prefs.begin(PREFS_NAMESPACE, false);
    g_calGoal = g_prefs.getInt(KEY_CAL_GOAL, 2200);
    // v4.1: bounds validation
    if (g_calGoal < 100 || g_calGoal > 9999) g_calGoal = 2200;

    // v4.1.5: restore volume
    g_volume = g_prefs.getUChar(KEY_VOLUME, 50);
    if (g_volume > 100) g_volume = 50;

    uint64_t savedTime = g_prefs.getULong64(KEY_LAST_TIME, 0);
    // v4.1: only override fallback if valid saved time exists
    if (savedTime > 1000000000) g_bootTime = (time_t)savedTime;

    loadCaffLog();
    loadCalLog();
    loadMemos();
    loadProfiles();
    loadEquips();
}

// ============================================================
// VAULT BOY GRAPHICS
// ============================================================

static void drawVaultBoyHead(int ox, int oy) {
    auto& d = M5Cardputer.Display;
    d.drawBitmap(ox, oy, VAULTBOY_HEAD, 40, 40, PIP_COL_GREEN, PIP_COL_BG);
}

static void drawVaultBoy(int ox, int oy) {
    auto& d = M5Cardputer.Display;
    d.drawBitmap(ox, oy, VAULTBOY_FULL, 55, 60, PIP_COL_GREEN, PIP_COL_BG);
}

// ============================================================
// SCREEN: STAT — CLOCK + SPECIAL + VAULT BOY
// ============================================================

static void drawStatClock() {
    auto& d = M5Cardputer.Display;
    time_t now = getNow();
    struct tm* ti = getCachedTm(now);

    char tbuf[16];
    strftime(tbuf, sizeof(tbuf), "%H:%M:%S", ti);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font4);
    d.setCursor(3, 26);
    d.print(tbuf);

    char dbuf[20];
    strftime(dbuf, sizeof(dbuf), "%a %m/%d/%y", ti);
    d.setFont(&fonts::Font0);
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(3, 55);
    d.print(dbuf);
}

static void drawStatSpecial() {
    auto& d = M5Cardputer.Display;
    const int SX = 120;
    const int SW = SCREEN_W - SX - 3;

    calcSpecial();
    d.setFont(&fonts::Font0);

    const char* names[] = {"S","P","E","C","I","A","L"};
    const int8_t* vals = &g_current.s;

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setCursor(SX, 17);
    d.print("> S.P.E.C.I.A.L.");

    d.drawFastHLine(SX, 25, SW, PIP_COL_BORDER);

    for (int i = 0; i < 7; i++) {
        int y = 30 + i * 10;
        int val = vals[i];
        int8_t baseVal = (&g_base.s)[i];
        bool boosted = (val > baseVal);  // v4.2.6: universal check — any stat above base

        // v4.2.6: boosted value text = CYAN (high contrast), bars = GOLD
        uint16_t valCol = boosted ? PIP_COL_CYAN  : PIP_COL_GREEN;
        uint16_t barCol = boosted ? PIP_COL_GOLD  : PIP_COL_GREEN;

        d.setTextColor(valCol, PIP_COL_BG);
        d.setCursor(SX, y);
        d.printf("%s %02d", names[i], val);

        int barX = SX + 28;
        int blocks = val > 10 ? 10 : val;
        for (int b = 0; b < 10; b++) {
            d.setCursor(barX + b * 6, y);
            if (b < blocks) {
                d.setTextColor(barCol, PIP_COL_BG);
                d.print("\xDB");
            } else {
                d.setTextColor(PIP_COL_BAR_BG, PIP_COL_BG);
                d.print("\xB0");
            }
        }
    }
}

static void drawStatFull() {
    auto& d = M5Cardputer.Display;
    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);

    drawHeader("STAT");
    drawTabBar(STAT);

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font0);
    d.setCursor(3, 17);
    d.print("> PIP-BOY 3000");

    drawStatClock();
    drawVaultBoyHead(8, 67);
    drawStatSpecial();

    // v4.1.3: selection hint under vault boy
    if (g_statSel == 1) {
        d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
        d.setCursor(3, 110);
        d.print("[ENTER] PROFILE");
    } else {
        d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
        d.setCursor(3, 110);
        d.print("[^/v] select vault boy");
    }
}

// v4.1.3: draws/removes blinking frame around vault boy head.
// Called from loop() every 500ms when on STAT screen with selection.
static void drawStatSelectionFrame() {
    if (g_screen != STAT) return;
    auto& d = M5Cardputer.Display;
    // Vault boy is at (8, 67) size 40x40 — frame slightly outside
    int fx = 6, fy = 65, fw = 44, fh = 44;
    uint16_t col = (g_statSel == 1 && g_statBlinkOn) ? PIP_COL_GOLD : PIP_COL_BG;
    d.drawRect(fx, fy, fw, fh, col);
}

static void drawStatClockPartial() {
    auto& d = M5Cardputer.Display;
    time_t now = getNow();
    struct tm* ti = getCachedTm(now);

    d.fillRect(3, 26, 72, 35, PIP_COL_BG);

    char tbuf[16];
    strftime(tbuf, sizeof(tbuf), "%H:%M:%S", ti);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font4);
    d.setCursor(3, 26);
    d.print(tbuf);

    d.setFont(&fonts::Font0);
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    char dbuf[20];
    strftime(dbuf, sizeof(dbuf), "%a %m/%d/%y", ti);
    d.setCursor(3, 55);
    d.print(dbuf);
}

// ============================================================
// SCREEN: CAFF — CAFFEINE TRACKER
// ============================================================

static void drawCaffMetabolism() {
    auto& d = M5Cardputer.Display;
    d.setFont(&fonts::Font0);

    int y = 56;

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setCursor(3, y);
    d.print("> METABOLISM (4H half-life)");
    y += 12;

    int activeMg = calcActiveCaffeine();
    // v4.1.2: total is today's intake, not all-time
    int todayCups = 0, todayMg = 0;
    calcTodayCaffeine(&todayCups, &todayMg);

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setCursor(3, y);
    d.printf("ACTIVE: %d / %d mg", activeMg, todayMg);

    int pct = todayMg > 0 ? (activeMg * 100 / todayMg) : 0;
    d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
    d.setCursor(132, y);
    d.printf("%d%%", pct);
    y += 14;

    int barX = 3;
    int barW = SCREEN_W - 6;
    int barH = 10;
    d.fillRect(barX, y, barW, barH, PIP_COL_BAR_BG);

    int fillW = todayMg > 0 ? (barW * activeMg / todayMg) : 0;
    if (fillW > 0) {
        d.fillRect(barX, y, fillW, barH, PIP_COL_GREEN);
    }

    for (int sx = barX; sx < barX + barW; sx += 3) {
        d.drawFastVLine(sx, y, barH, PIP_COL_BG);
    }
    y += barH + 3;

    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(barX, y);
    d.print("0H");
    drawTextCenter(y, "2H", PIP_COL_DIM);
    drawTextRight(barX + barW, y, "4H", PIP_COL_DIM);
    y += 11;

    d.drawFastHLine(3, y, SCREEN_W - 6, PIP_COL_BORDER);
    y += 4;  // tight fit above tab bar

    if (g_caffCount > 0) {
        time_t now = getNow();
        auto& r = g_caffLog[0];
        long elapsed = now - r.ts;
        if (elapsed > CAFF_HALF_LIFE_SEC) elapsed = CAFF_HALF_LIFE_SEC;
        int remainMg = r.mg - (r.mg * elapsed / CAFF_HALF_LIFE_SEC);
        int remainPct = r.mg > 0 ? (remainMg * 100 / r.mg) : 0;

        char timeStr[8];
        formatTime(timeStr, sizeof(timeStr), r.ts);

        d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
        d.setCursor(3, y);
        d.print("LATEST CUP");

        d.setCursor(60, y);
        d.print(timeStr);

        int miniBarW = 76;
        int miniBarX = 106;
        int miniFill = (miniBarW * remainPct) / 100;
        d.fillRect(miniBarX, y + 1, miniBarW, 6, PIP_COL_BAR_BG);
        d.fillRect(miniBarX, y + 1, miniFill, 6,
                   remainPct > 25 ? PIP_COL_GREEN : PIP_COL_DIM);

        d.setTextColor(remainPct > 25 ? PIP_COL_GREEN : PIP_COL_GOLD,
                       PIP_COL_BG);
        d.setCursor(miniBarX + miniBarW + 3, y);
        d.printf("%d%%", remainPct);
    }
}

static void drawCaffFull() {
    auto& d = M5Cardputer.Display;
    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);

    drawHeader("CAFF");
    drawTabBar(CAFF);

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font0);
    d.setCursor(3, 17);
    d.print("> CAFFEINE TRACKER");

    // v4.1.2: only show today's stats (resets after midnight)
    int todayCups = 0, todayMg = 0;
    calcTodayCaffeine(&todayCups, &todayMg);

    d.setCursor(3, 28);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.printf("TODAY: %d cups  %dmg", todayCups, todayMg);

    d.setCursor(3, 40);
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    int bonus = (calcActiveCaffeine() / CAFF_BONUS_PER_MG) * CAFF_END_BONUS;
    if (bonus > CAFF_END_MAX_BONUS) bonus = CAFF_END_MAX_BONUS;
    d.printf("+%d END  per %dmg active caffeine", bonus, CAFF_BONUS_PER_MG);

    d.drawFastHLine(3, 51, SCREEN_W - 6, PIP_COL_BORDER);
    drawCaffMetabolism();
}

static void drawCaffMetabPartial() {
    auto& d = M5Cardputer.Display;
    d.fillRect(3, 56, SCREEN_W - 6, SCREEN_H - 77, PIP_COL_BG);
    drawCaffMetabolism();
}

// ============================================================
// SCREEN: CAL — CALORIE TRACKER
// ============================================================

static void drawCalFull() {
    auto& d = M5Cardputer.Display;
    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);

    drawHeader("CAL ");
    drawTabBar(CAL);

    d.setFont(&fonts::Font0);

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setCursor(3, 17);
    d.print("> CALORIE TRACKER");

    int todayKcal = calcTodayCalories();
    d.setCursor(3, 28);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.printf("TODAY: %d kcal", todayKcal);

    d.setCursor(3, 39);
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.printf("GOAL : %d kcal", g_calGoal);

    int barX = 3;
    int barY = 49;
    int barW = SCREEN_W - 6;
    int barH = 10;
    d.fillRect(barX, barY, barW, barH, PIP_COL_BAR_BG);

    int fillW = g_calGoal > 0 ? (barW * todayKcal / g_calGoal) : 0;
    if (fillW > barW) fillW = barW;
    if (fillW > 0) {
        uint16_t barColor = fillW >= barW ? PIP_COL_GOLD : PIP_COL_GREEN;
        d.fillRect(barX, barY, fillW, barH, barColor);
    }

    int calPct = g_calGoal > 0 ? (todayKcal * 100 / g_calGoal) : 0;
    d.setCursor(3, barY + barH + 3);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.printf("%d%% of daily goal", calPct);

    d.setCursor(3, barY + barH + 12);
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.printf("+%dSTR +%dAGL/%dkcal", CAL_STR_BONUS, CAL_AGI_BONUS, CAL_BONUS_PER_KCAL);

    int menuY = barY + barH + 22;
    d.drawFastHLine(3, menuY, SCREEN_W - 6, PIP_COL_BORDER);

    const int ITEM_H  = 13;
    const int ITEM_X  = 6;
    const int ITEM_W  = 112;
    const int ITEM_Y0 = menuY + 3;
    const int ITEM_Y1 = ITEM_Y0 + ITEM_H;
    const char* items[] = { "SET DAILY GOAL", "ADD MEAL" };

    for (int i = 0; i < 2; i++) {
        int iy = (i == 0) ? ITEM_Y0 : ITEM_Y1;
        bool sel = (i == g_calMenuSel);

        if (sel) {
            d.fillRect(ITEM_X, iy, ITEM_W, ITEM_H, PIP_COL_GREEN);
            d.setTextColor(PIP_COL_BG, PIP_COL_GREEN);
        } else {
            d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
        }
        d.setCursor(ITEM_X + 3, iy + 1);
        d.print(sel ? "> " : "  ");
        d.print(items[i]);
    }

    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(3, ITEM_Y1 + ITEM_H);  // aligned with other pages at y=110
    d.print("[^/v] sel  [ENTER] ok  [</>] tab");
}

// ============================================================
// CAL SUB-MENU — daily goal setting (v4.1: char buffer)
// ============================================================

static void setCalGoal() {
    auto& d = M5Cardputer.Display;
    g_inModal = true;  // v4.1.1: block handleNormalKeys

    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
    drawHeader("CAL ");
    drawTabBar(CAL);

    d.setFont(&fonts::Font0);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setCursor(3, 20);
    d.print("> SET DAILY GOAL (kcal)");
    d.setCursor(3, 31);
    d.printf("> CURRENT: %d kcal", g_calGoal);
    d.setCursor(3, 43);
    d.print("> NEW:");
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(3, 62);
    d.print("[ENTER] confirm  [BS] del  [ESC] cancel");

    // v4.1: fixed char buffer instead of String
    char  numBuf[6] = "";
    int   numLen = 0;
    bool  done = false;

    while (!done) {
        d.fillRect(3, 51, SCREEN_W - 6, 11, PIP_COL_BG);
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.setCursor(3, 53);
        d.print(numBuf);
        if ((millis() / 500) % 2) d.print("_");

        M5Cardputer.update();
        if (handleBtnAHome()) { g_inModal = false; drawCalFull(); return; }
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();

            for (char c : s.word) {
                if (c >= '0' && c <= '9' && numLen < 5)
                    numBuf[numLen++] = c;
            }
            numBuf[numLen] = '\0';

            if (s.backspace && numLen > 0)
                numBuf[--numLen] = '\0';

            if (s.enter && numLen > 0) {
                int val = atoi(numBuf);
                if (val >= 100 && val <= 9999) {
                    g_calGoal = val;
                    g_prefs.putInt(KEY_CAL_GOAL, g_calGoal);
                    d.fillRect(3, 68, SCREEN_W - 6, 14, PIP_COL_BG);
                    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
                    d.setCursor(3, 72);
                    d.printf("> GOAL SET: %d kcal", g_calGoal);
                    delay(1000);
                }
                done = true;
            }
            if (s.esc) done = true;
        }
        delay(20);
    }

    g_inModal = false;
    g_calMenuSel = 0;
    drawCalFull();
}

// ============================================================
// SCREEN: MEMO — WASTELAND MEMOS
// ============================================================

static void drawMemoFull() {
    auto& d = M5Cardputer.Display;
    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);

    drawHeader("MEMO");
    drawTabBar(MEMO);
    d.setFont(&fonts::Font0);

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setCursor(3, 17);
    d.print("> MEMO LOG");

    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(3, 26);
    d.printf("ENTRIES: %d", g_memoCount);

    d.drawFastHLine(3, 33, SCREEN_W - 6, PIP_COL_BORDER);

    int y = 37, shown = 0;

    for (int i = 0; i < g_memoCount && shown < 5; i++, shown++) {
        char idx[8];
        snprintf(idx, sizeof(idx), "%02d", i + 1);

        d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
        d.setCursor(3, y);
        d.print(idx);

        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.setCursor(20, y);
        String memo = String(g_memos[i]);
        if (memo.length() > 28) memo = memo.substring(0, 27) + ">";
        d.print(memo);
        y += 10;
    }

    if (shown == 0) {
        d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
        d.setCursor(3, y);
        d.print("No memos yet");
    }

    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(3, 110);  // aligned with other page hints
    d.print("[ENTER] new  [1-9] edit");
}

// ============================================================
// RECORD TIME ENTRY (v4.1: char buffer, hardened state machine)
// ============================================================

// v4.1.2: rewritten with dirty-flag rendering + modal guard to eliminate
// flicker and prevent loop()'s handleNormalKeys from stealing arrow-key events.
// v4.1.2: fixed arrow-key detection (isKeyPressed fallback) + layout fix
// (hint text moved above tab bar to prevent overlap).
static time_t enterRecordTime(const char* label) {
    auto& d = M5Cardputer.Display;

    g_inModal = true;   // block handleNormalKeys in loop()

    // v4.1.2: content area = y14 to y117 (tab bar starts at y119)
    const int CONTENT_BOTTOM = 117;

    // --- draw static backdrop ONCE (never changes) ---
    d.fillRect(0, 14, SCREEN_W, CONTENT_BOTTOM - 14, PIP_COL_BG);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font0);
    d.setCursor(3, 20);
    d.printf("> %s @ WHEN?", label);

    int     sel       = 0;
    bool    inInput   = false;
    char    digits[5]  = "";
    int     digLen    = 0;
    bool    dirty     = true;   // trigger first draw
    unsigned long lastBlink = 0;
    bool    blinkOn   = true;

    while (true) {
        // --- blink timer (500ms) ---
        unsigned long nowMs = millis();
        if (nowMs - lastBlink >= 500) {
            lastBlink = nowMs;
            blinkOn   = !blinkOn;
            if (inInput) {
                dirty = true;
            }
        }

        // --- render only when something changed ---
        if (dirty) {
            dirty = false;

            if (!inInput) {
                // Clear selection area only, leave title + tab bar alone
                d.fillRect(0, 34, SCREEN_W, CONTENT_BOTTOM - 34, PIP_COL_BG);

                int y0 = 38;
                d.fillRect(2, y0, SCREEN_W - 8, 16,
                           sel == 0 ? PIP_COL_GREEN : PIP_COL_BG);
                d.setTextColor(sel == 0 ? PIP_COL_BG : PIP_COL_GREEN,
                              sel == 0 ? PIP_COL_GREEN : PIP_COL_BG);
                d.setCursor(8, y0 + 2);
                d.print(sel == 0 ? "> NOW" : "  NOW");

                int y1 = 58;
                d.fillRect(2, y1, SCREEN_W - 8, 16,
                           sel == 1 ? PIP_COL_GREEN : PIP_COL_BG);
                d.setTextColor(sel == 1 ? PIP_COL_BG : PIP_COL_GREEN,
                              sel == 1 ? PIP_COL_GREEN : PIP_COL_BG);
                d.setCursor(8, y1 + 2);
                d.print(sel == 1 ? "> HH:MM __:__" : "  HH:MM __:__");

                // v4.1.2: hint moved up to y=104 (above tab bar at y=119)
                d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
                d.setCursor(3, 104);
                d.print("[^/v] select  [ENTER] confirm  [DEL] cancel");
            } else {
                // Clear only the digit-input area
                d.fillRect(0, 34, SCREEN_W, CONTENT_BOTTOM - 34, PIP_COL_BG);

                d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
                d.setCursor(3, 40);
                d.print("  HH:MM ");

                // Auto-format digits
                switch (digLen) {
                    case 0: d.print("--:--"); break;
                    case 1: d.printf("0%c:--", digits[0]); break;
                    case 2: d.printf("%c%c:--", digits[0], digits[1]); break;
                    case 3: d.printf("%c%c:%c-", digits[0], digits[1], digits[2]); break;
                    case 4: d.printf("%c%c:%c%c", digits[0], digits[1], digits[2], digits[3]); break;
                }
                // blinking cursor
                if (blinkOn && digLen < 4) d.print("_");

                // v4.1.2: hint moved up to y=104
                d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
                d.setCursor(3, 104);
                d.print("[BS] back  [ENTER] confirm  [ESC] back");
            }
        }

        M5Cardputer.update();
        if (handleBtnAHome()) return -1;
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();

            // v4.1.2: use isKeyPressed fallback for arrow keys —
            // Cardputer's ; and . keys are the physical up/down arrows,
            // but s.up/s.down are not always reliable in keysState().
            bool goUp   = s.up   || M5Cardputer.Keyboard.isKeyPressed(';');
            bool goDown = s.down || M5Cardputer.Keyboard.isKeyPressed('.');

            // DEL always cancels entire flow
            if (s.del) { g_inModal = false; return -1; }

            if (!inInput) {
                // --- selection state: NOW vs HH:MM ---
                bool prevSel = sel;
                if (goUp   && sel > 0) sel = 0;
                if (goDown && sel < 1) sel = 1;
                if (sel != prevSel) dirty = true;

                if (s.enter) {
                    if (sel == 0) {
                        g_inModal = false;
                        return 0;
                    } else {
                        inInput = true;
                        digLen  = 0;
                        digits[0] = '\0';
                        dirty = true;
                    }
                }
                if (s.esc) { g_inModal = false; return -1; }
            } else {
                // --- digit input state ---
                bool keyConsumed = false;

                if (s.esc) {
                    inInput   = false;
                    digLen    = 0;
                    digits[0] = '\0';
                    dirty     = true;
                    keyConsumed = true;
                }
                if (!keyConsumed && s.backspace && digLen > 0) {
                    digits[--digLen] = '\0';
                    dirty = true;
                    keyConsumed = true;
                }

                if (!keyConsumed) {
                    for (char c : s.word) {
                        if (c >= '0' && c <= '9' && digLen < 4) {
                            digits[digLen++] = c;
                            digits[digLen] = '\0';
                            dirty = true;
                            break; // consume one digit per frame
                        }
                    }
                }

                if (s.enter) {
                    if (digLen == 0) {
                        inInput = false;
                        dirty   = true;
                        continue;
                    }

                    int h = 0, m = 0;
                    if (digLen == 1) {
                        h = digits[0] - '0';
                    } else if (digLen == 2) {
                        h = (digits[0] - '0') * 10 + (digits[1] - '0');
                    } else if (digLen == 3) {
                        h = (digits[0] - '0') * 10 + (digits[1] - '0');
                        m = (digits[2] - '0') * 10;
                    } else {
                        h = (digits[0] - '0') * 10 + (digits[1] - '0');
                        m = (digits[2] - '0') * 10 + (digits[3] - '0');
                    }

                    if (h < 0 || h > 23 || m < 0 || m > 59) {
                        // v4.1.2: error message also moved up
                        d.fillRect(3, 88, SCREEN_W - 6, 12, PIP_COL_BG);
                        d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
                        d.setCursor(3, 90);
                        d.print("> INVALID TIME");
                        delay(800);
                        digLen    = 0;
                        digits[0] = '\0';
                        dirty     = true;
                        continue;
                    }

                    time_t now = getNow();
                    struct tm* ti = getCachedTm(now);
                    struct tm recTi = *ti;
                    recTi.tm_hour = h;
                    recTi.tm_min  = m;
                    recTi.tm_sec  = 0;
                    time_t t = mktime(&recTi);
                    if (t > now) t = now;
                    g_inModal = false;
                    return t;
                }
            }
        }
        delay(20);
    }
    g_inModal = false;
    return -1;
}

// ============================================================
// DATA ENTRY: ADD COFFEE
// ============================================================

static void addCoffee() {
    auto& d = M5Cardputer.Display;
    g_inModal = true;  // v4.1.1: block handleNormalKeys

    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
    drawHeader("CAFF");
    drawTabBar(CAFF);

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font0);
    d.setCursor(3, 20); d.print("> ADD CAFFEINE DOSE");
    d.setCursor(3, 32); d.print("1: 50mg   2: 80mg");
    d.setCursor(3, 42); d.print("3:100mg   4:150mg");
    d.setCursor(3, 52); d.print("5:200mg");
    d.setCursor(3, 64);
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.print("[1-5] select  [DEL] cancel");

    while (true) {
        M5Cardputer.update();
        if (handleBtnAHome()) return;
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
            int doses[] = { 0, 50, 80, 100, 150, 200 };

            for (char c : status.word) {
                if (c >= '1' && c <= '5') {
                    int idx = c - '0';
                    int mg = doses[idx];

                    char lbl[16];
                    snprintf(lbl, sizeof(lbl), "%dmg", mg);
                    time_t recTs = enterRecordTime(lbl);
                    // enterRecordTime already clears g_inModal, re-set it
                    g_inModal = true;

                    if (recTs < 0) {
                        d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
                        drawHeader("CAFF");
                        drawTabBar(CAFF);
                        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
                        d.setFont(&fonts::Font0);
                        d.setCursor(3, 20); d.print("> ADD CAFFEINE DOSE");
                        d.setCursor(3, 32); d.print("1: 50mg   2: 80mg");
                        d.setCursor(3, 42); d.print("3:100mg   4:150mg");
                        d.setCursor(3, 52); d.print("5:200mg");
                        d.setCursor(3, 64);
                        d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
                        d.print("[1-5] select  [DEL] cancel");
                        continue;
                    }

                    if (recTs == 0) recTs = getNow();

                    CaffRecord rec;
                    rec.ts = recTs;
                    rec.mg = mg;
                    int mv = g_caffCount >= MAX_CAFF_RECORDS ? MAX_CAFF_RECORDS - 1 : g_caffCount;
                    for (int j = mv; j > 0; j--) g_caffLog[j] = g_caffLog[j - 1];
                    g_caffLog[0] = rec;
                    if (g_caffCount < MAX_CAFF_RECORDS) g_caffCount++;
                    saveCaffLog();

                    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
                    drawHeader("CAFF");
                    drawTabBar(CAFF);
                    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
                    d.setFont(&fonts::Font0);
                    d.setCursor(3, 40);
                    d.printf("> +%dmg RECORDED", mg);
                    char timeBuf[8];
                    formatTime(timeBuf, sizeof(timeBuf), recTs);
                    d.setCursor(3, 54);
                    d.printf("  @ %s", timeBuf);
                    delay(1200);
                    g_inModal = false;
                    drawCaffFull();
                    return;
                }
            }
            if (status.del || status.esc) {
                g_inModal = false;
                drawCaffFull();
                return;
            }
        }
        delay(10);
    }
    g_inModal = false;
}

// ============================================================
// DATA ENTRY: ADD MEAL (v4.1: char buffer, hardened state)
// ============================================================

static void addMeal() {
    auto& d = M5Cardputer.Display;
    g_inModal = true;  // v4.1.1: block handleNormalKeys

    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
    drawHeader("CAL ");
    drawTabBar(CAL);

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font0);
    d.setCursor(3, 20); d.print("> ADD MEAL (kcal)");
    d.setCursor(3, 32);     d.print("Type calories then ENTER:");
    d.setCursor(3, 44);
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.print("[BS] backspace  [DEL] cancel");

    // v4.1: fixed char buffer instead of String
    char  numBuf[6] = "";
    int   numLen = 0;
    bool  done = false;

    while (!done) {
        d.fillRect(3, 54, SCREEN_W - 6, 18, PIP_COL_BG);
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.setCursor(3, 58);
        d.print(numBuf);
        d.print("_");

        M5Cardputer.update();
        if (handleBtnAHome()) { g_inModal = false; drawCalFull(); return; }
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

            for (char c : status.word) {
                if (c >= '0' && c <= '9' && numLen < 5)
                    numBuf[numLen++] = c;
            }
            numBuf[numLen] = '\0';

            if (status.backspace && numLen > 0)
                numBuf[--numLen] = '\0';

            if (status.enter) {
                if (numLen > 0) {
                    int kcal = atoi(numBuf);
                    if (kcal > 0 && kcal < 10000) {

                        char lbl[16];
                        snprintf(lbl, sizeof(lbl), "%dkcal", kcal);
                        time_t recTs = enterRecordTime(lbl);
                        // enterRecordTime clears g_inModal, re-set for our loop
                        g_inModal = true;

                        if (recTs < 0) {
                            d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
                            drawHeader("CAL ");
                            drawTabBar(CAL);
                            d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
                            d.setFont(&fonts::Font0);
                            d.setCursor(3, 20); d.print("> ADD MEAL (kcal)");
                            d.setCursor(3, 32); d.print("Type calories then ENTER:");
                            d.setCursor(3, 44);
                            d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
                            d.print("[BS] backspace  [DEL] cancel");
                            numLen = 0;
                            numBuf[0] = '\0';
                            continue;
                        }

                        if (recTs == 0) recTs = getNow();

                        CalRecord rec;
                        rec.ts   = recTs;
                        rec.kcal = kcal;
                        int mv = g_calCount >= MAX_CAL_RECORDS ? MAX_CAL_RECORDS - 1 : g_calCount;
                        for (int j = mv; j > 0; j--) g_calLog[j] = g_calLog[j - 1];
                        g_calLog[0] = rec;
                        if (g_calCount < MAX_CAL_RECORDS) g_calCount++;
                        saveCalLog();

                        d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
                        drawHeader("CAL ");
                        drawTabBar(CAL);
                        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
                        d.setFont(&fonts::Font0);
                        d.setCursor(3, 40);
                        d.printf("> +%dkcal RECORDED", kcal);
                        char timeBuf[8];
                        formatTime(timeBuf, sizeof(timeBuf), recTs);
                        d.setCursor(3, 54);
                        d.printf("  @ %s", timeBuf);
                        delay(1200);
                        done = true;
                    }
                }
            }
            // v4.1: hardened — separate conditions for empty-input cancel
            if (numLen == 0 && (status.backspace || status.del || status.esc)) {
                done = true;
            }
            if (status.esc) {
                done = true;
            }
        }
        delay(20);
    }
    g_inModal = false;
    drawCalFull();
}

// ============================================================
// DATA ENTRY: ADD MEMO
// ============================================================

static void addMemo() {
    auto& d = M5Cardputer.Display;

    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
    drawHeader("MEMO");
    drawTabBar(MEMO);

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font0);
    d.setCursor(3, 20); d.print("> NEW MEMO");
    d.setCursor(3, 30); d.print("Type memo then ENTER:");
    d.setCursor(3, 40);
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.print("[ENTER] save  [BS] bksp  [Fn+BS]/[ESC] cancel");

    String text = "";
    bool done = false;

    while (!done) {
        d.fillRect(3, 50, SCREEN_W - 6, 35, PIP_COL_BG);
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.setCursor(3, 54);

        String display = text;
        if (display.length() > 56) display = ">" + display.substring(display.length() - 55);
        d.print(display);
        if ((millis() / 500) % 2) d.print("_");

        M5Cardputer.update();
        // v4.2.5: BtnA (G0) — save current memo text and return to STAT
        if (handleBtnAHome()) {
            if (text.length() > 0) {
                int mv = g_memoCount >= MAX_MEMOS ? MAX_MEMOS - 1 : g_memoCount;
                for (int j = mv; j > 0; j--)
                    strncpy(g_memos[j], g_memos[j - 1], MEMO_MAX_LEN);
                strncpy(g_memos[0], text.c_str(), MEMO_MAX_LEN);
                g_memos[0][MEMO_MAX_LEN] = '\0';
                if (g_memoCount < MAX_MEMOS) g_memoCount++;
                saveMemos();
            }
            drawMemoFull();
            return;
        }
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

            for (char c : status.word) {
                if (c >= 32 && c <= 126 && text.length() < 128) text += c;
            }
            if (status.del) {
                done = true;
            }
            if (status.esc) {
                done = true;
            }
            if (status.backspace && text.length() > 0)
                text = text.substring(0, text.length() - 1);
            if (status.backspace && text.length() == 0) {
                done = true;
            }
            if (status.enter) {
                if (text.length() > 0) {
                    int mv = g_memoCount >= MAX_MEMOS ? MAX_MEMOS - 1 : g_memoCount;
                    for (int j = mv; j > 0; j--)
                        strncpy(g_memos[j], g_memos[j - 1], MEMO_MAX_LEN);
                    strncpy(g_memos[0], text.c_str(), MEMO_MAX_LEN);
                    g_memos[0][MEMO_MAX_LEN] = '\0';
                    if (g_memoCount < MAX_MEMOS) g_memoCount++;
                    saveMemos();  // v4.1: marks dirty
                    done = true;
                }
            }
        }
        delay(20);
    }
    drawMemoFull();
}

// ============================================================
// MEMO EDITOR — view + edit memo with cursor
// ============================================================

static void memoEditor(int index) {
    auto& d = M5Cardputer.Display;

    if (index < 0 || index >= g_memoCount) return;

    String text = String(g_memos[index]);
    int cursor = text.length();
    unsigned long lastBlink = 0;
    bool blinkOn = true;
    bool dirty = true;

    g_memoView = index;

    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
    drawHeader("MEMO");
    drawTabBar(MEMO);

    d.setFont(&fonts::Font0);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setCursor(3, 17);
    d.printf("> EDIT MEMO #%02d", index + 1);
    d.drawFastHLine(3, 24, SCREEN_W - 6, PIP_COL_BORDER);

    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(3, SCREEN_H - 20);
    d.print("[ESC] save  [BS] bksp  [Fn+BS] del memo  < > cursor");

    const int TXT_Y    = 30;
    const int MAX_COLS = 34;
    const int LINE_H   = 10;
    const int MAX_LINES = 6;

    while (true) {
        if (dirty) {
            d.fillRect(3, TXT_Y, SCREEN_W - 6, MAX_LINES * LINE_H, PIP_COL_BG);

            int line = 0;
            int pos  = 0;
            int totalLen = text.length();

            while (pos <= totalLen && line < MAX_LINES) {
                int lineEnd = pos + MAX_COLS;
                if (lineEnd > totalLen) lineEnd = totalLen;

                String chunk = text.substring(pos, lineEnd);
                d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
                d.setCursor(3, TXT_Y + line * LINE_H);
                d.print(chunk);

                if (cursor >= pos && cursor <= lineEnd && blinkOn) {
                    int local = cursor - pos;
                    int cx = 3;
                    if (local > 0 && local <= (int)chunk.length()) {
                        cx += d.textWidth(chunk.substring(0, local));
                    } else if (local > (int)chunk.length()) {
                        cx += d.textWidth(chunk);
                    }
                    d.fillRect(cx, TXT_Y + line * LINE_H, 4, LINE_H, PIP_COL_GREEN);
                }

                pos = lineEnd;
                if (lineEnd >= totalLen) break;
                line++;
            }

            dirty = false;
        }

        unsigned long now = millis();
        if (now - lastBlink >= 500) {
            lastBlink = now;
            blinkOn = !blinkOn;
            dirty = true;
        }

        M5Cardputer.update();
        // v4.2.5: BtnA (G0) — save current text and return to STAT
        if (handleBtnAHome()) {
            strncpy(g_memos[index], text.c_str(), MEMO_MAX_LEN);
            g_memos[index][MEMO_MAX_LEN] = '\0';
            saveMemos();
            g_memoView = -1;
            drawMemoFull();
            return;
        }
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();

            if (s.del) {
                for (int i = index; i < g_memoCount - 1; i++)
                    strncpy(g_memos[i], g_memos[i + 1], MEMO_MAX_LEN);
                g_memoCount--;
                saveMemos();  // v4.1: marks dirty
                g_memoView = -1;
                d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
                drawHeader("MEMO");
                drawTabBar(MEMO);
                d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
                d.setFont(&fonts::Font0);
                d.setCursor(3, 40);
                d.printf("> MEMO #%02d DELETED", index + 1);
                delay(800);
                drawMemoFull();
                return;
            }

            if (s.esc) {
                if (text.length() == 0) {
                    for (int i = index; i < g_memoCount - 1; i++)
                        strncpy(g_memos[i], g_memos[i + 1], MEMO_MAX_LEN);
                    g_memoCount--;
                } else {
                    strncpy(g_memos[index], text.c_str(), MEMO_MAX_LEN);
                    g_memos[index][MEMO_MAX_LEN] = '\0';
                }
                saveMemos();  // v4.1: marks dirty
                g_memoView = -1;
                drawMemoFull();
                return;
            }

            if (s.backspace && cursor > 0) {
                text = text.substring(0, cursor - 1) + text.substring(cursor);
                cursor--;
                dirty = true;
            }

            bool goLeft  = s.left  || M5Cardputer.Keyboard.isKeyPressed(',');
            bool goRight = s.right || M5Cardputer.Keyboard.isKeyPressed('/');
            bool goHome  = s.up    || M5Cardputer.Keyboard.isKeyPressed(';');
            bool goEnd   = s.down  || M5Cardputer.Keyboard.isKeyPressed('.');

            int oldCursor = cursor;
            if (goLeft  && cursor > 0)              cursor--;
            if (goRight && cursor < (int)text.length()) cursor++;
            if (goHome)                              cursor = 0;
            if (goEnd)                               cursor = text.length();
            if (cursor != oldCursor)                 dirty = true;

            for (char c : s.word) {
                if (c >= 32 && c <= 126 && text.length() < 128) {
                    text = text.substring(0, cursor) + c + text.substring(cursor);
                    cursor++;
                    dirty = true;
                }
            }
        }

        delay(20);
    }
}

// ============================================================
// BOOT SPLASH
// ============================================================

static void drawBootSplash() {
    auto& d = M5Cardputer.Display;
    d.fillScreen(PIP_COL_BG);

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font2);
    drawTextCenter(10, "VAULT-TEC", PIP_COL_GREEN);

    d.setFont(&fonts::Font0);
    drawTextCenter(35, "PIP-BOY 3000", PIP_COL_GREEN);
    drawTextCenter(45, "Terminal OS v4.1.8", PIP_COL_DIM);

    drawVaultBoy((SCREEN_W - 55) / 2, 42);
    drawTextCenter(SCREEN_H - 30, "INITIALIZING...", PIP_COL_DIM);

    int barX = 30, barY = SCREEN_H - 22, barW = SCREEN_W - 60;
    d.drawRect(barX, barY, barW, 6, PIP_COL_GREEN);
    for (int i = 0; i < barW; i += 4) {
        d.fillRect(barX + 1, barY + 1, i, 4, PIP_COL_GREEN);
        delay(15);
    }
    delay(800);
    d.fillScreen(PIP_COL_BG);
}

// ============================================================
// SCREEN: LORA — WASTELAND WALKIE-TALKIE
// ============================================================

#define LORA_CHANNEL_DEFAULT   "868.0 MHz"
#define LORA_PTT_KEY           ' '

static String  g_loraChannel = LORA_CHANNEL_DEFAULT;
static bool    g_loraPtt     = false;
static bool    g_loraRx      = false;
static int     g_loraRssi    = -120;
static bool    g_loraReady   = false;

static void drawLoraFull() {
    auto& d = M5Cardputer.Display;
    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);

    drawHeader("LORA ");
    drawTabBar(LORA);

    d.setFont(&fonts::Font0);

    d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
    d.setCursor(3, 17);
    d.print("> WASTELAND COMMS");

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setCursor(3, 28);
    d.print("CH: ");
    d.print(g_loraChannel.c_str());

    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(3, 39);
    if (!g_loraReady) {
        d.print("MODULE: NOT FOUND");
    } else if (g_loraPtt) {
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.print(">>> TRANSMITTING <<<");
    } else if (g_loraRx) {
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.print("<<< RECEIVING >>>");
    } else {
        d.print("STATUS: STANDBY");
    }

    d.drawFastHLine(3, 48, SCREEN_W - 6, PIP_COL_BORDER);

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setCursor(3, 53);
    d.print("> SIGNAL");

    int sigBars = 0;
    if (g_loraRssi > -70)      sigBars = 5;
    else if (g_loraRssi > -85) sigBars = 4;
    else if (g_loraRssi > -95) sigBars = 3;
    else if (g_loraRssi > -105) sigBars = 2;
    else if (g_loraRssi > -115) sigBars = 1;

    int sX = 3, sY = 65;
    for (int j = 0; j < 5; j++) {
        int bh = 4 + j * 3;
        uint16_t col = (j < sigBars) ? PIP_COL_GREEN : PIP_COL_BAR_BG;
        d.fillRect(sX + j * 7, sY + (15 - bh), 5, bh, col);
    }
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(sX + 40, sY + 5);
    d.printf("%d dBm", g_loraRssi);

    int volX = SCREEN_W - 60, volY = sY + 18;
    d.setCursor(volX, volY);
    d.printf("VOL: %3d%%", g_volume);
    int vBarW = 56, vBarH = 5;
    d.fillRect(volX, volY + 10, vBarW, vBarH, PIP_COL_BAR_BG);
    int vFill = (vBarW * g_volume) / 100;
    d.fillRect(volX, volY + 10, vFill, vBarH, g_volume > 80 ? PIP_COL_GOLD : PIP_COL_GREEN);

    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.fillRect(0, 108, SCREEN_W, 12, PIP_COL_BG);
    d.setCursor(3, 110);
    d.print("[SPACE] PTT  [-/=] vol  [</>] tab");
}

// ============================================================
// PERSONAL PROFILE (v4.1.3: Vault Boy entry on STAT)
// ============================================================

// Helper: alphanumeric text input for profile name (similar to wifiInputField
// but with auto-uppercase and shorter hint).
static void profileTextInput(const char* label, char* outBuf, int maxLen) {
    auto& d = M5Cardputer.Display;
    int len = strlen(outBuf);

    g_inModal = true;
    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
    drawHeader("PROFILE");
    d.setFont(&fonts::Font0);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setCursor(3, 20); d.print(label);
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(3, 100); d.print("[ENTER] ok  [BS] del  [ESC] skip");

    while (true) {
        d.fillRect(3, 32, SCREEN_W - 6, 22, PIP_COL_BG);
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.setCursor(3, 40);
        d.print(outBuf);
        if ((millis() / 500) % 2) d.print("_");

        M5Cardputer.update();
        if (handleBtnAHome()) { g_inModal = false; return; }
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();
            if (s.esc) { g_inModal = false; return; }
            if (s.backspace && len > 0) outBuf[--len] = '\0';
            if (s.enter) { g_inModal = false; return; }
            for (char c : s.word) {
                if (c >= 32 && c <= 126 && len < maxLen - 1) {
                    // auto-uppercase letters
                    if (c >= 'a' && c <= 'z') c -= 32;
                    outBuf[len++] = c;
                    outBuf[len] = '\0';
                }
            }
        }
        delay(20);
    }
}

// Helper: numeric input. Reads up to maxDigits decimal digits into outBuf.
static void profileNumInput(const char* label, char* outBuf, int maxDigits,
                            const char* suffix) {
    auto& d = M5Cardputer.Display;
    int len = strlen(outBuf);

    g_inModal = true;
    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
    drawHeader("PROFILE");
    d.setFont(&fonts::Font0);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setCursor(3, 20); d.print(label);
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(3, 100); d.print("[ENTER] ok  [BS] del  [ESC] skip");

    while (true) {
        d.fillRect(3, 32, SCREEN_W - 6, 22, PIP_COL_BG);
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.setCursor(3, 40);
        d.print(outBuf);
        if (suffix) d.print(suffix);
        if ((millis() / 500) % 2) d.print("_");

        M5Cardputer.update();
        if (handleBtnAHome()) { g_inModal = false; return; }
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();
            if (s.esc) { g_inModal = false; return; }
            if (s.backspace && len > 0) outBuf[--len] = '\0';
            if (s.enter) { g_inModal = false; return; }
            for (char c : s.word) {
                if (c >= '0' && c <= '9' && len < maxDigits) {
                    outBuf[len++] = c;
                    outBuf[len] = '\0';
                }
            }
        }
        delay(20);
    }
}

// Register a new profile entry. Called from viewProfile() when no profiles
// exist OR when user selects "NEW RECORD".
// v4.1.5: added `update` flag — when true, overwrites g_profiles[0] instead
// of inserting a new record.
static void registerProfile(bool update) {
    auto& d = M5Cardputer.Display;
    g_inModal = true;

    ProfileRecord rec;
    memset(&rec, 0, sizeof(rec));
    rec.gender = 'M';

    // Field 1: NAME
    char nameBuf[PROF_NAME_LEN] = "";
    profileTextInput("> NAME:", nameBuf, PROF_NAME_LEN);
    if (nameBuf[0] == '\0') { g_inModal = false; return; }
    strncpy(rec.name, nameBuf, PROF_NAME_LEN - 1);
    rec.name[PROF_NAME_LEN - 1] = '\0';

    // Field 2: GENDER (M/F/O toggle)
    {
        d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
        drawHeader("PROFILE");
        d.setFont(&fonts::Font0);
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.setCursor(3, 20); d.print("> GENDER:");
        d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
        d.setCursor(3, 100); d.print("[ENTER] ok  [ESC] skip");

        char opts[] = {'M', 'F', 'O'};
        int sel = 0;
        while (true) {
            d.fillRect(3, 35, SCREEN_W - 6, 20, PIP_COL_BG);
            for (int i = 0; i < 3; i++) {
                int x = 20 + i * 60;
                if (i == sel) d.fillRect(x - 4, 35, 50, 20, PIP_COL_GREEN);
                d.setTextColor(i == sel ? PIP_COL_BG : PIP_COL_GREEN,
                              i == sel ? PIP_COL_GREEN : PIP_COL_BG);
                d.setCursor(x, 42);
                d.printf("%c", opts[i]);
            }
            M5Cardputer.update();
            if (handleBtnAHome()) { g_inModal = false; return; }
            if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
                Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();
                bool goL = s.left  || M5Cardputer.Keyboard.isKeyPressed(',');
                bool goR = s.right || M5Cardputer.Keyboard.isKeyPressed('/');
                bool goU = s.up    || M5Cardputer.Keyboard.isKeyPressed(';');
                bool goD = s.down  || M5Cardputer.Keyboard.isKeyPressed('.');
                if (goL || goU) sel = (sel + 2) % 3;
                if (goR || goD) sel = (sel + 1) % 3;
                if (s.enter) { rec.gender = opts[sel]; break; }
                if (s.esc)   break;
            }
            delay(20);
        }
    }

    // Field 3: BIRTH YEAR (4 digits)
    {
        char yrBuf[5] = "1990";
        profileNumInput("> BIRTH YEAR (YYYY):", yrBuf, 4, "");
        if (yrBuf[0] == '\0') { g_inModal = false; return; }
        rec.birthYear = (int16_t)atoi(yrBuf);
        if (rec.birthYear < 1900) rec.birthYear = 1900;
        if (rec.birthYear > 2030) rec.birthYear = 2030;
    }

    // Field 4: BIRTH MONTH (1-2 digits)
    {
        char moBuf[3] = "1";
        profileNumInput("> BIRTH MONTH (1-12):", moBuf, 2, "");
        if (moBuf[0] == '\0') { g_inModal = false; return; }
        int mo = atoi(moBuf);
        if (mo < 1) mo = 1; if (mo > 12) mo = 12;
        rec.birthMonth = (uint8_t)mo;
    }

    // Field 5: BIRTH DAY (1-2 digits)
    {
        char dayBuf[3] = "1";
        profileNumInput("> BIRTH DAY (1-31):", dayBuf, 2, "");
        if (dayBuf[0] == '\0') { g_inModal = false; return; }
        int day = atoi(dayBuf);
        if (day < 1) day = 1; if (day > 31) day = 31;
        rec.birthDay = (uint8_t)day;
    }

    // Field 6: HEIGHT (cm, 3 digits)
    {
        char hBuf[4] = "170";
        profileNumInput("> HEIGHT (cm):", hBuf, 3, " cm");
        if (hBuf[0] == '\0') { g_inModal = false; return; }
        int h = atoi(hBuf);
        if (h < 100) h = 100; if (h > 250) h = 250;
        rec.heightCm = (uint8_t)h;
    }

    // Field 7: WEIGHT (kg, 3 digits)
    {
        char wBuf[4] = "65";
        profileNumInput("> WEIGHT (kg):", wBuf, 3, " kg");
        if (wBuf[0] == '\0') { g_inModal = false; return; }
        int w = atoi(wBuf);
        if (w < 30) w = 30; if (w > 200) w = 200;
        rec.weightKg = (uint8_t)w;
    }

    // Registration timestamp = current time
    rec.regTs = getNow();

    // v4.1.5: update mode overwrites existing, insert mode adds new
    if (update && g_profileCount > 0) {
        g_profiles[0] = rec;  // overwrite current profile
    } else {
        // Append to log (most recent first)
        int mv = g_profileCount >= MAX_PROFILES ? MAX_PROFILES - 1 : g_profileCount;
        for (int j = mv; j > 0; j--) g_profiles[j] = g_profiles[j - 1];
        g_profiles[0] = rec;
        if (g_profileCount < MAX_PROFILES) g_profileCount++;
    }
    saveProfiles();
    flushProfiles();   // immediate write — important data

    // Confirmation splash (Fallout style)
    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
    drawHeader("PROFILE");
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font0);
    d.setCursor(3, 30); d.print(update ? "> UPDATE COMPLETE" : "> REGISTRATION COMPLETE");
    d.drawFastHLine(3, 42, SCREEN_W - 6, PIP_COL_BORDER);
    d.setCursor(3, 50); d.printf(">%s", rec.name);
    d.setCursor(3, 62); d.printf(">%c  %04d-%02d-%02d",
        rec.gender, rec.birthYear, rec.birthMonth, rec.birthDay);
    d.setCursor(3, 74); d.printf(">H %dcm  W %dkg",
        rec.heightCm, rec.weightKg);
    char dateBuf[16];
    struct tm* ti = getCachedTm(rec.regTs);
    strftime(dateBuf, sizeof(dateBuf), "%Y/%m/%d", ti);
    d.setCursor(3, 86); d.printf(">LOGGED %s", dateBuf);
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(3, 100); d.print("[any key] continue");
    delay(800);
    // wait for any key
    while (true) {
        M5Cardputer.update();
        if (handleBtnAHome()) return;
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) break;
        delay(20);
    }
    g_inModal = false;
}

// View weight history (sorted by registration date desc). Navigation with
// up/down — same pattern as wifiScanAndPick().
// v4.1.5: dirty-flag rendering (no flicker)
static void viewWeightHistory() {
    auto& d = M5Cardputer.Display;
    g_inModal = true;

    if (g_profileCount == 0) {
        d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
        drawHeader("WEIGHT");
        d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
        d.setFont(&fonts::Font0);
        d.setCursor(3, 50); d.print("> NO RECORDS");
        d.setCursor(3, 64); d.print("> USE PROFILE -> NEW");
        delay(1500);
        g_inModal = false;
        return;
    }

    const int MAX_VIS = 5;
    int selected = 0;
    int scrollOff = 0;
    bool dirty = true;       // trigger first draw
    bool needFull = true;    // full redraw needed

    // Static header area (drawn once)
    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
    drawHeader("WEIGHT HX");
    drawTabBar(STAT);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font0);
    d.setCursor(3, 17); d.print("> WEIGHT HISTORY");
    d.drawFastHLine(3, 25, SCREEN_W - 6, PIP_COL_BORDER);

    while (true) {
        if (dirty) {
            dirty = false;

            // Clear list area only
            d.fillRect(0, 26, SCREEN_W, 74, PIP_COL_BG);

            int y = 28;
            int n = g_profileCount;
            int visEnd = (n < scrollOff + MAX_VIS) ? n : scrollOff + MAX_VIS;
            for (int i = scrollOff; i < visEnd; i++) {
                auto& r = g_profiles[i];
                char dateBuf[12];
                struct tm* ti = getCachedTm(r.regTs);
                strftime(dateBuf, sizeof(dateBuf), "%m/%d/%y", ti);

                bool isSel = (i == selected);
                if (isSel) d.fillRect(2, y - 1, SCREEN_W - 4, 12, PIP_COL_GREEN);
                d.setTextColor(isSel ? PIP_COL_BG : PIP_COL_GREEN,
                              isSel ? PIP_COL_GREEN : PIP_COL_BG);
                d.setCursor(4, y);
                d.printf("%s  %dkg", dateBuf, r.weightKg);
                y += 13;
            }

            // Hint (aligned with other pages at y=110)
            d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
            d.fillRect(0, 108, SCREEN_W, 12, PIP_COL_BG);
            d.setCursor(3, 110);
            d.print("[^/v] nav  [ESC] back");
        }

        M5Cardputer.update();
        if (handleBtnAHome()) return;
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();
            bool goUp   = s.up   || M5Cardputer.Keyboard.isKeyPressed(';');
            bool goDown = s.down || M5Cardputer.Keyboard.isKeyPressed('.');

            int prevSel = selected;
            if (goUp && selected > 0) {
                selected--;
                if (selected < scrollOff) scrollOff = selected;
            }
            if (goDown && selected < g_profileCount - 1) {
                selected++;
                if (selected >= scrollOff + MAX_VIS)
                    scrollOff = selected - MAX_VIS + 1;
            }
            if (selected != prevSel) dirty = true;
            if (s.esc || s.enter) { g_inModal = false; return; }
        }
        delay(30);
    }
}

// View latest profile. Two interactive items: [WEIGHT HX] and [UPDATE].
// v4.1.5: no NEW/DELETE menu items; FN+Backspace triggers delete confirm.
static void viewProfile() {
    auto& d = M5Cardputer.Display;
    g_inModal = true;

    if (g_profileCount == 0) {
        registerProfile();
        g_inModal = false;
        return;
    }

    const uint8_t MENU_WGT = 0;
    const uint8_t MENU_UPD = 1;
    uint8_t menuSel = MENU_WGT;
    bool dirty       = true;
    bool needRedraw  = true;

    const int Y_WGT = 64;
    const int Y_UPD = 88;

    while (true) {
        if (dirty) {
            dirty = false;

            if (needRedraw) {
                needRedraw = false;
                d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
                drawHeader("PROFILE");
                drawTabBar(STAT);

                d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
                d.setFont(&fonts::Font0);
                d.setCursor(3, 17); d.print("> PERSONAL FILE");
                d.drawFastHLine(3, 25, SCREEN_W - 6, PIP_COL_BORDER);

                if (g_profileCount == 0) {
                    d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
                    d.setCursor(3, 50); d.print("> NO PROFILE");
                    d.setCursor(3, 64); d.print("> PRESS ENTER TO REGISTER");
                } else {
                    auto& r = g_profiles[0];
                    time_t now = getNow();
                    struct tm* nti = getCachedTm(now);
                    int age = nti->tm_year + 1900 - r.birthYear;
                    if (nti->tm_mon + 1 < r.birthMonth ||
                        (nti->tm_mon + 1 == r.birthMonth && nti->tm_mday < r.birthDay))
                        age--;
                    if (age < 0) age = 0;

                    char dateBuf[14];
                    struct tm* rti = getCachedTm(r.regTs);
                    strftime(dateBuf, sizeof(dateBuf), "%Y/%m/%d", rti);

                    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
                    d.setCursor(3, 30); d.printf("NAME: %s", r.name);
                    d.setCursor(3, 42); d.printf("SEX : %c   DOB: %04d-%02d-%02d",
                        r.gender, r.birthYear, r.birthMonth, r.birthDay);
                    d.setCursor(3, 54); d.printf("AGE : %d   HGT: %dcm", age, r.heightCm);
                    d.setCursor(3, Y_WGT); d.printf("WGT : %d kg <", r.weightKg);
                    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
                    d.setCursor(3, 76); d.printf("LOG : %s", dateBuf);
                    d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
                    d.setCursor(3, Y_UPD); d.print("> UPDATE PROFILE");
                }
            }

            if (g_profileCount > 0) {
                auto& r = g_profiles[0];

                d.fillRect(2, Y_WGT - 1, SCREEN_W - 4, 12, PIP_COL_BG);
                if (menuSel == MENU_WGT)
                    d.fillRect(2, Y_WGT - 1, SCREEN_W - 4, 12, PIP_COL_GREEN);
                d.setTextColor(menuSel == MENU_WGT ? PIP_COL_BG : PIP_COL_GREEN,
                              menuSel == MENU_WGT ? PIP_COL_GREEN : PIP_COL_BG);
                d.setCursor(3, Y_WGT); d.printf("WGT : %d kg <", r.weightKg);

                d.fillRect(2, Y_UPD - 1, SCREEN_W - 4, 12, PIP_COL_BG);
                if (menuSel == MENU_UPD)
                    d.fillRect(2, Y_UPD - 1, SCREEN_W - 4, 12, PIP_COL_GREEN);
                d.setTextColor(menuSel == MENU_UPD ? PIP_COL_BG : PIP_COL_GOLD,
                              menuSel == MENU_UPD ? PIP_COL_GREEN : PIP_COL_BG);
                d.setCursor(3, Y_UPD); d.print("> UPDATE PROFILE");
            }

            d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
            d.fillRect(0, 108, SCREEN_W, 12, PIP_COL_BG);
            d.setCursor(3, 110);
            d.print(g_profileCount == 0
                    ? "[ENTER] register  [ESC] back"
                    : "[^/v] nav  [ENTER] pick  [ESC] back");
        }

        M5Cardputer.update();
        if (handleBtnAHome()) return;
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();
            bool goUp   = s.up   || M5Cardputer.Keyboard.isKeyPressed(';');
            bool goDown = s.down || M5Cardputer.Keyboard.isKeyPressed('.');

            // v4.1.5: FN + Backspace = delete profile
            // Note: M5Cardputer Keyboard lib maps Fn+BS → s.del, not s.fn+s.backspace
            if ((s.fn && s.backspace) || s.del) {
                d.fillRect(0, 86, SCREEN_W, 14, PIP_COL_BG);
                d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
                d.setCursor(3, 88);
                d.print("DELETE? [ENTER]yes [ESC]no");

                bool confirmed = false, cancelled = false;
                while (!confirmed && !cancelled) {
                    M5Cardputer.update();
                    if (handleBtnAHome()) return;
                    if (M5Cardputer.Keyboard.isChange() &&
                        M5Cardputer.Keyboard.isPressed()) {
                        Keyboard_Class::KeysState cs = M5Cardputer.Keyboard.keysState();
                        if (cs.enter) confirmed = true;
                        if (cs.esc)   cancelled = true;
                    }
                    delay(20);
                }

                if (confirmed) {
                    for (int i = 0; i < g_profileCount - 1; i++)
                        g_profiles[i] = g_profiles[i + 1];
                    g_profileCount--;
                    saveProfiles();
                    flushProfiles();

                    d.fillRect(0, 86, SCREEN_W, 14, PIP_COL_BG);
                    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
                    d.setCursor(3, 88);
                    d.print(g_profileCount > 0 ? "> DELETED" : "> ALL CLEARED");
                    delay(800);

                    if (g_profileCount == 0) {
                        g_inModal = false;
                        return;   // back to STAT, next entry triggers register
                    }
                    menuSel = MENU_WGT;
                }
                needRedraw = true; dirty = true;
                continue;
            }

            if (g_profileCount == 0) {
                if (s.enter) {
                    registerProfile();
                    g_inModal = true;
                    needRedraw = true; dirty = true;
                }
                if (s.esc) { g_inModal = false; return; }
            } else {
                if (goUp)   { menuSel = 1 - menuSel; dirty = true; }
                if (goDown) { menuSel = 1 - menuSel; dirty = true; }

                if (s.enter) {
                    if (menuSel == MENU_WGT) {
                        viewWeightHistory();
                        g_inModal = true; needRedraw = true; dirty = true;
                    } else if (menuSel == MENU_UPD) {
                        registerProfile(true);  // update existing
                        g_inModal = true; needRedraw = true; dirty = true;
                    }
                }
                if (s.esc) { g_inModal = false; return; }
            }
        }
        delay(30);
    }
}

// ============================================================
// v4.1.6: SCREEN: EQIP — EQUIPMENT TRACKER (long-term items)
// ============================================================

static void drawEqipFull() {
    auto& d = M5Cardputer.Display;
    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);

    drawHeader("EQIP");
    drawTabBar(EQIP);

    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font0);
    d.setCursor(3, 17);
    d.print("> EQUIPMENT LOG");
    d.drawFastHLine(3, 25, SCREEN_W - 6, PIP_COL_BORDER);

    if (g_equipCount == 0) {
        g_equipCursor = -1;
        d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
        d.setCursor(3, 50);
        d.print("> NO ITEMS RECORDED");
        d.setCursor(3, 64);
        d.print("> PRESS [n] TO ADD");
    } else {
        // Clamp cursor
        if (g_equipCursor >= g_equipCount) g_equipCursor = g_equipCount - 1;
        if (g_equipCursor < 0) g_equipCursor = 0;

        time_t now = getNow();
        int y = 28;
        int maxShow = 6;
        int showCount = (g_equipCount < maxShow) ? g_equipCount : maxShow;

        for (int i = 0; i < showCount; i++) {
            auto& r = g_equips[i];
            long days = (long)((now - r.purchaseTs) / 86400L);
            if (days < 0) days = 0;

            bool isSel = (i == g_equipCursor);
            if (isSel) d.fillRect(2, y - 1, SCREEN_W - 4, 12, PIP_COL_GREEN);

            uint16_t col = (days >= 365) ? PIP_COL_GOLD : PIP_COL_GREEN;
            d.setTextColor(isSel ? PIP_COL_BG : col,
                          isSel ? PIP_COL_GREEN : PIP_COL_BG);
            d.setCursor(4, y);
            char nm[EQUIP_NAME_LEN];
            strncpy(nm, r.name, 14);
            nm[14] = '\0';
            d.printf("%-14s %4ldd", nm, days);
            y += 13;
        }

        if (g_equipCount > maxShow) {
            d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
            d.setCursor(3, y);
            d.printf("+ %d more...", g_equipCount - maxShow);
        }
    }

    // Hint (aligned with other pages at y=110)
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.fillRect(0, 108, SCREEN_W, 12, PIP_COL_BG);
    d.setCursor(3, 110);
    d.print("[n] new  [ENTER] select  [^/v] nav");
}

static void drawEquipIcon(int ox, int oy, int iconIdx, uint16_t fg, uint16_t bg) {
    if (iconIdx < 0 || iconIdx >= ICON_COUNT) return;
    auto& d = M5Cardputer.Display;
    d.drawBitmap(ox, oy, g_iconLib[iconIdx].data, 25, 25, fg, bg);
}

// ── Icon selector: 6-column scrollable grid ──
static int selectEquipIcon() {
    auto& d = M5Cardputer.Display;
    g_inModal = true;

    if (ICON_COUNT == 0) { g_inModal = false; return -1; }

    const int COLS         = 6;
    const int CELL_W       = SCREEN_W / COLS;          // 40
    const int ICON_W       = 25, ICON_H = 25;
    const int LABEL_H      = 8;
    const int ROW_H        = ICON_H + LABEL_H + 4;     // 37
    const int TOTAL_ROWS   = (ICON_COUNT + COLS - 1) / COLS;  // 8
    const int VISIBLE_ROWS = 2;
    const int GRID_Y       = 26;
    const int GRID_BOTTOM  = GRID_Y + VISIBLE_ROWS * ROW_H;   // 90

    int sel       = 0;        // flat index 0..ICON_COUNT-1
    int scrollRow = 0;        // first visible row
    bool dirty    = true;

    while (true) {
        // ── Clamp & auto-scroll ──
        if (sel < 0) sel = 0;
        if (sel >= ICON_COUNT) sel = ICON_COUNT - 1;
        int selRow = sel / COLS;

        if (selRow < scrollRow) scrollRow = selRow;
        if (selRow >= scrollRow + VISIBLE_ROWS) scrollRow = selRow - VISIBLE_ROWS + 1;
        if (scrollRow < 0) scrollRow = 0;
        int maxScroll = TOTAL_ROWS - VISIBLE_ROWS;
        if (maxScroll < 0) maxScroll = 0;
        if (scrollRow > maxScroll) scrollRow = maxScroll;

        if (dirty) {
            dirty = false;
            d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
            drawHeader("ICON");
            drawTabBar(EQIP);

            d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
            d.setFont(&fonts::Font0);
            d.setCursor(3, 17);
            d.print("> SELECT ICON");
            d.drawFastHLine(3, 25, SCREEN_W - 6, PIP_COL_BORDER);

            // ── Draw visible rows ──
            for (int r = scrollRow; r < scrollRow + VISIBLE_ROWS && r < TOTAL_ROWS; r++) {
                for (int c = 0; c < COLS; c++) {
                    int idx = r * COLS + c;
                    if (idx >= ICON_COUNT) break;

                    int cx = c * CELL_W + (CELL_W - ICON_W) / 2;      // icon x
                    int cy = GRID_Y + (r - scrollRow) * ROW_H;         // icon y
                    bool isSel = (idx == sel);

                    // Label (abbreviated, centered under icon)
                    d.setTextColor(isSel ? PIP_COL_GOLD : PIP_COL_DIM, PIP_COL_BG);
                    int labelX = c * CELL_W;
                    // Truncate to fit cell width (~6 chars at Font0)
                    char lbl[9];
                    strncpy(lbl, g_iconLib[idx].name, CELL_W / 6);
                    lbl[CELL_W / 6] = '\0';
                    // Center the label text
                    int lblW = strlen(lbl) * 6;
                    int lblX = labelX + (CELL_W - lblW) / 2;
                    if (lblX < labelX) lblX = labelX;
                    d.setCursor(lblX, cy + ICON_H + 1);
                    d.print(lbl);

                    // Icon bitmap
                    uint16_t fgc = isSel ? PIP_COL_GOLD : PIP_COL_GREEN;
                    uint16_t bg  = PIP_COL_BG;
                    d.drawBitmap(cx, cy, g_iconLib[idx].data, ICON_W, ICON_H, fgc, bg);

                    // Golden selection frame
                    if (isSel) {
                        d.drawRect(cx - 1, cy - 1, ICON_W + 2, ICON_H + 2, PIP_COL_GOLD);
                    }
                }
            }

            // ── Scrollbar (right edge) ──
            if (TOTAL_ROWS > VISIBLE_ROWS) {
                const int SB_X = SCREEN_W - 3;
                const int SB_Y = GRID_Y;
                const int SB_H = VISIBLE_ROWS * ROW_H;
                // Track
                d.drawFastVLine(SB_X, SB_Y, SB_H, PIP_COL_BORDER);
                // Thumb
                int thumbH = SB_H * VISIBLE_ROWS / TOTAL_ROWS;
                if (thumbH < 4) thumbH = 4;
                int thumbRange = SB_H - thumbH;
                int thumbY = SB_Y;
                if (maxScroll > 0)
                    thumbY = SB_Y + (long)thumbRange * scrollRow / maxScroll;
                d.fillRect(SB_X, thumbY, 2, thumbH, PIP_COL_GREEN);
                // Reset the border line over the filled area
                d.drawFastVLine(SB_X + 2, SB_Y, SB_H, PIP_COL_BORDER);
            }

            // ── Page counter ──
            d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
            d.setCursor(3, GRID_BOTTOM + 2);
            d.printf("%d/%d", sel + 1, ICON_COUNT);

            // ── Hint bar ──
            d.fillRect(0, GRID_BOTTOM + 12, SCREEN_W, 12, PIP_COL_BG);
            d.setCursor(3, GRID_BOTTOM + 14);
            d.print("[Arrow keys] nav  [ENTER] ok  [ESC] cancel");
        }

        M5Cardputer.update();
        if (handleBtnAHome()) { g_inModal = false; return -1; }
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();

            int prevSel = sel;
            int col = sel % COLS;
            int row = sel / COLS;

            // ← / →
            if (s.left || M5Cardputer.Keyboard.isKeyPressed(',')) {
                if (col > 0)
                    sel--;
                else if (row > 0)
                    sel = (row - 1) * COLS + (COLS - 1);   // wrap up
            }
            if (s.right || M5Cardputer.Keyboard.isKeyPressed('/')) {
                if (col < COLS - 1 && sel + 1 < ICON_COUNT)
                    sel++;
                else if (row < TOTAL_ROWS - 1) {
                    int nxt = (row + 1) * COLS;
                    if (nxt < ICON_COUNT) sel = nxt;       // wrap down
                }
            }

            // ↑ / ↓  — jump one full row
            if (s.up || M5Cardputer.Keyboard.isKeyPressed(';')) {
                int upIdx = sel - COLS;
                if (upIdx >= 0) sel = upIdx;
            }
            if (s.down || M5Cardputer.Keyboard.isKeyPressed('.')) {
                int dnIdx = sel + COLS;
                if (dnIdx < ICON_COUNT) sel = dnIdx;
            }

            if (sel != prevSel) dirty = true;
            if (s.enter) { g_inModal = false; return sel; }
            if (s.esc)   { g_inModal = false; return -1; }
        }
        delay(30);
    }
}

// v4.3.2: auto-calculate SPECIAL bonus from equipment name hash
static void autoCalcEquipBonus(const char* name, SPCIAL* bonus) {
    memset(bonus, 0, sizeof(SPCIAL));
    int hash = 0;
    for (const char* p = name; *p; p++) {
        hash += (unsigned char)(*p);
    }
    int8_t* ptr = (int8_t*)bonus;
    // primary attribute +1
    int attr1 = hash % 7;
    ptr[attr1] = 1;
    // secondary attribute +1 (different from primary)
    int attr2 = (hash / 7) % 7;
    if (attr2 == attr1) attr2 = (attr2 + 1) % 7;
    ptr[attr2] = 1;
    // 1/3 chance of a third +1 attribute
    int attr3 = (hash / 49) % 7;
    if (attr3 == attr1) attr3 = (attr3 + 1) % 7;
    if (attr3 == attr2) attr3 = (attr3 + 1) % 7;
    if ((hash % 3) == 0) ptr[attr3] = 1;
}

static void addEquipment() {
    auto& d = M5Cardputer.Display;
    g_inModal = true;

    EquipRecord rec;
    memset(&rec, 0, sizeof(rec));
    rec.iconIndex = -1;  // no icon by default

    // Field 1: NAME
    char nameBuf[EQUIP_NAME_LEN] = "";
    profileTextInput("> ITEM NAME:", nameBuf, EQUIP_NAME_LEN);
    if (nameBuf[0] == '\0') { g_inModal = false; return; }
    strncpy(rec.name, nameBuf, EQUIP_NAME_LEN - 1);
    rec.name[EQUIP_NAME_LEN - 1] = '\0';

    // Field 2: PURCHASE YEAR
    {
        char yrBuf[5] = "2024";
        profileNumInput("> PURCHASE YEAR (YYYY):", yrBuf, 4, "");
        if (yrBuf[0] == '\0') { g_inModal = false; return; }
        int yr = atoi(yrBuf);
        if (yr < 2000) yr = 2000;
        if (yr > 2030) yr = 2030;

        char moBuf[3] = "1";
        profileNumInput("> PURCHASE MONTH (1-12):", moBuf, 2, "");
        if (moBuf[0] == '\0') { g_inModal = false; return; }
        int mo = atoi(moBuf);
        if (mo < 1) mo = 1; if (mo > 12) mo = 12;

        char dayBuf[3] = "1";
        profileNumInput("> PURCHASE DAY (1-31):", dayBuf, 2, "");
        if (dayBuf[0] == '\0') { g_inModal = false; return; }
        int day = atoi(dayBuf);
        if (day < 1) day = 1; if (day > 31) day = 31;

        struct tm t = {0};
        t.tm_year = yr - 1900;
        t.tm_mon  = mo - 1;
        t.tm_mday = day;
        t.tm_hour = 12;
        rec.purchaseTs = mktime(&t);
        if (rec.purchaseTs <= 0) rec.purchaseTs = getNow();
    }

    // v4.2.3: Field 2.5 — PRICE (optional)
    {
        char prBuf[12] = "";
        profileNumInput("> PRICE (0=skip):", prBuf, 10, ".");
        rec.price = (prBuf[0] != '\0') ? atof(prBuf) : 0.0f;
        if (rec.price < 0.0f) rec.price = 0.0f;
    }

    // v4.3.2: auto-calculate SPECIAL bonus from name (no longer manual)
    autoCalcEquipBonus(rec.name, &rec.bonus);

    // v4.2: Field 4 — Icon selection
    g_inModal = true;
    {
        d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.setFont(&fonts::Font0);
        d.setCursor(3, 30); d.print("> SELECT ICON?");
        d.setCursor(3, 44); d.print("[ENTER] yes  [ESC] skip");
        delay(300);
        bool doIcon = false, doISkip = false;
        while (!doIcon && !doISkip) {
            M5Cardputer.update();
            if (handleBtnAHome()) { g_inModal = false; return; }
            if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
                Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();
                if (s.enter) doIcon = true;
                if (s.esc)   doISkip = true;
            }
            delay(20);
        }
        if (doIcon) {
            rec.iconIndex = selectEquipIcon();
        }
    }

    // Insert at position 0 (newest first)
    int mv = g_equipCount >= MAX_EQUIP ? MAX_EQUIP - 1 : g_equipCount;
    for (int j = mv; j > 0; j--) g_equips[j] = g_equips[j - 1];
    g_equips[0] = rec;
    if (g_equipCount < MAX_EQUIP) g_equipCount++;
    saveEquips();
    flushEquips();

    // Confirmation
    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
    drawHeader("EQIP");
    drawTabBar(EQIP);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font0);
    d.setCursor(3, 30); d.print("> ITEM ADDED");
    d.drawFastHLine(3, 42, SCREEN_W - 6, PIP_COL_BORDER);
    d.setCursor(3, 50); d.printf(">%s", rec.name);
    char dateBuf[16];
    struct tm* ti = getCachedTm(rec.purchaseTs);
    strftime(dateBuf, sizeof(dateBuf), "%Y/%m/%d", ti);
    d.setCursor(3, 64); d.printf(">SINCE %s", dateBuf);
    // v4.3.2: show auto-calculated bonus on confirmation
    {
        char bbuf[32] = ">BONUS:";
        const char* spNames = "SPCIAL";
        int8_t* bptr = (int8_t*)&rec.bonus;
        for (int i = 0; i < 7; i++) {
            if (bptr[i] != 0) {
                char tmp[8];
                snprintf(tmp, sizeof(tmp), " %c%+d", spNames[i], bptr[i]);
                strncat(bbuf, tmp, sizeof(bbuf) - strlen(bbuf) - 1);
            }
        }
        d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
        d.setCursor(3, 74); d.print(bbuf);
    }
    if (rec.price > 0.0f) {
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.setCursor(3, 88); d.printf(">PRICE: %d", (int)rec.price);
    }
    if (rec.iconIndex >= 0) {
        d.drawBitmap(180, 48, g_iconLib[rec.iconIndex].data, 25, 25, PIP_COL_GREEN, PIP_COL_BG);
    }
    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(3, 100); d.print("[any key] continue");
    delay(800);
    while (true) {
        M5Cardputer.update();
        if (handleBtnAHome()) { g_inModal = false; return; }
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) break;
        delay(20);
    }
    g_inModal = false;
}

// v4.2: Single equipment item detail view — replaces old viewEquipList
static void viewEquipDetail(int index) {
    auto& d = M5Cardputer.Display;
    g_inModal = true;

    if (index < 0 || index >= g_equipCount) { g_inModal = false; return; }

    EquipRecord& rec = g_equips[index];
    bool dirty = true;
    int iconSel = 0;   // 0 = no icon area selected, 1 = icon area selected (golden frame)

    while (true) {
        if (dirty) {
            dirty = false;
            d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
            drawHeader("DETAIL");
            drawTabBar(EQIP);

            d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
            d.setFont(&fonts::Font0);

            // Subtitle + separator (compact, at very top)
            d.setCursor(3, 17);
            d.print("> ITEM DETAIL");
            d.drawFastHLine(3, 25, SCREEN_W - 6, PIP_COL_BORDER);

            // --- Content starts after separator, shifted 8px down ---
            // Name
            d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
            d.setCursor(3, 30);
            d.printf("NAME: %s", rec.name);

            // Purchase time
            char dateBuf[16];
            struct tm* ti = getCachedTm(rec.purchaseTs);
            strftime(dateBuf, sizeof(dateBuf), "%Y/%m/%d", ti);
            d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
            d.setCursor(3, 42);
            d.printf("PURCHASED: %s", dateBuf);

            // Companion time
            time_t now = getNow();
            long days = (long)((now - rec.purchaseTs) / 86400L);
            if (days < 0) days = 0;
            long years = days / 365;
            long remDays = days % 365;
            d.setTextColor((days >= 365) ? PIP_COL_GOLD : PIP_COL_GREEN, PIP_COL_BG);
            d.setCursor(3, 54);
            if (years > 0)
                d.printf("DAYS: %ldd (%ldy %ldd)", days, years, remDays);
            else
                d.printf("DAYS: %ldd", days);

            // Price + avg daily cost (v4.2.3)
            if (rec.price > 0.0f && days > 0) {
                float avgDay = rec.price / (float)days;
                d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
                d.setCursor(3, 66);
                d.printf("PRICE: %d", (int)rec.price);
                if (avgDay >= 1.0f)
                    d.printf("  AVG: %.0f/day", avgDay);
                else
                    d.printf("  AVG: %.2f/day", avgDay);
            } else if (rec.price > 0.0f) {
                d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
                d.setCursor(3, 66);
                d.printf("PRICE: %d", (int)rec.price);
            }

            // Stat bonus (v4.2.6: show raw + effective with diminishing div)
            bool hasBonus = false;
            const int8_t* bv = &rec.bonus.s;
            for (int i = 0; i < 7; i++) { if (bv[i] != 0) hasBonus = true; }
            if (hasBonus) {
                int div = max(1, (g_equipCount + 1) / 2);
                d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
                d.setCursor(3, 78);
                d.printf("BONUS: S+%d", rec.bonus.s / div);
                if (rec.bonus.p != 0) d.printf(" P+%d", rec.bonus.p / div);
                if (rec.bonus.e != 0) d.printf(" E+%d", rec.bonus.e / div);
                if (rec.bonus.c != 0) d.printf(" C+%d", rec.bonus.c / div);
                if (rec.bonus.i != 0) d.printf(" I+%d", rec.bonus.i / div);
                if (rec.bonus.a != 0) d.printf(" A+%d", rec.bonus.a / div);
                if (rec.bonus.l != 0) d.printf(" L+%d", rec.bonus.l / div);

                // v4.3: aging effect inline — C fades, I grows with age
                time_t now = getNow();
                long itemAgeDays = (now - rec.purchaseTs) / 86400L;
                if (itemAgeDays > 180) {
                    int ap = itemAgeDays / 180;
                    d.setTextColor(PIP_COL_CYAN, PIP_COL_BG);
                    d.printf(" | C-%d I+%d", ap, ap);
                }
            }

            // Icon display area (right side, aligned with content mid-area)
            const int iconX = 195;
            const int iconY = 40;
            bool hasIcon = (rec.iconIndex >= 0 && rec.iconIndex < ICON_COUNT);

            if (hasIcon) {
                d.drawBitmap(iconX, iconY, g_iconLib[rec.iconIndex].data, 25, 25,
                    PIP_COL_GREEN, PIP_COL_BG);
                if (iconSel == 1) {
                    d.drawRect(iconX - 1, iconY - 1, 27, 27, PIP_COL_GOLD);
                }
            } else {
                d.drawRect(iconX, iconY, 25, 25, PIP_COL_BORDER);
                if (iconSel == 1) {
                    d.drawRect(iconX - 1, iconY - 1, 27, 27, PIP_COL_GOLD);
                }
            }

            // Icon selection hint (aligned with other pages at y=110)
            d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
            d.fillRect(0, 108, SCREEN_W, 12, PIP_COL_BG);
            d.setCursor(3, 110);
            if (iconSel == 1) {
                d.print("[< >] icon  [ENTER] pick  [ESC] back");
            } else {
                d.print("[< >] icon  [ESC] back  [FN+BS] del");
            }
        }

        M5Cardputer.update();
        if (handleBtnAHome()) return;
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();
            bool goLeft  = s.left  || M5Cardputer.Keyboard.isKeyPressed(',');
            bool goRight = s.right || M5Cardputer.Keyboard.isKeyPressed('/');

            if (goLeft || goRight) {
                iconSel = 1 - iconSel;  // toggle between detail area and icon area
                dirty = true;
            }

            // Enter on icon area: open icon picker
            if (s.enter && iconSel == 1) {
                int newIcon = selectEquipIcon();
                if (newIcon >= 0) {
                    rec.iconIndex = newIcon;
                    saveEquips();
                    flushEquips();
                }
                g_inModal = true;
                iconSel = 0;
                dirty = true;
            }

            // FN+Backspace = delete
            // Note: M5Cardputer Keyboard lib maps Fn+BS → s.del, not s.fn+s.backspace
            if ((s.fn && s.backspace) || s.del) {
                d.fillRect(0, 86, SCREEN_W, 14, PIP_COL_BG);
                d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
                d.setCursor(3, 88);
                d.print("DELETE? [ENTER]yes [ESC]no");

                bool confirmed = false, cancelled = false;
                while (!confirmed && !cancelled) {
                    M5Cardputer.update();
                    if (handleBtnAHome()) return;
                    if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
                        Keyboard_Class::KeysState cs = M5Cardputer.Keyboard.keysState();
                        if (cs.enter) confirmed = true;
                        if (cs.esc)   cancelled = true;
                    }
                    delay(20);
                }

                if (confirmed) {
                    for (int i = index; i < g_equipCount - 1; i++)
                        g_equips[i] = g_equips[i + 1];
                    g_equipCount--;
                    saveEquips();
                    flushEquips();
                    g_inModal = false;
                    return;
                }
                dirty = true;
            }

            if (s.esc) { g_inModal = false; return; }
        }
        delay(30);
    }
}

// ============================================================
// v4.1.7: SCREENSHOT — save display to SD card as BMP
// ============================================================

// Cardputer SD card pin assignment (from M5Unified pin table):
//   SCK  = GPIO40   (NOT the CS pin!)
//   MOSI = GPIO14
//   MISO = GPIO39
//   CS   = GPIO12
// Display uses SPI3 (MOSI=GPIO35, SCLK=GPIO36, CS=GPIO37) — separate bus.
//
// The previous SD.begin(40) was wrong: GPIO40 is SCK not CS, and Arduino's
// default SPI pins (GPIO18/19/23) don't match Cardputer hardware, causing
// SD init to hang and corrupt the display SPI bus → "frozen" symptom.

static bool takeScreenshot() {
    auto& d = M5Cardputer.Display;

    // Show capture indicator (drawn on display BEFORE touching SD)
    d.fillRect(0, 0, SCREEN_W, 14, PIP_COL_BORDER);
    d.setTextColor(PIP_COL_GOLD, PIP_COL_BORDER);
    d.setFont(&fonts::Font0);
    d.setCursor(3, 3);
    d.print("> CAPTURING...");

    // v4.1.7: init SD with correct pins on a dedicated SPI2 bus
    if (!g_sdReady) {
        g_sdSPI.begin(40, 39, 14, 12);   // SCK, MISO, MOSI, SS
        if (!SD.begin(12, g_sdSPI, 20000000)) {
            d.fillRect(0, 0, SCREEN_W, 14, PIP_COL_BORDER);
            d.setTextColor(PIP_COL_GOLD, PIP_COL_BORDER);
            d.setCursor(3, 3);
            d.print("> NO SD CARD");
            delay(1500);
            // redraw header
            switch (g_screen) {
                case STAT: drawStatFull(); break;
                case EQIP: drawEqipFull(); break;
                case CAL:  drawCalFull();  break;
                case CAFF: drawCaffFull(); break;
                case LORA: drawLoraFull(); break;
                case MEMO: drawMemoFull(); break;
            }
            return false;
        }
        g_sdReady = true;
    }

    // Create /picture directory if it doesn't exist
    if (!SD.exists("/picture")) {
        SD.mkdir("/picture");
    }

    // Find next available filename
    char filename[40];
    int shotNum = 0;
    do {
        snprintf(filename, sizeof(filename), "/picture/shot_%04d.bmp", shotNum);
        shotNum++;
        if (shotNum > 9999) {
            d.fillRect(0, 0, SCREEN_W, 14, PIP_COL_BORDER);
            d.setTextColor(PIP_COL_GOLD, PIP_COL_BORDER);
            d.setCursor(3, 3);
            d.print("> TOO MANY SHOTS");
            delay(1500);
            return false;
        }
    } while (SD.exists(filename));

    File file = SD.open(filename, FILE_WRITE);
    if (!file) {
        d.fillRect(0, 0, SCREEN_W, 14, PIP_COL_BORDER);
        d.setTextColor(PIP_COL_GOLD, PIP_COL_BORDER);
        d.setCursor(3, 3);
        d.print("> WRITE FAILED");
        delay(1500);
        return false;
    }

    const int W = SCREEN_W;   // 240
    const int H = SCREEN_H;   // 135
    const int rowSize = (W * 3 + 3) & ~3;  // 4-byte aligned = 720
    const uint32_t pixelDataSize = rowSize * H;
    const uint32_t fileSize = 54 + pixelDataSize;

    // --- BMP File Header (14 bytes) + DIB Header (40 bytes) ---
    uint8_t bmpHeader[54];
    memset(bmpHeader, 0, sizeof(bmpHeader));
    bmpHeader[0]  = 'B';
    bmpHeader[1]  = 'M';
    bmpHeader[2]  = fileSize & 0xFF;
    bmpHeader[3]  = (fileSize >> 8) & 0xFF;
    bmpHeader[4]  = (fileSize >> 16) & 0xFF;
    bmpHeader[5]  = (fileSize >> 24) & 0xFF;
    bmpHeader[10] = 54;
    bmpHeader[14] = 40;
    bmpHeader[18] = W & 0xFF;
    bmpHeader[19] = (W >> 8) & 0xFF;
    bmpHeader[22] = H & 0xFF;
    bmpHeader[23] = (H >> 8) & 0xFF;
    bmpHeader[26] = 1;
    bmpHeader[28] = 24;
    bmpHeader[34] = pixelDataSize & 0xFF;
    bmpHeader[35] = (pixelDataSize >> 8) & 0xFF;
    bmpHeader[36] = (pixelDataSize >> 16) & 0xFF;
    bmpHeader[37] = (pixelDataSize >> 24) & 0xFF;

    file.write(bmpHeader, 54);

    // Read display pixels line by line (bottom-to-top for BMP format)
    // and convert RGB565 → BGR888.
    // Cardputer ST7789 is configured readable=true (3-wire SPI half-duplex).
    // Each row read takes ~20-50ms, total ~3-7 seconds for 135 rows.
    uint16_t rowBuf565[W];
    uint8_t  rowBufBGR[rowSize];
    memset(rowBufBGR, 0, sizeof(rowBufBGR));

    for (int row = 0; row < H; row++) {
        // BMP is bottom-to-top: row 0 in file = bottom row of display
        int displayY = H - 1 - row;

        // Read one row of RGB565 pixels from display
        d.readRect(0, displayY, W, 1, rowBuf565);

        // Convert to BGR888
        // v4.3.2: M5GFX readRect returns big-endian RGB565 on ST7789;
        // swap bytes to get correct little-endian before decoding.
        for (int x = 0; x < W; x++) {
            uint16_t px = rowBuf565[x];
            px = ((px >> 8) & 0xFF) | ((px & 0xFF) << 8);  // swap bytes
            uint8_t r = ((px >> 11) & 0x1F) << 3;
            uint8_t g = ((px >> 5)  & 0x3F) << 2;
            uint8_t b = (px         & 0x1F) << 3;
            rowBufBGR[x * 3]     = b;  // B
            rowBufBGR[x * 3 + 1] = g;  // G
            rowBufBGR[x * 3 + 2] = r;  // R
        }

        file.write(rowBufBGR, rowSize);

        // v4.1.7: update progress bar every 15 rows so user sees it's alive
        if (row % 15 == 0) {
            int pct = (row * 100) / H;
            d.fillRect(100, 0, 60, 14, PIP_COL_BORDER);
            d.setTextColor(PIP_COL_GREEN, PIP_COL_BORDER);
            d.setCursor(100, 3);
            d.printf("%d%%", pct);
        }
    }

    file.close();

    // Success message
    d.fillRect(0, 0, SCREEN_W, 14, PIP_COL_BORDER);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BORDER);
    d.setCursor(3, 3);
    d.printf("> SAVED %s", filename);
    delay(1500);

    // Redraw the original screen
    switch (g_screen) {
        case STAT:  drawStatFull();  break;
        case EQIP:  drawEqipFull();  break;
        case CAL:   drawCalFull();   break;
        case CAFF:  drawCaffFull();  break;
        case LORA:  drawLoraFull();  break;
        case MEMO:  drawMemoFull();  break;
    }
    return true;
}



// v4.1: fixed char buffer — no heap String allocation
static void wifiInputField(const char* label, char* outBuf, int maxLen, const char* defaultVal, bool isPassword) {
    auto& d = M5Cardputer.Display;
    // Start with default value
    int len = 0;
    if (defaultVal && defaultVal[0]) {
        len = strlen(defaultVal);
        if (len >= maxLen) len = maxLen - 1;
        memcpy(outBuf, defaultVal, len);
    }
    outBuf[len] = '\0';

    // v4.3.4: caps lock toggle for password input (case-sensitive)
    bool capsLock = false;

    d.fillRect(0, 14, SCREEN_W, SCREEN_H - 30, PIP_COL_BG);
    drawHeader("SETUP");

    d.setFont(&fonts::Font0);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setCursor(3, 20);
    d.print(label);

    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
    d.setCursor(3, 60);
    d.print("[ENTER]ok [BS]del [SHIFT]CAPS [ESC]skip");

    while (true) {
        // v4.3.4: always show plaintext (no asterisk masking)
        d.fillRect(3, 32, SCREEN_W - 6, 22, PIP_COL_BG);
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.setCursor(3, 40);
        d.print(outBuf);
        if ((millis() / 500) % 2) d.print("_");

        // Caps lock indicator (top-right corner)
        d.fillRect(SCREEN_W - 52, 20, 52, 12, PIP_COL_BG);
        d.setTextColor(capsLock ? PIP_COL_GOLD : PIP_COL_DIM, PIP_COL_BG);
        d.setCursor(SCREEN_W - 50, 22);
        d.printf("CAPS:%s", capsLock ? "ON" : "OFF");

        M5Cardputer.update();
        if (handleBtnAHome()) { outBuf[0] = '\0'; return; }
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();

            // v4.1: ESC returns empty string (skip)
            if (s.esc) { outBuf[0] = '\0'; return; }

            // v4.3.5: Shift key (Fn右侧专属键) pressed alone → toggle caps lock
            if (s.shift && s.word.empty()) {
                capsLock = !capsLock;
            } else {
                if (s.backspace && len > 0)
                    outBuf[--len] = '\0';

                // ENTER → keep current buffer content and return
                if (s.enter) return;

                for (char c : s.word) {
                    if (c >= 32 && c <= 126 && len < maxLen - 1) {
                        // v4.3.4: apply caps lock to lowercase letters
                        if (capsLock && c >= 'a' && c <= 'z')
                            c -= 32;
                        outBuf[len++] = c;
                        outBuf[len] = '\0';
                    }
                }
            }
        }
        delay(20);
    }
}

static bool wifiConnectAndSync(const char* ssid, const char* pass) {
    auto& d = M5Cardputer.Display;

    esp_task_wdt_config_t wdtCfg = {
        .timeout_ms = 30000, .idle_core_mask = 0, .trigger_panic = true
    };
    esp_task_wdt_reconfigure(&wdtCfg);
    esp_task_wdt_reset();

    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(false);
    WiFi.begin(ssid, pass);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 40) {
        esp_task_wdt_reset();
        delay(250);
        attempts++;
        if (attempts % 4 == 0) d.print(".");
        // v4.3.4: early exit on definitive failure (wrong password)
        if (WiFi.status() == WL_CONNECT_FAILED) break;
    }

    if (WiFi.status() != WL_CONNECTED) {
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        esp_task_wdt_config_t nWdt = { .timeout_ms = 10000, .idle_core_mask = 0, .trigger_panic = true };
        esp_task_wdt_reconfigure(&nWdt);
        return false;
    }

    d.setCursor(10, 65);
    d.print("\n> SYNCING PIP-BOY CLOCK...");
    configTime(GMT_OFFSET, DST_OFFSET, NTP_SERVER);

    int ntAttempts = 0;
    struct tm ti;
    while (!getLocalTime(&ti) && ntAttempts < 30) {
        esp_task_wdt_reset();
        delay(250);
        ntAttempts++;
        if (ntAttempts % 4 == 0) d.print(".");
    }

    if (getLocalTime(&ti)) {
        g_timeValid = true;
        g_prefs.putULong64(KEY_LAST_TIME, (uint64_t)mktime(&ti));
        d.setCursor(10, 80);
        d.print("\n> CLOCK SYNCHRONIZED");
    }

    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);

    esp_task_wdt_config_t nWdt = { .timeout_ms = 10000, .idle_core_mask = 0, .trigger_panic = true };
    esp_task_wdt_reconfigure(&nWdt);

    delay(1000);
    return true;
}

// ============================================================
// WIFI SCAN & PICK
// ============================================================

static void wifiScanAndPick(char* outBuf, int maxLen) {
    auto& d = M5Cardputer.Display;

    d.fillScreen(PIP_COL_BG);
    d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
    d.setFont(&fonts::Font0);
    d.setCursor(10, 40);
    d.print("> SCANNING VAULT-NET...");
    d.setCursor(10, 55);
    d.print("> PLEASE WAIT");

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    int n = WiFi.scanNetworks();

    d.fillScreen(PIP_COL_BG);
    if (n <= 0) {
        d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
        d.setCursor(10, 55);
        d.print("> NO NETWORKS FOUND");
        d.setCursor(10, 72);
        d.print("> [ANY KEY] back");
        while (true) {
            M5Cardputer.update();
            if (handleBtnAHome()) { outBuf[0] = '\0'; return; }
            if (M5Cardputer.Keyboard.isChange() &&
                M5Cardputer.Keyboard.isPressed()) {
                outBuf[0] = '\0';
                return;
            }
            delay(30);
        }
    }

    int selected  = 0;
    int scrollOff = 0;
    const int LIST_Y0 = 18;
    const int ITEM_H  = 12;
    const int MAX_VIS = 8;

    while (true) {
        d.fillRect(0, 0, SCREEN_W, 14, PIP_COL_BORDER);
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BORDER);
        d.setCursor(3, 3);
        d.printf("NETWORKS: %d", n);

        for (int i = scrollOff; i < scrollOff + MAX_VIS && i < n; i++) {
            int y  = LIST_Y0 + (i - scrollOff) * ITEM_H;
            bool sel = (i == selected);

            d.fillRect(0, y, SCREEN_W, ITEM_H,
                       sel ? PIP_COL_GREEN : PIP_COL_BG);
            d.setTextColor(sel ? PIP_COL_BG : PIP_COL_GREEN,
                          sel ? PIP_COL_GREEN : PIP_COL_BG);
            d.setCursor(5, y + 1);

            String ssid = WiFi.SSID(i);
            if (ssid.length() > 26) ssid = ssid.substring(0, 24) + "..";
            d.print(sel ? "> " : "  ");
            d.print(ssid);

            int rssi = WiFi.RSSI(i);
            int bars = 0;
            if (rssi > -55)      bars = 4;
            else if (rssi > -70) bars = 3;
            else if (rssi > -85) bars = 2;
            else                 bars = 1;

            d.setCursor(SCREEN_W - 22, y + 1);
            for (int b = 0; b < 4; b++) {
                d.print(b < bars ? "|" : " ");
            }
        }

        d.fillRect(0, SCREEN_H - 14, SCREEN_W, 14, PIP_COL_BG);
        d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
        d.setCursor(3, SCREEN_H - 10);
        d.print("[^/v] nav  [ENTER] pick  [ESC] back");

        M5Cardputer.update();
        if (handleBtnAHome()) { outBuf[0] = '\0'; return; }
        if (M5Cardputer.Keyboard.isChange() &&
            M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();

            bool goUp   = s.up   || M5Cardputer.Keyboard.isKeyPressed(';');
            bool goDown = s.down || M5Cardputer.Keyboard.isKeyPressed('.');

            if (goUp && selected > 0) {
                selected--;
                if (selected < scrollOff) scrollOff = selected;
            }
            if (goDown && selected < n - 1) {
                selected++;
                if (selected >= scrollOff + MAX_VIS)
                    scrollOff = selected - MAX_VIS + 1;
            }
            if (s.enter) {
                String chosen = WiFi.SSID(selected);
                // v4.1: copy to fixed buffer
                int clen = chosen.length();
                if (clen >= maxLen) clen = maxLen - 1;
                memcpy(outBuf, chosen.c_str(), clen);
                outBuf[clen] = '\0';
                WiFi.scanDelete();
                WiFi.mode(WIFI_OFF);
                return;
            }
            if (s.esc) {
                outBuf[0] = '\0';
                WiFi.scanDelete();
                WiFi.mode(WIFI_OFF);
                return;
            }
        }
        delay(30);
    }
}

static int wifiSetupMenu() {
    auto& d = M5Cardputer.Display;

    // v4.3.5: 上下导航 + Enter 确认，与系统其他菜单操作逻辑统一
    int sel = 0;  // 0=scan, 1=manual, 2=offline
    const int NUM_ITEMS = 3;
    const char* items[] = {
        "SCAN NEARBY NETWORKS",
        "TYPE SSID MANUALLY",
        "SKIP - GO OFFLINE"
    };
    bool dirty = true;

    while (true) {
        if (dirty) {
            dirty = false;
            d.fillScreen(PIP_COL_BG);
            d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
            d.setFont(&fonts::Font0);

            d.setCursor(10, 20);
            d.print("> SELECT WIFI METHOD");
            d.drawFastHLine(10, 38, SCREEN_W - 20, PIP_COL_BORDER);

            for (int i = 0; i < NUM_ITEMS; i++) {
                int y = 46 + i * 16;
                bool isSel = (i == sel);
                if (isSel) {
                    d.fillRect(6, y - 1, SCREEN_W - 12, 14, PIP_COL_GREEN);
                    d.setTextColor(PIP_COL_BG, PIP_COL_GREEN);
                } else {
                    d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
                }
                d.setCursor(14, y + 1);
                d.printf("%s %s", isSel ? ">" : " ", items[i]);
            }

            d.setTextColor(PIP_COL_DIM, PIP_COL_BG);
            d.setCursor(10, SCREEN_H - 12);
            d.print("[^/v] select  [ENTER] confirm");
        }

        M5Cardputer.update();
        if (handleBtnAHome()) return 0;
        if (M5Cardputer.Keyboard.isChange() &&
            M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();

            if (s.esc) return 0;

            bool goUp   = s.up   || M5Cardputer.Keyboard.isKeyPressed(';');
            bool goDown = s.down || M5Cardputer.Keyboard.isKeyPressed('.');

            if (goUp)   { sel = (sel - 1 + NUM_ITEMS) % NUM_ITEMS; dirty = true; }
            if (goDown) { sel = (sel + 1) % NUM_ITEMS; dirty = true; }

            if (s.enter) {
                // 0=scan→return 1, 1=manual→return 2, 2=offline→return 0
                return sel == 2 ? 0 : sel + 1;
            }
        }
        delay(30);
    }
}

static bool wifiSetup() {
    auto& d = M5Cardputer.Display;

    // v4.1: fixed char buffers for SSID/password
    char ssid[33] = "";
    char pass[33] = "";

    // Load stored credentials into buffers
    String storedSsid = g_prefs.getString(KEY_WIFI_SSID, "");
    String storedPass = g_prefs.getString(KEY_WIFI_PASS, "");
    storedSsid.toCharArray(ssid, sizeof(ssid));
    storedPass.toCharArray(pass, sizeof(pass));

    // Try silent connect if stored credentials exist
    if (ssid[0] != '\0') {
        d.fillScreen(PIP_COL_BG);
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.setFont(&fonts::Font0);
        d.setCursor(10, 50);
        d.print("> CONNECTING TO VAULT-NET...");
        d.setCursor(10, 60);
        d.printf("> SSID: %s", ssid);

        if (wifiConnectAndSync(ssid, pass)) {
            return true;
        }

        d.fillScreen(PIP_COL_BG);
        d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
        d.setCursor(10, 50);
        d.print("> SIGNAL LOST");
        d.setCursor(10, 65);
        d.print("> RE-ENTER CREDENTIALS...");
        delay(1500);
    }

    // v4.3.4: retry loop — on connection failure, show error and return to
    // network selection so the user can re-pick SSID and re-enter password.
    while (true) {
        int method = wifiSetupMenu();

        if (method == 0) {
            g_timeValid = false;
            d.fillScreen(PIP_COL_BG);
            d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
            d.setFont(&fonts::Font0);
            d.setCursor(10, 55);
            d.print("> OFFLINE MODE");
            d.setCursor(10, 70);
            d.print("> LOCAL TIME ACTIVE");
            delay(1500);
            return false;
        }

        if (method == 1) {
            wifiScanAndPick(ssid, sizeof(ssid));
        } else {
            wifiInputField("> SSID:", ssid, sizeof(ssid), ssid, false);
        }

        if (ssid[0] == '\0') {
            g_timeValid = false;
            d.fillScreen(PIP_COL_BG);
            d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
            d.setFont(&fonts::Font0);
            d.setCursor(10, 55);
            d.print("> OFFLINE MODE");
            d.setCursor(10, 70);
            d.print("> LOCAL TIME ACTIVE");
            delay(1500);
            return false;
        }

        wifiInputField("> PASSWORD:", pass, sizeof(pass), pass, true);

        // Save credentials (only at this point, via String for Preferences API)
        g_prefs.putString(KEY_WIFI_SSID, String(ssid));
        g_prefs.putString(KEY_WIFI_PASS, String(pass));

        d.fillScreen(PIP_COL_BG);
        d.setTextColor(PIP_COL_GREEN, PIP_COL_BG);
        d.setFont(&fonts::Font0);
        d.setCursor(10, 50);
        d.print("> CONNECTING TO VAULT-NET...");
        d.setCursor(10, 60);
        d.printf("> SSID: %s", ssid);

        bool ok = wifiConnectAndSync(ssid, pass);
        if (ok) return true;

        // v4.3.4: connection failed — show error, loop back to network selection
        d.fillScreen(PIP_COL_BG);
        d.setTextColor(PIP_COL_GOLD, PIP_COL_BG);
        d.setFont(&fonts::Font0);
        d.setCursor(10, 45);
        d.print("> PASSWORD ERROR");
        d.setCursor(10, 60);
        d.print("> OR NETWORK UNAVAILABLE");
        d.setCursor(10, 75);
        d.print("> RETRY IN 2s...");
        delay(2000);
        // Loop back to wifiSetupMenu() — user can re-pick network & password
    }
}

// ============================================================
// KEYBOARD INPUT (v4.1: debounce)
// ============================================================

static void handleNormalKeys() {
    // v4.1.1: do NOT intercept when a modal dialog (enterRecordTime,
    // addCoffee, addMeal, setCalGoal) is consuming keyboard events.
    if (g_inModal) return;

    // v4.1: M5Cardputer.update() already called in loop() before us
    // (needed for BtnA state too).

    if (!M5Cardputer.Keyboard.isChange() || !M5Cardputer.Keyboard.isPressed())
        return;

    // v4.1: debounce — skip rapid repeated key events
    unsigned long now = millis();
    if (now - g_lastKeyTime < KEY_DEBOUNCE_MS) return;
    g_lastKeyTime = now;

    Keyboard_Class::KeysState s = M5Cardputer.Keyboard.keysState();

    bool goLeft  = s.left  || M5Cardputer.Keyboard.isKeyPressed(',');
    bool goRight = s.right || M5Cardputer.Keyboard.isKeyPressed('/')
                          || s.tab;
    bool goUp    = s.up    || M5Cardputer.Keyboard.isKeyPressed(';');
    bool goDown  = s.down  || M5Cardputer.Keyboard.isKeyPressed('.');

    // v4.1.6: CTRL+S = screenshot to SD card
    if (s.ctrl) {
        for (char c : s.word) {
            if (c == 'S' || c == 's') {
                takeScreenshot();
                return;
            }
        }
    }

    // --- Volume (LORA only) ---
    bool volDown = M5Cardputer.Keyboard.isKeyPressed('-');
    bool volUp   = M5Cardputer.Keyboard.isKeyPressed('=');
    if ((volDown || volUp) && g_screen == LORA) {
        if (volDown && g_volume > 0)   g_volume -= 5;
        if (volUp   && g_volume < 100) g_volume += 5;
        flushVolume();
        drawLoraFull();
        return;
    }

    // --- Left/Right tab switching ---
    if (goRight) {
        g_screen = (Screen)(((int)g_screen + 1) % NUM_SCREENS);
        switch (g_screen) {
            case STAT:  drawStatFull();  break;
            case EQIP:  drawEqipFull();  break;
            case CAL:   drawCalFull();   break;
            case CAFF:  drawCaffFull();  break;
            case LORA:  drawLoraFull();  break;
            case MEMO:  drawMemoFull();  break;
        }
        return;
    }
    if (goLeft) {
        g_screen = (Screen)(((int)g_screen + NUM_SCREENS - 1) % NUM_SCREENS);
        switch (g_screen) {
            case STAT:  drawStatFull();  break;
            case EQIP:  drawEqipFull();  break;
            case CAL:   drawCalFull();   break;
            case CAFF:  drawCaffFull();  break;
            case LORA:  drawLoraFull();  break;
            case MEMO:  drawMemoFull();  break;
        }
        return;
    }

    // --- STAT vault boy selection (v4.1.3) ---
    if (g_screen == STAT) {
        if (goUp || goDown) {
            g_statSel = 1 - g_statSel;
            // v4.1.3: reset blink state so frame shows immediately on select
            g_statBlinkOn = true;
            g_lastStatBlink = millis();
            drawStatFull();
            if (g_statSel == 1) drawStatSelectionFrame();
            return;
        }
        if (s.enter && g_statSel == 1) {
            viewProfile();
            drawStatFull();
            return;
        }
        return;
    }

    // --- CAL inline menu ---
    if (g_screen == CAL) {
        if (goUp || goDown) {
            g_calMenuSel = 1 - g_calMenuSel;
            drawCalFull();
            return;
        }
        if (s.enter) {
            if (g_calMenuSel == 0) { setCalGoal(); }
            else                   { addMeal();    }
            return;
        }
        return;
    }

    // --- MEMO number keys ---
    if (g_screen == MEMO) {
        for (char c : s.word) {
            if (c >= '1' && c <= '9') {
                int idx = c - '1';
                if (idx < g_memoCount) {
                    memoEditor(idx);
                    return;
                }
            }
        }
    }

    // --- EQIP: up/down navigates items ---
    if (g_screen == EQIP) {
        if (goUp && g_equipCount > 0 && g_equipCursor > 0) {
            g_equipCursor--;
            drawEqipFull();
            return;
        }
        if (goDown && g_equipCount > 0 && g_equipCursor < g_equipCount - 1) {
            g_equipCursor++;
            drawEqipFull();
            return;
        }
        // --- n key: add new equipment ---
        for (char c : s.word) {
            if (c == 'n' || c == 'N') {
                addEquipment();
                drawEqipFull();
                return;
            }
        }
    }

    // --- Enter actions ---
    if (s.enter) {
        switch (g_screen) {
            case CAFF:  addCoffee();       break;
            case MEMO:  addMemo();         break;
            case EQIP:
                if (g_equipCount > 0 && g_equipCursor >= 0) {
                    viewEquipDetail(g_equipCursor);
                    drawEqipFull();
                }
                break;
            default: break;
        }
        return;
    }

    // --- LORA PTT ---
    if (g_screen == LORA) {
        bool pttPressed = M5Cardputer.Keyboard.isKeyPressed(' ');
        if (pttPressed && !g_loraPtt) {
            g_loraPtt = true;
            drawLoraFull();
            return;
        }
        if (!pttPressed && g_loraPtt) {
            g_loraPtt = false;
            drawLoraFull();
            return;
        }
    }
}

// ============================================================
// SETUP & LOOP (v4.1: fixed g_bootTime order, NVS flushing)
// ============================================================

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);

    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setBrightness(128);

    // v4.1: FIXED — fallback first, then loadData() may override
    g_bootTime = 1719700000;   // hardcoded fallback
    loadData();                 // restores saved time if it exists (only if > 1e9)

    drawBootSplash();

    wifiSetup();

    // Re-inject M5 config if WiFi killed it
    if (!M5Cardputer.Display.width()) {
        M5Cardputer.begin(cfg, true);
        M5Cardputer.Display.setRotation(1);
        M5Cardputer.Display.setBrightness(128);
    }

    drawStatFull();
}

void loop() {
    // v4.1.8: single update() call per frame — drives keyboard, BtnA, etc.
    M5Cardputer.update();

    // v4.2.6: capture BtnA press into a global flag BEFORE processing.
    // wasPressed() is edge-triggered with a one-frame window; the modal's
    // own update() would advance _oldPress and clear the latch otherwise.
    if (M5Cardputer.BtnA.wasPressed()) g_btnAHome = true;

    handleNormalKeys();

    // v4.2.6: handle BtnA → STAT for non-modal screens.
    // Modal loops check g_btnAHome via handleBtnAHome() internally.
    if (g_btnAHome && !g_inModal) {
        g_btnAHome = false;
        if (g_screen != STAT) {
            g_screen = STAT;
            g_statSel = 0;
            drawStatFull();
        }
    }

    unsigned long now = millis();

    // --- Battery refresh ---
    if (now - g_lastBattRead >= BATT_READ_INTERVAL_MS) {
        updateBatteryDisplay();
    }

    // --- STAT clock + S.P.E.C.I.A.L. + vault boy blink (v4.1.3) ---
    if (g_screen == STAT) {
        if (now - g_lastClock >= 1000) {
            g_lastClock = now;
            drawStatClockPartial();
            static unsigned long lastSpcl = 0;
            if (now - lastSpcl >= 5000) {
                lastSpcl = now;
                drawStatSpecial();
            }
        }
        // v4.1.3: blink selection frame at 1Hz (1000ms full cycle, 500ms toggle)
        if (g_statSel == 1 && now - g_lastStatBlink >= 500) {
            g_lastStatBlink = now;
            g_statBlinkOn = !g_statBlinkOn;
            drawStatSelectionFrame();
        }
    }

    // --- CAFF metabolism ---
    if (g_screen == CAFF) {
        if (now - g_lastMetab >= 30000) {
            g_lastMetab = now;
            drawCaffMetabPartial();
        }
    }

    // === v4.1: NVS dirty flag flushing (batched, every 5 seconds) ===
    if (now - g_lastNvsFlush >= NVS_FLUSH_INTERVAL_MS) {
        g_lastNvsFlush = now;
        flushAllNvs();
    }

    delay(20);
}
