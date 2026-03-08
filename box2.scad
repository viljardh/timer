$fn = $preview ? 56 : 200;

// Outer box dimensions.
length = 75;
width = 55;
height = 35;
radius = 10;

// Feature dimensions.
micRadius = 5;
buzzRadius = 6.2;
potRadius = 3;
potWidth = 9.8;
potHeight = 10.5;
buttWidth = 6.2;
buttHeight = 6.3;
sWidth = 25;
sHeight = 14;
usbWidth = 7.7;
usbHeight = 3.8;

// Construction dimensions.
wall = 1;
cutDepth = 5;
micCutDepth = 20;
screwBlockSize = 4;
screwRadius = 1;
screwDepth = 10;

//Screw positions
screenScrewPos = [
    [width / 2 + 2, height + sHeight - 1, 0],
    [sWidth / 2 - 6, height + sHeight - 1, 0],
    [sWidth / 2 - 6, height - 5, 0],
    [width / 2 + 2, height - 5, 0]
];

micScrewPos = [
    [2, height + sHeight + 2, 0],
    [-7, height + sHeight + 2, 0]
];

buzzScrewPos = [
    [width / 3 + 6, 9, 0],
    [width / 3 + 6, -3, 0],
    [8, -3, 0],
    [8, 9, 0]
];

top();
bottom();

module top() {
    translate([10, 10, 0]) {
        difference() {
            roundedBox(length, width, height, radius);

            // Hollow out box and keep mounting standoffs.
            translate([wall, wall, wall]) {
                difference() {
                    roundedBox(length - 2 * wall, width - 2 * wall, height, radius);
                    placeScrewHoles(screenScrewPos);
                    placeScrewHoles(micScrewPos);
                    placeScrewHoles(buzzScrewPos);
                }
            }

            // Screen cutout (+ mic opening tied to screen area).
            translate([width / 2 - sWidth / 2 + 6, height + sHeight / 2, 0]) {
                cube([sWidth, sHeight, cutDepth], center = true);
                cylinder(h = cutDepth, r = micRadius, center = true);
            }

            // Mic cutout.
            translate([0, height + sHeight, 0]) {
                cylinder(h = micCutDepth, r = micRadius, center = true);
            }

            // Button cutouts.
            translate([0, height, 0]) {
                cube([buttWidth, buttHeight, cutDepth], center = true);
            }
            translate([0, height - 10, 0]) {
                cube([buttWidth, buttHeight, cutDepth], center = true);
            }

            // Buzzer and pot cutouts.
            translate([width / 3 + 2, 6, 0]) {
                cylinder(h = cutDepth, r = buzzRadius, center = true);
            }
            translate([2, 2, 0]) {
                cylinder(h = cutDepth, r = potRadius, center = true);
            }
        }
    }
}

module bottom() {
    translate([width * 2, 10, 0]) {
        mirror([1, 0, 0]) {
            union() {
                roundedBox(length, width, 1, radius);
                difference() {
                    translate([1, 1, 0]) {
                        roundedBox(length - 2, width - 2, 3, radius);
                    }
                    translate([2, 2, 0]) {
                        roundedBox(length - 4, width - 4, 4, radius);
                    }
                }
            }
        }
    }
}

module placeScrewHoles(positions) {
    for (p = positions) {
        translate(p) {
            screwHole();
        }
    }
}

module roundedBox(length, width, height, radius) {
    dRadius = 2 * radius;
    minkowski() {
        cube(size = [width - dRadius, length - dRadius, height]);
        cylinder(r = radius, h = 0.01);
    }
}

module screwHole() {
    difference() {
        cube(screwBlockSize);
        translate([screwBlockSize / 2, screwBlockSize / 2, -1]) {
            cylinder(h = screwDepth, r = screwRadius, center = false);
        }
    }
}


