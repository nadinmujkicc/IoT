const http = require('http');

const host = '192.168.64.118';
const port = 80;

const server = http.createServer((req, res) => {
    res.statusCode = 200;
    res.setHeader('Content-Type', 'text/plain');
    res.end('Hello World\n');
});

server.listen(port, host, () => {
    console.log(`Server running at http://${host}:${port}/`);
});