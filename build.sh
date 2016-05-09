#!/bin/sh
#### This build script is for running sample programs related to libprocess###########

COMPILER="g++"
MESOS_HOME="/home/ubuntu/fedCloud/mesos"
LIBP_PATH="$MESOS_HOME/3rdparty/libprocess"

INCLUDE_PATH="  -I $LIBP_PATH/include
                -I $LIBP_PATH/3rdparty/gmock-1.7.0
                -I $LIBP_PATH/3rdparty/gmock-1.7.0/gtest/include/gtest
                -I $LIBP_PATH/3rdparty/stout/include
                -I $LIBP_PATH/3rdparty/picojson-1.3.0
                -I $LIBP_PATH/build/3rdparty/glog-0.3.3/src
                -I $LIBP_PATH/build/3rdparty/picojson-1.3.0
                -I $MESOS_HOME/build/3rdparty/libprocess/3rdparty/boost-1.53.0"

LIBS_PATH="      $LIBP_PATH/build/.libs/libprocess.a
                 $LIBP_PATH/3rdparty/gmock-1.7.0/build/lib/.libs/libgmock.a
                 $LIBP_PATH/build/3rdparty/gmock-1.7.0/gtest/build/lib/.libs/libgtest.a
                 $LIBP_PATH/build/3rdparty/libev-4.22/.libs/libev.a
                 $LIBP_PATH/build/3rdparty/glog-0.3.3/.libs/libglog.a"

$COMPILER $INCLUDE_PATH -std=gnu++11 http_test.cpp -o abc.out $LIBS_PATH -ldl -lz -lcurl -lsvn_delta-1 -lsvn_subr-1 -lapr-1  -lrt -lpthread
