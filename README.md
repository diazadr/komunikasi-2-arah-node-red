# Two Way Communication ESP8266 Node-RED

![Project Status](https://img.shields.io/badge/status-completed-brightgreen) [![License](https://img.shields.io/badge/license-MIT-blue)](./LICENSE)

Advanced IoT project using the **MQTT protocol** and **Node-RED dashboard** as part of a **Manufacturing Execution System (MES)** communication simulation. This project demonstrates **two-way communication** between two ESP8266 devices through the **Shiftr.io MQTT broker**, visualized in **Node-RED**.

---

## **Project Overview**

Imagine an electronic assembly factory managed by a **Manufacturing Execution System (MES)** as the central control unit. In this factory, two stations communicate with each other through MQTT, represented by two **ESP8266** devices.

* **Station 1 (ESP DIAZ)**: Controls an **RGB indicator lamp**. The MES (Node-RED) sends color commands, and this station reports the current active color. A **Button A** is used to send a servo position command to the second station.
* **Station 2 (ESP BAYU)**: Controls a **servo motor** to adjust the component’s position. When **Button B** is pressed, it sends a signal to the lamp station to turn off the LED, marking the completion of the process.

All communication runs **in real-time** via **MQTT and Node-RED**, allowing the MES to coordinate both stations efficiently and responsively.

---

## **Components Used**

* ESP8266
* Breadboard
* Push Button
* LED RGB
* Servo Motor SG90
* Node-RED
* Shiftr.io
* Arduino IDE

---

## **Workflows**

### **1. LED Color Control**

1. Node-RED sends a color command to a specific topic.
2. Shiftr.io forwards the message to **ESP DIAZ**.
3. **ESP DIAZ** changes the RGB LED color accordingly.
4. The latest color status is published back to Node-RED and shown on the dashboard.

---

### **2. Servo Position Control**

1. Button A is pressed on **ESP DIAZ**.
2. **ESP DIAZ** sends a servo position command (0 or 180) to a topic.
3. Shiftr.io forwards the command to **ESP BAYU**.
4. **ESP BAYU** moves the servo to the specified position.
5. The servo position status is published back to Node-RED and displayed on the dashboard.

---

### **3. LED Toggle from Servo Station**

1. Button B is pressed on **ESP BAYU**.
2. **ESP BAYU** sends a TOGGLE command to **ESP DIAZ** via MQTT.
3. **ESP DIAZ** turns the LED on or off accordingly.
4. The LED status update is sent back and displayed in Node-RED.

---

## **Technologies Used**

* ESP8266
* MQTT Protocol
* Node-RED Dashboard
* Shiftr.io MQTT Broker
* Arduino IDE

---

## **Features**

* **Two-way communication** between two ESP8266 devices.
* **Real-time MQTT message exchange**.
* **Visual dashboard monitoring** using Node-RED.
* **Physical button interaction** to trigger events.
* **Cloud-based MQTT broker integration** via Shiftr.io.

---

## **Demo**

### **LED Color Control**

![LED Control Demo](https://github.com/user-attachments/assets/5e72eb53-2cc7-4eb5-bc41-73415a308994)

### **Servo Control**

![Servo Control Demo](https://github.com/user-attachments/assets/16fa57c3-7399-476d-a995-b90bb39c0432)

### **Hardware Setup**

![Hardware Setup 1](https://github.com/user-attachments/assets/52e62445-2d85-4f7d-b004-5c5e2ece0d35)
![Hardware Setup 2](https://github.com/user-attachments/assets/b0cbb745-1ab4-45d9-af1f-0df1951b60ea)

### **Cloud Shiftr.io Dashboard**

![Shiftr.io Cloud Dashboard](https://github.com/user-attachments/assets/d3197d72-eca6-41db-b055-b933a6902e61)

---

## **Setup**

1. **Clone the repository**

   ```sh
   git clone https://github.com/diazadr/two-way-communication-node-red.git
   cd two-way-communication-node-red
   ```

2. **Install Node-RED**

   ```sh
   npm install -g node-red
   ```

3. **Import the provided Node-RED flow**

   * Open [http://localhost:1880](http://localhost:1880)
   * Import `flow.json` from this repository

4. **Configure Shiftr.io Broker**

   * Create an account at [https://shiftr.io](https://shiftr.io)
   * Retrieve MQTT broker URL and credentials
   * Update them in both Node-RED and ESP8266 code

5. **Upload Arduino Code**

   * Open `.ino` files in Arduino IDE
   * Select **NodeMCU 1.0 (ESP8266)** board
   * Upload to both ESP devices

---

## **Usage**

1. Run Node-RED and open the dashboard.
2. Press **Button A** to control the servo motor via MQTT.
3. Press **Button B** to toggle the RGB LED.
4. Observe real-time updates and device states in the Node-RED dashboard.

---

## **Project Status**

This project is **completed** and serves as a demonstration of IoT-based MES communication using MQTT and Node-RED.

---

## **License**

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
