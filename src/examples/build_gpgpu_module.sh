#!/bin/sh

#
# Testing the Apache Mesos module build and test
# thus far, i'm automating the build
#
# author : Raymond Tay
# date   : 26 august 2015
#
# export HOME=/home/tayboonl
export HOME=/Users/raymondtay
export MESOS_INSTALL_DIR=$HOME/apache-mesos/build
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$MESOS_INSTALL_DIR/src/.libs
export GPGPU_OBJ_FILE=gpgpu_module_impl.o

echo "[Debug] dynamic libs = $LD_LIBRARY_PATH"
echo "[Debug] dynamic libs = $LD_LIBRARY_PATH"
echo "[Debug] About to build ..."

g++ -c -std=c++11 -I $HOME/apache-mesos/build/src -I $HOME/apache-mesos/build/3rdparty/libprocess/3rdparty/protobuf-2.5.0/src -I $HOME/apache-mesos/src -I $HOME/apache-mesos/./build/3rdparty/libprocess/3rdparty/picojson-4f93734/ -I $HOME/apache-mesos/./3rdparty/libprocess/3rdparty/stout/include -I $HOME/apache-mesos/./3rdparty/libprocess/include/ -I $HOME/apache-mesos/./build/3rdparty/libprocess/3rdparty/glog-0.3.3/src/ -I $HOME/apache-mesos/./3rdparty/libprocess/3rdparty/stout/include -I $HOME/apache-mesos/build/include -I $HOME/apache-mesos/include -L $LD_LIBRARY_PATH -lmesos -lprotobuf -fpic -o $GPGPU_OBJ_FILE ./gpgpu_module_impl.cpp

if (test -e ./$GPGPU_OBJ_FILE)
then
  g++ -shared -o libgpgpu_module.so $GPGPU_OBJ_FILE
else
  echo "Cannot locate the object file: $GPGPU_OBJ_FILE; exiting"
fi
