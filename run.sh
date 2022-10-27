#!/bin/bash
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -soundhw all -device intel-hda -device hda-duplex -device hda-output 
