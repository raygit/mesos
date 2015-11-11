#!/bin/sh

#
# Testing the Apache Mesos module build and test
# thus far, i'm automating the build
#
# author : Raymond Tay
# date   : 26 august 2015
#
export HOME=/Users/raymondtay
export MESOS_INSTALL_DIR=$HOME/apache-mesos/build
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$MESOS_INSTALL_DIR/src/.libs

echo "[Debug] dynamic libs = ${LD_LIBRARY_PATH}"
echo "[Debug] dynamic libs = ${LD_LIBRARY_PATH}"
echo "[Debug] About to build ..."

g++ -c -std=c++11 -I $HOME/apache-mesos/build/3rdparty/libprocess/3rdparty/protobuf-2.5.0/src -I $HOME/apache-mesos/build/src -I $HOME/apache-mesos/src -I $HOME/apache-mesos/./build/3rdparty/libprocess/3rdparty/picojson-4f93734/ -I $HOME/apache-mesos/./3rdparty/libprocess/3rdparty/stout/include -I $HOME/apache-mesos/./3rdparty/libprocess/include/ -I $HOME/apache-mesos/./build/3rdparty/libprocess/3rdparty/glog-0.3.3/src/ -I $HOME/apache-mesos/./3rdparty/libprocess/3rdparty/stout/include -I $HOME/apache-mesos/build/include -I $HOME/apache-mesos/include -L$LD_LIBRARY_PATH -lmesos -lprotobuf -fpic -o nvidia_gpgpu.o ./nvidia_gpgpu.cpp

if (test -e ./nvidia_gpgpu.o)
then
  g++ -shared -o libnvidia_gpgpu.so nvidia_gpgpu.o
else
  exit
fi
