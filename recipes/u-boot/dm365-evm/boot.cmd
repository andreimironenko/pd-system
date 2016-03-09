mmc rescan 0
setenv bootargs 'console=ttyS0,115200n8 root=/dev/mmcblk0p1 rw ip=off mem=216M video=davincifb:vid0=OFF:vid1=OFF:osd0=1280x720x16,4050K dm365_imp.oper_mode=0 davinci_capture.device_type=4  davinci_enc_mngr.ch0_output=COMPONENT davinci_enc_mngr.ch0_mode=720P-60 rootwait'
ext2load mmc 0:1 80700000 /boot/uImage
bootm 80700000
