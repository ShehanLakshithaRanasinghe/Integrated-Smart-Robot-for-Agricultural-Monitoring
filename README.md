# 🤖 Integrated Smart Robot System for Agricultural & Environmental Monitoring  

[![Status](https://img.shields.io/badge/Project-Completed-green)]()  
[![Platform](https://img.shields.io/badge/Platform-Arduino%20%7C%20LabVIEW-blue)]()  
[![Sensors](https://img.shields.io/badge/Sensors-LM35%20%7C%20LDR%20%7C%20VL53L0X%20%7C%20Custom%20Water%20Level-orange)]()  
[![Functions](https://img.shields.io/badge/Functions-Grass%20Cutting%20%7C%20Watering%20%7C%20Navigation-yellow)]()  

An autonomous **multi-functional robot** designed for **agricultural and environmental monitoring**.  
This project integrates **hardware, software, and instrumentation principles** to automate grass cutting, smart watering, obstacle detection, and environmental sensing.  

---

##  Core Functionalities  

###  Grass Cutting Automation  
- Blade activates automatically when the robot moves forward.  
- Deactivates during stops or directional turns.  
- Controlled by **Arduino Uno** logic + **LabVIEW sequencing**.  

###  Intelligent Watering System  
- **Two modes**:  
  - *Manual*: Triggered via a LabVIEW virtual switch.  
  - *Automatic*: Based on sensor data (temperature, humidity, light).  
- Default watering duration: **60s**, adjustable via a custom timer.  

###  Obstacle Detection & Navigation  
- **Sensors**: Four VL53L0X ToF sensors (2 front, 2 sides).  
- Behavior:  
  - If obstacle < 20 cm → turn left/right.  
  - If obstacle < 10 cm → stop.  
- Decision-making handled by **Arduino Uno**, motor control via **LabVIEW interface**.  
- Includes **manual navigation buttons** in LabVIEW for operator override.  

###  Custom Conductive Water Level Sensor  
- 3-step water level detection using conductive probes.  
- Calibrated for accuracy.  
- Levels displayed as **Boolean indicators** on the LabVIEW dashboard.  


---

##  Hardware Components  

- **Arduino Uno** – Core controller  
- **LM35 Sensor** – Temperature monitoring  
- **LDR** – Ambient light measurement  
- **Humidity Sensor** – Environmental tracking  
- **VL53L0X Sensors (x4)** – Obstacle detection  
- **DC Motors + Drivers** – Navigation system  
- **Relay / Driver Circuit** – Grass cutting blade  
- **Pump + Custom Conductive Sensor** – Watering system  

---

##  Software & Tools  

- **Arduino IDE** (programming microcontroller)  
- **LabVIEW** (UI, control logic, visualization)  
- **NI DAQ Interface** (for data monitoring)  
- **Serial Communication (UART)** for Arduino ↔ LabVIEW  

---

##  Usage  

1. Power on the robot and initialize the **Arduino Uno**.  
2. Launch **LabVIEW Dashboard** to monitor and control.  
3. Choose operation mode:  
   - *Autonomous*: Robot navigates, cuts grass, and waters plants automatically.  
   - *Manual*: Control via LabVIEW buttons.  
4. Monitor:  
   - Sensor values (temperature, humidity, light).  
   - Water level indicators.  
   - Obstacle detection status.  

---

##  Demonstration  

- ✅ Automatic grass cutting while moving forward  
- ✅ Obstacle avoidance & safe navigation  
- ✅ Watering triggered automatically / manually  
- ✅ Real-time environmental monitoring via LabVIEW  

---

##  Future Enhancements  

- Add **solar panel power system** for sustainability.  
- Integrate **wireless communication (Wi-Fi / IoT dashboard)**.  
- Deploy **machine learning models** for predictive watering.  
- Multi-compartment water tank for **fertilizer spraying**.  

---

