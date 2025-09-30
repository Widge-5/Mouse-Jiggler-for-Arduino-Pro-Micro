// Pro Micro Mouse Jiggler - by Widge, 2025
// TX LED blinks each jiggle, RX LED heartbeats every 2s
// Both LEDs off if no host is enumerated


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



#include <Mouse.h>
bool stateActive = false;
constexpr unsigned long checkWait = hostCheck *1000UL;
unsigned long previousMillis = 0;
constexpr unsigned long interval = (periodicityMinutes * 60000UL) + (periodicitySeconds * 1000UL);
unsigned long ledMillis = 0;
constexpr unsigned long ledPeriod = heartbeat * 1000UL;
bool ledOn = false;
bool txBlinkActive = false;
int txBlinkCount = 0;
unsigned long txLastToggle = 0;
constexpr unsigned long txBlinkInterval = 200; // ms


static inline bool usbConfigured() {
  // On 32U4 Arduino cores, this reports true once the host has enumerated the CDC device.
  USBDevice.poll();
  return USBDevice.configured() && !USBDevice.isSuspended();
}


void triggerTxBlink() {
  txBlinkActive = true;
  txLastToggle = 0;
  txBlinkCount = 0;
  TXLED0; // ensure OFF before starting
}


void updateTxBlink() {
  if (!txBlinkActive) return;
  unsigned long now = millis();

  if (txLastToggle == 0 || (now - txLastToggle) >= txBlinkInterval) {
    txLastToggle = now;

    // Toggle ON/OFF each call
    if (txBlinkCount % 2 == 0) {
      TXLED1; // ON
    } else {
      TXLED0; // OFF
    }
    txBlinkCount++;

    // Blink away
    if (txBlinkCount >= (blinks *2)) {
      txBlinkActive = false;
      TXLED0; // ensure OFF at the end
    }
  }
}


void jigglypuff() {
  const unsigned long now = millis();

  // --- Heartbeat on RX LED (quick blink to show sketch is alive) ---
  if (now - ledMillis >= ledPeriod) {
    ledMillis = now;
    ledOn = !ledOn;
    if (ledOn) RXLED1; else RXLED0;
    stateActive = usbConfigured();
  }

  // --- Periodic mouse jiggle ---
  if (now - previousMillis >= interval) {
    previousMillis = now;

    Mouse.move(jiggle, 0, 0);
    delay(jiggleFreeze);     // tiny pause so host sees two distinct reports
    Mouse.move(-jiggle, 0, 0);
    triggerTxBlink();
  }
  updateTxBlink();  
}


void setup() {
  TX_RX_LED_INIT;
  TXLED0; RXLED0;
  Mouse.begin();
  stateActive = usbConfigured();
  if (stateActive) previousMillis = millis();
}


void loop() {
  if (stateActive) {
    jigglypuff();
  } else {
    TXLED0;    // TX OFF
    RXLED0;    // RX OFF
    delay (checkWait);
    stateActive = usbConfigured();
    if (stateActive) previousMillis = millis();
  }
}
