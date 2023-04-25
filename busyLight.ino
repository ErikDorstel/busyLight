boolean debug=true;

const char* appName="busyLight";
const char* appDesc="Light Pillar";

#include "lightPillar.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTP.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initPillar();
  initWLAN();
  initDNS();
  initHTTP(); }

void loop() { pillarWorker(); wlanWorker(); dnsWorker(); httpWorker(); }
