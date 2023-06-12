//---------------------------------------------------------------------------------------------------------------------
// Imports (Custom)

#include "CarlaDefines.h"

//---------------------------------------------------------------------------------------------------------------------
// Static MIDI CC list

/*
static const char* const* const MIDI_CC_LIST = {
    "0x01 Modulation",
    "0x02 Breath",
    "0x03 (Undefined)",
    "0x04 Foot",
    "0x05 Portamento",
    "0x07 Volume",
    "0x08 Balance",
    "0x09 (Undefined)",
    "0x0A Pan",
    "0x0B Expression",
    "0x0C FX Control 1",
    "0x0D FX Control 2",
    "0x0E (Undefined)",
    "0x0F (Undefined)",
    "0x10 General Purpose 1",
    "0x11 General Purpose 2",
    "0x12 General Purpose 3",
    "0x13 General Purpose 4",
    "0x14 (Undefined)",
    "0x15 (Undefined)",
    "0x16 (Undefined)",
    "0x17 (Undefined)",
    "0x18 (Undefined)",
    "0x19 (Undefined)",
    "0x1A (Undefined)",
    "0x1B (Undefined)",
    "0x1C (Undefined)",
    "0x1D (Undefined)",
    "0x1E (Undefined)",
    "0x1F (Undefined)",
    "0x46 Control 1 [Variation]",
    "0x47 Control 2 [Timbre]",
    "0x48 Control 3 [Release]",
    "0x49 Control 4 [Attack]",
    "0x4A Control 5 [Brightness]",
    "0x4B Control 6 [Decay]",
    "0x4C Control 7 [Vib Rate]",
    "0x4D Control 8 [Vib Depth]",
    "0x4E Control 9 [Vib Delay]",
    "0x4F Control 10 [Undefined]",
    "0x50 General Purpose 5",
    "0x51 General Purpose 6",
    "0x52 General Purpose 7",
    "0x53 General Purpose 8",
    "0x54 Portamento Control",
    "0x5B FX 1 Depth [Reverb]",
    "0x5C FX 2 Depth [Tremolo]",
    "0x5D FX 3 Depth [Chorus]",
    "0x5E FX 4 Depth [Detune]",
    "0x5F FX 5 Depth [Phaser]",
    nullptr
};
*/

//---------------------------------------------------------------------------------------------------------------------
// Carla Settings keys

#define CARLA_KEY_MAIN_PROJECT_FOLDER   "Main/ProjectFolder"   /* str  */
#define CARLA_KEY_MAIN_USE_PRO_THEME    "Main/UseProTheme"     /* bool */
#define CARLA_KEY_MAIN_PRO_THEME_COLOR  "Main/ProThemeColor"   /* str  */
#define CARLA_KEY_MAIN_REFRESH_INTERVAL "Main/RefreshInterval" /* int  */
#define CARLA_KEY_MAIN_CONFIRM_EXIT     "Main/ConfirmExit"     /* bool */
#define CARLA_KEY_MAIN_SHOW_LOGS        "Main/ShowLogs"        /* bool */
#define CARLA_KEY_MAIN_EXPERIMENTAL     "Main/Experimental"    /* bool */

