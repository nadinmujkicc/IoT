import * as http from 'http';
import express from 'express';
import ip from 'ip';

const app = express();

const hostname = '192.168.64.118';
const port = 80;

const server = http.createServer(app).listen(port);

app.get('/', function (req, res) {
    res.send('Hello World!');
});

console.log("Pokrenuto...");
console.log("IP adresa: " + ip.address());