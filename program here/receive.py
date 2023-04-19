import serial
import matplotlib.pyplot as plt

# Open serial port
serialport = serial.Serial('COM5', baudrate = 9600, timeout = 2) # Replace 'COM1' with the name of your serial port and 9600 with the baud rate

# Set up plots
plt.style.use('ggplot')
fig, axs = plt.subplots(nrows=3, ncols=2, figsize=(10, 8))
axs[0, 0].set_ylabel('Value 1')
axs[0, 1].set_ylabel('Value 2')
axs[1, 0].set_ylabel('Value 3')
axs[1, 1].set_ylabel('Value 4')
axs[2, 0].set_ylabel('Value 5')
axs[2, 1].set_ylabel('Value 6')
lines = []
for ax in axs.flatten():
    line, = ax.plot([], [])
    lines.append(line)

# Read and plot data from serial port in real-time
xdata = [ [] for i in range(6) ]
ydata = [ [] for i in range(6) ]
plt.show(block=False)
while True:
    data = serialport.readline().decode("ascii")
    print(data)
    try:
        values = str(data)
        print(values)
        for i in range(6):
            xdata[i].append(int(values[i]))
            ydata[i].append(int(values[i]))
            lines[i].set_data(xdata[i], ydata[i])
            axs[i//2, i%2].relim()
            axs[i//2, i%2].autoscale_view()
        plt.draw()
        plt.pause(0.5)
    except ValueError:
        pass


