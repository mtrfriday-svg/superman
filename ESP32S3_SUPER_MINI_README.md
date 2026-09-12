# ESP32-S3 Super Mini board added

A new board has been added at `main/boards/esp32-s3-super-mini/` wired exactly
to your pinout:

| Device            | GPIO |
|-------------------|------|
| OLED SDA          | 8    |
| OLED SCL          | 9    |
| INMP441 WS        | 2    |
| INMP441 SCK       | 3    |
| INMP441 DIN       | 4    |
| MAX98357A DOUT    | 5    |
| MAX98357A BCLK    | 6    |
| MAX98357A LRCK    | 7    |
| LED               | 48   |
| Wake/Boot button  | 1    |
| Volume +          | 10   |
| Volume -          | 11   |

It's a copy of the stock "Bread Compact Wi-Fi" board (same audio/display
stack, all the same firmware features — WiFi, MCP tools, OTA, wake word,
etc.), just repointed to your pins, and with the capacitive touch-to-talk
button removed since you don't have one wired up. Target chip: ESP32-S3.

Three build variants exist depending on which OLED you actually have:
- `esp32-s3-super-mini-128x64` — SSD1306 128x64 **(this is yours — grab this artifact)**
- `esp32-s3-super-mini` — SSD1306 128x32
- `esp32-s3-super-mini-sh1106` — SH1106 128x64

## Chip-specific fixes (from your `43007.jpg` chip info)

Your module reports **ESP32-S3 (QFN56), 4MB embedded flash (XMC), 2MB embedded
PSRAM**. The project's stock defaults assume a 16MB-flash, Octal-PSRAM chip —
which is a *different* silicon variant than yours and would fail to boot
(PSRAM init would fail, and the 16MB partition table wouldn't even fit on a
4MB chip). All three build variants for this board now override that with:
- `CONFIG_SPIRAM_MODE_QUAD=y` (your PSRAM is Quad, not Octal)
- `CONFIG_ESPTOOLPY_FLASHSIZE_4MB=y`
- A 4MB partition table (`partitions/v2/4m.csv`)

One tradeoff of the 4MB layout: it has a single "factory" app slot instead of
the usual A/B OTA slots (4MB isn't enough room for two full copies of the
firmware). Everything else — WiFi, voice, MCP tools, display — works
normally; over-the-air self-updates are just not available on this variant,
you'd reflash manually for updates.

## Building with no computer (phone-only)

This project uses ESP-IDF (not Arduino), so it can't be compiled directly on
a phone. But the repo already ships a GitHub Actions workflow
(`.github/workflows/build.yml`) that compiles every board — including this
new one — in the cloud on every push, and uploads the firmware as a
downloadable artifact. That's the phone-friendly path:

1. On GitHub (mobile app or mobile browser), create a new repository and
   upload the contents of this zip to it (or push it from any machine you
   have brief access to, or ask a friend to `git push` it once).
2. Pushing to `main` triggers the Actions workflow automatically. Under the
   repo's **Actions** tab, wait for the "Build Boards" run to finish — open
   the job named `esp32-s3-super-mini` (or the `-128x64` / `-sh1106` variant
   matching your OLED).
3. Download that job's artifact zip — it contains `merged-binary.bin`, a
   single flashable image (bootloader + partition table + app already
   merged).

## Flashing from a phone

You'll need a USB-C OTG adapter/cable to connect the ESP32-S3 to your phone.
Espressif's official web flasher works over WebSerial in Chrome for Android:

- Open https://espressif.github.io/esptool-js/ in Chrome on your phone.
- Connect the board via the OTG cable, tap **Connect**, and pick the device
  when prompted.
- Put the board in download mode (hold BOOT/GPIO0 while tapping RESET, if
  your Super Mini board has those buttons — most do, separate from the
  GPIO1 "wake" button we wired above).
- Flash `merged-binary.bin` at offset `0x0`.

If Chrome doesn't offer a serial permission prompt, your phone/cable may not
support USB OTG serial passthrough — some phones and cheap OTG cables don't.

## One thing to double check

The onboard LED on many "ESP32-S3 Super Mini" clone boards at GPIO48 is
actually an addressable WS2812 RGB LED, not a plain on/off LED. This board
config treats it as a simple GPIO LED, matching what you specified. If it
behaves oddly (stays a weird color, doesn't blink as expected), let me know
and I can switch it to the WS2812 driver instead.
