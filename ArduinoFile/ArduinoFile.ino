
#include <WiFi.h>
#include <HttpClient.h>

// Constants, like PINs
const int MosfetPin = 5;
const int rotationSensor = 39;
const int freq = 5000;
const int Channel = 0;
const int resolution = 8;

// Enum for Checking the Current Mode
enum currentMode{OnlineControll,ManuellControll,APIControll};
currentMode Active = ManuellControll;
enum currentSpeed

WiFiClient client;


//Internet
const char* ssid     = "Nicola";
const char* password = "12345678";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request, Global
String header;

void setup() {  // Setting up some Stuff in order to Work.
  Serial.begin(115200);
  pinMode(rotationSensor, INPUT);
  pinMode(MosfetPin, OUTPUT);
  ledcSetup(Channel, freq, resolution);
  ledcAttachPin(MosfetPin, Channel);



  //Connecting to the Declared WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print the IP of the Webserver.
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  //Starts the Server
  server.begin();
}

void loop() {
  //Serial.println(analogRead(rotationSensor));
  int rotVal = analogRead(rotationSensor);
  int mappedRotVal = map(rotVal,0, 4095,0,255);
  ledcWrite(Channel, mappedRotVal);
  delay(30);



  WiFiClient client = server.available();   // Listen for incoming clients




// Transfer the Information if a Client is Available
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
// This Part is the Same no Matter wich Page is Loaded, No need for Redundatnt Code
client.println(" <!DOCTYPE html> ");
client.println("<html lang=\"en\">");
client.println("    <head> ");
client.println("        <meta charset=\"utf-8\">");
client.println("        <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
client.println("        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\">");
 
client.println("        <title>Arduino Fancontroller</title>");
client.println("        <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\">");
client.println("    </head>");
client.println("    <body>");
client.println("        <div class=\"container\">");
client.println("            <div class=\"masthead\">");
client.println("                <h3 class=\"text-muted\">project by Moritz &amp; Nicola</h3>");
client.println("                <nav class=\"bg-light mb-3 navbar navbar-expand-md navbar-light rounded\">");
client.println("                    <button class=\"navbar-toggler\" type=\"button\" data-toggle=\"collapse\" data-target=\"#navbarCollapse\" aria-controls=\"navbarCollapse\" aria-expanded=\"false\" aria-label=\"Toggle navigation\">");
client.println("                        <span class=\"navbar-toggler-icon\"></span>");
client.println("                    </button>");
client.println("                    <div class=\"collapse navbar-collapse\" id=\"navbarCollapse\">");
client.println("                        <ul class=\"nav-justified navbar-nav text-md-center w-100\">");
// Now the Individuall Part Starts
            
            if (header.indexOf("GET /Manuell") >= 0){
client.println("                            <li class=\"active nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/Manuell\">Manuell</a>");
client.println("                            </li>");
client.println("                            <li class=\"nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/OnlineController\">Online Controller</a>");
client.println("                            </li>");
client.println("                            <li class=\"nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/APIController\">API Controller</a>");
client.println("                            </li>");
client.println("                        </ul>");
client.println("                    </div>");
client.println("                </nav>");
client.println("            </div>");

client.println("            <div class=\"jumbotron\">");
client.println("                <h1>Regulierung über Rotationssensor</h1>");
client.println("                <p class=\"lead\">Sie Können die Geschwindigkeit des Fans über den eingebauten Rotationssensor Steuern, dafür muss der Modus jedoch auf Manuelle Kontrolle Geschaltet sein.</p>");
client.println("                <p><a class=\"btn btn-lg btn-success\" href=\"/OnlineController/TurnON\" role=\"button\"> API Aktivieren (Not Working Yet)</a></p>");
client.println("            </div>");
            }


            
            else if (header.indexOf("GET /OnlineController") >= 0){
client.println("                            <li class=\"nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/Manuell\">Manuell</a>");
client.println("                            </li>");
client.println("                            <li class=\"active nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/OnlineController\">Online Controller</a>");
client.println("                            </li>");
client.println("                            <li class=\"nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/APIController\">API Controller</a>");
client.println("                            </li>");
client.println("                        </ul>");
client.println("                    </div>");
client.println("                </nav>");
client.println("            </div>");

// Edit Code Below HERE
client.println("            <div class=\"jumbotron\">");
client.println("                <h1>Regulierung über Webserver</h1>");
client.println("                <p class=\"lead alert-danger\"> This Feature is Still work in Progress! \n you will be Able to Switch to Auto Controller, currently this Button does Nothing</p>");
client.println("                <p><a class=\"btn btn-lg btn-success\" href=\"/OnlineController/TurnON\" role=\"button\"> API Aktivieren (Not Working Yet)</a></p>");
client.println("            </div>");
            }


            
            else if (header.indexOf("GET /APIController") >= 0){
client.println("                            <li class=\"nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/Manuell\">Manuell</a>");
client.println("                            </li>");
client.println("                            <li class=\"nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/OnlineController\">Online Controller</a>");
client.println("                            </li>");
client.println("                            <li class=\"nav-item\">");
client.println("                                <a class=\"active nav-link\" href=\"/APIController\">API Controller</a>");
client.println("                            </li>");
client.println("                        </ul>");
client.println("                    </div>");
client.println("                </nav>");
client.println("            </div>");

// Edit code Below API

client.println("            <div class=\"jumbotron\">");
client.println("                <h1>Automatische Regelierung über API</h1>");
client.println("                <p class=\"lead alert-danger\"> This Feature is Still work in Progress! You will not be Able to Switch to API Controll. So this Button does Nothing</p>");
client.println("                <p><a class=\"btn btn-lg btn-success\" href=\"/APIController/SwitchAPItoON\" role=\"button\"> Switch to API Mode (Not Working Yet)</a></p>");
client.println("            </div>");
            }
            else{

              
// There is No Page Selected so we are just Loading the Standart Page, Here are Just Links, we are not Taking anything else Out of the Request

client.println("                            <li class=\"nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/Manuell\">Manuell</a>");
client.println("                            </li>");
client.println("                            <li class=\"nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/OnlineController\">Online Controller</a>");
client.println("                            </li>");
client.println("                            <li class=\"nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/APIController\">API Controller</a>");
client.println("                            </li>");
client.println("                        </ul>");
client.println("                    </div>");
client.println("                </nav>");
client.println("            </div>");




client.println("            <div class=\"jumbotron\">");
client.println("                <h1>The Collest Fan Controllcenter</h1>");
client.println("                <p class=\"lead\">Willkommen im Controllcenter des Arduino Controlled Fan von Moritz und Nicola. Hier Haben sie die Möglichkeit die Geschwindigkeit der Lüfter zu regulieren, auf auf die Steuerung über eine Wetter API umzuschalten oder auf eine Manuelle Steuerung per Rotations Sensor umzuschalten</p>");

client.println("                            <li class=\"active nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/Manuell\">Manuell</a>");
client.println("                            </li>");
client.println("                            <li class=\"nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/OnlineController\">Online Controller</a>");
client.println("                            </li>");
client.println("                            <li class=\"nav-item\">");
client.println("                                <a class=\"nav-link\" href=\"/APIController\">API Controller</a>");
client.println("                            </li>");
          if (Active = OnlineControll){
          client.println("                <p><a class=\"btn btn-lg btn-success\" href=\"/OnlineController\" role=\"button\">Online Controller</a></p>");  
          }
          else if(Active = ManuellControll){
          client.println("                <p><a class=\"btn btn-lg btn-success\" href=\"/Manuell\" role=\"button\">Manuell Controller</a></p>");
          }
          else if(Active = APIControll){
          client.println("                <p><a class=\"btn btn-lg btn-success\" href=\"/APIController\" role=\"button\">API Controller</a></p>");
          }
          else{
          client.println("                <p><a class=\"btn btn-lg btn-success\" href=\"#\" role=\"button\">Something went Verry Verry Much Wrong</a></p>");
          }

client.println("            </div>");
}
            //------ Here Again this Code is Needed in All Versions

client.println("        </div>");  

client.println("<script src=\"https://code.jquery.com/jquery-3.3.1.slim.min.js\" integrity=\"sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo\" crossorigin=\"anonymous\"></script>");
client.println("<script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js\" integrity=\"sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1\" crossorigin=\"anonymous\"></script>");
client.println("<script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js\" integrity=\"sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM\" crossorigin=\"anonymous\"></script>");

client.println("    </body>");
client.println("</html>");  
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

}
