#!/bin/bash

bin= ./build/main/main
id=$(pidof $bin)
echo $id
function start(){
  if [ -z "$id" ];then
    ./$bin
    echo "$id process running end ..."
  else
    echo "$bin is running..."
  fi
}
function stop(){
  if [ -z "$id" ];then
    echo "$id process is not exists!"
  else
    kill -9 $id
    echo "$bin is end.."
  fi
}

function status(){
  if 'pidof $bin > /dev/null'; then
    echo "status:running"
  else
    echo "status:dead"
  fi
}


case $1 in
  "run" )
    start
    ;;
  "stop" )
    stop
    ;;
  * )
esac




