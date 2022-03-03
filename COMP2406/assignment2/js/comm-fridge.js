// 'global' elements
let title, body, menu_button, contents_div, pickup_list_div, drop_off_submit, add_item_submit;
let pickup_items = {};
let filters = [];
let fridges = [];
let availableItems = [];
let validSelectedItem, validNumberOfItems;
let validNewItemName, validNewItemType, validNewItemImage;
let dropOffObject = {
    name: "",
    number: -1,
    img: ""
};




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
                callback = () => {
                    const getFridgeDataXhttp = new XMLHttpRequest();
                    getFridgeDataXhttp.open("GET", "http://localhost:8000/comm-fridge-data.json", true);
                    getFridgeDataXhttp.send();
                    getFridgeDataXhttp.onreadystatechange = () => {
                        if (getFridgeDataXhttp.readyState === XMLHttpRequest.DONE && getFridgeDataXhttp.status === 200) {
                            const fridgeData = getFridgeDataXhttp.responseText;
                            fridges = JSON.parse(fridgeData);
                            
                            const getFridgeItemsXhttp = new XMLHttpRequest();
                            getFridgeItemsXhttp.open("GET", "http://localhost:8000/comm-fridge-items.json", true);
                            getFridgeItemsXhttp.send();
                            getFridgeItemsXhttp.onreadystatechange = () => {
                                if (getFridgeItemsXhttp.readyState === XMLHttpRequest.DONE && getFridgeItemsXhttp.status === 200) {
                                    const fridgeItems = getFridgeItemsXhttp.responseText;
                                    availableItems = JSON.parse(fridgeItems);

                                    create_choose_fridge();
                                }
                            };
                        }
                    };
                };
                break;
            case "drop-off":
                callback = () => {
                    const xhttp = new XMLHttpRequest();
                    xhttp.open("GET", "http://localhost:8000/comm-fridge-items.json", true);
                    xhttp.send();
                    xhttp.onreadystatechange = () => {
                        if (xhttp.readyState === XMLHttpRequest.DONE && xhttp.status === 200) {
                            const data = xhttp.responseText;
                            availableItems = JSON.parse(data);
                            create_drop_off_page();
                        }
                    };
                };
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

// creates the drop off page
const create_drop_off_page = () => {
    wipe();
    display_menu_button();

    // head changes
    const titleText = "Drop off an item to a community fridge";
    title.text = titleText;

    // body changes, add event listeners
    body.id = "drop-off-items";

    const section = document.createElement("section");
    body.appendChild(section);

    const h1 = document.createElement("h1");
    h1.innerHTML = titleText;
    section.appendChild(h1);

    const form = document.createElement("form");
    section.appendChild(form);

    const grocery_item_label = document.createElement("label");
    grocery_item_label.innerHTML = "Choose an item:";
    grocery_item_label.for = "grocery-item-select";
    const grocery_item_select = document.createElement("select");
    grocery_item_select.id = "grocery-item-select";
    grocery_item_select.addEventListener("change", check_drop_off);
    const placeholderOption = document.createElement("option");
    placeholderOption.innerHTML = "Choose an item...";
    placeholderOption.disabled = true;
    placeholderOption.selected = true;
    grocery_item_select.appendChild(placeholderOption);
    availableItems.forEach((item) => {
        const option = document.createElement("option");
        option.value = item.name.toLowerCase().replaceAll(" ", "-");
        option.innerHTML = item.name;
        grocery_item_select.appendChild(option);
    });
    form.appendChild(grocery_item_label);
    form.appendChild(grocery_item_select);
    form.appendChild(document.createElement("br"));

    const add_item_button = document.createElement("button");
    add_item_button.innerHTML = "Add an item";
    add_item_button.addEventListener("click", create_add_item_page);
    add_item_button.addEventListener("mouseenter", (event) => event.target.classList.add("mouseenter"));
    add_item_button.addEventListener("mouseleave", (event) => event.target.classList.remove("mouseenter"));
    form.appendChild(add_item_button);
    form.appendChild(document.createElement("br"));
    form.appendChild(document.createElement("br"));

    const number_items_label = document.createElement("label");
    number_items_label.innerHTML = "Number of items:";
    number_items_label.for = "number-items-input";
    const number_items_input = document.createElement("input");
    number_items_input.type = "text";
    number_items_input.id = "number-items-input";
    number_items_input.addEventListener("input", check_drop_off);
    form.appendChild(number_items_label);
    form.appendChild(number_items_input);
    form.appendChild(document.createElement("br"));
    form.appendChild(document.createElement("br"));

    drop_off_submit = document.createElement("button");
    drop_off_submit.innerHTML = "Find fridges";
    drop_off_submit.disabled = true;
    drop_off_submit.addEventListener("mouseenter", (event) => {
        if (!event.target.disabled) {
            event.target.classList.add("mouseenter");
        }
    });
    drop_off_submit.addEventListener("mouseleave", (event) => {
        if (!event.target.disabled) {
            event.target.classList.remove("mouseenter");
        }
    });
    drop_off_submit.addEventListener("click", find_fridges);
    form.appendChild(drop_off_submit);
};

