#!/bin/sh

set HOME=/home/tayboonl
set MESOS_INSTALL_DIR=$HOME/apache-mesos/build

$MESOS_INSTALL_DIR/bin/mesos-tests.sh --modules="file://$MESOS_INSTALL_DIR/../src/examples/nvidia.json" --isolation="org_apache_mesos_TestGpuIsolator"
