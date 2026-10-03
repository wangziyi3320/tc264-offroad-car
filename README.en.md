# TC264 Off-Road Racing Car

This repository archives the embedded project used by a student team in an off-road racing competition. It contains camera-based track processing, GPS/IMU handling, motion control, and peripheral drivers. It is a competition snapshot, not ready-to-run firmware for arbitrary hardware.

## My contribution

As a core team member, I worked on **vision processing and voice interaction**. The vision work visible in this repository is mainly in [`images.c`](TC264_jisuyueye/code/images.c) and [`images.h`](TC264_jisuyueye/code/images.h): thresholding and binarization, track-boundary and centerline extraction, and deviation calculation. The voice-related source and demo materials have not yet been organized as a standalone module in this repository.

GPS/IMU handling, PID control, and the overall vehicle architecture are team-project components; this repository should not be presented as my solo work.

## Layout and reproduction

- `TC264_jisuyueye/code/`: application modules, including image processing and control logic.
- `TC264_jisuyueye/user/`: entry points and interrupt handlers.
- `TC264_jisuyueye/libraries/`: chip and device libraries, including third-party code.
- `TC264_jisuyueye/.project` and `.cproject`: AURIX/Eclipse project configuration targeting TC26xB.

Reproduction requires compatible TC264 hardware, camera/peripherals, and the matching AURIX/TASKING toolchain. Pins and parameters must be checked against the actual vehicle. No independent build, hardware benchmark, or standardized image dataset is provided here.

## Rights and scope

This is a team project with third-party dependencies. The repository currently has no overall open-source license; public visibility does not grant permission to reuse all code. Check team authorization and upstream component licenses before reuse.
