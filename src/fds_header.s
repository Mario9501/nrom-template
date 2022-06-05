;Setup Bypass here so we don't reqire the license screen
BYPASS   = 1    ; bypass the license screen
WIPE_RAM = 1    ; wipes unused portion of FDS RAM at startup

; setting the file count 1 higher than files on disk for the license "bypass" technique
FILE_COUNT = 2 + BYPASS

;Header information here
.segment "FDS_HEADER"       ;Call segment FDS_HEADER here for header info.
.byte 'F','D','S',$1A
.byte 1 ; side count
.segment "SIDE1A"
;(Header info for FDS)
.byte $01                   ;block number 1.
.byte "*NINTENDO-HVC*" 
.byte $00                   ; manufacturer
.byte "EXA" ;
.byte $20                   ; normal disk
.byte $00                   ; game version
.byte $00                   ; side
.byte $00                   ; disk
.byte $00                   ; disk type
.byte $00                   ; unknown
.byte FILE_COUNT            ; boot file count
.byte $FF,$FF,$FF,$FF,$FF
.byte $97                   ; 2022
.byte $06                   ; July
.byte $5                    ; 5
.byte $49                   ; country
.byte $61, $00, $00, $02, $00, $00, $00, $00, $00 ; unknown
.byte $92                   ; 2017
.byte $04                   ; april
.byte $17                   ; 17
.byte $00, $80              ; unknown
.byte $00, $00              ; disk writer serial number
.byte $07                   ; unknown
.byte $00                   ; disk write count
.byte $00                   ; actual disk side
.byte $00                   ; unknown
.byte $00                   ; price
.byte $02                   ;Block Number 2
.byte FILE_COUNT

.segment "FILE0_HDR"
; block 3
.import __FILE0_DAT_RUN__
.import __FILE0_DAT_SIZE__
.byte $03
.byte 0,0
.byte "FILE0..."
.word __FILE0_DAT_RUN__
.word __FILE0_DAT_SIZE__
.byte 0                     ; PRG
; block 4
.byte $04
;.segment "FILE0_DAT"
;.incbin "" ; this is FILE0_DAT below
.if (BYPASS <> 0)
; This block is the last to load, and enables NMI by "loading" the NMI enable value
; directly into the PPU control register at $2000.
; While the disk loader continues searching for one more boot file,
; eventually an NMI fires, allowing us to take control of the CPU before the
; license screen is displayed.
.segment "FILE1_HDR"
; block 3
.import __FILE1_DAT_SIZE__
.import __FILE1_DAT_RUN__
.byte $03
.byte 5,5
.byte "FILE1..."
.word $2000
.word __FILE1_DAT_SIZE__
.byte 0 ; PRG (CPU:$2000)
; block 4
.byte $04
.segment "FILE1_DAT"
.byte $90 ; enable NMI byte sent to $2000

.else
; Alternative to the license screen bypass, just put the required copyright message at PPU:$2800.
.segment "FILE1_HDR"
; block 3
.import __FILE1_DAT_SIZE__
.import __FILE1_DAT_RUN__
.byte $03
.byte 5,5
.byte "KYODAKU-"
.word $2800
.word __FILE1_DAT_SIZE__
.byte 2 ; nametable (PPU:$2800)
; block 4
.byte $04
.segment "FILE1_DAT"
.incbin "check.bin"
.endif
;
; FDS vectors
;

