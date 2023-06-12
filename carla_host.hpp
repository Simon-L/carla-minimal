#include <cstdio>
#include <string>

#include "CarlaHost.h"
#include "CarlaJuceUtils.hpp"

CARLA_BACKEND_USE_NAMESPACE;

//---------------------------------------------------------------------------------------------------------------------

class CarlaHost
{
public:
    // host handle
    CarlaHostHandle handle;

    // info about this host object
    bool isControl;
    bool isPlugin;
    bool isRemote;
    bool nsmOK;

    // settings
    EngineProcessMode processMode;
    EngineTransportMode transportMode;
    std::string transportExtra;
    EngineProcessMode nextProcessMode;
    bool processModeForced;
    std::string audioDriverForced;

    // settings
    bool experimental;
    bool exportLV2;
    bool forceStereo;
    bool manageUIs;
    uint maxParameters;
    bool resetXruns;
    bool preferPluginBridges;
    bool preferUIBridges;
    bool preventBadBehaviour;
    bool showLogs;
    bool showPluginBridges;
    bool showWineBridges;
    bool uiBridgesTimeout;
    bool uisAlwaysOnTop;

    // settings
    std::string pathBinaries;
    std::string pathResources;

    CarlaHost();

    void SignalTerminate();
    void SignalSave();

    // Engine stuff
    void EngineStartedCallback(uint pluginCount, int processMode, int transportMode, uint bufferSize, float sampleRate, std::string driverName);
    void EngineStoppedCallback();

private:
    CARLA_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CarlaHost)
};

void loadHostSettings(CarlaHost& host);
void setHostSettings(const CarlaHost& host);
std::string setEngineSettings(CarlaHost& host);
