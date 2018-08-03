    .text
    .align  2
    .globl  user_bootloader
    .ent    user_bootloader
user_bootloader:
    .set noreorder
    nop                     # 0x0  -- 0
    li  $4, 0x10000000      # 0x4  -- 4: load hi-16
    ori $4, $4, 0x18        # 0x8  -- 8: load lo-16
    lw  $5, 0($4)           # 0xc  -- 12
    jr  $5                  # 0x10 -- 20
    nop                     # 0x14 -- 16
    # place address here    # 0x18 -- 24: 0x10000018
    .set reorder
    .end user_bootloader
