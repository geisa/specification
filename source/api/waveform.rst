Waveform Data 
----------------------

|geisa-api-hdr|

The GEISA API exposes metrology waveform data to applications over
the GEISA API message bus :doc:`/api/architecture`.

Waveform data will be pushed over the message bus based on a 
stream configuration request.

GEISA applications must be able to query the platform to understand what
forms of waveform data are supported.  Generally, platforms that provide
waveform data MUST, at a minimum provide:

- 64 samples per cycle (e.g 3.84kHz for 60 Hz AC)
- 16-bit sample resolution
- data MUST be pushed at least every 200 ms
- data MUST indicate whether it is zero-crossing aligned
- zero-crossing aligned data MUST be aligned to the zero cross of 
  Phase A on Polyphase Devices 

Platforms MAY offer alternate sample rates and resolutions.  
For convenience, binary multiples for samples per cycle are preferred:

- 128, 256, 512, and 16,384 samples per cycle 
  (e.g. ~8 kHz, ~16 kHz, ~32 kHz, and ~1MHz, respectively)
- 32-bit sample resolution

Data MUST be interleaved by channel, alternating between voltage and current 
until all phases are exhausted, before moving to the next sample period.

For example, a polyphase wye connected meter would report its data as follows:

- Voltage Phase A, Time 0
- Current Phase A, Time 0
- Voltage Phase B, Time 0
- Current Phase B, Time 0
- Voltage Phase C, Time 0
- Current Phase C, Time 0
- Voltage Phase A, Time 1
- Current Phase A, Time 1
- Voltage Phase B, Time 1
- Current Phase B, Time 1
- Voltage Phase C, Time 1
- Current Phase C, Time 1
- Voltage Phase A, Time 2 . . .
 
A standard split phase meter would report its data as follows:
 
- Voltage, Time 0
- Current, Time 0
- Voltage, Time 1
- Current, Time 1
- Voltage, Time 2 . . .
 
Split phase meters with a neutral reference would report data as Phase A and Phase B:
 
- Voltage Phase A, Time 0
- Current Phase A, Time 0
- Voltage Phase B, Time 0
- Current Phase B, Time 0
- Voltage Phase A, Time 1
- Current Phase A, Time 1
- Voltage Phase B, Time 1
- Current Phase B, Time 1
- Voltage Phase A, Time 2 . . .
 
For example, a polyphase delta connected meter would report its data as follows:

- Voltage Phase AB, Time 0
- Current Phase AB, Time 0
- Voltage Phase BC, Time 0
- Current Phase BC, Time 0
- Voltage Phase CA, Time 0
- Current Phase CA, Time 0
- Voltage Phase AB, Time 1
- Current Phase AB, Time 1
- Voltage Phase BC, Time 1
- Current Phase BC, Time 1
- Voltage Phase CA, Time 1
- Current Phase CA, Time 1
- Voltage Phase AB, Time 2 . . .
 
 

|geisa-pyramid|



