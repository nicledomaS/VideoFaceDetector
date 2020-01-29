# VideoFaceDetector

cmake 3.10
opencv 4.2.0

Build opencv:
cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D INSTALL_PYTHON_EXAMPLES=OFF \
      -D INSTALL_C_EXAMPLES=OFF \
      -D WITH_TBB=ON \
      -D WITH_CUDA=ON \
      -D WITH_CUDNN=ON \
      -D OPENCV_DNN_CUDA=ON \
      -D WITH_NVCUVID=ON \
      -D WITH_CUBLAS=1 \
      -D CUDA_ARCH_BIN="6.2" \
      -D CUDA_ARCH_PTX="" \
      -D BUILD_opencv_cudacodec=ON \
      -D ENABLE_FAST_MATH=1 \
      -D CUDA_FAST_MATH=1 \
      -D WITH_CUBLAS=1 \
      -D WITH_V4L=ON \
      -D WITH_QT=OFF \
      -D WITH_OPENGL=ON \
      -D WITH_GSTREAMER=ON \
      -D OPENCV_GENERATE_PKGCONFIG=ON \
      -D OPENCV_PC_FILE_NAME=opencv.pc \
      -D OPENCV_ENABLE_NONFREE=ON \
      -D OPENCV_PYTHON3_INSTALL_PATH=~/.virtualenvs/cv/lib/python3.6/site-packages \
      -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib-4.2.0/modules \
      -D PYTHON_EXECUTABLE=~/.virtualenvs/cv/bin/python \
      -D BUILD_EXAMPLES=OFF  \
      -D BUILD_TESTS=ON \
      -D BUILD_PERF_TESTS=ON \
      -D BUILD_EXAMPLES=ON \
      ..

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
