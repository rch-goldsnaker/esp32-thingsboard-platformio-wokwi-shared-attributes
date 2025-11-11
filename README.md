# ESP32 ThingsBoard Shared Attributes

This project demonstrates **Shared Attributes** functionality with ESP32 and **ThingsBoard** IoT platform. The ESP32 controls an LED remotely using ThingsBoard shared attributes, allowing real-time control from the dashboard, simulated in **Wokwi**.

## 🎯 Features

- **Remote LED Control**: Control LED from ThingsBoard dashboard
- **Real-time Updates**: Instant LED response to shared attribute changes
- **Bidirectional Sync**: LED state synchronized between device and server
- **Simple Design**: Minimal code, maximum IoT functionality
- **Wokwi Simulation**: Complete hardware simulation with LED

## 📚 Dependencies and Libraries

### PlatformIO Libraries
```ini
lib_deps = 
    thingsboard/ThingsBoard@0.14.0                    # ThingsBoard MQTT Client
    arduino-libraries/ArduinoHttpClient@^0.6.1        # HTTP Client
    arduino-libraries/ArduinoMqttClient@^0.1.8        # MQTT Client
    knolleary/PubSubClient@^2.8                       # MQTT Pub/Sub
```

### System Libraries
- `WiFi.h` - WiFi connectivity (ESP32)
- `Arduino_MQTT_Client.h` - MQTT client for ThingsBoard
- `Attribute_Request.h` - Attribute request management
- `Shared_Attribute_Update.h` - Shared attributes real-time updates

## ⚙️ Configuration

### 1. WiFi Credentials
```cpp
constexpr char WIFI_SSID[] = "Wokwi-GUEST";      // WiFi Network
constexpr char WIFI_PASSWORD[] = "";             // Password (empty for Wokwi)
```

### 2. ThingsBoard Configuration
```cpp
constexpr char TOKEN[] = "xxxxxxxxxxxxxxxxxxxx";           // Device token (from ThingsBoard)
constexpr char THINGSBOARD_SERVER[] = "thingsboard.cloud"; // ThingsBoard server
constexpr uint16_t THINGSBOARD_PORT = 1883U;               // MQTT port
constexpr const char LED_STATE_ATTR[] = "ledState";        // Shared attribute name
```

### 3. Hardware Configuration
```cpp
#define LED_PIN 2        // LED connected to GPIO 2
```

## 🚀 Installation and Usage

### 1. Prerequisites
- [PlatformIO IDE](https://platformio.org/platformio-ide) or [PlatformIO Core](https://platformio.org/install/cli)
- Account on [ThingsBoard Cloud](https://thingsboard.cloud/) or local server
- Access to [Wokwi](https://wokwi.com/) for simulation

### 2. Project Setup
```bash
# Clone the repository
git clone <repository-url>
cd esp32-thingsboard-platformio-wokwi-telemetry
```

### 3. ThingsBoard Configuration
1. Create a new device in ThingsBoard
2. Copy the device **Access Token**
3. Replace the `TOKEN` in `main.cpp`
4. Create a shared attribute `ledState` (boolean) in the device dashboard

### 4. Wokwi Simulation
1. Open the project in Wokwi
2. The `diagram.json` contains:
   - ESP32 DevKit C V4
   - Red LED on GPIO 2
3. Run the simulation
4. Monitor serial port for connection status
5. Control LED from ThingsBoard dashboard

## 🔧 How It Works

### Shared Attributes Flow
1. **Connection**: ESP32 connects to WiFi and ThingsBoard
2. **Subscribe**: Automatically subscribes to `ledState` shared attribute updates
3. **Request**: Requests current `ledState` value from server
4. **Real-time Control**: LED responds instantly to dashboard changes
5. **Bidirectional Sync**: Device and server stay synchronized

### Hardware Components
- **LED (GPIO 2)**: Visual indicator controlled remotely
- **Serial Monitor**: Status messages and debugging

## 📊 ThingsBoard Integration

### Shared Attributes
- **ledState** (boolean): Controls LED state remotely from dashboard

### Device Behavior
- **First Connection**: Requests current shared attribute value
- **Real-time Updates**: LED changes instantly when attribute is modified
- **Dashboard Control**: Toggle LED from ThingsBoard web interface
- **State Synchronization**: Device and server maintain consistent state

## 🎮 Usage

1. **Power On**: Device connects and requests current LED state
2. **Dashboard Control**: Go to ThingsBoard → Device → Attributes tab
3. **Toggle LED**: Modify `ledState` shared attribute (true/false)
4. **Real-time Response**: LED changes instantly on the device
5. **Restart Device**: LED automatically syncs with server state

## �📄 License

This project is an open source educational template. Free to use and modify.


## 📞 Support

For questions or issues:
- Create an issue in the repository
- Review [ThingsBoard documentation](https://thingsboard.io/docs/devices-library/esp32-dev-kit-v1/)
- Check [Wokwi documentation](https://docs.wokwi.com/)

## 🔍 Troubleshooting

### Common Issues
- **"Failed to connect to ThingsBoard"**: Check device token and internet connection
- **"LED value not found in shared attributes"**: Create `ledState` shared attribute in dashboard
- **"Failed to subscribe for shared attribute updates"**: Check MQTT connection
- **"Timeout: No response from ThingsBoard"**: Network or server issues

### Serial Monitor Messages
- `LED state updated from shared attributes: ON/OFF` - Remote control successful
- `Subscribed to shared attributes` - Ready to receive updates
- `Connected to ThingsBoard successfully!` - Device online and ready

---
**Author**: Mirutec - Roger Chung  
**Version**: 1.0 - Shared Attributes  
**Date**: November 2025
