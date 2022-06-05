;FDS Registers Macros.
;This file is to help with the FDS Register Bytes and Addresses.
.ifndef FDS_INC      ; setup a define so we can use it for including in files.
.define FDS_INC 1    
;-------------------------------------------------
;                     $402x bytes are read only.
;notes: Whenever $4022 (FDS_IRQ_CONTROL) is written with bit 1 [xxxx xxx1] IRQ is set, and reload value is copied into the IRQ's Counter. 
;Counter is decremented by 1 cpu cycle if the enable flag is set.
;If the counter value is 0 and IRQ Enable Flag is set to 1. 
;An IRQ is generated. IRQ counter is reset to it's reload value in FDS_IRQ_RELOAD_LOW & FDS_IRQ_RELOAD_HI. 
;If IRQ repeat flag is not set then IRQ enabled flag is cleared to 0 and the counter stops.
;--------------------------------------------------
;                     $402x IRQ Registers.        
;--------------------------------------------------
FDS_IRQ_RELOAD_LOW	    = $4020 ;8 bits of IRQ reload value low. [is used as a reset value for IRQ Counter]
FDS_IRQ_RELOAD_HI	    = $4021 ;8 bits of IRQ reload value hi.  [is used as a reset value for IRQ Counter]
FDS_IRQ_CONTROL		    = $4022 ;lower 2 bits for IRQ control.

FDS_MASTER_IO_ENA	    = $4023
FDS_WRITE_DATA_REG	    = $4024
FDS_CONTROL			    = $4025
FDS_EXTERNAL_CONNECT    = $4026


;--------------------------------------------------
;       FDS Controls bits. (some bits keep set on 1)
;INFO FROM: https://www.nesdev.org/wiki/Family_Computer_Disk_System
;Legend:             IS1BMRTD
;I (Interupt Transfer) 0: Transfer without using IRQ.| 1: Enable IRQ when the drive is ready for a Transfer
; S (Read/Write Start) Turn on motor. Set to 1 when drive becomes ready for read/write. [use this instead of manually turning on and off the FDS motor bit.]
;  1 (Keep bit on 1) Keep this bit on 1 at all times.
;   B (CRC control) Set during CRC calculation of transfer.
;    M (Mirroring) 0: for Virtical | 1: for Horizontal.
;     R (Read/Write Mode) 0: Write mode set | 1: Read mode set
;      T (Transfer reset) set to 1 to reset transfer timing to inital state.
;       D (Drive motor Control)
;---------------------------------------------------
FDS_SET_MOTOR_ON_V =  #%00100011 ; turn on the Motor on the FDS.   (Normally isn't used manually but is here for convenience)
FDS_SET_MOTOR_OFF_V=  #%00100010 ; turn off the Motor on the FDS.  (Normally isn't used manually but is here for convenience)
FDS_SET_MOTOR_ON_M =  #%00101011 ; turn on the Motor on the FDS.   (Normally isn't used manually but is here for convenience)
FDS_SET_MOTOR_OFF_M=  #%00101010 ; turn off the Motor on the FDS.  (Normally isn't used manually but is here for convenience)
FDS_INIT_V_MIRROR =   #%11110111 ; Turn every bit to 1 except for the 4th bit to turn on virtical mirroring. (used for initalization.)
FDS_INIT_M_MIRROR =   #%11111111 ; Turn every bit on. (used for initalization.)
;---------------------------------------------------


;---------------------------------------------------
;           Famicom Disk System BIOS Bytes.
;---------------------------------------------------
FDS_LOAD_BIOS_BYTE_F9   = $F9
FDS_LOAD_BIOS_BYTE_FA   = $FA
FDS_LOAD_BIOS_BYTE_FB   = $FB
FDS_LOAD_BIOS_BYTE_FC   = $FC
FDS_LOAD_BIOS_BYTE_FD   = $FD
FDS_LOAD_BIOS_BYTE_FE   = $FE
FDS_LOAD_BIOS_BYTE_FF   = $FF
;---------------------------------------------------
;TODO: setup other registers and bytes for ease of use.
;For now this file is done.
;---------------------------------------------------