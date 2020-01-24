# VideoFaceDetector

using libs
opencv 4.1.2
cmake 3.15.2

## Build

```sh
cmake -B <path to dir build>
cmake --build <path to dir build>
```

## Run

```sh
./VideoFaceDetector -FileName=<file path or rtsp path> -FaceCascade=<file path to cascade> -CascadeCount=<cascade count(create thread for each cascade(default 2))>
./VideoFaceDetector -CameraId=<id web cam (default 0)> -FaceCascade=<file path to cascade>
```
