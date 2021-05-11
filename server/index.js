const express = require("express");
const { spawn } = require('child_process');
var cors = require('cors')
var app = express()

app.use(cors())

const port = 8081;

app.get('/switch/:id', (req, res) => {
    console.log(req.params)
    const python = spawn('python', ['sendMulCast.py', req.params.id]);
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