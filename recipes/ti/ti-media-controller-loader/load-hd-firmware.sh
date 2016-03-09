#!/bin/sh
#
# manage HDVICP2 and HDVPSS Engine firmware


DSP_ID=0
HDVICP2_ID=1
HDVPSS_ID=2

PATH=$PATH:/usr/share/ti/ti-media-controller-utils
MEMMAP_PATH=/usr/share/ti/ti-mcutils-tree/src/mm_host_util
FIRMWARE_PATH=/usr/share/ti/ti-media-controller-utils

PATH=$PATH:$MEMMAP_PATH
MEMMAP="-mmap ${MEMMAP_PATH}/mm_dm81xxbm_512M.bin -i2c 0"

#declare default_mode
#declare -i XRES
#declare -i YRES
#declare -i FREQ

# Enable the graphic mode 
# by removing comment for the required mode

#default_mode="1024x768@60"
#default_mode="1280x768@60"
#default_mode="1280x1024@60"
#default_mode="1366x768@60"
#default_mode="1440x900@60"
#default_mode="1400x1050@60"
#default_mode="1600x900@60"
#default_mode="1680x1050@60"
#default_mode="1600x1200@60"
#default_mode="1920x528@60"
#default_mode="1920x540@60"
#default_mode="1920x552@60"
#default_mode="1920x1080@60"


#Meaning of the timing parameters:

#H_RES/H_FRONT_PORCH/H_BACK_PORCH/H_SYNC_TIME
#V_RES/V_FRONT_PORCH/V_BACK_PORCH/V_SYNC_TIME,
#POLARITY


configure_led()
{
  if [ "$default_mode" = "1024x768@60" ]; then 
    #echo 1024x768@60 > /sys/devices/platform/vpss/display0/mode
    CMD="echo 1024x768@60 > /sys/devices/platform/vpss/display0/mode"
    XRES=1024
    YRES=768
    FREQ=60

  elif [ "$default_mode" = "1280x768@60" ] ; then
    CMD="echo 79500,1280/64/192/128,768/3/20/7,1 > /sys/devices/platform/vpss/display0/timings"
    XRES=1280
    YRES=768
    FREQ=60

  elif [ "$default_mode" = "1280x1024@60" ] ; then
    CMD="echo 1280x1024@60 > /sys/devices/platform/vpss/display0/mode"
    XRES=1280
    YRES=1024
    FREQ=60


  elif [ "$default_mode" = "1366x768@60" ] ; then
    CMD="echo  84750,1366/72/208/136,768/3/22/5  > /sys/devices/platform/vpss/display0/timings"
    XRES=1366
    YRES=768
    FREQ=60


  elif [ "$default_mode" = "1440x900@60" ] ; then
    CMD="echo 106500,1440/80/232/152,900/3/25/6,1 > /sys/devices/platform/vpss/display0/timings"
    XRES=1440
    YRES=900
    FREQ=60


  elif [ "$default_mode" = "1400x1050@60" ] ; then
    CMD="echo 121750,1400/88/232/144,1050/3/32/4,1 > /sys/devices/platform/vpss/display0/timings"
    XRES=1400
    YRES=1050
    FREQ=60


  elif [ "$default_mode" = "1600x900@60" ] ; then
    CMD="echo 97750,1600/48/80/32,900/3/18/5,1 > /sys/devices/platform/vpss/display0/timings"
    XRES=1600
    YRES=900
    FREQ=60


  elif [ "$default_mode" = "1680x1050@60" ] ; then
    CMD="echo 119000,1680/48/80/32,1050/3/21/6,1 > /sys/devices/platform/vpss/display0/timings"
    XRES=1680
    YRES=1050
    FREQ=60


  elif [ "$default_mode" = "1600x1200@60" ] ; then
    CMD="echo 1600x1200@60 > /sys/devices/platform/vpss/display0/mode"
    XRES=1600
    YRES=1200
    FREQ=60


  elif [ "$default_mode" = "1920x528@60" ]  ; then
    CMD="echo 74250,1920/528/148/44,528/2/15/5,1 > /sys/devices/platform/vpss/display0/timings"
    XRES=1920
    YRES=528
    FREQ=60
    
  elif [ "$default_mode" = "1920x540@60" ]  ; then
    CMD="echo 81570,1920/64/256/192,540/1/15/3,1 > /sys/devices/platform/vpss/display0/timings"
    XRES=1920
    YRES=540
    FREQ=60
    
  elif [ "$default_mode" = "1920x552@60" ]  ; then
    CMD="echo 83500,1920/64/256/192,552/3/9/10,1 > /sys/devices/platform/vpss/display0/timings"
    XRES=1920
    YRES=540
    FREQ=60
    
 elif [ "$default_mode" = "1920x1080@60" ] ; then
    CMD="echo 1920x1080@60 > /sys/devices/platform/vpss/display0/mode"
    XRES=1920
    YRES=1080
    FREQ=60

  else 
	CMD="echo 1920x1080@60 > /sys/devices/platform/vpss/display0/mode"
    XRES=1920
    YRES=1080
    FREQ=60
   fi


}

