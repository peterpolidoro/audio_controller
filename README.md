#audio_controller

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

##More Detailed Help on Installation and Usage

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

##Device Information

```json
{
  "id":"?",
  "result":{
    "device_info":{
      "name":"audio_controller",
      "model_number":1150,
      "serial_number":0,
      "firmware_version":{
        "major":0,
        "minor":1,
        "patch":0
      }
    },
    "methods":[
      "resetDefaults",
      "setSerialNumber",
      "getSDCardInfo",
      "getAudioPaths",
      "playAudioPath",
      "isPlaying",
      "getLastAudioPathPlayed",
      "setVolume"
    ]
  }
}
```

##Verbose Device Information

```json
{
  "id":"??",
  "result":{
    "device_info":{
      "name":"audio_controller",
      "model_number":1150,
      "serial_number":0,
      "firmware_version":{
        "major":0,
        "minor":1,
        "patch":0
      }
    },
    "methods":[
      {
        "name":"resetDefaults",
        "parameters":[],
        "result_type":null
      },
      {
        "name":"setSerialNumber",
        "parameters":[],
        "result_type":null
      },
      {
        "name":"getSDCardInfo",
        "parameters":[],
        "result_type":"object"
      },
      {
        "name":"getAudioPaths",
        "parameters":[],
        "result_type":"array"
      },
      {
        "name":"playAudioPath",
        "parameters":[
          "path"
        ],
        "result_type":null
      },
      {
        "name":"isPlaying",
        "parameters":[],
        "result_type":"bool"
      },
      {
        "name":"getLastAudioPathPlayed",
        "parameters":[],
        "result_type":"string"
      },
      {
        "name":"setVolume",
        "parameters":[
          "percent"
        ],
        "result_type":null
      }
    ],
    "parameters":[
      {
        "name":"serial_number",
        "type":"long",
        "min":0,
        "max":65535
      },
      {
        "name":"path",
        "type":"string"
      },
      {
        "name":"percent",
        "type":"long",
        "min":0,
        "max":100
      }
    ]
  }
}
```