#define CARLA_KEY_CANVAS_THEME             "Canvas/Theme"           /* str */
#define CARLA_KEY_CANVAS_SIZE              "Canvas/Size"            /* str "NxN" */
#define CARLA_KEY_CANVAS_USE_BEZIER_LINES  "Canvas/UseBezierLines"  /* bool */
#define CARLA_KEY_CANVAS_AUTO_HIDE_GROUPS  "Canvas/AutoHideGroups"  /* bool */
#define CARLA_KEY_CANVAS_AUTO_SELECT_ITEMS "Canvas/AutoSelectItems" /* bool */
#define CARLA_KEY_CANVAS_EYE_CANDY         "Canvas/EyeCandy2"       /* bool */
#define CARLA_KEY_CANVAS_FANCY_EYE_CANDY   "Canvas/FancyEyeCandy"   /* bool */
#define CARLA_KEY_CANVAS_USE_OPENGL        "Canvas/UseOpenGL"       /* bool */
#define CARLA_KEY_CANVAS_ANTIALIASING      "Canvas/Antialiasing"    /* enum */
#define CARLA_KEY_CANVAS_HQ_ANTIALIASING   "Canvas/HQAntialiasing"  /* bool */
#define CARLA_KEY_CANVAS_INLINE_DISPLAYS   "Canvas/InlineDisplays"  /* bool */
#define CARLA_KEY_CANVAS_FULL_REPAINTS     "Canvas/FullRepaints"    /* bool */

#define CARLA_KEY_ENGINE_DRIVER_PREFIX         "Engine/Driver-"
#define CARLA_KEY_ENGINE_AUDIO_DRIVER          "Engine/AudioDriver"         /* str  */
#define CARLA_KEY_ENGINE_PROCESS_MODE          "Engine/ProcessMode"         /* enum */
#define CARLA_KEY_ENGINE_TRANSPORT_MODE        "Engine/TransportMode"       /* enum */
#define CARLA_KEY_ENGINE_TRANSPORT_EXTRA       "Engine/TransportExtra"      /* str  */
#define CARLA_KEY_ENGINE_FORCE_STEREO          "Engine/ForceStereo"         /* bool */
#define CARLA_KEY_ENGINE_PREFER_PLUGIN_BRIDGES "Engine/PreferPluginBridges" /* bool */
#define CARLA_KEY_ENGINE_PREFER_UI_BRIDGES     "Engine/PreferUiBridges"     /* bool */
#define CARLA_KEY_ENGINE_MANAGE_UIS            "Engine/ManageUIs"           /* bool */
#define CARLA_KEY_ENGINE_UIS_ALWAYS_ON_TOP     "Engine/UIsAlwaysOnTop"      /* bool */
#define CARLA_KEY_ENGINE_MAX_PARAMETERS        "Engine/MaxParameters"       /* int  */
#define CARLA_KEY_ENGINE_RESET_XRUNS           "Engine/ResetXruns"          /* bool */
#define CARLA_KEY_ENGINE_UI_BRIDGES_TIMEOUT    "Engine/UiBridgesTimeout"    /* int  */

#define CARLA_KEY_OSC_ENABLED          "OSC/Enabled"
#define CARLA_KEY_OSC_TCP_PORT_ENABLED "OSC/TCPEnabled"
#define CARLA_KEY_OSC_TCP_PORT_NUMBER  "OSC/TCPNumber"
#define CARLA_KEY_OSC_TCP_PORT_RANDOM  "OSC/TCPRandom"
#define CARLA_KEY_OSC_UDP_PORT_ENABLED "OSC/UDPEnabled"
#define CARLA_KEY_OSC_UDP_PORT_NUMBER  "OSC/UDPNumber"
#define CARLA_KEY_OSC_UDP_PORT_RANDOM  "OSC/UDPRandom"

#define CARLA_KEY_PATHS_AUDIO "Paths/Audio"
#define CARLA_KEY_PATHS_MIDI  "Paths/MIDI"

#define CARLA_KEY_PATHS_LADSPA "Paths/LADSPA"
#define CARLA_KEY_PATHS_DSSI   "Paths/DSSI"
#define CARLA_KEY_PATHS_LV2    "Paths/LV2"
#define CARLA_KEY_PATHS_VST2   "Paths/VST2"
#define CARLA_KEY_PATHS_VST3   "Paths/VST3"
#define CARLA_KEY_PATHS_SF2    "Paths/SF2"
#define CARLA_KEY_PATHS_SFZ    "Paths/SFZ"
#define CARLA_KEY_PATHS_JSFX   "Paths/JSFX"

