const checkTextField_ids = ["snum", "fname", "lname", "agrade", "tgrade", "egrade"];

// see line 168
const afterLoaded = () => {
    populateStudents();
    checkTextField_ids.forEach((elem) => {
        document.getElementById(elem).addEventListener("input", checkTextField);
    });
};


// adds/removes classes from element according to becomeValid
const setValidity = (element, becomeValid) => {
    if (becomeValid) {
        element.classList.add("valid");
        element.classList.remove("invalid");
    } else {
        element.classList.add("invalid");
        element.classList.remove("valid");
    }
}

const checkTextField = (event) => {
    const target = event.target;
    const value = target.value;
    switch (target.id) {
        case "snum":
            // valid student IDs are 9 digits
            if (value.match(/^\d{9}$/) === null) {
                setValidity(target, false);
            } else {
                setValidity(target, true);
            }
            break;
        case "fname":
        case "lname":
            // first/last names should start with a capital letter, then any number of lower case letters
            if (value.match(/^[A-Z][a-z]+$/) === null) {
                setValidity(target, false);
            } else {
                setValidity(target, true);
            }
            break;
        case "agrade":
        case "tgrade":
        case "egrade":
            // any grade can has up to 3 digits
            // then . and any number of digits after (optional)
            if (value.match(/^\d{1,3}(\.\d*)?$/) === null) {
                setValidity(target, false);
            } else {
                // ensure that the grade is between 0 and 100, inclusive
                const grade_float = parseFloat(value, 10);
                if (grade_float < 0 || grade_float > 100) {
                    setValidity(event.target, false);
                } else {
                    setValidity(event.target, true);
                }
            }
            break;
    }

    // if all fields are valid, enable the submit button
    // else dont
    const allGreen = document.getElementsByClassName("valid").length === 6;
    const btnSubmit = document.getElementById("btnSubmit");
    if (allGreen) {
        btnSubmit.disabled = false;
    } else {
        btnSubmit.disabled = true;
    }
};

const processForm = () => {
    const new_student = {
        snum: "",
        fname: "",
        lname: "",
        agrade: 0,
        tgrade: 0,
        egrade: 0
    };

    const table = document.querySelector("table");
    const row = document.createElement("tr");
    checkTextField_ids.forEach((id) => {
        const cell = document.createElement("td");
        const content = document.getElementById(`${id}`).value;
        switch (id) {
            case "snum":
            case "fname":
            case "lname":
                cell.textContent = content;
                new_student[`${id}`] = content;
                break;
            case "agrade":
            case "tgrade":
            case "egrade":
                const truncated = parseFloat(content, 10).toFixed(2);
                cell.textContent = truncated;
                new_student[`${id}`] = truncated;
                break;
        };
        row.append(cell);
    });
    table.appendChild(row);

    // just in case?
    students.push(new_student);
};

// populate the table with student data from students.js file. We're reading information
// from an on object and using that to populate the table
const populateStudents = (reset = false) => {
    let table = document.querySelector("table");

    // iterate through all the objects in the students array
    for (let student of students) {
        // save the information for the current in variables
        let studentID = student.snum;
        let firstName = student.fname;
        let lastName = student.lname;
        let assignmentGrade = student.agrade;
        let tutorialGrade = student.tgrade;
        let examGrade = student.egrade;

        // time to create a new HTML element!
        // 1). we first need to create a new row
        let row = document.createElement("tr");

        // create a cell for the student ID, update its text value, and append it to the row
        let iDCell = document.createElement("td");
        iDCell.textContent = studentID;
        row.appendChild(iDCell);

        // create a cell for the first name, update its text value, and append it to the row
        let fNameCell = document.createElement("td");
        fNameCell.textContent = firstName;
        row.appendChild(fNameCell);

        // create a cell for the last name, update its text value, and append it to the row
        let lNameCell = document.createElement("td");
        lNameCell.textContent = lastName;
        row.appendChild(lNameCell);

        // create a cell for the assignment grade, update its text value, and append it to the row
        let aGradeCell = document.createElement("td");
        aGradeCell.textContent = assignmentGrade.toFixed(2);
        row.appendChild(aGradeCell);


        // create a cell for the tutorial grade, update its text value, and append it to the row
        let tGradeCell = document.createElement("td");
        tGradeCell.textContent = tutorialGrade.toFixed(2);
        row.appendChild(tGradeCell);

        // create a cell for the exam grade, update its text value, and append it to the row
        let eGradeCell = document.createElement("td");
        eGradeCell.textContent = examGrade.toFixed(2);
        row.appendChild(eGradeCell);

        // append the row to the table
        table.appendChild(row);
    }
};


// apparently, the HTML usually isn't loaded by the time the JS is ready to run
// so we call a function with all the setup stuff after it loads
if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", afterLoaded);
} else {
    afterLoaded();
}