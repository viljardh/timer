$fn = 200;

length = 50;
width = 50;
height = 20;
radius = 10;

swidth = 24.5;
sheight = 15.2;

translate([10, 10, 0]){ 
    difference() {
        roundedBox(length, width, height, radius);
        translate([1, 1, 1]) {
            roundedBox(length-2, width-2, height, radius);
        }
    }
}

translate([width*2, 10, 0]) {
    mirror([1, 0, 0]) {
        difference() {
            union() {
                roundedBox(length, width, 1, radius);
                difference() {
                    translate([1, 1, -1]) {
                        roundedBox(length-2, width-2, 4, radius);
                    }
                    translate([2, 2, 0]) {
                        roundedBox(length-4, width-4, 4, radius);
                    }
                }
            }
            translate([3, -1, -2]) {
                cube([swidth, sheight, 5]);
            }
            translate([length/2 + 4, width/2 + 2, -2]) {
                cylinder(h=height, r = 4.9, center = true);
            }
            translate([length/5 + 8, width/2 + 2, -2]) {
                cylinder(h=height, r = 2.9, center = true);
            }
            
            translate([length/2 - 25, width/2 - 4, -2]) {
                cube([12, 11, 5]);
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
