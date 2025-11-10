/* $Id$ */
#include "colors.inc"
#include "shapes.inc"
#include "textures.inc"
#include "skies.inc"

object {
	O_Cloud1
}

sky_sphere {
	pigment {
		gradient y
		color_map {
			[0.0 White*0.8]
			[0.2 rgb<0.2 0.2 0.7>]
		}
	}
}

plane {
	y, 0
	pigment {
		checker White Red
	}
	finish {
		phong 1.0
		reflection 0.3
	}
}

object {
	union {
		difference {
			cylinder {
				<0, 0, 1>
				<0, 0, -1>
				1
			}
			object {
				Cube
				scale <1, 1, 2>
				rotate <0, 0, 45>
				scale <0.5, 0.5, 1>
				translate <0.5, 0.5, 0>
			}
			object {
				Cube
				scale <1, 1, 2>
				rotate <0, 0, 45>
				scale <0.5, 0.5, 1>
				translate <sqrt(2)/4, sqrt(2)/4, 0>
			}
			cylinder {
				<0, 0, 2>
				<0, 0, -2>
				0.5
			}
			translate <sqrt(2) / 4, sqrt(2) / 4, 0>
		}
#declare I = 1;
#while (I <= 4)
		object {
			Cube
			scale <0.5, 0.5, 1>
			rotate <0, 0, 45>
			translate <-sqrt(2)/2*I+0.25, -sqrt(2)/2*I+0.25, 0>
		}
#declare I = I + 1;
#end
		cylinder {
			<-sqrt(2)/2*I+0.25+sqrt(2)/4, -sqrt(2)/2*I+0.25+sqrt(2)/4, 1>
			<-sqrt(2)/2*I+0.25+sqrt(2)/4, -sqrt(2)/2*I+0.25+sqrt(2)/4, -1>
			0.5
		}
		translate <0.5, 3.5, 0>
		scale <1, 1, 0.5>
		scale <0.3, 0.3, 0.3>
	}
	pigment {
		color rgb <0.75, 0.75, 0.75>
	}
	finish {
		phong 1.0
		reflection 0.05
	}
}

light_source {
	<250, 250, 250>
	color White * 2
	parallel point_at <0, 0, 0>
}

camera {
	location <1.25/1.25, 0.4, 3/1.25>
	look_at <-0.125, 0.75, 0>
	angle 35
	up <0, 1, 0>
	right image_width/image_height*x
}
