#!/bin/bash

rm -r isodir
rm -r release

mkdir -p isodir/boot/grub
mkdir -p release

cp build/kernel.bin isodir/boot/kernel.bin

cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o release/os.iso isodir

rm -r isodir