// creates the add item page
const create_add_item_page = () => {
    wipe();
    display_menu_button();

    const titleText = "Add an item";
    title.text = titleText;

    body.id = "add-an-item";

    const section = document.createElement("section");
    body.appendChild(section);

    const h1 = document.createElement("h1");
    h1.innerHTML = titleText;
    section.appendChild(h1);

    const form = document.createElement("form");
    section.appendChild(form);

    const name_label = document.createElement("label");
    name_label.innerHTML = "Name: ";
    name_label.for = "name-input";
    const name_input = document.createElement("input");
    name_input.type = "text";
    name_input.id = "name-input";
    name_input.addEventListener("input", check_add_item_fields);
    form.appendChild(name_label);
    form.appendChild(name_input);
    form.appendChild(document.createElement("br"));
    form.appendChild(document.createElement("br"));

    const type_label = document.createElement("label");
    type_label.innerHTML = "Type: ";
    type_label.for = "type-input";
    const type_input = document.createElement("input");
    type_input.type = "text";
    type_input.id = "type-input";
    type_input.addEventListener("input", check_add_item_fields);
    form.appendChild(type_label);
    form.appendChild(type_input);
    form.appendChild(document.createElement("br"));
    form.appendChild(document.createElement("br"));

    const image_label = document.createElement("label");
    image_label.innerHTML = "Image: ";
    image_label.for = "image-input";
    const image_input = document.createElement("input");
    image_input.type = "file";
    image_input.accept = "image/jpeg, image/png";
    image_input.id = "image-input";
    image_input.addEventListener("input", check_add_item_fields);
    form.appendChild(image_label);
    form.appendChild(image_input);

    add_item_submit = document.createElement("button");
    add_item_submit.innerHTML = "Add item";
    add_item_submit.disabled = true;
    add_item_submit.addEventListener("mouseenter", (event) => {
        if (!event.target.disabled) {
            event.target.classList.add("mouseenter");
        }
    });
    add_item_submit.addEventListener("mouseleave", (event) => {
        if (!event.target.disabled) {
            event.target.classList.remove("mouseenter");
        }
    });
    add_item_submit.addEventListener("click", (event) => {
        event.preventDefault();

        const image = image_input.files[0];
        const filetype = image.type.slice(image.type.indexOf("/") + 1);
        const filename = `/images/${type_input.value}/${name_input.value}.${filetype}`;

        const base64Reader = new FileReader();
        base64Reader.readAsDataURL(image);

        let base64 = "";
        base64Reader.onload = () => {
            base64 += base64Reader.result;
        };
        base64Reader.onerror = (error) => console.log(`Error: ${error}`);
        base64Reader.onloadend = () => {
            const payload = {
                name: name_input.value,
                type: type_input.value,
                path: filename,
                data: base64
            };

            const postXhttp = new XMLHttpRequest();
            postXhttp.open("POST", "http://localhost:8000/newItem", true);
            postXhttp.setRequestHeader("Content-Type", 'application/json');
            postXhttp.send(JSON.stringify(payload));
            postXhttp.onreadystatechange = () => {
                if (postXhttp.readyState === XMLHttpRequest.DONE && postXhttp.status === 201) {
                    // on success retrieve newer data
                    const getXhttp = new XMLHttpRequest();
                    getXhttp.open("GET", "http://localhost:8000/comm-fridge-items.json", true);
                    getXhttp.send();
                    getXhttp.onreadystatechange = () => {
                        if (getXhttp.readyState === XMLHttpRequest.DONE && getXhttp.status === 200) {
                            // on success create the success notification
                            availableItems = JSON.parse(getXhttp.responseText);
                            show_notification(`${name_input.value} was successfully added to the items list!`);

                            // i guess it's best to recreate the page at this point
                            create_drop_off_page();
                        }
                    };
                }
            }
        };
    });
    form.appendChild(add_item_submit);
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

    const availableFilters = new Set(availableItems.map((item) => item.type));
    availableFilters.forEach((filter) => {
        const filter_li = document.createElement("li");
        const filter_item_count = Object.values(selected_fridge.items).filter((item) => item.type === filter).length;
        filter_li.innerHTML = `${filter.charAt(0).toUpperCase()}${filter.substring(1).toLowerCase()} (${filter_item_count})`;

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

    // determine available quantity for item
    const item_name = event.target.parentNode.parentNode.childNodes[0].textContent;
    const pickup_quantity_elem = event.target.parentNode.querySelector("textarea");
    const quantityString = Object.values(event.target.parentNode.parentNode.childNodes).filter((elem) => elem.textContent.match(/^Quantity: \d+$/) !== null)[0].textContent;
    const max_pickup = parseInt(quantityString.slice(quantityString.indexOf(" ")), 10);
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

// validates drop off items against fridge capability and capacity
// enables "Find fridges" button if so
const check_drop_off = (event) => {
    switch (event.target.id) {
        case "grocery-item-select":
            dropOffObject.name = `${event.target.value.charAt(0).toUpperCase()}${event.target.value.slice(1)}`.replaceAll("-", " ");
            validSelectedItem = true;
            break;
        case "number-items-input":
            dropOffObject.number = parseInt(event.target.value, 10);
            validNumberOfItems = !isNaN(dropOffObject.number);
            break;
    }
    drop_off_submit.disabled = !(validSelectedItem && validNumberOfItems);
};

// when the "Find fridges" button is pressed on the drop off page
const find_fridges = (event) => {
    event.preventDefault();
    const callback = () => {
        const itemType = availableItems.filter((item) => item.name === dropOffObject.name)[0].type;
        let availableFridges = fridges.filter((fridge) => {
            console.log(fridge)
            if (
                // fridge is not full
                (fridge.capacity !== 100) &&
                // fridge accepts item type
                (fridge.accepted_types.includes(itemType)) &&
                // fridge can accept item count
                (fridge.can_accept_items >= dropOffObject.number)
            ) {
                return fridge;
            }
        });

        if (availableFridges.length > 1) {
            // custom sort
            availableFridges = availableFridges.sort((f1, f2) => {
                // check if fridge doesn't have the item
                const f1_item = f1.items.filter((item) => item.name === dropOffObject.name);
                const f2_item = f2.items.filter((item) => item.name === dropOffObject.name);
                if (f1_item.length === 1 && f2_item.length === 0) {
                    return 1;
                } else if (f1_item.length === 0 && f2_item.length === 1) {
                    return -1;
                } else if (f1_item.length === 0 && f2_item.length === 0) {
                    // check which fridge is less full, since neither fridge has any quantity of said item
                    const f1_capacity = f1.capacity;
                    const f2_capacity = f2.capacity;
                    if (f1_capacity > f2_capacity) {
                        return 1;
                    } else if (f1_capacity < f2_capacity) {
                        return -1;
                    } else {
                        return 0;
                    }
                } else {
                    // check which fridge has less of the item
                    const f1_item_count = f1_item[0].quantity;
                    const f2_item_count = f2_item[0].quantity;
                    if (f1_item_count > f2_item_count) {
                        return 1;
                    } else if (f1_item_count < f2_item_count) {
                        return -1;
                    } else {
                        // check which fridge is less full
                        const f1_capacity = f1.capacity;
                        const f2_capacity = f2.capacity;
                        if (f1_capacity > f2_capacity) {
                            return 1;
                        } else if (f1_capacity < f2_capacity) {
                            return -1;
                        } else {
                            return 0;
                        }
                    }
                }
            });
        }

        // recreate section if needed (when find fridges is pressed again)
        let section = document.getElementById("found-fridges");
        if (section !== null) {
            body.removeChild(section);
        }
        section = document.createElement("section");
        section.id = "found-fridges";
        body.appendChild(section);

        // creates the fridge buttons
        const fridge_ids = availableFridges.map((fridge) => fridge.name.replaceAll(" ", "-"));
        for (let i = 0; i < fridge_ids.length; i++) {
            const fridge = availableFridges[i];

            const image = document.createElement("img");
            image.src = "images/fridge.svg";
            image.id = fridge_ids[i];

            const button = document.createElement("button");
            if (i === 0) {
                // since we sorted the availableFridges array, index 0 is the optimal fridge
                button.innerHTML += `Needs ${dropOffObject.name} the most!`;
            }
            button.appendChild(image);
            button.id = fridge_ids[i];
            button.innerHTML += `<br>${fridge.name}<br>${fridge.address.street}<br>${fridge.contact_phone}`;

            button.addEventListener("mouseenter", (event) => event.target.classList.add("mouseenter"));
            button.addEventListener("mouseleave", (event) => event.target.classList.remove("mouseenter"));

            button.addEventListener("click", update_fridge);

            section.appendChild(button);
        };
    };

    // first, ensure that fridges data is current
    if (fridges.length === 0) {
        const xhttp = new XMLHttpRequest();
        xhttp.open("GET", "http://localhost:8000/comm-fridge-data.json", true);
        xhttp.send();
        xhttp.onreadystatechange = () => {
            if (xhttp.readyState === XMLHttpRequest.DONE && xhttp.status === 200) {
                const data = xhttp.responseText;
                fridges = JSON.parse(data);
                callback();
            }
        }
    } else {
        callback();
    }
};

// when a fridge is selected to be the recipient of the drop off items
const update_fridge = (event) => {
    const itemMetadata = availableItems.filter((item) => item.name === dropOffObject.name)[0];
    const payload = {
        fridge: event.target.id.replaceAll("-", " "),
        quantity: dropOffObject.number,
        itemName: itemMetadata.name,
        itemType: itemMetadata.type,
        itemImg: itemMetadata.img
    };

    // PUT item and fridge data
    const putXhttp = new XMLHttpRequest();
    putXhttp.open("PUT", "http://localhost:8000/updateFridge", true);
    putXhttp.setRequestHeader("Content-Type", "application/json");
    putXhttp.send(JSON.stringify(payload));
    putXhttp.onreadystatechange = () => {
        if (putXhttp.readyState === XMLHttpRequest.DONE && putXhttp.status === 200) {
            // on success retrieve newer data
            const getXhttp = new XMLHttpRequest();
            getXhttp.open("GET", "http://localhost:8000/comm-fridge-data.json", true);
            getXhttp.send();
            getXhttp.onreadystatechange = () => {
                if (getXhttp.readyState === XMLHttpRequest.DONE && getXhttp.status === 200) {
                    // on success create the success notification
                    fridges = JSON.parse(getXhttp.responseText);
                    show_notification(`The item has been successfully added to the ${payload.fridge}!`);

                    // i guess it's best to recreate the page at this point
                    create_drop_off_page();
                }
            };
        }
    };
};

// event handler for "Add an item" fields
const check_add_item_fields = (event) => {
    const value = event.target.value;
    switch (event.target.id) {
        case "name-input":
            if (value.match(/^[A-Z][a-z]+( [a-z]+)*$/)) {
                event.target.style.backgroundColor = "white";
                validNewItemName = true;
            } else {
                event.target.style.backgroundColor = "lightcoral";
                validNewItemName = false;
            }
            break;
        case "type-input":
            if (value.match(/^[a-z]+$/)) {
                event.target.style.backgroundColor = "white";
                validNewItemType = true;
            } else {
                event.target.style.backgroundColor = "lightcoral";
                validNewItemType = false;
            }
            break;
        case "image-input":
            const image = event.target.files[0];
            validNewItemImage = image.type === "image/png" || image.type === "image/jpeg";
            break;
    }

    // disable/enable the form submit button accordingly
    add_item_submit.disabled = !(validNewItemName && validNewItemType && validNewItemImage);
};

// shows a notification briefly
const show_notification = (text) => {
    const notification = document.createElement("p");
    notification.style.opacity = 1;
    notification.id = "notification";
    notification.innerHTML = text;
    const htmlTag = document.querySelector("html");
    htmlTag.appendChild(notification);

    // very extra fade out effect
    setTimeout(() => {
        const fadeEffect = setInterval(() => notification.style.opacity -= 0.01, 10);
        setTimeout(() => {
            notification.remove();
            clearInterval(fadeEffect);
        }, 2000);
    }, 2000);
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
