#include "EspWifiManager.h"

const char login_html[] PROGMEM = R"===(
<html>
    <head>
        <title>
            Moody Node - Connect to WiFi
        </title>
        <style>
            .login {
                margin: auto;
                width: 450px;
                height: auto;
                font-family: Courier New;
                border-radius: 25px;
                background-color: #ebeeff;
                text-align: left;
                padding: 1%;
                padding-right: 0%;
                padding-left: 0%;
                text-decoration: none;
                font-size: 15px;
                border: 1px solid #af7bc7;
            }

            .login h3 {
                text-align: center;
            }

            .login table {
                margin: auto;
                padding: 0;
            }

            .login td {
                font-size: 15px;
            }
        </style>
    </head>
    <body>
        <div class="login">
            <h3>Connect to your home WiFi</h3>
            <table>
                <tr>
                    <td>SSID:</td>
                    <td><input type="text" name="ssid" id="ssid" /></td>
                </tr>
                <tr>
                    <td>KEY:</td>
                    <td><input type="password" name="key" id="key"/></td>
                </tr>
                <tr>
                    <td>Broker Address:</td>
                    <td><input type="text" name="broker" id="broker"/></td>
                </tr>
                <tr>
                    <td><input type="submit" value="Connect" onclick="save_credentials()" /></td>
                </tr>
            </table>
        </div>
    </body>
    <script>
        function save_credentials() {
            let xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if(this.readyState === 4 && this.status === 200){
                    alert("The esp will now reset and try to connect to the specified network.");
                } else if(this.status === 422) {
                    alert("Invalid or missing parameter!");
                }
            };
            xhttp.open("POST", "/connect", true);
            xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
            let ssid = document.getElementById("ssid").value;
            let key = document.getElementById("key").value;
            let broker = document.getElementById("broker").value;
            if(!ssid || !key || !broker) {
                alert("A field is missing!");
            }
            let params = "ssid="+ssid+"&key="+key+"&broker="+broker;
            xhttp.send(params);
        }

    </script>
</html>
)===";
