
const http = require('http');
const fs = require("fs");

//Create a server, giving it the handler function
//Request represents the incoming request object
//Response represents the outgoing response object
//Remember, you can break this apart to make it look cleaner
const server = http.createServer(function (request, response) {
    console.log(request.url);
    if(request.method === "GET"){
        if(request.url === "/" || request.url === "/todo.html"){
            //read the todo.html file and send it back
            fs.readFile("todo.html", function(err, data){
                if(err){
                    response.statusCode = 500;
                    response.write("Server error.");
                    response.end();
                    return;
                }
                response.statusCode = 200;
                response.setHeader("Content-Type", "text/html");
                response.write(data);
                response.end();
            });
        }else if(request.url === "/todo.js"){
            //read todo.js file and send it back
            fs.readFile("todo.js", function(err, data){
                if(err){
                    response.statusCode = 500;
                    response.write("Server error.");
                    response.end();
                    return;
                }
                response.statusCode = 200;
                response.setHeader("Content-Type", "application/javascript");
                response.write(data);
                response.end();
            });
        } else if (request.url === "/list") {
            response.statusCode = 200;
            response.setHeader("Content-Type", "applicaton/json");
            response.write(JSON.stringify(listObj));
            response.end();
        //Add any more 'routes' and their handling code here
        //e.g., GET requests for "/list", POST request to "/list"
        }else{
            response.statusCode = 404;
            response.write("Unknwn resource.");
            response.end();
        }
    }else if(request.method === "POST") {
        if (request.url === "/newitem") {
            let body = "";
            request.on("data", (chunk) => body += chunk);
            request.on("end", () => {
                const newItem = JSON.parse(body);
                listObj.list.push({
                    name: newItem.name,
                    light: newItem.light,
                    checked: newItem.checked
                })
            });

            response.statusCode = 201;
            response.end();
        } else {
            response.statusCode = 404;
            response.write("Unknwn resource.");
            response.end();
        }
    } else if (request.method === "PUT") {
        if (request.url === "/deleteitems") {
            let body = "";
            request.on("data", (chunk) => body += chunk);
            request.on("end", () => {
                const targetsToKeep = JSON.parse(body).targetsToKeep;
                const newItems = [];
                targetsToKeep.forEach(target => {
                    listObj.list.forEach(elem => {
                        if (elem.name === target) {
                            newItems.push(elem);
                        }
                    });
                });
                listObj.list = newItems;
            });
        } else {
            response.statusCode = 404;
            response.write("Unknwn resource.");
            response.end();
        }
    }
});

const listObj = {
    list: [
        {
            name: "Lorem ipsum",
            light: false,
            checked: false
        },
        {
            name: "dolor sit amet",
            light: false,
            checked: false
        },
        {
            name: "consectetur adipiscing",
            light: false,
            checked: false
        }
    ]
};

//Server listens on port 3000
server.listen(3000);
console.log('Server running at http://127.0.0.1:3000/');