case "$1" in
    start)
        # By default, Angstrom generates an empty fb.modes file.
        # We are not using it and it's a problem for SDL. 
        # So we just remove this file here if it exists.
        if [ -f "/etc/fb.modes" ] ; then
          rm /etc/fb.modes
        fi
        
        if [ -f "/etc/display_resolution.conf" ] ; then
        	default_mode=`cat /etc/display_resolution.conf`
			if [ ! -z ${default_mode} ] ; then
        		default_mode="$default_mode@60"
        	fi
        else
        	default_mode=""
        fi
      
        #Get graphic mode settings  
        configure_led
        
        echo "Loading syslink"
        prcm_config_app s
        modprobe syslink
        until [[ -e /dev/syslinkipc_ProcMgr && -e /dev/syslinkipc_ClientNotifyMgr ]]
        do                                                
            sleep 0.5
        done

        echo "Loading HDVICP2 Firmware"
        firmware_loader $HDVICP2_ID $FIRMWARE_PATH/dm814x_hdvicp.xem3 start ${MEMMAP}

        sleep 0.5

        modprobe tlc59108

        echo "Loading HDVPSS Firmware"

        firmware_loader $HDVPSS_ID $FIRMWARE_PATH/dm814x_hdvpss.xem3 start ${MEMMAP}
        modprobe vpss sbufaddr=0xBFB00000 debug=1 mode=hdmi:${default_mode} i2c_mode=1
        modprobe ti81xxfb vram=0:24M,1:16M,2:6M
        modprobe ti81xxhdmi
       
         
        echo "Disable graphics0 pipeline"
		echo 0 > /sys/devices/platform/vpss/graphics0/enabled
		echo "Disable hdmi VENC"
		echo 0 > /sys/devices/platform/vpss/display0/enabled
	
		echo "Set the graphics mode or timing parameters"	
		eval $CMD
		
		echo "Enable HDMI VENC"
		echo 1 > /sys/devices/platform/vpss/display0/enabled
		echo "Enable graphics0 pipeline"
		echo 1 > /sys/devices/platform/vpss/graphics0/enabled

		#Set framebuffer resolution 
		fbset -xres ${XRES} -yres ${YRES} -vxres ${XRES} -vyres ${YRES} 

        #echo "Loading DSP Firmware"
        #modprobe cmemk phys_start=0x8E000000 phys_end=0x93000000
        #firmware_loader $DSP_ID $FIRMWARE_PATH/dm814x_c6xdsp.xe674 start ${MEMMAP}


              ;;
    stop)
        echo "Unloading HDVICP2 Firmware"
        firmware_loader $HDVICP2_ID $FIRMWARE_PATH/dm814x_hdvicp.xem3 stop ${MEMMAP}
        echo "Unloading HDVPSS Firmware"
        rmmod tlc59108
        rmmod ti81xxhdmi
        rmmod ti81xxfb
        rmmod vpss
        firmware_loader $HDVPSS_ID $FIRMWARE_PATH/dm814x_hdvpss.xem3 stop ${MEMMAP}
        rm /tmp/firmware.$HDVPSS_ID
        rmmod syslink
      ;;
    *)
        echo "Usage: /etc/init.d/load-hd-firmware.sh {start|stop}"
        exit 1
        ;;
esac

exit 0

