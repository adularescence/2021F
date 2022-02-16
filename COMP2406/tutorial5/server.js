const http = require("http"); // import the http module, so that we can create a web server
const file = require("fs"); // import the fs (file system) module so that we read and write data to files
const url = require("url"); // import the url module so we can parse the web address of the request into readable parts


const host = "localhost"; // address of the server; localhost means that the server is referring to itself and is not accessible from the internet
const port = 8000; // port most commonly used by webservers

// process a request received, prepare and send a response back to the client
const processRequest = (request, response) => {
    const urlObject = url.parse(request.url, true); // parses the URL into readable parts

    // TODO 1: receive the request for the index.html web page, read the contents of the index.html webpage from the file system, and then send the contents of the web page as a response to the client
    if (urlObject.pathname === "/index.html") {
        file.readFile("index.html", (err, data) => {
            if (err) {
                throw err;
            }
            response.writeHeader(200, {
                "Content-Type": "text/html"
            });
            response.write(data);
            response.end();
        });
    }

    // TODO 2: receive the request for the t5.css CSS file, read contents of the t5.css file from the file system, and then send the contents of this file as a response to the client
    else if (urlObject.pathname === "/t5.css") {
        file.readFile("t5.css", (err, data) => {
            if (err) {
                throw err;
            }
            response.writeHeader(200, {
                "Content-Type": "text/css"
            });
            response.write(data);
            response.end();
        });
    }

    // TODO 3: receive the request for the t5.js JavaScript file, read contents of the t5.js file from the file system, and then send the contents of this file as a response to the client
    else if (urlObject.pathname === "/t5.js") {
        file.readFile("t5.js", (err, data) => {
            if (err) {
                throw err;
            }
            response.writeHeader(200, {
                "Content-Type": "text/javascript"
            });
            response.write(data);
            response.end();
        });
    }

    // TODO 4: receive the request for the students.js JavaScript file, read contents of the students.js file from the file system, and then send the contents of this file as a response to the client
    // else if (urlObject.pathname === "/students.js") {
    //     file.readFile("students.js", (err, data) => {
    //         if (err) {
    //             throw err;
    //         }
    //         response.writeHeader(200, {
    //             "Content-Type": "text/javascript"
    //         });
    //         response.write(data);
    //         response.end();
    //     });
    // }

    // TODO 5: receive the request for the students.json JSON file, read contents of the file from the file system, and then send the contents of this file as a response to the client
    else if (urlObject.pathname === "/students.json") {
        file.readFile("students.json", (err, data) => {
            if (err) {
                throw err;
            }
            response.writeHeader(200, {
                "Content-Type": "application/json"
            });
            response.write(data);
            response.end();
        });
    }

    else if (urlObject.pathname === "/newStudent" && request.method === "POST") {
        let body = "";
        request.on("data", (data) => {
            body += data;
        });
        request.on("end", () => {
            const newStudent = JSON.parse(body);
            updateStudents(newStudent);

            response.writeHeader(201);
            response.end();
        })
    }
}

const updateStudents = (newStudent) => {
    file.readFile("students.json", (readErr, data) => {
        if (readErr) {
            throw readErr;
        }
        const studentsJSON = JSON.parse(data.toString());
        studentsJSON.students.push(newStudent);
        
        const buffer = Buffer.from(JSON.stringify(studentsJSON), "utf-8");
        file.writeFile("students.json", buffer, (writeErr) => {
            if (writeErr) {
                throw writeErr;
            }
        });
    });
};

// run the server: node server.js
// if you make a change to your server code, you must restart the server

const server = http.createServer(processRequest); // create the server object

server.listen(port, host, () => { // Bind the port and host to the server
    console.log("Server is running!");
});