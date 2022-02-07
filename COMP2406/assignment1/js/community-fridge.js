// 'global' elements
let title, body, menu_button, contents_div, pickup_list_div;
let pickup_items = {};
let filters = [];




// methods to create a page

// creates the main page
const create_main_page = () => {
    wipe();

    // head changes
    const titleText = "Community Fridge Management System";
    title.text = titleText;

    // body changes, add event listeners
    body.id = "main-page";

    const h1 = document.createElement("h1");
    h1.innerHTML = titleText;
    body.appendChild(h1);

    const button_ids_innerHTML = {
        "pick-up": "Pick up an item",
        "drop-off": "Drop off an item",
        "search-for": "Search for an item"
    };
    Object.entries(button_ids_innerHTML).forEach(([id, innerHTML]) => {
        const button = document.createElement("button");
        button.id = id;
        button.innerHTML = innerHTML;

        button.addEventListener("mouseenter", (event) => event.target.classList.add("mouseenter"));
        button.addEventListener("mouseleave", (event) => event.target.classList.remove("mouseenter"));

        let callback;
        switch (id) {
            case "pick-up":
                callback = create_choose_fridge;
                break;
            default:
                // the last two functionalities of “dropping off an item” and “searching for an item” are placeholders and not functional
                callback = () => alert("placeholder button");
                break;
        }
        button.addEventListener("click", callback);

        body.appendChild(button);
    });
};

// creates the fridge selection pages
const create_choose_fridge = () => {
    wipe();
    display_menu_button();

    // head changes
    const titleText = "Available fridges";
    title.text = titleText;

    // body changes, add event listeners
    body.id = "choose-fridge";

    const h1 = document.createElement("h1");
    h1.innerHTML = titleText;
    body.appendChild(h1);

    // buttons for the fridges with contact info and an image
    const fridge_ids = fridges.map((fridge) => fridge.name.replaceAll(" ", "-"));
    for (let i = 0; i < fridge_ids.length; i++) {
        const fridge = fridges[i];

        const image = document.createElement("img");
        image.src = "images/fridge.svg";
        image.id = fridge_ids[i];

        const button = document.createElement("button");
        button.appendChild(image);
        button.id = fridge_ids[i];
        button.innerHTML += `<br>${fridge.name}<br>${fridge.address.street}<br>${fridge.contact_phone}`;

        button.addEventListener("mouseenter", (event) => event.target.classList.add("mouseenter"));
        button.addEventListener("mouseleave", (event) => event.target.classList.remove("mouseenter"));

        button.addEventListener("click", create_fridge_contents);

        body.appendChild(button);
    };
};

// creates the fridge content's page
const create_fridge_contents = (event) => {
    wipe();
    display_menu_button();
    const selected_fridge = fridges.filter((fridge) => fridge.name === event.target.id.replaceAll("-", " "))[0];

    // head changes
    const titleText = `Items in the ${selected_fridge.name}`;
    title.text = titleText;

    // body changes, add event listeners
    body.id = "fridge-contents";

    const h1 = document.createElement("h1");
    h1.innerHTML = titleText;
    body.appendChild(h1);

    const items_in_the_fridge_div = document.createElement("div");

    // create 3 divs, so that they may be styled with flex
    // fridge metadata
    const fridge_metadata_div = document.createElement("div");
    fridge_metadata_div.id = "fridge-metadata"
    create_fridge_metadata(fridge_metadata_div, selected_fridge);
    items_in_the_fridge_div.appendChild(fridge_metadata_div)

    // fridge contents
    contents_div = document.createElement("div");
    contents_div.id = "contents"
    create_contents_list(contents_div, Object.values(selected_fridge.items));
    items_in_the_fridge_div.appendChild(contents_div);

    // pick up list
    pickup_list_div = document.createElement("div");
    pickup_list_div.id = "pickup-list";
    create_pickup_list(pickup_list_div);
    items_in_the_fridge_div.appendChild(pickup_list_div);

    body.appendChild(items_in_the_fridge_div);
};




// helper methods

// wipes the page
const wipe = () => {
    while (body.lastElementChild) {
        body.removeChild(body.lastElementChild);
    }
    body.removeAttribute("id");
    menu_button.classList.add("hide");
    pickup_items = {};
    filters = [];
};

// toggles the menu button's visibility
const display_menu_button = () => {
    menu_button.classList.remove("hide");
};

