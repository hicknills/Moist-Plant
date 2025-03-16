import serial
import json
import time

SERIAL_PORT = "COM5"  # Change this to match your Arduino port
BAUD_RATE = 9600
OUTPUT_FILE = "moisture_data.json"

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {SERIAL_PORT}")

    with open(OUTPUT_FILE, "a") as file:
        while True:
            line = ser.readline().decode('utf-8').strip()
            if line:
                print(f"Received: {line}")
                try:
                    data = json.loads(line)  # Convert string to JSON
                    data["timestamp"] = time.strftime("%Y-%m-%d %H:%M:%S")  # Add computer's real timestamp

                    file.write(json.dumps(data) + "\n")  # Save to file
                    file.flush()

                except json.JSONDecodeError:
                    print("Invalid JSON format, skipping...")

except serial.SerialException:
    print(f"Could not open {SERIAL_PORT}. Check if the Arduino is connected.")
except KeyboardInterrupt:
    print("\nStopped by user. Data saved to", OUTPUT_FILE)
finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
