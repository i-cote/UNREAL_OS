#!/bin/bash
killall qemu-system-x86_64
make -C /root/Pre-TPE_Arqui/x64barebones clean
docker run --rm -v /root/Pre-TPE_Arqui/x64barebones:/root --security-opt seccomp:unconfined agodio/itba-so:1.0 make -C /root
if [[ !  $? -eq 0 ]]
	then echo "COMPILATION ERROR"
	exit -1
fi
qemu-system-x86_64 -hda /root/Pre-TPE_Arqui/x64barebones/Image/x64BareBonesImage.qcow2 -m 512 1>/dev/null 2>&1 &
vncviewer 1>/dev/null 2>&1 &