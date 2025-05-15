from microbit import display, sleep, uart, pin0
import radio

# Start radio
radio.on()
radio.config(group=1, power=7)

# Set up UART on P0 (TX)
uart.init(baudrate=9600, tx=pin0)

while True:
    packet = radio.receive()
    if packet:
        parts = packet.split(",")
        if len(parts) == 2:
            try:
                x = int(parts[0])
                y = int(parts[1])

                # Send x and y over UART as "x y\n"
                message = str(x) + " " + str(y) + "\n"
                uart.write(message)
            except ValueError:
                pass
    sleep(100)
