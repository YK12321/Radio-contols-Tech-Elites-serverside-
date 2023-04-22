import receive
import serial
from PIL import Image, ImageTk
import tkinter as tk
import threading

# Create a Tkinter window
root = tk.Tk()
root.title("Camera Viewer")

# Create a label to display the image
img_label = tk.Label(root)
img_label.pack()

# Open the serial port
ser = serial.Serial('COM23', 1000000)

# Flag to indicate if livestream is running
livestream_running = False


# Function to update the image
def update_image():
    # Send a "c" character to trigger the camera to take and send an image
    data = ""
    # Read the image data from the serial port
    recieved = 0
    while received < 1600*1200:
        inp = ser.readline()
        inp.rstrip(b'\r\n')
        if len(inp) > 0:
            ser.write('received\n')
            data += inp
            received += 1
        else:
            ser.write('resend\n')

    # Create a PIL Image object from the raw image data
    new_img = Image.frombytes('L', (1600, 1200), data)

    # Update the displayed image
    img_tk = ImageTk.PhotoImage(new_img)
    img_label.config(image=img_tk)
    img_label.image = img_tk

    # If livestream is running, schedule another update
    if livestream_running:
        root.after(1, update_image)


# Function to handle button click
def on_click():
    global livestream_running

    # Toggle livestream_running flag
    livestream_running = not livestream_running

    if livestream_running:
        # Start livestream
        livestream_button.config(text="Stop Livestream")
        threading.Thread(target=update_image).start()
    else:
        # Stop livestream
        livestream_button.config(text="Start Livestream")


# Create a button to start/stop the livestream
livestream_button = tk.Button(root, text="Start Livestream", command=on_click)
livestream_button.pack()

# Start the Tkinter main loop
root.mainloop()
