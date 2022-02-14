let xhttp; // variable to store the XMLHttpRequest object

// object which stores information about the specific type of vaccince
let vaccines = {};
// Prototype of the object (key = vaccine name, value = object)
// type1: {doses: , first_date: , last_date: , most_amount: , most_date: },
// type2: {doses: , first_date: , last_date: , most_amount: , most_date: },

// specifies what should happen when the window of the browser loads
window.onload = () => {
    // call the requestData function to perform an AJAX request to retrieve data from the URL provided
    requestData("https://opendata.arcgis.com/datasets/691e786f545349c6a4f23341ddfcad41_0.geojson");
};

// sends a request to the server to retrieve the data from the specified URL
const requestData = (URL) => {
    // create a new XMLHttpRequest object and send the request to the server
    xhttp = new XMLHttpRequest();
    xhttp.open('GET', URL, true);
    xhttp.send();
    xhttp.onreadystatechange = loadCovidData;
};

// processes results from the AJAX query. Specifically, this function reviews the data returned and then organizes the relevant parts in the vaccines object
const loadCovidData = () => {
    if (xhttp.readyState === XMLHttpRequest.DONE && xhttp.status === 200) {
        // JSON data returned by the AJAX request
        let data = xhttp.responseText;

        // Before we can use the data as objects, we first have to convert it into JSON objects using the parse function
        let results = JSON.parse(data);

        // it looks like most of the data we want is located within the features attribute, which is an object itself
        let features = results.features;

        // iterate over the all the rows in the features object to populate the vaccines object defined at the top of this file. Review the prototype of the object above to get an understanding of how to populate it
        features.forEach((feature) => {
            const props = feature.properties;
            if (!(props.Type_of_Vaccine in vaccines)) {
                // probably ok to use today's date as the first_date (to compare against)
                const today = new Date();
                vaccines[`${props.Type_of_Vaccine}`] = {
                    doses: 0,
                    first_date: today.toString(),
                    last_date: null,
                    most_amount: 0,
                    most_date: null
                };
            }
            // increment doses
            vaccines[`${props.Type_of_Vaccine}`].doses += props.Number_of_doses_administered_in;

            //check if new first date
            const featureDate = new Date(props.Date);
            if (featureDate < new Date(vaccines[`${props.Type_of_Vaccine}`].first_date)) {
                vaccines[`${props.Type_of_Vaccine}`].first_date = formatDate(featureDate);
            }

            // check if new last date
            if (featureDate > new Date(vaccines[`${props.Type_of_Vaccine}`].last_date)) {
                vaccines[`${props.Type_of_Vaccine}`].last_date = formatDate(featureDate);
            }

            // check if new most doses
            if (props.Number_of_doses_administered_in > vaccines[`${props.Type_of_Vaccine}`].most_amount) {
                vaccines[`${props.Type_of_Vaccine}`].most_amount = props.Number_of_doses_administered_in;
                vaccines[`${props.Type_of_Vaccine}`].most_date = formatDate(featureDate);
            }
        });

        // call the createContent method to create the DOM for the radio buttons
        createContent();
    }
    else {
        console.log("There was a problem with the request.");
    }
}

// TODO: populates the DOM for the radio buttons. It is called from the loadCOVIDData() function
const createContent = () => {
    const vaccineInfo = document.getElementById("vaccine_info");

    Object.keys(vaccines).forEach((vaccine) => {
        const inputElem = document.createElement("input");
        
        inputElem.setAttribute("type", "radio");
        inputElem.addEventListener("click", showResults);
        inputElem.name = "vaccine-radio"

        const label = document.createElement("label");
        label.innerHTML = `${vaccine}<br>`;
        switch (vaccine) {
            case "AstraZeneca":
                inputElem.id = "az";
                label.htmlFor = "az";
                break;
            case "Johnson & Johnson":
                inputElem.id = "jj";
                label.htmlFor = "jj";
                break;
            case "Moderna":
                inputElem.id = "mo";
                label.htmlFor = "mo";
                break;
            case "Pediatric Pfizer":
                inputElem.id = "pp";
                label.htmlFor = "pp";
                break;
            case "Pfizer":
                inputElem.id = "pf";
                label.htmlFor = "pf";
                break;
        }

        vaccineInfo.appendChild(inputElem);
        vaccineInfo.appendChild(label);
    });
};

// TODO: processes the events on the radio buttons. Specifically, it displays data associated with the user's selection in the results section on the right hand side of the screen
const showResults = (event) => {
    let vaccine;
    switch (event.target.id) {
        case "az":
            vaccine = "AstraZeneca";
            break;
        case "jj":
            vaccine = "Johnson & Johnson";
            break;
        case "mo":
            vaccine = "Moderna";
            break;
        case "pp":
            vaccine = "Pediatric Pfizer";
            break;
        case "pf":
            vaccine = "Pfizer";
            break;
    }
    const vaccineDetails = vaccines[`${vaccine}`];

    const viewResults = document.getElementById("view_results");
    while (viewResults.lastElementChild) {
        viewResults.removeChild(viewResults.lastElementChild);
    }
    viewResults.classList.remove("hidden");

    const viewResultsH2 = document.createElement("h2");
    viewResultsH2.textContent = `${vaccine} details`;
    viewResults.appendChild(viewResultsH2);

    const viewResultsUl = document.createElement("ul");
    Object.entries(vaccineDetails).forEach(([key, value]) => {
        // type2: {doses: , first_date: , last_date: , most_amount: , most_date: },
        const li = document.createElement("li");
        switch (key) {
            case "doses":
                li.textContent = `Total number of doses: ${value}`;
                break;
            case "first_date":
                li.textContent = `Start period: ${value}`;
                break;
            case "last_date":
                li.textContent = `End period: ${value}`;
                break;
            case "most_amount":
                return;
            case "most_date":
                li.textContent = `Date most doses received: ${value} (${vaccineDetails.most_amount})`;
                break;
        }
        viewResultsUl.appendChild(li);
    })
    viewResults.appendChild(viewResultsUl);
};

// returns Date object as YYYY-MM-DD string
const formatDate = (date) => {
    let month = date.getMonth() + 1;
    if (month < 10) {
        month = `0${month}`;
    }
    return `${date.getFullYear()}-${month}-${date.getDate()}`;
};