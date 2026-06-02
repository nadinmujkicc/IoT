import * as http from "http";
import express from "express";
import ip from "ip";
import path from "path";
import { join, dirname } from "path";
import { fileURLToPath } from "url";
import WebSocket, { WebSocketServer } from 'ws';

const __dirname = dirname(fileURLToPath(import.meta.url));
const app = express();

const hostname = "0.0.0.0";
const port = 8080;

const server = http.createServer(app).listen(port);

const wss1 = new WebSocketServer({ port: 8888 });
const wss2 = new WebSocketServer({ port: 8811 });

app.get('/', function (req, res) {
    res.sendFile(path.join(__dirname, '10.html'));
});

wss1.broadcast = function broadcast(data) {
    wss1.clients.forEach(function each(client) {
        if (client.readyState == WebSocket.OPEN) {
            client.send(data);
        }
    });
}

wss2.broadcast = function broadcast(data) {
    wss2.clients.forEach(function each(client) {
        if (client.readyState == WebSocket.OPEN) {
            client.send(data);
        }
    });
}

wss1.on('connection', function (ws, req) {
    console.log('Klijent - korisnik se povezao sa 8888');
});

wss2.on('connection', function (ws, req) {
    console.log("esp32 povezan dvosmerno na 8811");
    ws.on('message', function (msgString) {
        try {
            var msg = JSON.parse(msgString);
            switch (msg.tipPoruke) {
                case "potenciometar":
                    funkcijaPotenciometar(msg);
                    break;
            }
        } catch (e) {
            console.error("Greska pri parsiranju poruke sa ESP32");
        }
    });
});

console.log('Streznik zagnan');
console.log('Adresa za Chrome: http://' + ip.address() + ':' + port);

function funkcijaPotenciometar(msg) {
    wss1.broadcast(JSON.stringify(msg));
}