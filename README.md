# BeAPad Led Project


Project for touch sensors combined to Neopixels and RTP Midi for controlling Light and music via midiMessages across wifi.


## Materials:
- ESP32 Microcontroller (WROOM DEVKIT_V1) [amazon](https://www.amazon.fr/SP-Cow-ESP-32S-d%C3%A9veloppement-Bluetooth-d%C3%A9nergie/dp/B07VJ34N2Q/ref=sr_1_5?__mk_fr_FR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=2QX1H1678O7M3&keywords=esp32+wroom+devkit&qid=1652459031&sprefix=esp32+wroom+devkit%2Caps%2C51&sr=8-5) [aliexpress](https://fr.aliexpress.com/item/1005001929935550.html?spm=a2g0o.search0304.0.0.a4b41103QWyj6D&algo_pvid=caa6f633-4206-442e-8846-f58ec6503b21&algo_exp_id=caa6f633-4206-442e-8846-f58ec6503b21-0&pdp_ext_f=%7B%22sku_id%22%3A%2212000022802021515%22%7D&pdp_npi=2%40dis%21EUR%21%2127.77%21%21%21%21%21%402100bdca16524589488372088ea014%2112000022802021515%21sea)
- MPR121 Touch Shield [amazon](https://www.amazon.fr/Adafruit-12-Key-Capacitive-Sensor-Breakout/dp/B00SK8PVNA)
- WS2812E leds [amazon](https://www.amazon.fr/gp/product/B088BRY2SH/ref=ppx_yo_dt_b_asin_title_o07_s00?ie=UTF8&th=1) **<u>MUST BE 60Leds/m for easy soldering on PCB</u>**
- Battery 1100 mAh Lithium 1S 3c
- 1 Capacitor 1000uF
- Steel plates
- Optional : Power Supply 5V 10A or 4 AA Batteries


## Mapping MidiReceive

```
Each MidiNote Receveid is connected to a specific light effect on board
 _______________________________________
|  | | | |  |  | | | | | |  |  | | | |  |
|  | | | |  |  | | | | | |  |  | | | |  |
|  | | | |  |  | | | | | |  |  | | | |  |
|  |_| |_|  |  |_| |_| |_|  |  |_| |_|  |
|   |   |   |   |   |   |   |   |   |   |
|   |   |   |   |   |   |   |   |   |   |
|___|___|___|___|___|___|___|___|___|___|

Mode FullBright: -- Not yet implemented --
    -> A0 ( MIDI 21 )      Board 1
    -> A#0 ( MIDI 22 )     Board 2
    -> B0 ( MIDI 23 )      Board 3
    -> C1 ( MIDI 24 )      Board 4
    -> C#1 ( MIDI 25 )     Board 5
    -> D1 ( MIDI 26 )      Board 6
    -> D#1 ( MIDI 27 )     Board 7
    -> E1 ( MIDI 28 )      Board 8
    -> F1 ( MIDI 29 )      Board 9
    -> F#1 ( MIDI 30 )     Board 10
    -> G1 ( MIDI 31 )      Board 11
    -> G#1 ( MIDI 32 )     Board 12
    
Mode Bounce: -- Not yet implemented --
    -> A1 ( MIDI 33 )      Board 1
    -> A#1 ( MIDI 34 )     Board 2
    -> B1 ( MIDI 35 )      Board 3
    -> C2 ( MIDI 36 )      Board 4
    -> C#2 ( MIDI 37 )     Board 5
    -> D2 ( MIDI 38 )      Board 6
    -> D#2 ( MIDI 39 )     Board 7
    -> E2 ( MIDI 40 )      Board 8
    -> F2 ( MIDI 41 )      Board 9
    -> F#2 ( MIDI 42 )     Board 10
    -> G2 ( MIDI 43 )      Board 11
    -> G#2 ( MIDI 44 )     Board 12
    
Mode Bounce-Low: -- Not yet implemented --
    -> A2 ( MIDI 45 )      Board 1
    -> A#2 ( MIDI 46 )     Board 2
    -> B2 ( MIDI 47 )      Board 3
    -> C3 ( MIDI 48 )      Board 4
    -> C#3 ( MIDI 49 )     Board 5
    -> D3 ( MIDI 50 )      Board 6
    -> D#3 ( MIDI 51 )     Board 7
    -> E3 ( MIDI 52 )      Board 8
    -> F3 ( MIDI 53 )      Board 9
    -> F#3 ( MIDI 54 )     Board 10
    -> G3 ( MIDI 55 )      Board 11
    -> G#3 ( MIDI 56 )     Board 12
    
Mode Serpentin: -- Not yet implemented --
    -> A3 ( MIDI 57 )      Board 1
    -> A#3 ( MIDI 58 )     Board 2
    -> B3 ( MIDI 59 )      Board 3
    -> C4 ( MIDI 60 )      Board 4
    -> C#4 ( MIDI 61 )     Board 5
    -> D4 ( MIDI 62 )      Board 6
    -> D#4 ( MIDI 63 )     Board 7
    -> E4 ( MIDI 64 )      Board 8
    -> F4 ( MIDI 65 )      Board 9
    -> F#4 ( MIDI 66 )     Board 10
    -> G4 ( MIDI 67 )      Board 11
    -> G#4 ( MIDI 68 )     Board 12
    
Mode Electric: -- Not yet implemented --
    -> A4 ( MIDI 69 )      Board 1
    -> A#4 ( MIDI 70 )     Board 2
    -> B4 ( MIDI 71 )      Board 3
    -> C5 ( MIDI 72 )      Board 4
    -> C#5 ( MIDI 73 )     Board 5
    -> D5 ( MIDI 74 )      Board 6
    -> D#5 ( MIDI 75 )     Board 7
    -> E5 ( MIDI 76 )      Board 8
    -> F5 ( MIDI 77 )      Board 9
    -> F#5 ( MIDI 78 )     Board 10
    -> G5 ( MIDI 79 )      Board 11
    -> G#5 ( MIDI 80 )     Board 12
    
**********************************************************
SPECIAL MODES - Same effect on all boards on 1 midiReceive
**********************************************************

SPECIAL EFFECT ALL BOUNCE: -- Not yet implemented --
    - A5 ( MIDI 81 )        All Boards
SPECIAL EFFECT ALL BOUNCE SLOW: -- Not yet implemented --
    - A#5 ( MIDI 82 )        All Boards
SPECIAL EFFECT ALL ELECTRIC: -- Not yet implemented --
    - B5 ( MIDI 83 )        All Boards
SPECIAL EFFECT WAVE UP TO DOWN: -- Not yet implemented --
    - C6 ( MIDI 84 )        All Boards
SPECIAL EFFECT WAVE INTERNAL TO EXTERNAL: -- Not yet implemented --
    - C#6 ( MIDI 85 )        All Boards

```

## Mapping MidiSends


// TODO implements a "shift key"

```
The boards always send the same midiNote:

Touch Board1 => Send Midi Note 60       ( C4 )
Touch Board2 => Send Midi Note 60       ( C#4 )
Touch Board3 => Send Midi Note 60       ( D4 )
Touch Board4 => Send Midi Note 60       ( D#4 )
Touch Board5 => Send Midi Note 60       ( E4 )
Touch Board6 => Send Midi Note 60       ( F4 )
Touch Board7 => Send Midi Note 60       ( F#4 )
Touch Board8 => Send Midi Note 60       ( G4 )
Touch Board9 => Send Midi Note 60       ( G#4 )
Touch Board10 => Send Midi Note 60      ( A4 )
Touch Board11 => Send Midi Note 60      ( A#4 )
Touch Board12 => Send Midi Note 60      ( B4 )

```