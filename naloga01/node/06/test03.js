const http = require('http');
const fs = require('fs');
const { dirname } = require('path');

const host = '192.168.64.118';
const port = 80;

const server = http.createServer((req, res) => {
    if (req.url === '/') {
        fs.readFile(__dirname + '/primer02.html', (err, data) => {
            if (err) {
                res.writeHead(500, { 'Content-Type': 'text/plain' });
                return res.end('Error loading primer02.html');
            }
            res.writeHead(200);
            res.end(data);
        });
    }

    if (req.url === '/sx') {
        fs.readFile(__dirname + '/primer03x.html', (err, data) => {
            if (err) {
                res.writeHead(500, { 'Content-Type': 'text/plain' });
                return res.end('Error loading primer03x.html');
            }
            res.writeHead(200);
            res.end(data);
        });
    }

    if (req.url === '/sy') {
        fs.readFile(__dirname + '/primer03y.html', (err, data) => {
            if (err) {
                res.writeHead(500, { 'Content-Type': 'text/plain' });
                return res.end('Error loading primer03y.html');
            }
            res.writeHead(200);
            res.end(data);
        });
    }
});

server.listen(port, host, () => {
    console.log(`Server running at http://${host}:${port}/`);
});