const express = require("express");
var cors = require('cors');
const bodyParser = require('body-parser');
const { spawn } = require('child_process');
var app = express()

app.use(cors())

app.use(bodyParser.json());

const port = 8081;

app.post('/switch', (req, res) => {
    console.log(req.body)
    const state = req.body.state ? "1" : "0"
    const python = spawn('python', ['sendMulCast.py', req.body.id, state]);
    python.stdout.on('data', function (data) {
        console.log('Pipe data from python script ...');
        dataToSend = data.toString();
    });
    python.on('close', (code) => {
        console.log(`child process close all stdio with code ${code}`);
        // send data to browser
        res.send(dataToSend)
    });
});

app.get('/', (req, res) => {
    res.send("Server alive")
});

app.listen(port, () => {
    console.log(`Server running on port ${port}`)
});