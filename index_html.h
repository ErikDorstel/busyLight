const char *index_html=R"(

<!DOCTYPE html>
<html lang="en"><head>
<title>busyLight</title>
<meta name="author" content="Erik Dorstel">
<meta name="generator" content="vi">
<meta name="repository" content="https://github.com/ErikDorstel/...">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
<style>
html   { font-family:Arial; }
div    { background-color:#e0e0e0; color:#000000; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
select { background-color:#f0f0f0; color:#000000; font-size:1.0em; border:0px; padding:0px; margin:0px; }
table  { margin-left:auto; margin-right:auto; }
td     { text-align:right; }
.x0a   { background-color:#c2d5ed; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b   { background-color:#c2d5ed; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0    { background-color:#c2d5ed; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1a   { background-color:#f0f0f0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1b   { background-color:#e0e0e0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2    { background-color:#e0e0e0; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3    { background-color:#e0e0e0; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4    { background-color:#e0e0e0; padding:0.3em 0em; width:24%; font-size:1.4em; }
</style>
<script>

function webUIinit() {
  timer=0; pillar="off"; window.setInterval("getPillar();",5000);
  appName="&nbsp;"; appDesc="&nbsp;"; ajaxObj=[]; requestAJAX('appName'); getPillar(); }

function doDisplay() {
  if (pillar=="red") { id("btnRedA").style.backgroundColor="#E09090"; } else { id("btnRedA").style.backgroundColor="#c0c0c0"; }
  if (pillar=="yellow") { id("btnYellowA").style.backgroundColor="#E5E554"; } else { id("btnYellowA").style.backgroundColor="#c0c0c0"; }
  if (pillar=="green") { id("btnGreenA").style.backgroundColor="#90E090"; } else { id("btnGreenA").style.backgroundColor="#c0c0c0"; }
  if (timer>60) { id("btnTimer").innerHTML=Math.floor(timer/60)+" Minuten verbleiben"; }
  else { id("btnTimer").innerHTML=timer+" Sekunden verbleiben"; } }

function getPillar() { requestAJAX('getPillar'); }

function setPillar(value) { requestAJAX('setPillar,'+value); requestAJAX('getPillar'); }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded");
  ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="appName") {
      id("appName").innerHTML=event.target.responseText.split(",")[0];
      id("appDesc").innerHTML=event.target.responseText.split(",")[1]; }
    else if (event.target.url=="getPillar") { timer=event.target.responseText.split(",")[0]; pillar=event.target.responseText.split(",")[1]; doDisplay(); } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="webUIinit();">

<div><div class="x0a" id="appName">&nbsp;</div></div>
<div><div class="x0b" id="appDesc">&nbsp;</div></div>

<div><div class="x1b" onclick="location.replace('/chooseAP');">Choose WLAN AP</div></div>

<div>
<div><div class="x2" id="btnTimer"></div>
     <div class="x2" onclick="setPillar('off');" ondblclick="setPillar('alarm');">Ausschalten</div></div>
<div><div class="x2" id="btnRedA">&nbsp</div>
     <div class="x2" onclick="setPillar('red');">+10 Minuten Rot</div></div>
<div><div class="x2" id="btnYellowA">&nbsp</div>
     <div class="x2" onclick="setPillar('yellow');">+10 Minuten Gelb</div></div>
<div><div class="x2" id="btnGreenA">&nbsp</div>
     <div class="x2" onclick="setPillar('green');">+10 Minuten Gr&uuml;n</div></div>
</div>

</body></html>

)";
