//web.cpp

#include "web.h"

String html;

String SendHTML(float pH, float PPM, float suhu, float tinggi_cm, String kondisiOtomatisasi){ 
html = "<!DOCTYPE html> <html>\n";
html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
html += "<title>Dashboard</title>\n";
html += "<style>html { font-family: Helvetica, Arial, sans-serif; display: inline-block; margin: 0px auto; text-align: center; background-color: #f4f4f9; }\n";
html += "body { margin-top: 50px; color: #333; }\n";
html += "h1 { color: #444444; margin: 50px auto 30px; font-size: 2rem; }\n";
html += "h2 { color: #666666; margin: 30px auto 20px; font-size: 1.5rem; }\n";
html += "p { font-size: 1.2rem; color: #444444; margin-bottom: 10px; }\n";
html += ".sensor-grid { display: grid; grid-template-columns: repeat(2, 1fr); gap: 20px; max-width: 500px; margin: 20px auto; }\n";
html += ".sensor-box { background-color: #ffffff; border: 1px solid #dddddd; border-radius: 10px; padding: 20px; box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.1); }\n";
html += ".status-box, .control-box { background-color: #ffffff; border: 1px solid #dddddd; border-radius: 10px; padding: 20px; margin: 20px auto; width: 100%; max-width: 500px; box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.1); }\n";
html += ".status-box p, .control-box p { font-size: 1.2rem; font-weight: bold; }\n";
html += ".control-box button { background-color: #4CAF50; border: none; color: white; padding: 15px 30px; font-size: 1rem; cursor: pointer; border-radius: 5px; box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.1); transition: background-color 0.3s ease; }\n";
html += ".control-box button:hover { background-color: #45a049; }\n";
html += "</style>\n";
html += "</head>\n";
html += "<body>\n";
html += "<h1>Sistem Monitoring Nutrisi Otomatis</h1>\n";
html += "<div id=\"webpage\">\n";
html += "<h2>Pembacaan Sensor</h2>\n";
html += "<div class=\"sensor-grid\">\n";
html += "<div class=\"sensor-box\">\n";
html += "<p><strong>pH</strong> : <span id=\"pH\">";
html += pH;
html += "</span></p>\n";
html += "</div>\n";
html += "<div class=\"sensor-box\">\n";
html += "<p><strong>PPM</strong>: <span id=\"PPM\">";
html += PPM;
html += "</span></p>\n";
html += "</div>\n";
html += "<div class=\"sensor-box\">\n";
html += "<p><strong>Suhu</strong>: <span id=\"suhu\">";
html += suhu;
html += "</span> <sup>o</sup>C</p>\n";
html += "</div>\n";
html += "<div class=\"sensor-box\">\n";
html += "<p><strong>Tinggi Air</strong>: <span id=\"tinggi_cm\">";
html += tinggi_cm;
html += "</span> cm</p>\n";
html += "</div>\n";
html += "</div>\n";
html += "<div class=\"status-box\">\n";
html += "<p><strong>Kondisi Otomatisasi:</strong> <br> <span id=\"kondisiOtomatisasi\">";
html += kondisiOtomatisasi;
html += "</span></p>\n";
html += "</div>\n";
html += "</div>\n";
html += "<h2>Kontrol Sistem</h2>\n";
html += "<div id=\"saklar\" class=\"control-box\">\n";
html += "<p>Saklar Otomatisasi</p>\n";
html += "<button onclick=\"control('/otomatisasi_on')\">ON</button>\n";
html += "</div>\n";
html += "<script>\n";
html += "function control(endpoint) {\n";
html += "  fetch(endpoint)\n";
html += "    .then(response => response.text())\n";
html += "    .then(data => {\n";
html += "      console.log(data);\n";
html += "    });\n";
html += "}\n";
html += "setInterval(() => {\n";
html += "  fetch('/data')\n";
html += "    .then(res => res.json())\n";
html += "    .then(data => {\n";
html += "      document.getElementById('pH').textContent = data.pH;\n";
html += "      document.getElementById('PPM').textContent = data.PPM;\n";
html += "      document.getElementById('suhu').textContent = data.suhu;\n";
html += "      document.getElementById('tinggi_cm').textContent = data.tinggi_cm;\n";
html += "      document.getElementById('kondisiOtomatisasi').textContent = data.kondisiOtomatisasi;\n";
html += "    });\n";
html += "}, 1000);\n";
html += "</script>\n";
html += "</body>\n";
html += "</html>\n";

return html; 
}
