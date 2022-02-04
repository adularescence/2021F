const people = [
    {
        name: "John Doe",
        age: 24,
        occupation: "Crypto Trader",
        salary: -1000000
    },
    {
        name: "Johnny Appleseed",
        age: 19,
        occupation: "NFT Collector",
        salary: -40000
    },
    {
        name: "Hans Meier",
        age: 22,
        occupation: "Unemployed",
        salary: 0
    },
    {
        name: "Literally Me",
        age: 23,
        occupation: "Student",
        salary: -20000
    }
];

const print_people = (people_arr) => {
    console.log("==========================");
    console.log(". notation");
    console.log("==========================");
    people_arr.forEach((person) => {
        console.log(person.name);
        console.log(person.age);
        console.log(person.occupation);
        console.log(person.salary);
        console.log();
    });

    console.log("==========================");
    console.log("Objects.values method");
    console.log("==========================");
    people_arr.forEach((person) => {
        Object.values(person).forEach((val) => console.log(val));
        console.log("");
    });
}

// part 3
let part3_first = null;
let part3_second = null;
const part3_first_callback = () => {
    part3_first.style.visibility = "hidden";
    part3_second.style.visibility = "visible";
};
const part3_second_callback = () => {
    part3_first.style.visibility = "visible";
    part3_second.style.visibility = "hidden";
};


// part 4
let dropdown_menu = null;
let amount_textfield = null;
let submit_button = null;
let cart = null;

const cart_map = {
    "Almond milk": 0,
    "Whole milk": 0,
    "Salted butter": 0,
    "Grapes": 0,
    "Apples": 0,
    "Bananas": 0,
    "Spinach": 0,
    "Lettuce": 0
};

const dropdown_populate = () => {
    const dropdown_elements = [
        "Almond milk",
        "Whole milk",
        "Salted butter",
        "Grapes",
        "Apples",
        "Bananas",
        "Spinach",
        "Lettuce"
    ];

    for (let i = 0; i < dropdown_elements.length; i++) {
        let option = document.createElement("option");
        option.value = i;
        option.innerHTML = dropdown_elements[i];
        dropdown_menu.appendChild(option);
    }
}

const submit_button_callback = () => {
    let selected_option = "";
    dropdown_menu.childNodes.forEach((option) => {
        if (option.selected) {
            selected_option = option.innerHTML;
        }
    });
    if (selected_option === "") {
        alert("You have not selected anything.");
        return;
    }

    let amount = NaN;
    amount = parseInt(amount_textfield.value, 10);
    if (isNaN(amount) || amount <= 0) {
        alert("You have not specified a valid amount.");
        return;
    }

    cart_map[selected_option] += amount;
    let lines = 2;
    let cart_text = "Cart";
    Object.keys(cart_map).forEach((key) => {
        if (cart_map[key] !== 0) {
            cart_text += `\n${cart_map[key]}x ${key}`;
            lines++;
        }
    });
    cart.value = cart_text;
    cart.style.height = `${lines}em`;
}

const afterLoaded = () => {
    if (document.title === 'Tutorial 2 - Part 3') {
        part3_first = document.getElementById("part2a-first");
        part3_second = document.getElementById("part2a-second");

        part3_first.addEventListener("click", part3_first_callback);
        part3_second.addEventListener("click", part3_second_callback);
        part3_second_callback();
    } else if (document.title === 'Tutorial 2 - Part 4') {
        dropdown_menu = document.getElementById("dropdown");
        amount_textfield = document.getElementById("amount-textfield");
        submit_button = document.getElementById("submit-button");
        cart = document.getElementById("cart");
        cart.value = "Cart";

        submit_button.addEventListener("click", submit_button_callback);
        dropdown_populate();
    }
}

if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', afterLoaded);
} else {
    afterLoaded();
}

print_people(people);