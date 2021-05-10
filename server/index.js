const express = require("express");

const app = express();

const port = 8081;

app.get('/', (req, res) => {
    res.send('Received request');
    var PORT = 4444;
    var MCAST_ADDR = "239.0.0.1"; //not your IP and should be a Class D address, see http://www.iana.org/assignments/multicast-addresses/multicast-addresses.xhtml
    var dgram = require('dgram');
    var server = dgram.createSocket("udp4");
    server.bind(PORT, function () {
        server.setBroadcast(true);
        server.setMulticastTTL(128);
        server.addMembership(MCAST_ADDR);
    });

    var message = Buffer.from("Hello");
    server.send(message, 0, message.length, PORT, MCAST_ADDR);
    console.log("Sent " + message + " to the wire...");

    res.send('SENT');
});

app.listen(port, () => {
    console.log(`Server running on port ${port}`)
});