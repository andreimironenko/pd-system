################################################################################
# ATTENTION!                                                                   #
# Be careful while modifying this file. Recommended way is going through       # 
# the list and comment/uncomment or/and modify the properties required. Adding # 
# a new settings or giving wrong values may cause the system hang.             #
################################################################################

################################################################################
# Boot mode:                                                                   #
#  'normal'  - Normal boot                                                     #
#  'upgrade' - Boot and upgrade                                                #
################################################################################
setenv bootmode 'normal'
################################################################################

################################################################################
# Boot media                                                                   #
#------------------------------------------------------------------------------#
# Attention! u-boot will set-up this variable for you, don't do it yourself!   #
#------------------------------------------------------------------------------#
#  'nand'  -   Booting from NAND flash                                         #
#  'sd'    -   Booting from SD card                                            #
################################################################################
#setenv bootmedia 'nand'
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
setenv rootfsmedia 'nand'
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
#setenv depotmedia 'tftp'
################################################################################


################################################################################
# Linux kernel IP configuration:                                               #
# 'static' - Linux kernel IP address is given static IP-address defined below  #
# 'none'   - Networking is disable                                             # 
# 'dhcp'   - IP address is assigned by DHCP server                             # 
################################################################################
setenv  kernel-ip  'dhcp'
################################################################################

################################################################################
# U-boot IP configuration:                                                     #
# 'static' - Linux kernel IP address is given static IP-address defined below  #
# 'none'   - Networking is disable                                             # 
# 'dhcp'   - IP address is assigned by DHCP server                             # 
################################################################################
setenv  uboot-ip 'dhcp'
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
#setenv ipaddr '10.42.43.85'
#setenv gatewayip '10.42.43.1'
#setenv netmask '255.255.255.0'
#setenv serverip '10.42.43.1'
#setenv dnsip '10.42.43.1'
#setenv dnsip2 '192.168.0.1'
setenv hostname 'iptft'
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
setenv  uboot-console 	'serial'
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
setenv  kern-console 	'serial'
################################################################################

################################################################################
# U-boot serial console port and speed                                         #
# -uboot-ser-port	(mandatory)	Serial port                                    #
# -uboot-ser-spped  (mandatory) Serial port bit-rate                           #
################################################################################
setenv uboot-serial-port  'ttyO0'
setenv uboot-serial-speed '115200'
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
setenv kern-serial-port    'ttyO0'
setenv kern-serial-speed  '115200'
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
