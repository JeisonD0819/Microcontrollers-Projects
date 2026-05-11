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

### Preview

![Project GIF](Media/gifProject.gif)

### Full Video

[▶️ Watch Project Video](Media/Proyecto_Microcontroladores.mp4)

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
│   │── gifProject.gif
│   │── Proyecto_Microcontroladores.mp4
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

# 🚀 Future Improvements

- Add EEPROM data storage
- Improve object detection accuracy
- Implement PID motor control
- Add wireless monitoring

---

# 👨‍💻 Author

Developed as part of a Microcontrollers course project using the PIC18F4550.