//  Gotta at shelves for buttons and comps to lean on 
// How in the hell am I gonna do that
// the lovely thing is also that all buttons and such
// must face up, not to the side because 3d-printing
// unsupported holes on the side isn't very good

$fn = 200;

// box measures
length = 75;
width = 55;
height = 35;
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

// screen
sWidth = 25;
sHeight = 14;

// usb
usbWidth = 7.7;
usbHeight = 3.8;

// Box
translate([10, 10, 0]){ 
    difference() {
        
        // Box  
        roundedBox(length, width, height, radius);
        
        translate([1, 1, 1]) {
            difference() {
                // Box interior
                roundedBox(length-2, width-2, height, radius);
                
                // Shelf, cubes and stuff go here
                // God damn this is gonna be finnicky
                
                // Screenholes
                translate([width/2+2, height+sHeight-1, 0]) {
                    screwHole(); 
                }
                translate([sWidth/2-6, height+sHeight-1, 0]) {
                    screwHole(); 
                }
                translate([sWidth/2-6, height-5, 0]) {
                    screwHole(); 
                }
                translate([width/2+2, height-5, 0]) {
                    screwHole(); 
                }
                
                // Micholes
                translate([2, height+sHeight+2, 0]) {
                    screwHole(); 
                }
                translate([-7, height+sHeight+2, 0]) {
                    screwHole(); 
                }
                
                // Buzzholes
                translate([width/3 + 6, 9, 0]) {
                    screwHole();
                }
                translate([width/3 + 6, -3, 0]) {
                    screwHole();
                }
                translate([8, -3, 0]) {
                    screwHole();
                }
                translate([8, 9, 0]) {
                    screwHole();
                }
            }
        }
        
        // Screen
        translate([width/2-sWidth/2 + 6, height+sHeight/2, 0]) {
            cube([sWidth, sHeight, 5], center = true);
            cylinder(h=5, r=micRadius, center = true);
        }
        // Mic
        translate([0, height+sHeight, 0]) {
            cylinder(h=20, r=micRadius, center = true);
        }
        // Button 1
        translate([0, height, 0]) {
            cube([buttWidth, buttHeight, 5], center = true);
        }
        // Button 2
        translate([0, height-10, 0]) {
            cube([buttWidth, buttHeight, 5], center = true);
        }
        // Buzzer
        translate([width/3 + 2, 6, 0]) {
            cylinder(h=5, r=buzzRadius, center = true);
        }
        // Potmeter
        translate([2, 2, 0]) {
            cylinder(h=5, r=potRadius, center = true);
        }
        
    } 
}

// Bottom
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

module screwHole() {
    difference() {
        cube(4);
        translate([2, 2, -1]) {
            cylinder(h=10,r=1,center=false);
        }
    }
}


