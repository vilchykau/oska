#!/bin/bash

rm -r isodir

mkdir -p isodir/boot/grub

cp build/kernel.bin isodir/boot/kernel.bin

cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir
