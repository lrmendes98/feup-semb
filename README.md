# SETR/SEMB PROJECT
## Smart House System

### Running

This is how to run the various components of our project:

#### Frontend
To run the frontend, open a terminal in the webapp folder and execute the commands:

```npm install```

```npm start```

This will create a React app running on localhost:8080.

#### Backend
To run the frontend, open a terminal in the server folder and execute the command:

```npm install```

```npm start```

This will create an Express.js server running on localhost:8081.

#### Arduino ESP8266

##### Compiling
To compile the code for the ESP8266 with the climate sensors, the library [DHT11](https://github.com/adidax/dht11) needs to be imported.
##### Running
Upload the code inside the Main folder to the Arduino.

#### Debug
You can use the MCastSnooper tool to see the packets beeing sent over the multicast group. To do so, run the script.bat file inside the McastSnooper folder.
