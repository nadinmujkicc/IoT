const http = require('http');
const fs = require('fs');
const { dirname } = require('path');

const host = '192.168.64.118';
const port = 80;

const server = http.createServer((req, res) => {
    fs.readFile(__dirname + '/primer02.html', (err, data) => {
        if (err) {
            res.writeHead(500, { 'Content-Type': 'text/plain' });
            return res.end('Error loading primer02.html');
        }
        res.writeHead(200);
        res.end(data);
    });
});

server.listen(port, host, () => {
    console.log(`Server running at http://${host}:${port}/`);
});