import * as http from 'http';
import express from 'express';
import ip from 'ip';
import path from 'path';
import { join, dirname } from 'path';
import { fileURLToPath } from 'url';

import WebSocket, { WebSocketServer } from 'ws';

const __dirname = dirname(fileURLToPath(import.meta.url));

const app = express();

const hostname = '192.168.64.118';
const port = 80;

const server = http.createServer(app).listen(port);

const wss1 = new WebSocketServer({ port: 8888 });

app.get('/', function (req, res) {
  console.log('HTTP client requested /');
  res.sendFile(join(__dirname, 'primer05.html'));
});

wss1.on('connection', function (ws, req) {
  console.log("Novi klijent se povezao.");
});

console.log("Pokrenuto...");
console.log("IP adresa: " + ip.address());