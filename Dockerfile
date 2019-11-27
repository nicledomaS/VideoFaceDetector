FROM gcc:latest as build


RUN apt-get update && \
    apt-get install -y build-essential cmake libgtk2.0-dev pkg-config \
                        python-numpy python-dev libavcodec-dev libavformat-dev \
                        libswscale-dev libjpeg-dev libpng-dev libtiff5-dev \
                        libjasper-dev libopencv-dev checkinstall pkg-config \
                        yasm libjpeg-dev libjasper-dev libavcodec-dev \
                        libavformat-dev libswscale-dev libdc1394-22-dev \
                        libxine2 libgstreamer0.10-dev  libv4l-dev \
                        libgstreamer-plugins-base0.10-dev python-dev \
                        python-numpy libtbb-dev libqt4-dev libgtk2.0-dev \
                        libmp3lame-dev libopencore-amrnb-dev \
                        libopencore-amrwb-dev libtheora-dev libvorbis-dev \
                        libxvidcore-dev x264 v4l-utils cmake
	
WORKDIR /app/build

RUN cmake -B build && cmake --build build

FROM ubuntu:latest
