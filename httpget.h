String httpget(String request) {
  String response="";

  // webUI specific pages

  if (request.indexOf("/getPillar")>=0) {
    if (activeIn==greenIn) { response=String((timerOne.timer-millis())/1000) + ",green,"; }
    else if (activeIn==yellowIn) { response=String((timerOne.timer-millis())/1000) + ",yellow,"; }
    else if (activeIn==redIn) { response=String((timerOne.timer-millis())/1000) + ",red,"; }
    else { response="0,off,"; } }

  else if (request.indexOf("/setPillar,green")>=0) { buttonChanged(greenIn,400); }
  else if (request.indexOf("/setPillar,yellow")>=0) { buttonChanged(yellowIn,400); }
  else if (request.indexOf("/setPillar,red")>=0) { buttonChanged(redIn,400); }
  else if (request.indexOf("/setPillar,off")>=0) { allOff(); }
  else if (request.indexOf("/setPillar,beep")>=0) { beepOn(); }
  else if (request.indexOf("/setPillar,alarm")>=0) { alarmOn(); }

  // WLAN Choose specific pages

  else if (request.indexOf("/appName")>=0) {
    response+=String(appName) + ",";
    response+=String(appDesc) + ","; }

  else if (request.indexOf("/chooseAP")>=0) { response=choose_html; }

  else if (request.indexOf("/statusAP")>=0) { if (wlanConfig.statusStation) { response="<div class=\"x1\">WLAN AP " + wlanConfig.ssidStation + " connected.</div>";
    response+="<div class=\"x1\">IP Address " + WiFi.localIP().toString() + "</div>"; } else { response="<div class=\"x1\">No WLAN AP connected.</div>"; } }

  else if (request.indexOf("/configAP")>=0) {
    if (WiFi.softAPgetStationNum()==0) { response=a2h(wlanConfig.ssidStation) + "," + a2h(wlanConfig.passwordStation) + ","; }
    else { response=a2h(wlanConfig.ssidStation) + ",,"; } }

  else if (request.indexOf("/scanAP")>=0) {
    wlanTimer=millis()+20000; int indexes=WiFi.scanNetworks(); response+="<div class=\"x1\"><table>"; for (int index=0;index<indexes;++index) { if (WiFi.SSID(index)!="") {
      response+="<tr><td onclick=\"setAP(\'" + WiFi.SSID(index) + "\');\">" + WiFi.RSSI(index) + "&nbsp;dB&nbsp;&nbsp;&nbsp;&nbsp;" + WiFi.SSID(index) + "</td></tr>"; } } response+="</table></div>"; }

  else if (request.indexOf("/connectAP")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1;
    if (!wlanConfig.statusStation || WiFi.softAPgetStationNum()==0) {
      wlanConfig.ssidStation=h2a(request.substring(a,b-1)); wlanConfig.passwordStation=h2a(request.substring(b)); wlanConfig.reconnectCount=0; reconnectWLAN(); }
    else { if (debug) { Serial.println("WLAN Station reconnect prevented."); } } }

  // Default page

  else { response=index_html; }

  return response; }
