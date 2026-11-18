
from ultralytics import YOLO
from pathlib import Path
import serial
folder = Path(__file__).resolve().parent
image = folder / "birou.jpg"
model = YOLO("yolo11n.pt")
uart = serial.Serial("/dev/serial0", 115200, timeout=1)
results = model(str(image))
objects = []
for result in results:
    for box in result.boxes:
        clasa = int(box.cls[0])
        nume = model.names[clasa]
        objects.append(nume)
print("Obiecte detectate:", objects)
if len(objects) >= 5:
    mesaj = "MESSY"
else:
    mesaj = "CLEAN"
uart.write((mesaj + "\n").encode("utf-8"))
print("Mesaj transmis:", mesaj)
uart.close()