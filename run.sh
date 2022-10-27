#!/bin/bash
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -soundhw pcspk #-audiodev pa,id=snd0,server=/run/user/1000/pulse/native -device ich9-intel-hda -device hda-output,audiodev=snd0 #-device intel-hda -device hda-output 
