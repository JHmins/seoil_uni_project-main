const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
.card{
    max-width: 400px;
     min-height: 250px;
     background: #02b875;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
</style>
<head>
<meta charset="utf-8">
</head>
<body>
 
<div class="card">
  <h4>센서 측정값 모니터</h4><br>
  <h1> <span id="SensorValue">0</span></h1><br>
  <br><a href="https://tklabs.co.kr">tklabs.co.kr</a>
</div>
<script>
 
setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
  getData2();
}, 2000); //2000mSeconds update rate
 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("SensorValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readSensor", true);
  xhttp.send();
}

</script>
</body>
</html>
)=====";
