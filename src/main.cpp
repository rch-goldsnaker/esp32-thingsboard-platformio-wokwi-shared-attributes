#include <WiFi.h>
#include <Arduino_MQTT_Client.h>
#include <ThingsBoard.h>
#include <Attribute_Request.h>

constexpr char WIFI_SSID[] = "Wokwi-GUEST";
constexpr char WIFI_PASSWORD[] = "";
constexpr char TOKEN[] = "qrXSMGvV47EJHBq4BkDm";
constexpr char THINGSBOARD_SERVER[] = "thingsboard.cloud";
constexpr uint16_t THINGSBOARD_PORT = 1883U;

#define LED_PIN 2
#define BUTTON_PIN 0

constexpr const char LED_STATE_ATTR[] = "ledState";
constexpr size_t MAX_ATTRIBUTES = 3U;
constexpr uint64_t REQUEST_TIMEOUT_MICROSECONDS = 5000U * 1000U;

WiFiClient wifiClient;
Arduino_MQTT_Client mqttClient(wifiClient);
Attribute_Request<1U, MAX_ATTRIBUTES> attr_request;
const std::array<IAPI_Implementation *, 1U> apis = {&attr_request};
ThingsBoard tb(mqttClient, 1024U, Default_Max_Stack_Size, apis);

bool ledState = false;

constexpr std::array<const char *, 1U> CLIENT_ATTRIBUTES_LIST = {LED_STATE_ATTR};

void processClientAttributes(const JsonObjectConst &data)
{
  bool attributeFound = false;
  for (auto it = data.begin(); it != data.end(); ++it)
  {
    if (strcmp(it->key().c_str(), LED_STATE_ATTR) == 0)
    {
      ledState = it->value().as<bool>();
      digitalWrite(LED_PIN, ledState);
      Serial.print("LED restored: ");
      Serial.println(ledState ? "ON" : "OFF");
      attributeFound = true;
    }
  }

  if (!attributeFound)
  {
    Serial.println("LED value not found on server, using current state");
  }
}

void requestTimedOut()
{
  Serial.println("Timeout: No response from ThingsBoard within 5 seconds.");
}

const Attribute_Request_Callback<MAX_ATTRIBUTES> attribute_client_request_callback(&processClientAttributes, REQUEST_TIMEOUT_MICROSECONDS, &requestTimedOut, CLIENT_ATTRIBUTES_LIST);

void InitWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

const bool reconnect() {
  const wl_status_t status = WiFi.status();
  if (status == WL_CONNECTED) {
    return true;
  }
  InitWiFi();
  return true;
}

void toggleLed()
{
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
  Serial.print("LED: ");
  Serial.println(ledState ? "ON" : "OFF");
  tb.sendAttributeData(LED_STATE_ATTR, ledState);
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  InitWiFi();
}

void loop()
{
  // Check WiFi connection
  if (!reconnect())
  {
    return;
  }

  // Connect to ThingsBoard if not connected
  if (!tb.connected())
  {
    Serial.print("Connecting to ThingsBoard: ");
    Serial.println(THINGSBOARD_SERVER);
    
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT))
    {
      Serial.println("Failed to connect to ThingsBoard!");
      return;
    }
    
    Serial.println("Connected to ThingsBoard successfully!");
    attr_request.Client_Attributes_Request(attribute_client_request_callback);
  }
  
  // Process ThingsBoard messages
  tb.loop();

  if (digitalRead(BUTTON_PIN) == LOW)
  {
    toggleLed();
    delay(200); // Simple delay to avoid multiple triggers
  }

  delay(200);
}
