rm -rf isodir
mkdir -p isodir
mkdir -p isodir/boot
cp myos.bin isodir/boot/myos.bin
mkdir -p isodir/boot/grub
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir
