################################################################################
# Constant variables provided by u-boot                                        #
################################################################################

################################################################################
#  bootmedia:                                                                  #
#  'sd'     - Booting from SD card                                             #
#  'nand'   - Booting from NAND                                                #
#  'spi'    - Booting from SPI flash                                           #            
################################################################################

################################################################################
# Boot mode:                                                                   #
#  'normal'  - Normal boot                                                     #
#  'upgrade' - Boot and upgrade                                                #
################################################################################
# setenv bootmode 'normal'
################################################################################

################################################################################
# Boot media                                                                   #
#------------------------------------------------------------------------------#
# Attention! u-boot will set-up this variable for you, don't do it yourself!   #
#------------------------------------------------------------------------------#
#  'nand'  -   Booting from NAND flash                                         #
#  'sd'    -   Booting from SD card                                            #
################################################################################
# setenv bootmedia 'nand'
################################################################################

################################################################################
# Root file system media                                                       #
#------------------------------------------------------------------------------#
# Change this variable in the u-boot to alter the root filesystem media.       # 
# For example for NFS boot perform the following steps:                        #
#   setenv rootfsmedia 'net'                                                   #
#   setenv rootfstype 'nfs'                                                    #
# If you would like to keep booting from NFS, save environment and reset:      #
#   saveenv                                                                    #
#   reset                                                                      # 
#------------------------------------------------------------------------------#
# Values:                                                                      # 
#  'net'   -   Network, the only file system supported - NFS                   #
#  'sd'    -   SD card, it can be various rootfs like EXT2 and EXT3            #
#  'nand'  -   NAND flash, it supports both UBIFS or JFFS2                     #
#  'ram'   -   Root file system resides on RAM disk                            #
#  'sata'  -   Root file system resides on SATA drive
################################################################################
# setenv rootfsmedia 'nand'
################################################################################


################################################################################
# Root file system type                                                        
#-------------------------------------------------------------------------------
# Change this variables in the u-boot to alter the root filesystem type. See   
# the notes above regading changing rootfs media as well.                      
#-------------------------------------------------------------------------------
# Values:
#  'nfs'   - Root file system resides on remote server NFS share
#  'ubifs' - Root file system resides on NAND and formated as UBIFS
#  'ext3'  - EXT2/EXT3 root file system (usually resides on SD card or SATA drive)
################################################################################
# setenv rootfstype 'ubifs'
################################################################################


################################################################################
# Depot media                                                                  #
#------------------------------------------------------------------------------#
# Values:                                                                      # 
#  'rootfs'   -    Upgrade u-boot images from root file system                 #
#  'tftp'     -    Upgrade u-boot images from TFTP server                      #
#  'usb'      -    Upgrade u-boot images from USB pen-drive                    #
################################################################################
# setenv depotmedia 'rootfs'
################################################################################


################################################################################
# Linux kernel IP configuration:                                               #
# 'static' - Linux kernel IP address is given static IP-address defined below  #
# 'none'   - Networking is disable                                             # 
# 'dhcp'   - IP address is assigned by DHCP server                             # 
################################################################################
# setenv  kernel-ip  'dhcp'
################################################################################

################################################################################
# U-boot IP configuration:                                                     #
# 'static' - Linux kernel IP address is given static IP-address defined below  #
# 'none'   - Networking is disable                                             # 
# 'dhcp'   - IP address is assigned by DHCP server                             # 
################################################################################
# setenv  uboot-ip 'dhcp'
################################################################################

################################################################################
# Network Configuration, must be defined if Kernel or U-boot static IP chosen  #
# - ipaddr       (mandatory) 	This board IP address                          #
# - gatewayip    (mandatory) 	Network gateway/router IP address              #
# - netmask      (mandatory) 	Network mask                                   #
# - serverip     (optional)     DHCP/TFTP server IP address                    #
# - dnsip/dnsip2 (optional)     DNS1/DNS2 IP addresses                         #
# - hostname     (optional)     This is the board network name, can be skipped #
################################################################################
# setenv ipaddr '10.42.43.85'
# setenv gatewayip '10.42.43.1'
# setenv netmask '255.255.255.0'
# setenv serverip '10.42.43.1'
# setenv dnsip '10.42.43.1'
# setenv dnsip2 '192.168.0.1'
# setenv hostname 'iptft'
################################################################################

################################################################################
# U-boot console mode:                                                         #
# 'serial'		-	The log is sent to the serial port. Port parameters must   #
#					be defined below by setting uboot-ser-port and             #
#					uboot-ser-speed variables                                  #
# 'netconsole'	-	The log is net to UDP network port. Network port parameters#
#					must be defined below by setting netcon_src_dev,           # 
#                   netcon_dst_port, netcon_dst_ip variables                   #
################################################################################
# setenv  uboot-console 	'serial'
################################################################################

################################################################################
# Linux kernel console mode:                                                   #
# 'serial'		-	The log is sent to the serial port. Port parameters must   #
#					be defined below by setting uboot-ser-port and             #
#					uboot-ser-speed variables                                  #
# 'netconsole'	-	The log is net to UDP network port. Network port parameters#
#					must be defined below by setting netcon_src_dev,           # 
#                   netcon_dst_port, netcon_dst_ip variables                   #
# ATTENTION!   KERNEL NETCONSOLE IS NOT WORKING YET!   DON'T USE IT FOR NOW !  #
################################################################################
# setenv  kern-console 	'serial'
################################################################################

################################################################################
# U-boot serial console port and speed                                         #
# -uboot-ser-port	(mandatory)	Serial port                                    #
# -uboot-ser-spped  (mandatory) Serial port bit-rate                           #
################################################################################
#setenv uboot-serial-port  'ttyO0'
#setenv uboot-serial-speed '115200'
################################################################################

################################################################################
# Kernel serial console port and speed                                         #
# -kern-ser-port  (mandatory) Serial port. To choose between serial or display #
#                             set the kern_ser_port to the required TTY,       #
#                             for example, in DM8148(Z3), the serial is 'ttyO0'#
#                             and graphical framebuffer console is 'tty1'.     # 
# -kern-ser-speed (mandatory) Serial port bit-rate. To setup graphical         #
#                             framebuffer console, set speed to '38400'        # 
################################################################################
#setenv kern-serial-port    'ttyO0'
#setenv kern-serial-speed  '115200'
################################################################################

################################################################################
# U-boot and kernel netconsole parameters, define these parameters if          #
# netconsole is chosen                                                         #
# must be configured if either Kernel or U-boot netconsole has been chosen     #
# -netcon_src_port '6666'	(mandatory)	Target source network port             #
# -netcon_src_dev  'eth0'	(mandatory)	Target source network device           #
# -netcon_dst_port '6666'  	(mandatory)	Destination computer network port      #
# -netcon_dst_ip   '192.168.9.1'  (mandatory) Destination computer IP address  #
################################################################################
#setenv netcon-src-port '6666'
#setenv netcon-src-dev  'eth0'
#setenv netcon-dst-port '6666'
#setenv netcon-dst-ip   '192.168.9.1'
################################################################################



################################################################################
# Constant platform parameters                                                 #
################################################################################

########################################
# General configuration                #
########################################
setenv bootargs_misc 'quite mem=176M earlyprintk'
setenv hostname 'iptft'
setenv loadaddr  0x81000000
setenv powerlevel '0x49'


########################################
# NAND layout configuration            #
########################################
setenv mtdids 'nand0=nand'
setenv mtdparts 'mtdparts=nand:128k(min)ro,1920k(uboot),512k(env),4352k(kernel),204928k(rootfs)' 

# u-boot-min partition - 128 KB
setenv min_nand_start        '0'
setenv min_nand_img_max_size '0x20000'
setenv min_nand_part_size    '0x20000'

# Max image size must be smaller than partition size as we need to count 
# possible bad blocks allocations

# u-boot :
# partition size  - 1920 KB
# max image size  - 1769 KB
setenv uboot_nand_start          '0x20000'
setenv uboot_nand_img_max_size   '0x1B0000'
setenv uboot_nand_part_size      '0x1E0000'

# Default environment:
# partition size - 512 KB
# max image size - 128 KB 
setenv default_nand_start        '0x200000'
setenv default_nand_img_max_size '0x20000'
setenv default_nand_part_size    '0x80000'

# Back-up kernel image 
# partition size - 4352 KB
# max image size - 4194 KB
setenv kernel_nand_start         '0x280000'
setenv kernel_nand_img_max_size  '0x400000'
setenv kernel_nand_part_size     '0x440000'

# UBIFS root file system 
# partition size - 209846 KB
# max image size - 207749 KB
setenv ubi_nand_start            '0x6C0000'
setenv ubi_nand_img_max_size     '0xC620000'     
setenv ubi_nand_part_size        '0xC820000'

# Root partition configuration
setenv ubifs_part_name 'rootfs'
setenv ubifs_hdr_offset '2048'
setenv ubifs_part_id '4'
setenv ubifs_dev 'ubi0'

########################################
# Common paths and files               #
########################################
setenv bootpath                 '/boot'
setenv imgpath                  '/boot/img'
setenv kernelimg                'uImage'
setenv bootscr                  'boot.scr'
setenv updatescr                'update.scr'
setenv defaultscr               'default.scr'


################################################################################
# U-boot configurations. They can be overriden                                 #
################################################################################
########################################
# Zero configration                    #
########################################
# Change config variable to change the configuration 
setenv bootmode             'normal'    
setenv kernel-ip            'dhcp'      
setenv uboot-ip             'dhcp'      
setenv uboot-console        'serial'    
setenv kern-console         'serial'    
setenv uboot-serial-port    'ttyO0'     
setenv uboot-serial-speed   '115200'    
setenv kern-serial-port     'ttyO0'     
setenv kern-serial-speed    '115200'    
setenv rootfsmedia          'nand'      
setenv rootfstype           'ubifs'    
setenv primary-rootfsmedia  'nand'      
setenv primary-rootfstype   'ubifs'     
setenv depotmedia           'rootfs'    
setenv just-upgraded-flag   '0'         
setenv hostname             'iptft'     

setenv set-config-zero 'if test true = true; then \
    setenv bootmode             'normal'    \
    setenv kernel-ip            'dhcp'      \
    setenv uboot-ip             'dhcp'      \
    setenv uboot-console        'serial'    \
    setenv kern-console         'serial'    \
    setenv uboot-serial-port    'ttyO0'     \
    setenv uboot-serial-speed   '115200'    \
    setenv kern-serial-port     'ttyO0'     \
    setenv kern-serial-speed    '115200'    \
    setenv rootfsmedia          'nand'      \
    setenv rootfstype           'ubifs'     \
    setenv primary-rootfsmedia  'nand'      \
    setenv primary-rootfstype   'ubifs'     \
    setenv depotmedia           'rootfs'    \
    setenv just-upgraded-flag   '0'         \
    setenv hostname             'iptft'     \
fi'

################################################################################
# Power configuration                                                          #
################################################################################
setenv set-power 'if test true = true; then \
    echo Set powerlevel to ${powerlevel} ;\
    mw.w 1000000 0;mw.w 1000000 0;i2c mw 1d 2 0;i2c mw 1d 1 ${powerlevel};\
    sleep 1;i2c mw 1d 3 0; \
    fi'

################################################################################
# U-boot network configuration                                                 #
################################################################################
setenv set-hostname 'set hostname iptft'

setenv start-net-static 'echo Static IP connection...'
setenv start-net-dhcp 'echo DHCP IP connection ...; dhcp'
setenv start-net-none 'echo No IP connection ...'

# Start network command
setenv start-net 'if test "${uboot-ip}"   = "none"  ;then run start-net-none;\
                  elif test "${uboot-ip}" = "static";then run start-net-static;\
                  elif test "${uboot-ip}" = "dhcp"  ;then run start-net-dhcp;\
                  else  run start-net-dhcp;\
                  fi'  

################################################################################
# Linux kernel network configurations                                          # 
################################################################################
setenv set-ip-static 'setenv ipargs ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}::off'
setenv set-ip-dhcp 'setenv ipargs ip=dhcp'
setenv set-ip-none 'setenv ipargs ip=none'

# The set-ip command defines ipargs
setenv set-ip 'if test "${kernel-ip}" = "none"    ; then run set-ip-none;\
                  elif test "${kernel-ip}" = "static" ; then run set-ip-static;\
                  elif test "${kernel-ip}" = "dhcp"   ; then run set-ip-dhcp;\
                  else  run set-ip-dhcp;\
                  fi' 

################################################################################
# Linux console configurations                                                 # 
################################################################################
setenv set-kernel-console 'if test "${kern-console}" = "netconsole" ; then \
        set bootargs_console netconsole=${netcon_src_port}@${ipaddr}/${netcon_src_dev},${netcond_dst_port}@${netcon_dst_ip} ; \
    elif test "${kern-console}" = "serial"; then \
        set bootargs_console console=${kern-serial-port},${kern-serial-speed} ; \ 
    else \
        set bootargs_console console=${kern-serial-port},${kern-serial-speed} ; \
    fi' 

setenv set-console 'if test "${uboot-console}" = "netconsole" ; then \
        set ncip ${masterip}; set stdin nc; set stdout nc; set stderr nc; \
     elif test "${uboot-console}" = "serial" ; then \
        set stdin serial; set stdout serial; set stderr serial; \ 
        set console ${uboot-serial-port},${uboot-serial-speed};\ 
     else \ 
        set stdin serial; set stdout serial; set stderr serial; \
        set console ${uboot-serial-port},${uboot-serial-speed};\ 
     fi' 
     
     
################################################################################
# Root file system media operations                                            #
################################################################################
########################################
# NAND-UBIFS                           #
########################################
setenv nand-ubifs-set-rootfs-binary 'set rootfsimg ubi.img'

setenv nand-ubifs-init 'if test true = true; then \
    echo Initializing NAND/UBIFS...; \
    nandecc sw; \
    chpart ${ubifs_part_name}; \
    ubi part ${ubifs_part_name} ${ubifs_hdr_offset}; \
    ubifsmount ${ubifs_part_name}; \
    fi'
    
setenv nand-ubifs-load-user 'if test true = true; then \
    echo Loading boot.scr from UBIFS ; \
    if ubifsload ${loadaddr} ${bootpath}/${bootscr}; then source ${loadaddr};fi \
    fi'

setenv nand-ubifs-load-update 'if test true = true; then \
    echo Loading update.scr from UBIFS ...; \ 
    mw.b ${loadaddr} 0x00 ${default_nand_img_max_size}; \
    if ubifsload ${loadaddr} ${bootpath}/${updatescr}; then \
    source ${loadaddr}; fi \
    fi'

setenv nand-ubifs-load-default 'if test true = true; then \
    echo Loading default.scr from UBIFS ...; \
    ubifsload ${loadaddr} ${imgpath}/${defaultscr}; \ 
    source; \
    fi'

setenv nand-ubifs-set-bootargs 'setenv bootargs ${bootargs_console} noinitrd rw ubi.mtd=${ubifs_part_id},${ubifs_hdr_offset} root=${ubifs_dev}:${ubifs_part_name} rootfstype=ubifs ${bootargs_misc}: ${ipargs}' 
    
setenv nand-ubifs-load-kernel 'ubifsload ${loadaddr} ${bootpath}/${kernelimg}'
    
setenv nand-ubifs-load-min 'if test true = true; then \
    echo Loading u-boot.min.nand from UBIFS...; \
    mw.b ${loadaddr} 0xFF ${min_nand_img_max_size}; \
    ubifsload ${loadaddr} ${imgpath}/${uboot-min-bin}; \
    fi' 

setenv nand-ubifs-load-uboot 'if test true = true; then \
    echo Loading u-boot.bin ...;  \
    mw.b ${loadaddr} 0xFF ${uboot_nand_img_max_size}; \
    ubifsload ${loadaddr} ${imgpath}/${uboot-bin}; \
    fi' 


# Writing rootfs NAND:UBIFS image  
setenv nand-ubifs-write-rootfs 'if test true = true; then \
    echo Writing rootfs image ubiimg to NAND ...; \
    nandecc sw; \
    nand erase ${ubi_nand_start} ${ubi_nand_part_size}; \
    nand write ${loadaddr} ${ubi_nand_start} ${ubi_nand_img_max_size}; \
    else \
    echo Wrong rootfstype ${rootfstype} can not continue ... ; \
    fi'
    
setenv nand-ubifs-set-functions 'if test ${rootfsmedia} = "nand" -a test ${rootfstype} = "ubifs" ; then \
    setenv set-rootfs-binary run nand-ubifs-set-rootfs-binary; \
    setenv rootfs-init run nand-ubifs-init; \
    setenv load-user run nand-ubifs-load-user; \
    setenv load-update run nand-ubifs-load-update; \
    setenv load-default run nand-ubifs-load-default; \
    setenv set-bootargs run nand-ubifs-set-bootargs; \
    setenv load-kernel  run nand-ubifs-load-kernel; \
    setenv load-min run nand-ubifs-load-min; \
    setenv load-uboot run nand-ubifs-load-uboot; \
    setenv write-rootfs run nand-ubifs-write-rootfs; \
     ; \
    fi'


########################################
# NET-NFS                              #
########################################
setenv nfs-set-rootfs-binary 'echo NFS does not have rootfs binary, skip it'

setenv nfs-init 'if test true = true; then \
    echo Initializing NFS...; \
    dhcp; \
    set nfsroot /opt/exports/${tftp_path}/../nfs; \
    fi'
    
setenv nfs-load-user 'if test true = true; then \
    echo Loading boot.scr from NFS ; \
    nfs ${loadaddr} ${serverip}:${nfsroot}${bootpath}/${bootscr}; \
    source ${loadaddr}; \
    fi'

setenv nfs-load-update 'if test true = true; then \
    echo Loading update.scr from NFS ...; \ 
    mw.b ${loadaddr} 0x00 ${default_nand_part_size}; \
    nfs ${loadaddr} ${serverip}:${nfsroot}${bootpath}/${updatescr}; \
    source ${loadaddr}; \
    fi'

setenv nfs-load-default 'if test true = true; then \
    echo Loading default.scr from UBIFS ...; \
    nfs ${loadaddr} ${serverip}:${nfsroot}${imgpath}/${defaultscr}; \ 
    source ${loadaddr}; \
    fi'

setenv nfs-set-bootargs 'setenv bootargs ${bootargs_console} noinitrd rw root=/dev/nfs nfsroot=${serverip}:${nfsroot},nolock rw rootfstype=nfs ${bootargs_misc}: ${ipargs}' 
    
setenv nfs-load-kernel 'nfs ${loadaddr} ${serverip}:${nfsroot}${bootpath}/${kernelimg}'
    
setenv nfs-load-min 'if test true = true; then \
    echo Loading u-boot.min.nand from NFS...; \
    mw.b ${loadaddr} 0xFF ${min_nand_part_size}; \
    nfs ${loadaddr} ${serverip}:${nfsroot}${imgpath}/${uboot-min-bin}; \
    fi' 

setenv nfs-load-uboot 'if test true = true; then \
    echo Loading u-boot.bin ...;  \
    mw.b ${loadaddr} 0xFF ${uboot_nand_part_size}; \ 
    nfs ${loadaddr} ${serverip}:${nfsroot}${imgpath}/${uboot-bin}; \ 
    fi' 


# Writing rootfs NET:NFS image      
setenv nfs-wrtie-rootfs 'if test true = true; then \
    echo "Write operation for NFS is not possible! "; \
    fi'
    
setenv nfs-set-functions 'if test ${rootfsmedia} = "net" -a test ${rootfstype}="nfs" ; then \
    setenv set-rootfs-binary run nfs-set-rootfs-binary; \
    setenv rootfs-init run nfs-init; \
    setenv load-user run nfs-load-user; \
    setenv load-update run nfs-load-update; \
    setenv load-default run nfs-load-default; \
    setenv set-bootargs run nfs-set-bootargs; \
    setenv load-kernel  run nfs-load-kernel; \
    setenv load-min run nfs-load-min; \
    setenv load-uboot run nfs-load-uboot; \
    setenv write-rootfs run nfs-write-rootfs; \ 
    ;\
    fi'
    
########################################
# SATA-EXT3                            #
########################################
setenv sata-ext3-set-rootfs-binary 'echo There is no rootfs binary to load'

setenv sata-ext3-init 'if test true = true; then \
    echo No need to initialize SATA EXT3 it is not supported by u-boot ...; \
    fi'
    
setenv sata-ext3-load-user 'if test true = true; then  \
    echo Can not read user.scr from SATA drive skip ... \
    fi'

setenv sata-ext3-load-update 'if test true = true; then  \
    echo Can not read update.scr from SATA drive skip ... ; \
    fi'

setenv sata-ext3-set-bootargs 'setenv bootargs ${bootargs_console} noinitrd rw root=/dev/sda1  rw rootfstype=ext3 ${bootargs_misc}: ${ipargs}' 

#Read kernel from row NAND partition    
setenv sata-ext3-load-kernel 'read-kernel'

setenv sata-ext3-load-default 'if test true = true; then \
    echo Can not read defalut.scr from SATA drive skip ...; \
    fi'
    
setenv sata-ext3-load-min 'if test true = true; then \
    echo Can not read uboot-min binary from SATA drive skip ...; \
    fi' 

setenv sata-ext3-load-uboot 'if test true = true; then \
    echo Can not read uboot binary from SATA drive skip ...; \
    fi' 

# Writing rootfs image      
setenv sata-ext3-wrtie-rootfs 'if test true = true; then \
    echo "Write operation for SATA drive is not possible!"; \
    fi'
    
setenv sata-ext3-set-functions 'if test ${rootfsmedia} = "sata" -a test ${rootfstype}="ext3" ; then \
    setenv set-rootfs-binary run sata-ext3-set-rootfs-binary; \
    setenv rootfs-init run sata-ext3-init; \
    setenv load-user run sata-ext3-load-user; \
    setenv load-update run sata-ext3-load-update; \
    setenv load-default run sata-ext3-load-default; \
    setenv set-bootargs run sata-ext3-set-bootargs; \
    setenv load-kernel  run sata-ext3-load-kernel; \
    setenv load-min run sata-ext3-load-min; \
    setenv load-uboot run sata-ext3-load-uboot; \
    setenv write-rootfs run sata-ext3-write-rootfs; \ 
    ;\
    fi'

########################################
# GENERIC ROOTFSMEDIA FUNCTIONS        #
########################################
setenv rootfs-media-set-functions 'if test "${rootfsmedia}" = "nand" -a "${rootfstype}" = "ubifs" ; then \
    echo Acivating ${rootfsmedia}:${rootfstype} functions: ; \
    run nand-ubifs-set-functions; \
elif test "${rootfsmedia}" = "net" -a "${rootfstype}" = "nfs" ; then \
    echo Acivating ${rootfsmedia}:${rootfstype} functions: ; \
    run nfs-set-functions; \
elif test "${rootfsmedia}" = "sata" -a "${rootfstype}" = "ext3" ; then \
    echo Acivating ${rootfsmedia}:${rootfstype} functions: ; \
    run sata-ext3-set-functions; \
else \
   echo Unknown rootfs media=${rootfsmedia} and type=${rootfstype} ; \
fi'
 

################################################################################
# Boot media functions                                                         #
################################################################################
########################################
# NAND                                 #
########################################
#Initializing NAND boot media
setenv nand-init 'if test true = true; then \
     echo Initializing NAND boot media ... ; \
     fi'

#Setting up u-boot binaries names 
setenv nand-set-uboot-binaries 'if test true = true; then \
    setenv uboot-min-bin  u-boot.min.nand ; \ 
    setenv uboot-bin u-boot.bin ; \
    fi'
    
# Writing u-boot-min
setenv nand-write-min 'if test true = true; then \
    echo Writing u-boot.min to NAND...; \
    nandecc hw 2;nand erase ${min_nand_start} ${min_nand_part_size}; \
    nand write ${loadaddr} ${min_nand_start} ${min_nand_img_max_size}; nandecc sw; \
    fi'

# Writing u-boot     
setenv nand-write-uboot 'if test true = true; then \
    echo Writing u-boot.bin to NAND ...; \
    nandecc sw; \
    nand erase ${uboot_nand_start} ${uboot_nand_part_size}; \
    nand write.i ${loadaddr} ${uboot_nand_start} ${uboot_nand_img_max_size}; \
    fi'

# Writing default environment    
setenv nand-write-default 'if test true = true; then \
    echo Saving u-boot default envronment...; \
    source ${loadaddr}; \
    saveenv \
 fi'
 
 # Read default environment, only works for first time boot!    
setenv nand-read-default 'if test true = true; then \
    echo Read u-boot default envronment...; \
    mw.b ${loadaddr} 0 ${default_nand_part_size} ; \
    nand read.i ${loadaddr} ${default_nand_start} ${default_nand_img_max_size} \ 
 fi'
 
# Writing back-up kernel image    
setenv nand-write-kernel 'if test true = true ; then \
    echo  Writing back-up kernel image to NAND ...; \
    nandecc sw; \
    nand erase ${kernel_nand_start} ${kernel_nand_part_size}; \
    nand write.i ${loadaddr} ${kernel_nand_start} ${kernel_nand_img_max_size}; \
 fi'
    
# Reading back-up kernel image    
setenv nand-read-kernel 'if test true = true ; then \
    echo  Reading back-up kernel image from NAND ...; \
    nandecc sw; \
    nand read.i ${loadaddr} ${kernel_nand_start} ${kernel_nand_img_max_size}; \
 fi'

# NAND media functions mapping to the generic ones
setenv nand-boot-media-set-functions 'if test "${bootmedia}" = "nand" ; then \
    setenv boot-media-init    run nand-init; \
    setenv set-uboot-binaries run nand-set-uboot-binaries; \
    setenv write-min run nand-write-min; \
    setenv write-uboot run nand-write-uboot; \
    setenv write-default run nand-write-default; \
    setenv read-default run nand-read-default; \
    setenv write-kernel run nand-write-kernel; \
    setenv read-kernel run nand-read-kernel; \
 else \
     "echo Wrong rootfsmedia is chosen, cant continue..."; \
 fi'

########################################
# GENERIC BOOTMEDIA FUNCTIONS          #
########################################
setenv boot-media-set-functions 'if test "${bootmedia}" = "nand" ; then \
    echo Activating boot media functions: ; \
    echo bootmedia = ${bootmedia}; \
    run nand-boot-media-set-functions; \
    else \
        echo Unknow boot media ${bootmedia}; \
    fi'
 

################################################################################
# Depot media                                                                  #
################################################################################
########################################
# ROOTFS                               #
########################################
setenv rootfs-depot-init 'if test true = true; then \
    echo Initializing depot from ${rootfstype}; \
    run rootfs-init; \
    fi'

setenv rootfs-depot-read-min 'if test true = true; then   \
    echo Reading ${uboot-min-bin} from ${rootfstype} ...; \
    mw.b ${loadaddr} 0xFF ${min_nand_part_size}; \
    run load-min; \
    fi'

setenv rootfs-depot-read-uboot 'if test true = true ; then \
    echo Reading ${uboot-bin} from ${rootfstype} ; \
    mw.b ${loadaddr} 0xFF ${uboot_nand_part_size}; \
    run load-uboot; \
    fi'

setenv rootfs-depot-read-default 'if test true = true; then \
    echo Reading ${defaultscr} from ${rootfstype} ...; \
    mw.b ${loadaddr} 0xFF ${default_nand_part_size};  \
    run load-default; \
    fi'

setenv rootfs-depot-read-kernel 'if test true = true; then \
    echo Reading ${kernelimg} from ${rootfstype} ...; \
    mw.b ${loadaddr} 0xFF ${kernel_nand_part_size}; \
    run load-kernel; \
    fi'

setenv rootfs-depot-read-rootfs 'if test true = true; then \
    echo Reading ${rootfsimg} from ${rootfstype} is not supported ... ; \
    fi'
    
