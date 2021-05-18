const express = require("express");
var cors = require('cors');
const bodyParser = require('body-parser');
require('dotenv').config()
const { spawn } = require('child_process');

var dgram = require('dgram');
var client = dgram.createSocket('udp4');

var app = express()
app.use(cors())
app.use(bodyParser.json());

var leds = [];
for (let i = 0; i < 16; i += 1)
    leds.push(0);

const port = 8081;

app.get('/', (req, res) => {
    res.send("Server alive")
});

app.post('/switch', (req, res) => {
    console.log(req.body)
    const python = spawn('python', ['sendMulCast.py', req.body.id]);
    python.stdout.on('data', function (data) {
        dataToSend = data.toString();
    });
    python.on('close', () => {
        // send data to browser
        res.send(dataToSend)
    });
});

app.get('/led/:id', (req, res) => {
    res.send(leds[req.params.id-1]+"");
});

app.listen(port, () => {
    console.log(`Server running on port ${port}`)
});

var mcAddr = process.env.MC_ADDR;
var mcPort = process.env.MC_PORT;
var HOST = process.env.HOST;

client.on('listening', function () {
    var address = client.address();
    console.log('UDP Client listening on ' + address.address + ":" + address.port);
    client.setBroadcast(true)
    client.setMulticastTTL(128);
    client.addMembership(mcAddr, HOST);
});

client.on('message', function (message, remote) {
    console.log('Received: ' + remote.address + ':' + remote.port + ' - ' + message);
    var ledId;
    var state;
    if (message.length == 3) {
        ledId = message[0]-48;
        state = message[2]-48;
    } else if (message.length == 4) {
        ledId = (message[0]-48) * 10 + message[1]-48;
        state = message[3]-48;
    } else return;
    leds[ledId-1] = state;
});

client.bind(mcPort, HOST);