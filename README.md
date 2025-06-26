# 🧠 Smart Temperature Monitoring System for Home-Alone Patients

This project is inspired by our university IoT lab course (**ITDS282**), and was developed to address the critical need for remote health monitoring — especially for patients who live alone and may not be able to seek help in emergencies.

---

## 📘 Project Overview

The **Smart Temperature Monitoring System** continuously measures a patient’s body temperature using a **DHT22 sensor** connected to an **ESP32 microcontroller**. If the temperature exceeds **39°C**, which is considered a dangerous fever level, the system will:

- 🔴 Trigger a **visible LED alert**
- ⏱️ Start a **timer** using the **RTC module (DS3231)**
- 📤 Send real-time data (temperature, humidity, and fever duration) to the cloud using **MQTT**
- 📱 Display data on a **Blynk dashboard**
- 🛑 Allow users to stop the alert by pressing a **physical button** when help has arrived

This ensures patients in isolation can receive timely attention if critical conditions are detected.

---

## ✨ Features

- 🌡️ Real-time **temperature & humidity monitoring**
- ⏲️ RTC-based **fever duration tracking**
- 🚨 **LED emergency indication**
- 🌐 Remote monitoring via **Blynk App**
- 🔗 Integration with **Node-RED** and **MQTT**
- 🧷 Push button to **manually stop the alert**

---

## 🧰 Technologies Used

- **ESP32**
- **DHT22** Temperature & Humidity Sensor
- **RTC DS3231**
- **Tactile Button** for manual stop
- **LED Indicator**
- **Node-RED** for data flow
- **MQTT Protocol**
- **Blynk IoT Platform**

---

## 🩺 Use Case Scenario

> Imagine an elderly patient or someone recovering from a virus like COVID-19 staying home alone.  
> If their body temperature spikes to 39°C, the system triggers an alert, starts counting how long the fever lasts,  
> and displays everything live to a remote caregiver’s Blynk dashboard.  
> A button is also available for the patient to stop the alert once help is received.

---

Would you like me to help write a **setup guide**, **circuit diagram**, or **code usage section** next?

