// ----------------------------------------------------------------------------
// Callbacks.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Callbacks.h"


namespace callbacks
{
// Callbacks must be non-blocking (avoid 'delay')
//
// modular_server.getParameterValue must be cast to either:
// const char*
// long
// double
// bool
// ArduinoJson::JsonArray&
// ArduinoJson::JsonObject&
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server.getSavedVariableValue type must match the saved variable default type
// modular_server.setSavedVariableValue type must match the saved variable default type

void getSDCardInfoCallback()
{
  SDInterface& sd_interface = controller.getSDInterface();
  modular_server.writeResultKeyToResponse();
  modular_server.beginResponseObject();
  modular_server.writeToResponse("detected",sd_interface.getDetected());
  modular_server.writeToResponse("type",sd_interface.getType());
  modular_server.writeToResponse("formatted",sd_interface.getFormatted());
  modular_server.writeToResponse("format",sd_interface.getFormat());
  modular_server.writeToResponse("volume_size",sd_interface.getVolumeSize());
  modular_server.writeToResponse("initialized",sd_interface.getInitialized());
  modular_server.endResponseObject();
}

void addDirectoryToResponse(File dir, const char *pwd)
{
  while (true)
  {
    File entry =  dir.openNextFile();
    if (!entry)
    {
      // no more files
      break;
    }
    char full_path[constants::STRING_LENGTH_PATH];
    full_path[0] = 0;
    strcat(full_path,pwd);
    strcat(full_path,entry.name());
    if (!entry.isDirectory())
    {
      bool audio_file = false;
      for (unsigned int i=0;i<constants::AUDIO_EXT_COUNT;++i)
      {
        if (strstr(full_path,constants::audio_exts[i]) != NULL)
        {
          audio_file = true;
        }
      }
      if (audio_file)
      {
        modular_server.writeToResponse(full_path);
      }
    }
    else
    {
      strcat(full_path,"/");
      addDirectoryToResponse(entry,full_path);
    }
    entry.close();
  }
}

void getAudioPathsCallback()
{
  File root = SD.open("/");
  modular_server.writeResultKeyToResponse();
  modular_server.beginResponseArray();
  addDirectoryToResponse(root,constants::sd_prefix);
  modular_server.endResponseArray();
}

void playAudioPathCallback()
{
  if (!controller.codecEnabled())
  {
    modular_server.sendErrorResponse("No audio codec chip detected.");
  }
  const char* path = modular_server.getParameterValue(constants::path_parameter_name);
  if (!controller.isAudioPath(path))
  {
    char err_msg[constants::STRING_LENGTH_ERROR_MESSAGE];
    err_msg[0] = 0;
    strcat(err_msg,"Invalid audio path: ");
    strcat(err_msg,path);
    modular_server.sendErrorResponse(err_msg);
    return;
  }
  bool playing = controller.playPath(path);
  if (!playing)
  {
    char err_msg[constants::STRING_LENGTH_ERROR_MESSAGE];
    err_msg[0] = 0;
    strcat(err_msg,"Unable to find audio path: ");
    strcat(err_msg,path);
    modular_server.sendErrorResponse(err_msg);
  }
}

void isPlayingCallback()
{
  modular_server.writeResultToResponse(controller.isPlaying());
}

void getLastAudioPathPlayedCallback()
{
  modular_server.writeResultToResponse(controller.getLastAudioPathPlayed());
}

void setVolumeCallback()
{
  if (!controller.codecEnabled())
  {
    modular_server.sendErrorResponse("No audio codec chip detected.");
  }
  long percent = modular_server.getParameterValue(constants::percent_parameter_name);
  controller.setVolume(percent);
}

}
