import serial
import time

# Configure this for your serial port settings
SERIAL_PORT = '/dev/ttyUSB0'  # Replace with your COM port
BAUD_RATE = 115200
EOT = b'EOFEOF'

def hexdump():
    # Open the serial port and the file
    with serial.Serial(SERIAL_PORT, BAUD_RATE) as ser, open('eeprom_dump.bin', 'wb') as file:
        time.sleep(2)  # Wait for Arduino to reset
        ser.write(b'P')
        buffer = b''
        
        while True:
            # Read a byte
            data = ser.read(1)

            # Add the incoming byte to the buffer
            buffer += data

            # Check if the buffer contains the EOT signal
            if EOT in buffer:
                # Find the position where EOT starts
                eot_index = buffer.index(EOT)
                # Write the data before EOT to the file and break the loop
                file.write(buffer[:eot_index])
                break
            else:
                # If buffer is large enough, write to file and clear buffer
                if len(buffer) >= 16:
                    file.write(buffer)
                    buffer = b''
                    
def writeData():
    with serial.Serial(SERIAL_PORT, BAUD_RATE) as ser:
        time.sleep(2)  # Wait for Arduino to reset
        ser.write(b'W')

def main():
    # hexdump()
    writeData()

if __name__ == '__main__':
    main()