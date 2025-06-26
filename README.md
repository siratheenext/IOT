Smart Temperature Monitoring System for Home-Alone Patients
This project is inspired by our university IoT lab course (ITDS282), and was developed to address the critical need for remote health monitoring—especially for patients who live alone and may not be able to seek help in emergencies.

🔍 Project Overview
The Smart Temperature Monitoring System continuously measures a patient’s body temperature using the DHT22 sensor connected to an ESP32 microcontroller. If the temperature exceeds 39°C (a high-fever threshold that may signal serious risk such as shock or unconsciousness), the system performs the following actions:

Triggers a visible LED alert

Starts a timer using the RTC module (DS3231)

Sends real-time data (temperature, humidity, and fever duration) to the cloud via MQTT protocol

Displays these values on a Blynk dashboard

Allows users to stop the timer by pressing a physical button when help has arrived

This system ensures that even patients in isolation can receive timely attention if critical conditions are detected.

🧠 Features
Real-time temperature & humidity monitoring

RTC-based fever duration tracking

LED emergency indication

Remote monitoring via Blynk App

Integration with Node-RED and MQTT

Push button to stop the alert manually

🧰 Technologies Used
ESP32

DHT22 temperature & humidity sensor

DS3231 RTC module

LED & tactile switch

Node-RED

Blynk IoT Platform

MQTT Protocol

Arduino IDE (C++)

🧪 Use Case
Imagine an elderly or COVID-19 patient staying at home alone. The system automatically detects high fever, begins recording how long it persists, and shows the data live on a dashboard that can be monitored by family or caregivers. This provides peace of mind and faster response in emergencies.
