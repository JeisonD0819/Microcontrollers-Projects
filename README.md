# 📦 Piece Counter System using PIC18F4550

## 📖 Description

This project was developed using the PIC18F4550 microcontroller as part of a microcontrollers course.

The objective was to integrate multiple embedded system concepts into a single industrial-style application: a conveyor belt piece counter.

The system includes:

- PWM motor control
- UART serial communication
- LCD interface
- Keypad configuration
- Ultrasonic sensing
- Analog input through potentiometer

All peripherals were connected directly to the PIC18F4550.

---

# ⚙️ System Features

- 📦 Piece counting system
- ⚡ PWM speed control
- 🎛 Speed adjustment using potentiometer
- 💻 Serial communication control
- 📟 LCD visualization
- ⌨️ Keypad parameter input
- 📏 Ultrasonic distance measurement

---

# 📸 Project Assembly

![Project Assembly](Media/foto_montaje.jpeg)

---

# 🎥 Project Demonstration

[![Project GIF](Media/gif_project.gif)](Media/proyecto_microcontroladores.mp4)

_Click the GIF to open the project video._

---

# 📂 Project Structure

```bash
/project
│── Proyecto/
│   │── debug/
│   │── dist/
│   │── nbproject/
│   │── entregaf.c
│   │── entregarFVF.c
│   │── libLCD.h
│   │── Makefile
│
│── Media/
│   │── foto_montaje.jpeg
│   │── gif_project.gif
│   │── proyecto_microcontroladores.mp4
│
│── README.md
```

---

# 🛠 Hardware Used

| Component | Description |
|---|---|
| PIC18F4550 | Main microcontroller |
| LCD Display | Real-time information |
| Ultrasonic Sensor | Object detection |
| Potentiometer | Manual PWM control |
| Keypad | Parameter configuration |
| DC Motor | Conveyor belt movement |

---

# 💻 Software & Tools

- MPLAB X IDE
- XC8 Compiler
- Embedded C

---

# 🧠 Concepts Applied

This project combines several embedded systems concepts:

- PWM (Pulse Width Modulation)
- ADC (Analog to Digital Conversion)
- UART Communication
- LCD interfacing
- Keypad scanning
- Sensor integration
- Embedded programming
- Real-time control systems

---

# 🔧 System Operation

1. The conveyor belt moves using a DC motor controlled by PWM.
2. The speed can be modified using:
   - A potentiometer
   - Serial communication
3. Objects pass through the sensing area.
4. The ultrasonic sensor detects the pieces.
5. The PIC18F4550 processes the information.
6. The LCD updates the piece counter in real time.
7. Parameters can be configured through the keypad.

---

# 🚀 Future Improvements

- Add EEPROM data storage
- Improve object detection accuracy
- Implement PID motor control
- Add wireless monitoring
- Develop a graphical monitoring interface

---

# 👨‍💻 Authors

- Jeison Nicolas Diaz Arciniegas
- Jorge Emilio Melo