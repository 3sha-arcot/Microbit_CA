from microbit import accelerometer, sleep
import radio

# ─── Configuration ────────────────────────────────────────────────
DEAD_ZONE   = 400    # ignore small jitters (±DEAD_ZONE)
ZONE_HIGH   = 800    # above this raw tilt → high speed
SPEED_LOW   = 70    # moderate tilt yields this PWM value
SPEED_HIGH  = 100    # strong tilt yields this PWM value

SEND_DELAY  = 50     # ms between transmissions

# ─── Radio Setup ─────────────────────────────────────────────────
radio.on()
radio.config(group=1, power=7)  # all boards in group 1 talk together

# ─── Helper ──────────────────────────────────────────────────────
def zone_speed(val):
    """
    Convert raw tilt (–1024…+1024) into one of:
      0, ±SPEED_LOW, or ±SPEED_HIGH
    """
    if val == 0:
        return 0
    sign = 1 if val > 0 else -1
    mag = abs(val)
    return sign * (SPEED_HIGH if mag >= ZONE_HIGH else SPEED_LOW)

# ─── Main Loop ───────────────────────────────────────────────────
while True:
    # 1) Read raw accelerometer values
    raw_x = accelerometer.get_x()
    raw_y = accelerometer.get_y()

    # 2) Apply dead-zone to filter out tiny tilts
    if abs(raw_x) < DEAD_ZONE:
        raw_x = 0
    if abs(raw_y) < DEAD_ZONE:
        raw_y = 0

    # 3) Convert raw to discrete speeds
    xs = zone_speed(raw_x)  # controls turning
    ys = zone_speed(raw_y)  # controls forward/back

    # 4) Initialize motor commands
    LSpeed = 0
    RSpeed = 0

    # 5) Straight forward/backward
    if   ys < 0 and xs == 0:
        # forward
        LSpeed = RSpeed = abs(ys)
    elif ys > 0 and xs == 0:
        # backward
        LSpeed = RSpeed = -abs(ys)

    # 6) In-place pivots (no translation)
    elif xs > 0 and ys == 0:
        LSpeed = 65
        RSpeed = -65
    elif xs < 0 and ys == 0:
        # pivot left
        LSpeed =  -65
        RSpeed = 65

    # 7) Forward arcs (combined translation + turning)
    elif ys < 0 and xs != 0:
        base = abs(ys)
        turn = abs(xs)
        if xs > 0:
            if xs==70 :
                LSpeed = abs(ys) + 5
                RSpeed = abs(ys) - 5
            elif xs==140 :
                LSpeed = abs(ys) + 25
                RSpeed = abs(ys) - 5
        else:
            if xs==-70 :
                LSpeed = abs(ys) - 5
                RSpeed = abs(ys) + 5
            elif xs==-140 :
                LSpeed = abs(ys) - 25
                RSpeed = abs(ys) + 5

    # 8) Backward arcs
    elif ys > 0 and xs != 0:
        base = abs(ys)
        turn = abs(xs)
        if xs > 0:
            if xs==70 :
                LSpeed = -ys - 5
                RSpeed = -ys + 5
            elif xs==140 :
                LSpeed = -ys - 25
                RSpeed = -ys + 5
        else:
            if xs==-70 :
                LSpeed = -ys + 5
                RSpeed = -ys - 5
            elif xs==-140 :
                LSpeed = -ys + 25
                RSpeed = -ys - 5

    # 9) Transmit as "LSpeed,RSpeed"
    radio.send("{},{}".format(LSpeed, RSpeed))

    # 10) Wait a moment
    sleep(10)