// appends selected fridge's metadata elements to the parent
// contact info, capacity, filters
// parent: a div
const create_fridge_metadata = (parent, selected_fridge) => {
    const fridge_metadata_h2 = document.createElement("h2");
    fridge_metadata_h2.innerHTML = selected_fridge.name;
    parent.appendChild(fridge_metadata_h2);

    const fridge_address = document.createElement("p");
    fridge_address.innerHTML = selected_fridge.address.street;
    parent.appendChild(fridge_address);

    const fridge_phone = document.createElement("p");
    fridge_phone.innerHTML = selected_fridge.contact_phone;
    parent.appendChild(fridge_phone);

    const fridge_capacity_p = document.createElement("p");
    fridge_capacity_p.innerHTML = "Current capacity:";
    parent.appendChild(fridge_capacity_p);

    const fridge_capacity_div = document.createElement("div");
    fridge_capacity_div.id = "capacity";
    fridge_capacity_div.style.height = "1em";
    fridge_capacity_div.style.width = `${selected_fridge.capacity}%`;
    fridge_capacity_div.innerHTML = `${selected_fridge.capacity}%`;
    if (selected_fridge.capacity === 100) {
        fridge_capacity_div.style.borderTopRightRadius = "0.5em";
        fridge_capacity_div.style.borderBottomRightRadius = "0.5em";
    }
    parent.appendChild(fridge_capacity_div);

    const filter_ul = document.createElement("ul");
    filter_ul.id = "filter";
    ["produce", "dairy", "bakery", "frozen", "pantry", "meat and seafood"].forEach((filter) => {
        const filter_li = document.createElement("li");
        const filter_item_count = Object.values(selected_fridge.items).filter((item) => item.type === filter).length;
        filter_li.innerHTML = `${filter.charAt(0).toUpperCase()}${filter.substring(1).toLowerCase()} (${filter_item_count})`;

        // Part 3.3.d [display] A hover effect should be applied to each element in the left menu.
        // Part 3.3.f [interaction] Clicking on a category with 0 items should not do anything.
        // why even let the ones with 0 items have a hover effect when you can't even select them
        // bad ui design
        // but I must code to the requirements
        if (filter_item_count !== 0) {
            filter_li.addEventListener("click", (event) => {
                // purge contents list
                contents_div.childNodes[0].remove();
    
                // if unselecting a filter
                const current_filter = Object.values(event.target.parentNode.childNodes).filter((li) => li.classList.contains("filtered"));
                if (current_filter.length !== 0) {
                    current_filter[0].classList.remove("filtered");
                    if (current_filter[0] === event.target) {
                        create_contents_list(contents_div, Object.values(selected_fridge.items));
                        return;
                    }
                }
                event.target.classList.add("filtered");
    
                // get clicked filter's name
                const target_textContent = event.target.textContent;
                const desired_filter = target_textContent.substring(0, target_textContent.lastIndexOf(" ")).toLowerCase();
    
                // recreate contents list
                create_contents_list(contents_div, Object.values(selected_fridge.items), desired_filter);
            });
        }
        
        // hover effect for filters
        filter_li.addEventListener("mouseenter", (event) => event.target.classList.add("mouseenter"));
        filter_li.addEventListener("mouseleave", (event) => event.target.classList.remove("mouseenter"));
        filter_ul.appendChild(filter_li);
    });
    parent.appendChild(filter_ul);
};

