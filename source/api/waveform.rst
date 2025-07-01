Waveform Data 
----------------------

|geisa-api-hdr|

The GEISA API exposes over the GEISA API message bus :doc:`/api/architecture` the details on the waveform data frame definition and the ability to activate or deactivate waveform data streaming.

Once activated, an application will receive waveform data via a dedicated socket between the platform implementation outside of the isolated environment and the application within the isolated environment.


Device Capabilities
^^^^^^^^^^^^^^^^^^^

GEISA applications MUST be able to query the platform to understand what
forms of waveform data are supported.  Platforms that provide
waveform data MUST, at a minimum provide:

- 128 samples per cycle (e.g 7.68kHz for 60 Hz AC or 6.4kHz for 50 Hz AC)
- 16-bit sample resolution
- data MUST be pushed at least every 200 ms
- data MUST indicate whether it is zero-crossing aligned or not
- zero-crossing aligned data MUST be aligned to the zero cross of 
  Phase A on Polyphase Devices 

Platforms MAY offer alternate sample rates and resolutions.  
For convenience, binary multiples for samples per cycle are preferred but not required:

- 128, 256, 512, and 16,384 samples per cycle 
  (e.g. ~8 kHz, ~16 kHz, ~32 kHz, and ~1MHz, respectively)
- 32-bit sample resolution

Different devices will have different number of capture channels each typically sampling a single Voltage or Current input.  The total number of channels and how those are assigned may not be known at application build time and are discoverable by querying the GEISA API message bus.

Data for all channels MUST be aligned to one another.  An individual sample in channel 1 MUST have been sampled at the same time that the corresponding samples in channels 2+ were.


.. Note::

  Devices MAY expose different waveform stream choices to applications if they support multiple capture frequencies or channel counts.  If so, an application MUST be able to activate one or more streams simultaneously if desired.


Metadata
^^^^^^^^

When activating a waveform stream, the platform provides the application the following metadata:

- The path to the data socket
- The type of data, one of int16, int32, or float32
- The number of voltage channels
- The number of current channels
- The total number of channels (Typically the sum of 3 items above, but MAY be larger)
- The sampling frequency in Hz
- If the frames are AC cycle aligned or not
- If data type is integer, the voltage scaling factor to convert to Volts
- If data type is integer, the current scaling factor to convert to Amps
- The expected data frame frequency (ex: 200msec)


Data Format
^^^^^^^^^^^

Once activated via GEISA API, applications can then open and start receiving data frames from a dedicated `AF_UNIX` family `SOCK_SEQPACKET` type socket.  This socket MUST be provisioned into the application's isolated environment using a path provided in the activation API response.

`SOCK_SEQPACKET` type sockets provide the application in-order delivery of data that honors message boundaries and provide the sender connection-oriented semantics.

The sending process in the platform, constructs data frames and sends them over this socket without serialization/deserialization and is suitable for receipt directly into native data buffers for processing by the application.

The data frame is formatted as follows (example C language structure)::

   struct geisa_waveform_frame
   {
     int64_t    timestamp;       /* in millisec */
     uint32_t   sequence_num;    /* unspecified starting value, incremented every frame */
     uint32_t   reserved;
     union {
       /* variable length array of 1 of 3 data types */
       int16_t  i16[0];
       int32_t  i32[0];
       float    f32[0];
     } data;
   };

Notably absent from the data frame is the metadata listed above as well as the frame length which is obtained from the `recv()` or similar syscall.

The `timestamp` field MUST be the timestamp for the first sample in the frame.

The `data` union represents a variable length array of one of the three supported data types.  The array size is computed as `sample_count * total_channel_count`.

Samples within the data array MUST be ordered as follows:

- Time 0

  - All voltage channels
  - All current channels

- Time 1

  - All voltage channels
  - All current channels

- Time 2

  - All voltage channels
  - All current channels

- And so on...


A standard split phase 2S meter with 1 Voltage and 2 Current channels (3 total channels) would report its data as follows:

- Voltage Phase AB, Time 0
- Current Phase A, Time 0
- Current Phase B, Time 0
- Voltage Phase AB, Time 1
- Current Phase A, Time 1
- Current Phase B, Time 1


A standard split phase 12S meter with 2 Voltage and 2 Current channels (4 total channels) would report its data as follows:

- Voltage Phase A, Time 0
- Voltage Phase B, Time 0
- Current Phase A, Time 0
- Current Phase B, Time 0
- Voltage Phase A, Time 1
- Voltage Phase B, Time 1
- Current Phase A, Time 1
- Current Phase B, Time 1


For example, a polyphase meter with 3 Voltage and 3 Current channels (6 total channels) would report its data as follows:

- Voltage Phase A, Time 0
- Voltage Phase B, Time 0
- Voltage Phase C, Time 0
- Current Phase A, Time 0
- Current Phase B, Time 0
- Current Phase C, Time 0
- Voltage Phase A, Time 1
- Voltage Phase B, Time 1
- Voltage Phase C, Time 1
- Current Phase A, Time 1
- Current Phase B, Time 1
- Current Phase C, Time 1


For example, a polyphase with neutral meter with 3 Voltage and 4 Current channels (7 total channels) would report its data as follows:

- Voltage Phase A, Time 0
- Voltage Phase B, Time 0
- Voltage Phase C, Time 0
- Current Phase A, Time 0
- Current Phase B, Time 0
- Current Phase C, Time 0
- Current Neutral, Time 0
- Voltage Phase A, Time 1
- Voltage Phase B, Time 1
- Voltage Phase C, Time 1
- Current Phase A, Time 1
- Current Phase B, Time 1
- Current Phase C, Time 1
- Current Neutral, Time 1
 
 

|geisa-pyramid|



