.import nmi_handler, reset_handler, irq_handler

.segment "INESHDR"
  .byte "NES",$1A  ; magic signature
  .byte 1          ; PRG ROM size in 16384 byte units
  .byte 1          ; CHR ROM size in 8192 byte units
  .byte $00        ; mirroring type and mapper number lower nibble
  .byte $00        ; mapper number upper nibble

.segment "VECTORS"
.addr nmi_handler, reset_handler, irq_handler