// appends items' metadata elements to parent
// name, quantity, pickup buttons
// parent: a div
// items: items object of a fridge object
// filter: select * where type = filter
const create_contents_list = (parent, items, filter = null) => {
    // filter items
    if (filter !== null) {
        items = items.filter((item) => item.type === filter);
    }

    // create the list
    const contents_ul = document.createElement("ul");
    items.forEach((item) => {
        const item_li = document.createElement("li");

        // need a div for Part 3.4.b
        const img_div = document.createElement("div");
        img_div.id = "img-div";

        const img = document.createElement("img");
        img.src = item.img;
        img.style.height = "4em";
        img_div.appendChild(img);
        item_li.appendChild(img_div);

        // need a div for Part 3.4.b
        const item_metadata_ul_wrapper_div = document.createElement("div");
        item_metadata_ul_wrapper_div.id = "item-metadata-div";
        const item_metadata_ul = document.createElement("ul");
        item_metadata_ul_wrapper_div.appendChild(item_metadata_ul);
        item_li.appendChild(item_metadata_ul_wrapper_div);

        // name
        const metadata_name_li = document.createElement("li");
        metadata_name_li.innerHTML = item.name;
        item_metadata_ul.appendChild(metadata_name_li);

        // quantity
        const metadata_quantity_li = document.createElement("li");
        metadata_quantity_li.innerHTML = `Quantity: ${item.quantity}`;
        item_metadata_ul.appendChild(metadata_quantity_li);

        // pickup amount increment/decrement
        const pickup_item_li = document.createElement("li");
        pickup_item_li.innerHTML = "Pickup item: ";
        item_metadata_ul.appendChild(pickup_item_li);

        const minus_button = document.createElement("button");
        minus_button.innerHTML = "-";
        minus_button.classList.add("pickup-decrement-button");
        minus_button.addEventListener("click", modify_cart);
        pickup_item_li.appendChild(minus_button);

        const pickup_quantity = document.createElement("textarea");
        pickup_quantity.style.resize = "none";
        pickup_quantity.style.height = "1em";
        pickup_quantity.style.width = "2em";
        pickup_quantity.style.userSelect = "none";
        if (item.name in pickup_items) {
            pickup_quantity.value = pickup_items[`${item.name}`];
        } else {
            pickup_quantity.value = 0;
        }
        pickup_quantity.readOnly = true;
        pickup_item_li.appendChild(pickup_quantity);

        const plus_button = document.createElement("button");
        plus_button.innerHTML = "+";
        plus_button.classList.add("pickup-increment-button");
        plus_button.addEventListener("click", modify_cart);
        pickup_item_li.appendChild(plus_button);

        contents_ul.appendChild(item_li);
    });

    // add class for CSS rule that adds lines between li elements
    const item_count = contents_ul.childNodes.length;
    if (item_count > 0) {
        for (let i = 0; i < item_count - 1; i++) {
            contents_ul.childNodes[i].classList.add("not-last");
        }
        contents_ul.childNodes[item_count - 1].classList.add("last");
    }

    parent.append(contents_ul);
};

// appends pickup list to parent
// parent: a div
const create_pickup_list = (parent) => {
    const text = document.createElement("h3");
    text.innerHTML = "You have picked up the following items:";
    parent.append(text);
};

// callback for the +- buttons for each item
// ensures that the quantities are respected and then updates the "cart" accordingly
const modify_cart = (event) => {
    // determine if source is increment/decrement
    const increment = event.target.classList[0] === "pickup-increment-button";

    // determine 
    const item_name = event.target.parentNode.parentNode.childNodes[0].textContent;
    const pickup_quantity_elem = event.target.parentNode.querySelector("textarea");
    const max_pickup = parseInt(Object.values(event.target.parentNode.parentNode.childNodes).filter((elem) => elem.textContent.match(/^Quantity: \d$/) !== null)[0].textContent.slice(-1));
    let pickup_quantity = parseInt(pickup_quantity_elem.value, 10);
    if (increment && pickup_quantity !== max_pickup) {
        pickup_quantity++;
    } else if (!increment && pickup_quantity !== 0) {
        pickup_quantity--;
    }
    pickup_quantity_elem.value = pickup_quantity;

    // update "cart"
    pickup_items[`${item_name}`] = pickup_quantity;
    Object.values(pickup_list_div.childNodes).filter((node) => node.tagName === "P").forEach((node) => node.remove());
    Object.entries(pickup_items).forEach(([key, value]) => {
        if (value !== 0) {
            const p = document.createElement("p");
            p.innerHTML = `${value} x ${key}`;
            pickup_list_div.appendChild(p);
        }
    });
};




// 'main' method
const after_loaded = () => {
    title = document.querySelector("title");
    body = document.querySelector("body");

    const menu_icon = document.createElement("i");
    menu_icon.classList.add("material-icons");
    menu_icon.innerHTML = "menu";
    menu_button = document.createElement("button");
    menu_button.appendChild(menu_icon);
    menu_button.id = "menu-button";
    menu_button.classList.add("hide");
    menu_button.addEventListener("click", create_main_page);
    document.querySelector("html").appendChild(menu_button);

    create_main_page();
};

if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", after_loaded)
} else {
    after_loaded()
}
