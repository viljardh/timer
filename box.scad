//  Gotta at shelves for buttons and comps to lean on 
// How in the hell am I gonna do that

$fn = 200;

// box measures
length = 70;
width = 50;
height = 30;
radius = 10;

// mic measures
micRadius = 5;

// buzzer measures
buzzRadius = 6.2;

// potmeter
potRadius = 3;
potWidth = 9.8;
potHeight = 10.5;

// button
buttWidth = 6.2;
buttHeight = 6.3;

swidth = 24.5;
sheight = 15.2;

// Box
translate([10, 10, 0]){ 
    difference() {
        roundedBox(length, width, height, radius);
        translate([1, 1, 1]) {
            roundedBox(length-2, width-2, height, radius);
        }
    } 
    // insert cutouts here
}

// Top
translate([width*2, 10, 0]) {
    mirror([1, 0, 0]) {
        difference() {
            union() {
                roundedBox(length, width, 1, radius);
                difference() {
                    translate([1, 1, 0]) {
                        roundedBox(length-2, width-2, 3, radius);
                    }
                    translate([2, 2, 0]) {
                        roundedBox(length-4, width-4, 4, radius);
                    }
                }
            }
        }
    }
}
// usb-b 12*11mm

module roundedBox(length, width, height, radius) {
    
    dRadius = 2*radius;
    
    minkowski() {
        cube(size=[width-dRadius, length-dRadius, height]);
        cylinder(r=radius, h=0.01);
    }
}
