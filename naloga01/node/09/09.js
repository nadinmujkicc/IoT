import * as http from "http";
import express from "express";
import ip from "ip";
import { join, dirname } from "path";
import { fileURLToPath } from "url";
import WebSocket, { WebSocketServer } from "ws";

const __dirname = dirname(fileURLToPath(import.meta.url));
const app = express();

const hostname = "0.0.0.0";
const port = 8080;

const server = http.createServer(app).listen(port);

const wss1 = new WebSocketServer({ port: 8888 });
const wss2 = new WebSocketServer({ port: 8811 });

app.get("/", (req, res) => {
    res.sendFile(join(__dirname, "09.html"));
});

wss2.broadcast = function broadcast(data) {
    wss2.clients.forEach(function each(client) {
        if (client.readyState === WebSocket.OPEN) {
            client.send(data);
        }
    });
};

wss1.broadcast = function broadcast(data) {
    wss1.clients.forEach(function each(client) {
        if (client.readyState === WebSocket.OPEN) {
            client.send(data);
        }
    });
};

wss1.on("connection", function (ws, req) {
    console.log("Klijent - brskalnik Chrome se je povezal na port 8888");
    ws.on("message", function (msgString) {
        console.log("Primljena poruka od Chrome-a: " + msgString);
        try {
            var msg = JSON.parse(msgString);
            switch (msg.tipSporocila) {
                case "LED":
                    funkcijaLED(msg);
                    break;
            }
        } catch (e) {
            console.error("Greška u JSON-u iz Chrome-a");
        }
    });
});

wss2.on("connection", function (ws, req) {
    console.log("ESP32 se je povezal na port 8811");
    ws.on("message", function (msgString) {
        console.log("Primljeno sa ESP32: " + msgString);
        try {
            var msg = JSON.parse(msgString);
            switch (msg.tipSporocila) {
                case "potenciometar":
                    funkcijaPotenciometar(msg);
                    break;
            }
        } catch (e) {
            console.error("Greška u JSON-u iz ESP32");
        }
    });
});

console.log("Streznik zagnan...");
console.log("Adresa za Chrome: http://" + ip.address() + ":" + port);

function funkcijaLED(msg) {
    wss2.broadcast(JSON.stringify(msg));
}

function funkcijaPotenciometar(msg) {
    wss1.broadcast(JSON.stringify(msg));
}