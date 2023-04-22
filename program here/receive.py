import serial
import matplotlib.pyplot as plt
import math
import numpy as np
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

axs[0, 0].set_xlabel('Time')
axs[0, 0].set_ylabel('Acceleration')

axs[0, 1].set_xlabel('Time')
axs[0, 1].set_ylabel('Humidity')

axs[1, 0].set_ylabel('Time')
axs[1, 0].set_ylabel('Pressure')

axs[1, 1].set_ylabel('Time')
axs[1, 1].set_ylabel('Temperature')

axs[2, 0].set_ylabel('Time')
axs[2, 0].set_ylabel('Air Pollution')

axs[2, 1].set_ylabel('Time')
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

aabs = 0.0
temp = 0.0
humid = 0.0
pres = 0.0
uv = 0.0
airQuality = 0.0
counter = 0.0

plt.show(block = False)

while True:
    #0     1      2     3         4         5   6
    #time, accel, temp, humidityT, pressure, uv, ppm
    data = serialport.readline().decode("ascii")
    print(data)
    if data.find("Rover mode") != -1:
        print("ROVER MODE")
        break
    # data = input()
    # print(data)
    try:

        values = str(data).split(',')
        if len(values) < 7:
            continue
        if len(time) > 0 and float(values[0]) <= float(time[-1]):
            continue
        counter += 1
        time.append(float(values[0]))
        height.append(press_to_height(float(values[4]), float(values[2])))
        print("Height:", press_to_height(float(values[4]), float(values[2])))

        aabs += float(values[1])
        temp += float(values[2])
        humid += float(values[3])
        pres += float(values[4])
        uv += float(values[5])
        airQuality += float(values[6])


        acceleration.append(float(values[1]))
        humidity.append(float(values[3]))
        pressure.append(float(values[4]))
        temperature.append(float(values[2]))
        pollution.append(float(values[6]))
        radiation.append(float(values[5]))
        lines[0].set_data(time, acceleration)
        axs[0, 0].relim()
        axs[0, 0].autoscale_view()

        lines[1].set_data(time, humidity)
        axs[0, 1].relim()
        axs[0, 1].autoscale_view()

        lines[2].set_data(time, pressure)
        axs[1, 0].relim()
        axs[1, 0].autoscale_view()

        lines[3].set_data(time, temperature)
        axs[1, 1].relim()
        axs[1, 1].autoscale_view()

        lines[4].set_data(time, pollution)
        axs[2, 0].relim()
        axs[2, 0].autoscale_view()

        lines[5].set_data(time, radiation)
        axs[2, 1].relim()
        axs[2, 1].autoscale_view()
        # for i in range(6):
        #     xdata[i].append(int(values[i]))
        #     ydata[i].append(int(values[i]))
        #     lines[i].set_data(xdata[i], ydata[i])
        #     axs[i//2, i%2].relim()
        #     axs[i//2, i%2].autoscale_view()
        plt.draw()
        plt.pause(1)

    except ValueError:
        break

aabs = aabs/counter
temp = temp/counter
humid = humid/counter
uv = uv/counter
pres = pres/counter
airQuality = airQuality/counter

if (aabs > 19.62):
    print("The Gravitational Pull is " + str(aabs) + " too strong for Human Growth")
elif (aabs < 5.00):
    print("The Gravitational Pull is " + str(aabs) + " too weak for Human Growth")
else:
    print("The Gravivational Pull is " + str(aabs) + " and is suitable for Human Growth")

if (temp > 50):
    print("The Temperature is " + str(temp) + " too high for Human Growth")
elif (temp < -20):
    print("The Temperature is " + str(temp) + " too low for Human Growth")
else:
    print("The Temperature is " + str(temp) + " and is suitable for Human Growth")

if (humid > 65):
    print("The Humidity is " + str(humid) + " too high for Human Growth")
elif (humid < 20):
    print("The Humidity is " + str(humid) + " too low for Human Growth")
else:
    print("The Humidity is " + str(humid) + " and is suitable for Human Growth")

if (uv > 11):
    print("The UV Radiation is " + str(uv) + " too high for Human Growth")
else:
    print("The UV Radiation is " + str(uv) + " suitable for Human Growth")

if (pres > 202.650):
    print("The Pressure is " + str(pres) + " too high for Human Growth")
elif (pres < 6.3):
    print("The Pressure is " + str(pres) + " too low for Human Growth")
else:
    print("The Pressure is " + str(pres) + " and is suitable for Human Growth")

if (airQuality > 800):
    print("The Air Quality is " + str(airQuality) + " too high for Human Growth")
else:
    print("The Air Quality is " + str(airQuality) + " and is suitable for Human Growth")
arr1 = np.array(height)
arr2 = np.array(acceleration)
arr3 = np.array(humidity)
arr5 = np.array(temperature)
arr6 = np.array(pollution)
arr7 = np.array(radiation)
np.savetxt("height.txt", arr1, fmt='%.2f')
np.savetxt("acceleration.txt", arr2, fmt='%.2f')
np.savetxt("humidity.txt", arr3, fmt='%.2f')
np.savetxt("temperature.txt", arr5, fmt='%.2f')
np.savetxt("pollution.txt", arr6, fmt='%.2f')
np.savetxt("radiation.txt", arr7, fmt='%.2f')

