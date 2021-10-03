const insectsDoubling = (count) => {
    let weeks = 1;
    console.log(`Week ${weeks}: ${count}`);
    while (count < 10000) {
        weeks++;
        count *= 2;
        console.log(`Week ${weeks}: ${count}`);
    }
    console.log(`It will take ${weeks} for the insect population to exceed 10,000 insects`);
}

const insectsDoublingWithDisease = (count) => {
    let weeks = 1;
    console.log(`Week ${weeks}: ${count}`);
    while (count < 10000) {
        weeks++;
        if (weeks % 4 === 0) {
            count *= 0.6;
        }
        count *= 2;
        console.log(`Week ${weeks}: ${count}`);
    }
    console.log(`It will take ${weeks} for the insect population to exceed 10,000 insects when 40% of the population\nis killed by disease every 4 weeks`);
}

insectsDoubling(2);
console.log(`\n================================\n`);
insectsDoublingWithDisease(2);