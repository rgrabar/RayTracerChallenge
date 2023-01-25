#include "Material.h"
#include <iostream>

bool operator==(const Material& lhs, const Material& rhs) {
 return lhs.color == rhs.color && lhs.ambient == rhs.ambient
	 && lhs.diffuse == rhs.diffuse && lhs.specular == rhs.specular
	 && lhs.shininess == rhs.shininess;
}