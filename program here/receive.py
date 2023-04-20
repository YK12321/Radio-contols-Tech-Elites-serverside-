import serial
import matplotlib.pyplot as plt
import math
# Open serial port
serialport = serial.Serial('COM5', baudrate = 9600, timeout = 2)

# Set up plots
plt.style.use('ggplot')
fig, axs = plt.subplots(nrows=3, ncols=2, figsize=(10, 8))

def press_to_height(press, temperature):
    R = 287
    T = temperature
    po = 101
    p = press
    e = 2.71828
    g = 9.81
    h = ((-R * T) / g) * math.log(p / po)
    return h
def total_acceleration(x, y, z):
    return math.sqrt(x**2+y**2+z**2)
# Acceleration vs Height
# Humidity vs Height
# Pressure vs Height
# Temperature vs Height
# Air Pollution vs Height
# UV Radiation vs Height

axs[0, 0].set_xlabel('Height')
axs[0, 0].set_ylabel('Acceleration')

axs[0, 1].set_xlabel('Height')
axs[0, 1].set_ylabel('Humidity')

axs[1, 0].set_ylabel('Height')
axs[1, 0].set_ylabel('Pressure')

axs[1, 1].set_ylabel('Height')
axs[1, 1].set_ylabel('Temperature')

axs[2, 0].set_ylabel('Height')
axs[2, 0].set_ylabel('Air Pollution')

axs[2, 1].set_ylabel('Height')
axs[2, 1].set_ylabel('UV Radiation')

lines = []
for ax in axs.flatten():
    line, = ax.plot([], [])
    lines.append(line)

# Read and plot data from serial port in real-time
# xdata = [[] for i in range(6)]
# ydata = [[] for i in range(6)]
time = []
height = []
acceleration = []
humidity = []
pressure = []
temperature = []
pollution = []
radiation =[]

plt.show(block = False)
while True:
    #0     1      2     3         4         5   6
    #time, accel, temp, humidity, pressure, uv, ppm
    data = serialport.readline().decode("ascii")
    if data == "Rover Mode":
        break
    # data = input()
    print(data)
    try:
        values = str(data).split(',')
        time.append(int(values[0]))
        height.append(press_to_height(values[4], values[2]))
        acceleration.append(values[1])
        humidity.append(values[3])
        pressure.append(values[4])
        temperature.append(values[2])
        pollution.append(values[6])
        radiation.append(values[5])
        lines[0].set_data(height, acceleration)
        axs[0, 0].relim()
        axs[0, 0].autoscale_view()

        lines[1].set_data(height, humidity)
        axs[0, 1].relim()
        axs[0, 1].autoscale_view()

        lines[2].set_data(height, pressure)
        axs[1, 0].relim()
        axs[1, 0].autoscale_view()

        lines[3].set_data(height, temperature)
        axs[1, 1].relim()
        axs[1, 1].autoscale_view()

        lines[4].set_data(height, pollution)
        axs[2, 0].relim()
        axs[2, 0].autoscale_view()

        lines[5].set_data(height, radiation)
        axs[2, 1].relim()
        axs[2, 1].autoscale_view()
        # for i in range(6):
        #     xdata[i].append(int(values[i]))
        #     ydata[i].append(int(values[i]))
        #     lines[i].set_data(xdata[i], ydata[i])
        #     axs[i//2, i%2].relim()
        #     axs[i//2, i%2].autoscale_view()
        plt.draw()
        plt.pause(0.5)
    except ValueError:
        break


