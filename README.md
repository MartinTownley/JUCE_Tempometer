
# Tempometer Plugin: Beat-detecting Reverse Metronome application (JUCE)

## Build / Download Instructions
### Build
 Launch the Projucer file and build the application in your chosen IDE
### Release
 Navigate to the Releases page to download binaries of the standalone and/or plugin application


## Dependencies
### BTrack

The beat-tracking processing in this project is performed by BTrack and its related classes. These are included in the repository, and their original source can be found here:
https://github.com/adamstark/BTrack

### libsamplerate

BTrack requires libsamplerate (aka Simple Rabbit Code) to be present in your Header Search Paths, in order to perform sample rate conversions necessary for the beat-tracking: http://www.mega-nerd.com/SRC/

### Kiss FFT / FFTW

BTrack requires EITHER the Kiss FFT (add flag -DUSE_KISS_FFT) or FFTW (add flag -DUSE_FFTW)  libraryto be present in your Header Search Path, for the purpose of FFT processing.
Kiss FFT is included in this repository.

- Kiss FFT: https://github.com/mborgerding/kissfft

- FFTW: http://fftw.org/

## Instructions

This application is designed to provide a real-time visual indicator representing the BPM of the incoming audio signal.
As such, it is aimed at drummers/percussionists/any percussive noisemakers to practice and analyse their timing.

After launching the application as standalone or as a plugin within your DAW of choice:
1) Check that the application is receiving audio. In standalone version, this can be done by clicking the Options menu and selecting the desired audio input. If running the plugin, check the audio configurations in your DAW.
2) To initiate the beat-tracker, click "Run Tempo-Tracker and Set Target BPM". The software will begin to calculate the tempo of the incoming audio signal.
3) After ten seconds, a target tempo will be assumed, and a moving meter will appear which represents the currently deduced BPM value.

- To reset the Target BPM value to the current BPM, click "Reset Target to Current BPM"
- If the calculated BPM is out of the range of the meter, the visual indicator will turn red