#define CARLA_KEY_WINE_EXECUTABLE      "Wine/Executable"     /* str  */
#define CARLA_KEY_WINE_AUTO_PREFIX     "Wine/AutoPrefix"     /* bool */
#define CARLA_KEY_WINE_FALLBACK_PREFIX "Wine/FallbackPrefix" /* str  */
#define CARLA_KEY_WINE_RT_PRIO_ENABLED "Wine/RtPrioEnabled"  /* bool */
#define CARLA_KEY_WINE_BASE_RT_PRIO    "Wine/BaseRtPrio"     /* int  */
#define CARLA_KEY_WINE_SERVER_RT_PRIO  "Wine/ServerRtPrio"   /* int  */

#define CARLA_KEY_EXPERIMENTAL_PLUGIN_BRIDGES        "Experimental/PluginBridges"       /* bool */
#define CARLA_KEY_EXPERIMENTAL_WINE_BRIDGES          "Experimental/WineBridges"         /* bool */
#define CARLA_KEY_EXPERIMENTAL_JACK_APPS             "Experimental/JackApplications"    /* bool */
#define CARLA_KEY_EXPERIMENTAL_EXPORT_LV2            "Experimental/ExportLV2"           /* bool */
#define CARLA_KEY_EXPERIMENTAL_PREVENT_BAD_BEHAVIOUR "Experimental/PreventBadBehaviour" /* bool */
#define CARLA_KEY_EXPERIMENTAL_LOAD_LIB_GLOBAL       "Experimental/LoadLibGlobal"       /* bool */

// if pro theme is on and color is black
#define CARLA_KEY_CUSTOM_PAINTING "UseCustomPainting" /* bool */

//---------------------------------------------------------------------------------------------------------------------
// Carla Settings defaults

// Main
#define CARLA_DEFAULT_MAIN_PROJECT_FOLDER   "/tmp"
#define CARLA_DEFAULT_MAIN_USE_PRO_THEME    true
#define CARLA_DEFAULT_MAIN_PRO_THEME_COLOR  "Black"
#define CARLA_DEFAULT_MAIN_REFRESH_INTERVAL 20
#define CARLA_DEFAULT_MAIN_CONFIRM_EXIT     true
#ifdef CARLA_OS_WIN
# define CARLA_DEFAULT_MAIN_SHOW_LOGS       false
#else
# define CARLA_DEFAULT_MAIN_SHOW_LOGS       true
#endif
#define CARLA_DEFAULT_MAIN_EXPERIMENTAL     false

// Engine
#define CARLA_DEFAULT_FORCE_STEREO          false
#define CARLA_DEFAULT_PREFER_PLUGIN_BRIDGES false
#define CARLA_DEFAULT_PREFER_UI_BRIDGES     true
#define CARLA_DEFAULT_MANAGE_UIS            true
#define CARLA_DEFAULT_UIS_ALWAYS_ON_TOP     false
#define CARLA_DEFAULT_MAX_PARAMETERS        MAX_DEFAULT_PARAMETERS
#define CARLA_DEFAULT_RESET_XRUNS           false
#define CARLA_DEFAULT_UI_BRIDGES_TIMEOUT    4000

#define CARLA_DEFAULT_AUDIO_BUFFER_SIZE     512
#define CARLA_DEFAULT_AUDIO_SAMPLE_RATE     44100
#define CARLA_DEFAULT_AUDIO_TRIPLE_BUFFER   false

# define CARLA_DEFAULT_AUDIO_DRIVER "JACK"

// #if CARLA_DEFAULT_AUDIO_DRIVER == "JACK"
// # define CARLA_DEFAULT_PROCESS_MODE   ENGINE_PROCESS_MODE_MULTIPLE_CLIENTS
// # define CARLA_DEFAULT_TRANSPORT_MODE ENGINE_TRANSPORT_MODE_JACK
// #else
# define CARLA_DEFAULT_PROCESS_MODE   ENGINE_PROCESS_MODE_MULTIPLE_CLIENTS
# define CARLA_DEFAULT_TRANSPORT_MODE ENGINE_TRANSPORT_MODE_JACK
// #endif

