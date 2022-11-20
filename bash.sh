pwd
cd ~/new_kernel/linux-5.19.9
pwd
make -j$(nproc)
make modules_install
cp -v /home/user/kernel/linux-5.19.9/arch/x86_64/boot/bzImage /vmlinuz-linux_hocus_pocus
