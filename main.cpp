#include <cstdio>
#include <string>
#include <atomic>
#include <csignal>

#include "carla_host.hpp"
#include "CarlaBackendUtils.hpp"
#include "CarlaTimeUtils.hpp"

//---------------------------------------------------------------------------------------------------------------------
// Signal handler

static CarlaHost host;
static std::atomic<bool> terminate{false};

static void signalHandler(const int sig)
{
  switch (sig)
  {
    case SIGINT:
    case SIGTERM:
      terminate = true;
      if (host.handle != nullptr)
        host.SignalTerminate();
      break;
    case SIGUSR1:
      if (host.handle != nullptr)
        host.SignalSave();
      break;
  }
}

void setUpSignals()
{
  struct sigaction sig;
  carla_zeroStruct(sig);
  sig.sa_handler = signalHandler;
  sig.sa_flags   = SA_RESTART;
  sigemptyset(&sig.sa_mask);
  sigaction(SIGTERM, &sig, nullptr);
  sigaction(SIGINT, &sig, nullptr);
  sigaction(SIGUSR1, &sig, nullptr);
}


static void _engineCallback(void* const ptr, const EngineCallbackOpcode action, uint pluginId, int value1, int value2, int value3, float valuef, const char* const valueStr)
{
  // carla_stdout("_engineCallback(%p, %i:%s, %u, %i, %i, %i, %f, %s)",
  //                ptr, action, EngineCallbackOpcode2Str(action), pluginId, value1, value2, value3, valuef, valueStr);

  CarlaHost* const host = (CarlaHost*)(ptr);
  CARLA_SAFE_ASSERT_RETURN(host != nullptr,);

  switch (action)
  {
    case ENGINE_CALLBACK_ENGINE_STARTED:
      host->processMode   = static_cast<EngineProcessMode>(value1);
      host->transportMode = static_cast<EngineTransportMode>(value2);
      break;
    case ENGINE_CALLBACK_PROCESS_MODE_CHANGED:
      host->processMode   = static_cast<EngineProcessMode>(value1);
      break;
    case ENGINE_CALLBACK_TRANSPORT_MODE_CHANGED:
      host->transportMode  = static_cast<EngineTransportMode>(value1);
      host->transportExtra = valueStr;
      break;
    default:
      break;
  }

  // TODO
  switch (action)
  {
    case ENGINE_CALLBACK_ENGINE_STARTED:
      CARLA_SAFE_ASSERT_INT_RETURN(value3 >= 0, value3,);
      host->EngineStartedCallback(pluginId, value1, value2, static_cast<uint>(value3), valuef, valueStr);
      break;
    case ENGINE_CALLBACK_ENGINE_STOPPED:
      host->EngineStoppedCallback();
      break;

    // FIXME
    default:
      break;
  }
}

static const char* _fileCallback(void*, const FileCallbackOpcode action, const bool isDir, const char* const title, const char* const filter)
{
  const char* fileRet = "";
  return fileRet;
}

int main(int argc, char const *argv[])
{
  // if (argc < 2)
  // {
  //   carla_stdout("Please provide .carxp file! Exiting.");
  //   std::exit(1);
  // }

  const std::string libFolder(carla_get_library_folder());

  carla_stdout("Carla %s started, status:", CARLA_VERSION_STRING);
  carla_stdout("  Binary dir:     %s", libFolder.c_str());
  carla_stdout("  Resources dir:  %s", libFolder.c_str());

  host.isControl = false;
  host.isPlugin  = false;

  setUpSignals();

  host.handle = carla_standalone_host_init();

  carla_set_engine_callback(host.handle, _engineCallback, &host);
  carla_set_file_callback(host.handle, _fileCallback, nullptr);

  // carla_set_engine_option(host.handle, ENGINE_OPTION_PATH_BINARIES, 0, "/mnt/DATA/Programmation/Carla/bin");
  // carla_set_engine_option(host.handle, ENGINE_OPTION_PATH_RESOURCES, 0, "/mnt/DATA/Programmation/Carla/bin/resources");

  loadHostSettings(host);
  // setHostSettings(host);
  auto audioDriver = setEngineSettings(host);

  if (! carla_engine_init(host.handle, audioDriver.c_str(), "Carla"))
  {
    carla_stdout("Engine failed to initialize, possible reasons:\n%s", carla_get_last_error(host.handle));
  }

  // std::string projectFile(argv[1]);
  // if (! carla_load_project(host.handle, projectFile.c_str()))
  // {
  //   carla_stdout("Failed to load selected project file, possible reasons:\n%s", carla_get_last_error(host.handle));
  //   carla_engine_close(host.handle);
  //   std::exit(1);
  // }

  //-----------------------------------------------------------------------------------------------------------------
  // Idle

  carla_stdout("Carla ready!");

  while (carla_is_engine_running(host.handle) && ! terminate)
  {
    carla_engine_idle(host.handle);
    carla_msleep(33); // 30 Hz
  }
  //-----------------------------------------------------------------------------------------------------------------
  // Stop

  carla_engine_close(host.handle);
  std::exit(0);
}
