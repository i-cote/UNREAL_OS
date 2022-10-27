#!/bin/bash
killall qemu-system-x86_64
make clean
make -C ./Toolchain clean
docker run --rm -v ${PWD}:/root --security-opt seccomp:unconfined agodio/itba-so:1.0 make -C /root/Toolchain
docker run --rm -v ${PWD}:/root --security-opt seccomp:unconfined agodio/itba-so:1.0 make -C /root
if [[ !  $? -eq 0 ]]
	then 
	echo "COMPILATION ERROR"
	exit -1
fi
if [[ "$1" = "gdb" ]]
	then
	qemu-system-x86_64 -s -S -hda ./Image/x64BareBonesImage.qcow2 -m 512 -soundhw pcspk -d int 1>/dev/null 2>&1 &
else
	qemu-system-x86_64 -hda ./Image/x64BareBonesImage.qcow2 -m 512 -soundhw pcspk 1>/dev/null 2>&1 &
fi
vncviewer 1>/dev/null 2>&1 &
