#include "carla_host.hpp"
#include "carla_shared.hpp"

#include "CarlaHost.h"
#include "CarlaUtils.h"

#include "CarlaBackendUtils.hpp"
#include "CarlaMathUtils.hpp"
#include "CarlaString.hpp"

CarlaHost::CarlaHost()
    : isControl(false),
      isPlugin(false),
      isRemote(false),
      nsmOK(false),
      processMode(ENGINE_PROCESS_MODE_MULTIPLE_CLIENTS),
      transportMode(ENGINE_TRANSPORT_MODE_INTERNAL),
      transportExtra(),
      nextProcessMode(ENGINE_PROCESS_MODE_MULTIPLE_CLIENTS),
      processModeForced(false),
      audioDriverForced(),
      experimental(false),
      exportLV2(false),
      forceStereo(false),
      manageUIs(false),
      maxParameters(200),
      resetXruns(false),
      preferPluginBridges(false),
      preferUIBridges(false),
      preventBadBehaviour(false),
      showLogs(false),
      showPluginBridges(false),
      showWineBridges(false),
      uiBridgesTimeout(0),
      uisAlwaysOnTop(false),
      pathBinaries(),
      pathResources() {}

void CarlaHost::SignalTerminate()
{
  carla_stdout("Signal Terminate");
}

void CarlaHost::SignalSave()
{
  carla_stdout("Signal Save");
}

void CarlaHost::EngineStartedCallback(uint pluginCount, int processMode, int transportMode, uint bufferSize, float sampleRate, std::string driverName)
{
  carla_stdout("======= Engine started ========");
  carla_stdout("Carla engine started, details:");
  carla_stdout("  Driver name:  %s", driverName.c_str());
  carla_stdout("  Sample rate:  %d", int(sampleRate));
  carla_stdout("  Process mode: %s", EngineProcessMode2Str((EngineProcessMode)processMode));
}
void CarlaHost::EngineStoppedCallback()
{
  carla_stdout("Engine Stopped Callback");
}


void loadHostSettings(CarlaHost& host)
{
  host.experimental = CARLA_DEFAULT_MAIN_EXPERIMENTAL;
  host.exportLV2 = CARLA_DEFAULT_EXPERIMENTAL_LV2_EXPORT;
  host.manageUIs = CARLA_DEFAULT_MANAGE_UIS;
  host.maxParameters = CARLA_DEFAULT_MAX_PARAMETERS;
  host.resetXruns = CARLA_DEFAULT_RESET_XRUNS;
  host.forceStereo = CARLA_DEFAULT_FORCE_STEREO;
  host.preferPluginBridges = CARLA_DEFAULT_PREFER_PLUGIN_BRIDGES;
  host.preferUIBridges = CARLA_DEFAULT_PREFER_UI_BRIDGES;
  host.preventBadBehaviour = CARLA_DEFAULT_EXPERIMENTAL_PREVENT_BAD_BEHAVIOUR;
  host.showLogs = CARLA_DEFAULT_MAIN_SHOW_LOGS;
  host.showPluginBridges = CARLA_DEFAULT_EXPERIMENTAL_PLUGIN_BRIDGES;
  host.showWineBridges = CARLA_DEFAULT_EXPERIMENTAL_WINE_BRIDGES;
  host.uiBridgesTimeout = CARLA_DEFAULT_UI_BRIDGES_TIMEOUT;
  host.uisAlwaysOnTop = CARLA_DEFAULT_UIS_ALWAYS_ON_TOP;

  host.transportExtra = "";

  host.nextProcessMode = host.processMode;

  host.transportMode = ENGINE_TRANSPORT_MODE_JACK;
}

void setHostSettings(const CarlaHost& host)
{
    carla_set_engine_option(host.handle, ENGINE_OPTION_FORCE_STEREO,          host.forceStereo,         "");
    carla_set_engine_option(host.handle, ENGINE_OPTION_MAX_PARAMETERS,        static_cast<int>(host.maxParameters), "");
    carla_set_engine_option(host.handle, ENGINE_OPTION_PREFER_PLUGIN_BRIDGES, host.preferPluginBridges, "");
    carla_set_engine_option(host.handle, ENGINE_OPTION_PREFER_UI_BRIDGES,     host.preferUIBridges,     "");
    carla_set_engine_option(host.handle, ENGINE_OPTION_PREVENT_BAD_BEHAVIOUR, host.preventBadBehaviour, "");
    carla_set_engine_option(host.handle, ENGINE_OPTION_UI_BRIDGES_TIMEOUT,    host.uiBridgesTimeout,    "");
    carla_set_engine_option(host.handle, ENGINE_OPTION_UIS_ALWAYS_ON_TOP,     host.uisAlwaysOnTop,      "");

    carla_set_engine_option(host.handle, ENGINE_OPTION_PROCESS_MODE,          host.nextProcessMode,     "");
    carla_set_engine_option(host.handle, ENGINE_OPTION_TRANSPORT_MODE,        host.transportMode,       "ENGINE_TRANSPORT_MODE_JACK");
    carla_set_engine_option(host.handle, ENGINE_OPTION_DEBUG_CONSOLE_OUTPUT,  host.showLogs,            "");
}

std::string setEngineSettings(CarlaHost& host)
{
  const bool oscEnabled = CARLA_DEFAULT_OSC_ENABLED;

  int portNumTCP, portNumUDP;
  portNumTCP = CARLA_DEFAULT_OSC_TCP_PORT_NUMBER;
  portNumUDP = CARLA_DEFAULT_OSC_UDP_PORT_NUMBER;

  carla_set_engine_option(host.handle, ENGINE_OPTION_OSC_ENABLED, oscEnabled ? 1 : 0, "");
  carla_set_engine_option(host.handle, ENGINE_OPTION_OSC_PORT_TCP, portNumTCP, "");
  carla_set_engine_option(host.handle, ENGINE_OPTION_OSC_PORT_UDP, portNumUDP, "");

  std::string audioDriver = CARLA_DEFAULT_AUDIO_DRIVER;
  std::string prefix = CARLA_KEY_ENGINE_DRIVER_PREFIX + audioDriver;
  carla_set_engine_option(host.handle, ENGINE_OPTION_AUDIO_DRIVER, 0, audioDriver.c_str());
  carla_set_engine_option(host.handle, ENGINE_OPTION_AUDIO_DEVICE, 0, "");

  return audioDriver;
}
