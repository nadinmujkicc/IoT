import * as http from 'http';
import express from 'express';
import ip from 'ip';
import path from 'path';
import { join, dirname } from 'path';
import { fileURLToPath } from 'url';
import WebSocket, { WebSocketServer } from 'ws';

const __dirname = dirname(fileURLToPath(import.meta.url));

const app = express();

const hostname = "0.0.0.0";
const port = 8080;

const wss1 = new WebSocketServer({ port: 8888 });
const wss2 = new WebSocketServer({ port: 8811 });

const server = http.createServer(app).listen(port);

app.get('/', function (req, res) {
    res.sendFile(path.join(__dirname, '11.html'));
});

wss1.broadcast = function broadcast(data) {
    wss1.clients.forEach(function each(client) {
        if (client.readyState === WebSocket.OPEN) {
            client.send(data);
        }
    });
};

wss2.broadcast = function broadcast(data) {
    wss2.clients.forEach(function each(client) {
        if (client.readyState === WebSocket.OPEN) {
            client.send(data);
        }
    });
};

wss1.on('connection', function (ws, req) {
    console.log("Klient - brskalnik Chrome se je povezal z dvosmerno povezavo prek vrat 8888.");
    ws.on('message', function (msgString) {
        console.log("Sporočilo iz Chrome prejeto, vsebina: " + msgString);
        try {
            let msg = JSON.parse(msgString);
            switch (msg.tipSporočila) {
                case "LED":
                    funkcijaLED(msg);
                    break;
            }
        } catch (e) {
            console.error("Napaka pri parsiranju JSON iz brskalnika");
        }
    });
});

wss2.on('connection', function (ws, req) {
    console.log("esp32 se je povezal z dvosmerno povezavo prek vrat 8811.");
    ws.on('message', function (msgString) {
        console.log("Sporočilo iz esp32 prejeto, vsebina: " + msgString);
        try {
            let msg = JSON.parse(msgString);
            switch (msg.tipSporočila) {
                case "fotoupornik":
                    funkcijaFotoupornik(msg);
                    break;
            }
        } catch (e) {
            console.error("Napaka pri parsiranju JSON iz ESP32");
        }
    });
});

console.log('Strežnik je zagnan');
console.log('Adresa za Chrome: http://' + ip.address() + ':' + port);

function funkcijaFotoupornik(msg) {
    wss1.broadcast(JSON.stringify(msg));
}

function funkcijaLED(msg) {
    wss2.broadcast(JSON.stringify(msg));
}