uniform float focusDistance;
uniform float aperture;

const float PI = 3.14159265;
const float maxSize = 32.;

void main() {
	// get the homogeneous 2d position
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	// use the distance from the camera and aperture to determine the radius
	// the +1 is because point sizes <1 are rendered differently than those >1
  gl_PointSize = min(maxSize, abs(gl_Position.z - focusDistance) * aperture + 1.);
  gl_FrontColor = gl_Color;
  float radius = gl_PointSize / 2.;
	// divide the color alpha by the area
  gl_FrontColor.a /= aperture;
  gl_FrontColor.a /= PI * radius * radius;
}