// OSC
#ifdef CARLA_OS_WIN
# define CARLA_DEFAULT_OSC_ENABLED false
#else
# define CARLA_DEFAULT_OSC_ENABLED true
#endif
#define CARLA_DEFAULT_OSC_TCP_PORT_ENABLED true
#define CARLA_DEFAULT_OSC_TCP_PORT_NUMBER  22752
#define CARLA_DEFAULT_OSC_TCP_PORT_RANDOM  false
#define CARLA_DEFAULT_OSC_UDP_PORT_ENABLED true
#define CARLA_DEFAULT_OSC_UDP_PORT_NUMBER  22752
#define CARLA_DEFAULT_OSC_UDP_PORT_RANDOM  false

// Wine
#define CARLA_DEFAULT_WINE_EXECUTABLE      "wine"
#define CARLA_DEFAULT_WINE_AUTO_PREFIX     true
#define CARLA_DEFAULT_WINE_FALLBACK_PREFIX "$HOME/.wine"
#define CARLA_DEFAULT_WINE_RT_PRIO_ENABLED true
#define CARLA_DEFAULT_WINE_BASE_RT_PRIO    15
#define CARLA_DEFAULT_WINE_SERVER_RT_PRIO  10

// Experimental
#define CARLA_DEFAULT_EXPERIMENTAL_PLUGIN_BRIDGES        false
#define CARLA_DEFAULT_EXPERIMENTAL_WINE_BRIDGES          false
#define CARLA_DEFAULT_EXPERIMENTAL_JACK_APPS             false
#define CARLA_DEFAULT_EXPERIMENTAL_LV2_EXPORT            false
#define CARLA_DEFAULT_EXPERIMENTAL_PREVENT_BAD_BEHAVIOUR false
#define CARLA_DEFAULT_EXPERIMENTAL_LOAD_LIB_GLOBAL       false

//---------------------------------------------------------------------------------------------------------------------
// Default File Folders

#define CARLA_DEFAULT_FILE_PATH_AUDIO {}
#define CARLA_DEFAULT_FILE_PATH_MIDI  {}

//---------------------------------------------------------------------------------------------------------------------
// Default Plugin Folders (get)

#define DEFAULT_LADSPA_PATH ""
#define DEFAULT_DSSI_PATH   ""
#define DEFAULT_LV2_PATH    ""
#define DEFAULT_VST2_PATH   ""
#define DEFAULT_VST3_PATH   ""
#define DEFAULT_SF2_PATH    ""
#define DEFAULT_SFZ_PATH    ""
#define DEFAULT_JSFX_PATH    ""

#ifdef CARLA_OS_WIN
# define CARLA_PATH_SPLITTER ";"
#else
# define CARLA_PATH_SPLITTER ":"
#endif

//---------------------------------------------------------------------------------------------------------------------
// Default Plugin Folders (set)

# define CARLA_DEFAULT_LADSPA_PATH DEFAULT_LADSPA_PATH
# define CARLA_DEFAULT_DSSI_PATH   DEFAULT_DSSI_PATH
# define CARLA_DEFAULT_LV2_PATH    DEFAULT_LV2_PATH
# define CARLA_DEFAULT_VST2_PATH   DEFAULT_VST2_PATH
# define CARLA_DEFAULT_VST3_PATH   DEFAULT_VST3_PATH
# define CARLA_DEFAULT_SF2_PATH    DEFAULT_SF2_PATH
# define CARLA_DEFAULT_SFZ_PATH    DEFAULT_SFZ_PATH
# define CARLA_DEFAULT_JSFX_PATH   DEFAULT_JSFX_PATH
