from serial import Serial
# connect just computer port to wavemeter using RS232 adapter
# not used for arduino

ser = Serial()
ser.port     = 'COM7'
ser.baudrate = 19200
ser.open()
print(ser.is_open)

#ser.write(b"*IDN?\n")
#ser.write("*IDN?\n".encode())
# end of line (EOL) character is \n
#print(ser.read(39)) # number of bytes, if larger than output will run loop

### Communicating read and write no matter how long ###
ser.write(b":READ:POWer:WAVelength?\n")
ser_bytes = ser.readline()
decoded_bytes = ser_bytes[0:len(ser_bytes)-1].decode()
print(decoded_bytes)

ser.write(b"*IDN?\n")
ser_bytes2 = ser.readline()
decoded_bytes2 = ser_bytes2[0:len(ser_bytes2)-1].decode()
print(decoded_bytes2)

### Loop ###
while True:
    try:
        ser.write(b":READ:POWer:WAVelength?\n")
        ser_bytes = ser.readline()
        decoded_bytes = ser_bytes[0:len(ser_bytes)-1].decode()
        print(decoded_bytes)
    except:
        print("Keyboard Interrupt")
        break

ser.close()

print("done")