setenv rootfs-depot-set-functions 'if test true = true; then \
    setenv depot-init           run rootfs-depot-init         \
    setenv depot-read-min       run rootfs-depot-read-min     \
    setenv depot-read-uboot     run rootfs-depot-read-uboot   \
    setenv depot-read-default   run rootfs-depot-read-default \
    setenv depot-read-kernel    run rootfs-depot-read-kernel  \
    setenv depot-read-rootfs    run rootfs-depot-read-rootfs  
    fi'

########################################
# TFTP                                 #
########################################

setenv tftp-depot-init 'if test true = true; then \
    echo Initializing depot from ${rootfstype}; \
    run start-net; \
    fi'

setenv tftp-depot-read-min 'if test true = true; then
    echo Downloading ${uboot-min-bin} from TFTP ...; \
    mw.b ${loadaddr} 0xFF ${min_nand_part_size}; \
    tftp ${loadaddr} ${tftp_path}/${uboot-min-bin}; \
    fi'

setenv tftp-depot-read-uboot 'if test true = true ; then
    echo Downloading ${uboot-bin} from TFTP ... ; \
    mw.b ${loadaddr} 0xFF ${uboot_nand_part_size}; \
    tftp ${loadaddr} ${tftp_path}/${uboot-bin}; \
    fi'

setenv tftp-depot-read-default 'if test true = true; then \
    echo Downloading ${defaultscr} from TFTP ... ; \
    mw.b ${loadaddr} 0xFF ${default_nand_part_size};  \
    tftp ${loadaddr} ${tftp_path}/${defaultscr}; \
    fi'

setenv tftp-depot-read-kernel 'if test true = true; then \
    echo Downloading ${kernelimg} from TFTP ... ; \
    mw.b ${loadaddr} 0xFF ${kernel_nand_part_size}; \
    tftp ${loadaddr} ${tftp_path}/${kernelimg};\
    fi'

setenv tftp-depot-read-rootfs 'if test true = true; then \
    echo Downloading ${rootfsimg} from TFTP ... ; \
    mw.b ${loadaddr} 0xFF ${ubi_nand_part_size}; \
    tftp ${loadaddr} ${tftp_path}/${rootfsimg}; \
    fi'
    
setenv tftp-depot-set-functions 'if test true = true; then \
    setenv depot-init           run tftp-depot-init         \
    setenv depot-read-min       run tftp-depot-read-min     \
    setenv depot-read-uboot     run tftp-depot-read-uboot   \
    setenv depot-read-default   run tftp-depot-read-default \
    setenv depot-read-kernel    run tftp-depot-read-kernel  \
    setenv depot-read-rootfs    run tftp-depot-read-rootfs  
    fi'

########################################
# USB                                  #
########################################

setenv usb-depot-init 'if test true = true; then \
    echo Initializing depot from ${rootfstype}; \
    usb start ; \
    fi'

setenv usb-depot-read-min 'if test true = true; then
    echo Downloading ${uboot-min-bin} from TFTP ...; \
    mw.b ${loadaddr} 0xFF ${min_nand_part_size}; \
    fatload usb 0 ${loadaddr} ${tftp_path}/${uboot-min-bin}; \
    fi'

setenv usb-depot-read-uboot 'if test true = true ; then
    echo Downloading ${uboot-bin} from TFTP ... ; \
    mw.b ${loadaddr} 0xFF ${uboot_nand_part_size}; \
    fatload usb 0 ${loadaddr} ${loadaddr} ${tftp_path}/${uboot-bin}; \
    fi'

setenv usb-depot-read-default 'if test true = true; then \
    echo Downloading ${defaultscr} from TFTP ... ; \
    mw.b ${loadaddr} 0xFF ${default_nand_part_size};  \
    fatload usb 0 ${loadaddr} ${tftp_path}/${defaultscr}; \
    fi'

setenv usb-depot-read-kernel 'if test true = true; then \
    echo Downloading ${kernelimg} from TFTP ... ; \
    mw.b ${loadaddr} 0xFF ${kernel_nand_part_size}; \
    fatload usb 0 ${loadaddr} ${loadaddr} ${tftp_path}/${kernelimg};\
    fi'

setenv usb-depot-read-rootfs 'if test true = true; then \
    echo Downloading ${rootfsimg} from TFTP ... ; \
    mw.b ${loadaddr} 0xFF ${ubi_nand_part_size}; \
    fatload usb 0 ${loadaddr} ${loadaddr} ${tftp_path}/${rootfsimg}; \
    fi'
    
setenv usb-depot-set-functions 'if test true = true; then \
    setenv depot-init           run usb-depot-init \
    setenv depot-read-min       run usb-depot-read-min     \
    setenv depot-read-uboot     run usb-depot-read-uboot   \
    setenv depot-read-default   run usb-depot-read-default \
    setenv depot-read-kernel    run usb-depot-read-kernel  \
    setenv depot-read-rootfs    run usb-depot-read-rootfs  
    fi'

