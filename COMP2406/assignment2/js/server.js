const http = require("http"); // import the http module, so that we can create a web server
const file = require("fs"); // import the fs (file system) module so that we read and write data to files
const url = require("url"); // import the url module so we can parse the web address of the request into readable parts
const path = require("path/posix");


const host = "localhost"; // address of the server; localhost means that the server is referring to itself and is not accessible from the internet
const port = 8000; // port most commonly used by webservers

// process a request received, prepare and send a response back to the client
const processRequest = (request, response) => {
    const urlObject = url.parse(request.url, true); // parses the URL into readable parts
    const pathname = urlObject.pathname;
    const filename = pathname.slice(pathname.indexOf('/'));

    // all .html file
    if (pathname.indexOf(".html") !== -1) {
        file.readFile(`..${filename}`, (err, data) => {
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

    // all .css files
    else if (pathname.indexOf(".css") !== -1) {
        file.readFile(`..${filename}`, (err, data) => {
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

    // all .json files
    else if (pathname.indexOf(".json") !== -1) {
        file.readFile(`.${filename}`, (err, data) => {
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

    // all .js files
    else if (pathname.indexOf(".js") !== -1) {
        file.readFile(`..${filename}`, (err, data) => {
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

    // all images in images/
    else if (pathname.indexOf("/images/") !== -1) {
        const imageFilename = filename.slice(filename.indexOf("/images/") + 8);
        const imageFiletype = filename.slice(filename.lastIndexOf(".") + 1);
        let mimeType = `image/${imageFiletype}`;
        if (imageFiletype === "svg") {
            mimeType = `image/svg+xml`;
        }
        // switch (imageFiletype) {
        //     case "jpeg":
        //         mimeType = "image/jpeg";
        //         break;
        //     case "svg":
        //         mimeType = "image/svg+xml";
        //         break;
        //     case "png":
        //         mimeType = "image/png";
        //         break;
        // }
        file.readFile(`../images/${imageFilename}`, (err, data) => {
            if (err) {
                throw err;
            }
            response.writeHeader(200, {
                "Content-Type": mimeType
            });
            response.write(data);
            response.end();
        });
    }

    // favicon.ico only
    else if (pathname === "/favicon.ico") {
        file.readFile("../favicon.ico", (err, data) => {
            if (err) {
                throw err;
            }
            response.writeHeader(200, {
                "Content-Type": "image/x-icon"
            });
            response.write(data);
            response.end();
        });
    }

    else if (pathname === "/updateFridge" && request.method === "PUT") {
        let body = "";
        request.on("data", (data) => body += data);
        request.on("end", () => {
            const json = JSON.parse(body);
            updateFridge(json, response);
        });
    }

    else if (pathname === "/newItem" && request.method === "POST") {
        let body = "";
        request.on("data", (data) => body += data);
        request.on("end", () => {
            const json = JSON.parse(body);
            addItem(json, response);
        });
    }

};

const updateFridge = (payload, response) => {
    file.readFile("comm-fridge-data.json", (readErr, data) => {
        if (readErr) {
            throw readErr;
        }
        const commFridgeDataJSON = JSON.parse(data.toString());
        const targetFridge = commFridgeDataJSON.filter((fridge) => fridge.name === payload.fridge)[0];
        const targetItem = targetFridge.items.filter((item) => item.name === payload.itemName);

        targetFridge.num_items_accepted += payload.quantity;
        targetFridge.can_accept_items -= payload.quantity;
        if (targetItem.length === 1) {
            targetItem.quantity += payload.quantity;
        } else {
            targetFridge.items.push({
                name: payload.itemName,
                quantity: payload.quantity,
                type: payload.itemType,
                img: payload.itemImg
            });
        }

        const buffer = Buffer.from(JSON.stringify(commFridgeDataJSON), "utf-8");
        file.writeFile("comm-fridge-data.json", buffer, (writeErr) => {
            if (writeErr) {
                throw writeErr;
            }
            response.writeHeader(200);
            response.end();
        });
    });
};

const addItem = (payload, response) => {
    const name = payload.name;
    const type = payload.type;
    const path = payload.path.replaceAll(" ", "_");
    const base64 = payload.data.split(";base64,").pop();
    let imageExists = false;
    try {
        imageExists = file.existsSync(payload.path);
    } catch (err) {
        console.log(err);
    }
    if (!imageExists) {
        // makes dir if not exists
        file.mkdirSync(`../images/${type}`, {recursive: true});

        // write image file
        file.writeFileSync(`..${path}`, base64, {encoding: "base64"}, (writeErr) => {
            if (writeErr) {
                throw writeErr;
            }
        });
    }

    file.readFile("comm-fridge-items.json", (readErr, data) => {
        if (readErr) {
            throw readErr;
        }
        const commFridgeItemsJSON = JSON.parse(data.toString());
        commFridgeItemsJSON.push({
            name: name,
            type: type,
            img: `http://localhost:8000${path}`
        });

        const buffer = Buffer.from(JSON.stringify(commFridgeItemsJSON), "utf-8");
        file.writeFile("comm-fridge-items.json", buffer, (writeErr) => {
            if (writeErr) {
                throw writeErr;
            }
            response.writeHeader(201);
            response.end();
        });
    });
};

const server = http.createServer(processRequest); // create the server object

server.listen(port, host, () => { // Bind the port and host to the server
    console.log("Server is running!");
});