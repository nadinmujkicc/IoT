import * as http from 'http';
import express from 'express';
import ip from 'ip';
import path from 'path';
import { join, dirname } from 'path';
import { fileURLToPath } from 'url';

const __dirname = dirname(fileURLToPath(import.meta.url));

const app = express();

const hostname = '192.168.64.118';
const port = 80;

const server = http.createServer(app).listen(port);

app.get('/', function (req, res) {
    res.sendFile(join(__dirname, 'primer04.html'));
});

console.log("Pokrenuto...");
console.log("IP adresa: " + ip.address());