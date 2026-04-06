.section .bss
.align 4

.space 0x4

.equ DMA_SAMPLE_BUFFER_SIZE, 1568
.equ SAMPLE_SCRATCHPAD_SIZE, 0x80

.equ N_STREAMS_MUS0, 15
.equ N_STREAMS_MUS1, 12
.equ N_STREAMS_MUS2, 12
.equ N_STREAMS_SFX, 5

.global sPCMBufferArea
sPCMBufferArea:
    .space 2 * DMA_SAMPLE_BUFFER_SIZE

.global sPCMScratchArea
sPCMScratchArea:
    .space 4 * SAMPLE_SCRATCHPAD_SIZE * 2

.global sSamplerArea
sSamplerArea:
    .space 0x180

.global sSoundChannelArea
sSoundChannelArea:
    .space 0x180

.global sMusicPlayer0Channels
sMusicPlayer0Channels:
    .space 0x20 * N_STREAMS_MUS0

.global sMusicPlayer0MidiBus
sMusicPlayer0MidiBus:
    .space 0x28

.global sMusicPlayer0Streams
sMusicPlayer0Streams:
    .space 0x1A8

.global sMusicPlayer1Channels
sMusicPlayer1Channels:
    .space 0x20 * N_STREAMS_MUS1

.global sMusicPlayer1MidiBus
sMusicPlayer1MidiBus:
    .space 0x28

.global sMusicPlayer1Streams
sMusicPlayer1Streams:
    .space 0x150

.global sMusicPlayer2Channels
sMusicPlayer2Channels:
    .space 0x20 * N_STREAMS_MUS2

.global sMusicPlayer2MidiBus
sMusicPlayer2MidiBus:
    .space 0x28

.global sMusicPlayer2Streams
sMusicPlayer2Streams:
    .space 0x150

.global sSfxPlayer0Channels
sSfxPlayer0Channels:
    .space 0x20 * N_STREAMS_SFX

.global sSfxPlayer0MidiBus
sSfxPlayer0MidiBus:
    .space 0x28

.global sSfxPlayer0Streams
sSfxPlayer0Streams:
    .space 0x90

.global sSfxPlayer1Channels
sSfxPlayer1Channels:
    .space 0x20 * N_STREAMS_SFX

.global sSfxPlayer1MidiBus
sSfxPlayer1MidiBus:
    .space 0x28

.global sSfxPlayer1Streams
sSfxPlayer1Streams:
    .space 0x90

.global sSfxPlayer2Channels
sSfxPlayer2Channels:
    .space 0x20 * N_STREAMS_SFX

.global sSfxPlayer2MidiBus
sSfxPlayer2MidiBus:
    .space 0x28

.global sSfxPlayer2Streams
sSfxPlayer2Streams:
    .space 0x90

.global sSfxPlayer3Channels
sSfxPlayer3Channels:
    .space 0x20 * N_STREAMS_SFX

.global sSfxPlayer3MidiBus
sSfxPlayer3MidiBus:
    .space 0x28

.global sSfxPlayer3Streams
sSfxPlayer3Streams:
    .space 0x90

.global sSfxPlayer4Channels
sSfxPlayer4Channels:
    .space 0x20 * N_STREAMS_SFX

.global sSfxPlayer4MidiBus
sSfxPlayer4MidiBus:
    .space 0x28

.global sSfxPlayer4Streams
sSfxPlayer4Streams:
    .space 0x90

.global sSfxPlayer5Channels
sSfxPlayer5Channels:
    .space 0x20 * N_STREAMS_SFX

.global sSfxPlayer5MidiBus
sSfxPlayer5MidiBus:
    .space 0x28

.global sSfxPlayer5Streams
sSfxPlayer5Streams:
    .space 0x90

.global sSfxPlayer6Channels
sSfxPlayer6Channels:
    .space 0x20 * N_STREAMS_SFX

.global sSfxPlayer6MidiBus
sSfxPlayer6MidiBus:
    .space 0x28

.global sSfxPlayer6Streams
sSfxPlayer6Streams:
    .space 0x90

.global sSfxPlayer7Channels
sSfxPlayer7Channels:
    .space 0x20 * N_STREAMS_SFX

.global sSfxPlayer7MidiBus
sSfxPlayer7MidiBus:
    .space 0x28

.global sSfxPlayer7Streams
sSfxPlayer7Streams:
    .space 0x90

.global sSfxPlayer8Channels
sSfxPlayer8Channels:
    .space 0x20 * N_STREAMS_SFX

.global sSfxPlayer8MidiBus
sSfxPlayer8MidiBus:
    .space 0x28

.global sSfxPlayer8Streams
sSfxPlayer8Streams:
    .space 0x90

.global sSfxPlayer9Channels
sSfxPlayer9Channels:
    .space 0x20 * N_STREAMS_SFX

.global sSfxPlayer9MidiBus
sSfxPlayer9MidiBus:
    .space 0x28

.global sSfxPlayer9Streams
sSfxPlayer9Streams:
    .space 0x90
