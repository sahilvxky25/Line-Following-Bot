# Line Follower Robot
### Arduino Nano · L293D Motor Driver · 3× IR Sensor · 2× DC Motor

---

## Overview

A two-wheeled autonomous robot that follows a black line on a white surface using three TCRT5000 infrared sensors and an L293D dual H-bridge motor driver controlled by an Arduino Nano. The bot reads left, centre, and right sensor states and adjusts motor speeds in real time to stay on track.

---

## Components

| Qty | Component | Label |
|-----|-----------|-------|
| 1 | Arduino Nano | U1 |
| 1 | L293D Dual H-Bridge Motor Driver IC | U5 |
| 1 | TCRT5000 IR Sensor — Left | U2 |
| 1 | TCRT5000 IR Sensor — Centre | U3 |
| 1 | TCRT5000 IR Sensor — Right | U4 |
| 2 | DC Geared Motor (3–6 V) | M1, M2 |
| 1 | 6 V Battery — Arduino power | BAT1 |
| 1 | 12 V Battery Pack  — Motor power | BAT2 |
| 1 | Robot chassis with 2 wheels + caster | — |
| — | Jumper wires, breadboard | — |

---

## Pin Connections

### IR Sensors → Arduino

| Sensor | Sensor Pin | Arduino Pin |
|--------|-----------|-------------|
| IR Left (U2) | VCC | 5V |
| IR Left (U2) | GND | GND |
| IR Left (U2) | OUT | **D2** |
| IR Centre (U3) | VCC | 5V |
| IR Centre (U3) | GND | GND |
| IR Centre (U3) | OUT | **D3** |
| IR Right (U4) | VCC | 5V |
| IR Right (U4) | GND | GND |
| IR Right (U4) | OUT | **D4** |

> IR sensors output **LOW** when over the black line, **HIGH** on white surface.

---

### Arduino → L293D Motor Driver

| Arduino Pin | Signal | L293D Pin |
|-------------|--------|-----------|
| D5 ~ (PWM) | ENA — Left speed | Pin 1 (1-2EN) |
| D6 | IN1 — Left direction A | Pin 2 (1A) |
| D7 | IN2 — Left direction B | Pin 7 (2A) |
| D8 ~ (PWM) | ENB — Right speed | Pin 9 (3-4EN) |
| D9 | IN3 — Right direction A | Pin 10 (3A) |
| D10 | IN4 — Right direction B | Pin 15 (4A) |

> Pins marked `~` must be PWM-capable. On Arduino Nano, D5, D6, D8 (via D9 swap) qualify. Double-check your board.

---

### L293D Power Pins

| L293D Pin | Connect To | Purpose |
|-----------|-----------|---------|
| Pin 16 (Vss / VCC1) | Arduino **5V** | IC logic supply |
| Pin 8 (Vs / VCC2) | BAT2 **+6V** | Motor power supply |
| Pins 4, 5, 12, 13 (GND) | Common GND | Ground |

---

### L293D → Motors

| L293D Pins | Motor |
|-----------|-------|
| Pin 3 (1Y) + Pin 6 (2Y) | M1 — Left motor |
| Pin 11 (3Y) + Pin 14 (4Y) | M2 — Right motor |

---

### Power & Ground Rail

```
BAT1 (+9V)  ──→  Arduino Vin
BAT1 (−)    ──┐
BAT2 (−)    ──┤──→  Common GND
Arduino GND ──┤
L293D GND   ──┘
IR Sensor GNDs (×3) → Common GND
```

> **Always connect all GND pins to a single common rail.** Floating grounds cause erratic sensor readings and motor misbehaviour.

---

## Logic Table

| IR Left | IR Centre | IR Right | Action |
|---------|-----------|----------|--------|
| 0 | 1 | 0 | Go straight |
| 0 | 0 | 1 | Turn right |
| 1 | 0 | 0 | Turn left |
| 0 | 1 | 1 | Gentle right |
| 1 | 1 | 0 | Gentle left |
| 1 | 1 | 1 | Straight (T-junction) |
| 0 | 0 | 0 | Stop (line lost) |

`1` = sensor over line (LOW signal) · `0` = sensor off line (HIGH signal)

---

## Speed Tuning

Inside the sketch, adjust these three constants to match your track and motors:

```cpp
const int BASE_SPEED  = 180;  // forward speed (0–255)
const int TURN_SPEED  = 220;  // outer wheel during turn
const int SLOW_SPEED  = 80;   // inner wheel during turn
```

Start with `BASE_SPEED = 150` on a first run, then increase once the bot tracks reliably.

---

## Arduino Sketch Summary

```
File   : line_following_bot.ino
Board  : Arduino Nao
Clock  : 16 MHz
Library: None (standard Arduino only)
```

**Key functions:**

| Function | Purpose |
|----------|---------|
| `moveForward(l, r)` | Drive both motors forward at given speeds |
| `moveBackward(l, r)` | Reverse both motors |
| `stopMotors()` | Cut power to both motors |

---

## Assembly Notes

1. Mount IR sensors at the **front underside** of the chassis, spaced ~3 cm apart, roughly 5–10 mm above the surface.
2. Place sensors **symmetrically** about the centre axis — left, centre, right in equal spacing.
3. Run the motor supply (BAT2) wiring with thicker gauge wire (22 AWG minimum) to handle current draw.
4. Keep signal wires (IR OUT lines) away from motor wires to reduce noise.
5. Use a **common ground** node — a small breadboard or terminal block works well.

---


*Built with Arduino Nano + Tinkercad · Schematic: Terrific Leelo-Tumelo*

# Owner
Sahil Kumar Patra, Somya Ranjan Suar