########################################
# Depot logic                          #
########################################
setenv depot-set-functions 'if test "${depotmedia}" = "rootfs" ;  then \
    run rootfs-depot-set-functions ; \
    elif "${depotmedia}" = "tftp" ; then \
    run tftp-depot-set-functions; \
    elif "${depotmedia}" = "usb" ; then \
    run usb-depot-set-functions; \
    else \
    echo Depot media is not recognised ; \
    fi' 

    
################################################################################
# Restore/Upgrade functions                                                    #
################################################################################

setenv upgrade-init 'if true = true ; then \
    echo Upgrade initialization ... ; \
    run boot-media-init; \
    run boot-media-set-functions; \
    run depot-init;     \
    run depot-set-functions; \ 
    fi'

setenv upgrade-min 'if true = true ; then \
    echo Statrt uboot-min upgrade ... ; \
    run depot-read-min; \
    run write-min \
    fi'
    
setenv upgrade-uboot 'if true = true ; then \
    echo Statrt uboot.bin upgrade ... ; \
    run depot-read-uboot; \
    run write-uboot; \
    fi'
    
setenv upgrade-default 'if true = true ; then \
    echo Statrt default u-boot environment upgrade ... ; \
    run depot-read-default; \
    run write-default; \
    fi'
 
setenv upgrade-kernel 'if true = true ; then \
    echo Statrt upgrade of backup kernel image ... ; \
    run depot-read-kernel; \
    run write-kernel; \
    fi'
 
setenv upgrade-rootfs 'if true = true ; then \
    echo Statrt upgrade of backup kernel image ... ; \
    run depot-read-rootfs; \
    run write-rootfs; \
    fi'

setenv upgrade-uboot-all 'if true = true ; then \
    echo Statrt upgrade of all u-boot images and backup kernel ... ; \
    run upgrade-init ; \
    run upgrade-min ; \
    run upgrade-uboot; \
    run upgrade-default; \
    run upgrade-kernel; \
    fi'

setenv upgrade-all 'if true = true ; then \
    echo Statrt upgrade of all images and including root file system ... ; \
    run upgrade-init ; \
    run upgrade-min ; \
    run upgrade-uboot; \
    run upgrade-default; \
    run upgrade-kernel; \
    run upgrade-rootfs; \
    fi'

setenv upgrade-logic 'if test "${bootmode}" = "upgrade" -a "${just-upgraded-flag}" = "0" ; then \
        echo Start upgrade ${bootmedia} from ${depotmedia} ... ; \
        set just-upgraded-flag '1'; \
        elif test "${bootmode}" = "upgrade" -a "${just-upgraded-flag}" = "1" ; then \
        echo After upgrade reboot. Reseting upgrade flag and continue normal boot ...; \
        set just-upgraded-flag '0'; \
	    else \
        echo No upgrade is indicated, continue with normal boot ... ; \
 fi'
 
################################################################################
# Boot logic                                                                   #
################################################################################
   
setenv bootcmd 'if test true = true ; then \
    echo Start boot ...;\
    run set-power; \
    echo Start boot media functions ...; \
    run boot-media-set-functions; \ 
    echo Setting rootfs media functions ...; \
    run rootfs-media-set-functions; \
    echo Setting-up u-boot and rootfs binary image names ...; \
    run set-rootfs-binary; \
    run set-uboot-binaries; \
    echo Start networking ...; \
    run start-net; \
    echo Setting up host-name base on eth0 EMAC address ...; \
    run set-hostname;
    echo Setting up kernel networking...; \
    run set-ip; \
    echo Setting up kernel console ...; \
    run set-kernel-console; \
    echo Setting up u-boot console ...; \
    run set-console; \
	if test "${bootmode}" = "upgrade" -a "${just-upgraded-flag}" = "0"; then \
        echo Start upgrade ${bootmedia} from ${depotmedia} ... ; \
        run depot-set-functions; \ 
        run depot-init;     \
        run upgrade-min ; \
        set just-upgraded-flag '1'; \
        saveenv; \
        reset; \
	elif test "${bootmode}" = "upgrade" -a "${just-upgraded-flag}" = "1"; then \
        echo After upgrade reboot. Removing upgrade-flag and continue boot ...;\
        set just-upgraded-flag '0'; \
        set bootmode normal; \
        saveenv; \
	else \
        echo No upgrade is indicated, continue with normal boot ... ; \
   fi; \
   echo Setting up kernel bootargs ...; \
   run set-bootargs ; \
   echo Start reading back-up image from ${bootmedia}; \
   run read-kernel; \
   bootm ${loadaddr}; \
fi'
       
         
