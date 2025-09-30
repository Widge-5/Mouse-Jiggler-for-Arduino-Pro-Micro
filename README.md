# Pro Micro Mouse Jiggler

Is your work computer snitching on you? Reporting you as idle if you don't happen to touch it for a few minutes?

If so, then perhaps you need a **Mouse Jiggler**™️!  But what do you do if you can't trust that little USB device from eBay not to be a corporate espionage device?  Well, make your own of course!

Here's my fully transparent and customisable **Arduino Pro Micro** sketch, designed to prevent your computer from going idle by simulating tiny, invisible mouse movements at regular intervals.  

Unlike software jigglers, this works entirely in hardware, so it doesn’t require installing or running anything on your PC. And the code is all here for you to see, so you can be sure that it does exactly what it should be doing *and nothing else!*

Note: This will present to your computer as "**HID-compliant mouse**" in the "*Mice and other pointing devices*" section of device manager, but will also show up as an **Arduino Leonardo** in the "*Ports (COM & LPT)*" section. It's not possible to hide this in a sketch.

---

## ✨ Features
- **Invisible jiggle**: moves the mouse a couple of pixels to the right and back again, quickly enough to be imperceptible to humans.
- **Configurable interval**: This is set to **4 minutes 55 seconds** by default, chosen specifically because many corporate systems report an "away" status after 5 minutes of inactivity.  
- **Heartbeat LED**: the **RX LED** blinks every few seconds to show the device is alive.  The pulse rate is configurable.
- **Activity LED**: the **TX LED** blinks a few times each time the jiggle occurs to let you know it did its thing. The amount of blinks is configurable.  
- **Host detection**: LEDs stay off and the jiggler remains idle when no host computer is connected. Useful if you have it connected to a powered hub, so the device isn't constantly blinking when the computer isn't present.  
- **Compact & discrete**: works great with [this 3D printed Pro Micro case with LED windows](https://makerworld.com/en/models/1819192-arduino-pro-micro-case-press-fit-w-led-windows#profileId-1941644).
- **No soldering**: Or any other electronics jiggery-pokery for that matter. This makes use of the LEDs already present on the Arduino Pro Micro board. just flash the sketch to the board and go!
---

## ⚙️ Customisation

At the top of the sketch, you’ll find the configuration section:

```cpp
// == SET YOUR SPECIFIC VALUES HERE ===========================
// ||                                                        ||
// || When active, how often should we wait between jiggles? ||
      constexpr int periodicityMinutes = 4;  // in minutes   ||
      constexpr int periodicitySeconds = 55; // and seconds  ||
// ||                                                        ||
// || How many pixels should we jiggle?                      ||
      constexpr int jiggle = 2;
// ||                                                        ||
// || How fast should we jiggle (in milliseconds)            ||
// || This is the delay between when the mouse is moved to   ||
// || the right and back to the left. A shorter delay makes  ||
// || it less perceptible to humans, but too short can cause ||
// || it to also fail to register to the computer. Increase  ||
// || this value if the jiggle fails to prevent inactivity.  ||
      constexpr int jiggleFreeze = 5;
// ||                                                        ||
// || When we jiggle, how many times should we blink the TX  ||
// || light?                                                 ||
      constexpr int blinks = 3;
// ||                                                        ||
// || When active, How often should we pulse the RX light to ||
// || indicate life? (in seconds                             ||
      constexpr int heartbeat = 2;
// ||                                                        ||
// || When powered, but no computer is connected, how often  ||
// || should we check for one? (in seconds)                  ||
    constexpr int hostCheck = 10;
// ||                                                        ||
// ============================================================ 
````

You can adjust these values to fit your needs. For example:

* Increase `jiggle` if your system needs larger movement to register.
* Increase `jiggleFreeze` if the computer needs more time to register the movement.
* Change `periodicityMinutes`/`Seconds` if your corporate timeout policy differs.
and so on...

---

## 🔧 Flashing the Sketch

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Open the sketch file (`mousejiggler.ino`) in the IDE.
3. Connect your Pro Micro via USB.
4. Under **Tools → Board**, select **Arduino Leonardo** (the Pro Micro uses the same ATmega32U4 chip).
5. Click **Upload**.

   * The Pro Micro should enumerate as a USB HID device (mouse).
   * If you’ve never used a Pro Micro before, you may need to install drivers for the ATmega32U4 board.

Once flashed, just plug it in – no software or drivers are required on the host machine.

---

## 🧪 Testing & Results

In my testing over several weeks:

* The jiggle is **completely invisible** on screen and does not interfere with normal computer use.
* My computer no longer reports inactivity if I step away for a bathroom break.
* The LEDs give useful feedback without being distracting: heartbeat for “alive”, blink burst for “jiggle”.

---

## 📦 Optional Case

For a neat and discrete build, I recommend this 3D printed case (available free on MakerWorld):

👉 [Arduino Pro Micro Case (press-fit, with LED windows)](https://makerworld.com/en/models/1819192-arduino-pro-micro-case-press-fit-w-led-windows#profileId-1941644)

It’s compact, easy to assemble, and shows the status LEDs through small windows.

---

## ⚠️ Disclaimer

This project is provided as-is, for educational and personal use.
Please use responsibly and respect your organisation’s IT policies.

---

