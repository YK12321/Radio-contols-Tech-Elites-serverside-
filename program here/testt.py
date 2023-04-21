import serial
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Open serial port
# ser = serial.Serial('COM1', 9600) # Replace 'COM1' with the name of your serial port and 9600 with the baud rate

# Set up plots
plt.style.use('ggplot')
fig, axs = plt.subplots(nrows=3, ncols=2, figsize=(10, 8), tight_layout=True)
axs[0, 0].set_ylabel('Value 1')
axs[0, 1].set_ylabel('Value 2')
axs[1, 0].set_ylabel('Value 3')
axs[1, 1].set_ylabel('Value 4')
axs[2, 0].set_ylabel('Value 5')
axs[2, 1].set_ylabel('Value 6')
lines = []
for ax in axs.flatten():
    line, = ax.plot([], [], lw=2)
    lines.append(line)

# Initialize data arrays
xdata = [np.array([]) for _ in range(6)]
ydata = [np.array([]) for _ in range(6)]

# Define function to update plots
def update(frame):
    # data = ser.readline().decode().rstrip()
    data = input()
    try:
        values = np.array(list(map(float, data.split(','))))
        for i in range(6):
            xdata[i] = np.append(xdata[i], len(ydata[i]))
            ydata[i] = np.append(ydata[i], values[i])
            lines[i].set_data(xdata[i], ydata[i])
            axs[i//2, i%2].relim()
            axs[i//2, i%2].autoscale_view()
        return lines
    except ValueError:
        return []

# Animate the plots
ani = FuncAnimation(fig, update, blit=True)
plt.show()
