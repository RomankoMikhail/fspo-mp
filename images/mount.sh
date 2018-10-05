#!/bin/bash
file=$(realpath disk.img)
#echo $dpath
mkdir -p /tmp/disk
pkexec mount -t vfat $file /tmp/disk -o rw,umask=0000
