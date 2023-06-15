#include "RayCastComponent.h"
#include "tigl.h"
#include "GameObject.h"
#include "CameraComponent.h"

#define focalLength 1000
RayCastComponent::RayCastComponent(glm::vec2 webcamResolution, glm::mat4* projection, std::list<glm::vec2>* points) : webcamResolution(webcamResolution),
opticalCenter(glm::vec2(webcamResolution.x / 2, webcamResolution.y / 2)), points(points), projectionMat(projection)
{

}

RayCastComponent::~RayCastComponent()
{

}

void RayCastComponent::update(float deltaTime)
{
	if (points->empty()) 
		return;
	
	for (auto& point : *points) {
		lines.push_back(pointToVec3(point));
	}
}

void RayCastComponent::draw()
{
	glBegin(GL_LINES);
	glEnable(GL_DEPTH_TEST);
	for (auto& line : lines) {
		glVertex3f(line.x, line.y, line.z - 5);
		glVertex3f(line.x, line.y, line.z + 5);
	}
	glEnd();

	lines.clear();
}

glm::vec3 RayCastComponent::pointToVec3(glm::vec2 point)
{
	glm::vec3 position;
	// Vertaal 2D-beeldco�rdinaten naar genormaliseerde apparaatco�rdinaten (-1.0 tot 1.0)
	float normalized_x = 2.0 * (point.x - opticalCenter.x) / webcamResolution.x;
	float normalized_y = 2.0 * (point.y - opticalCenter.y) / webcamResolution.y;

	// Projectie van genormaliseerde apparaatco�rdinaten naar 3D-co�rdinaten
	glm::mat4 projection_matrix = glm::mat4(1.f);
	auto cameraComponent = gameObject->getComponent<CameraComponent>();
	if (cameraComponent) {
		projection_matrix = *projectionMat;
	}
		
	glm::vec4 homogeneous_coords(normalized_x, normalized_y, 0.0f, 1.0f);
	glm::vec4 transformed_coords = projection_matrix * homogeneous_coords;

	position.x = transformed_coords[0];
	position.y = -transformed_coords[1];
	position.z = transformed_coords[2];

	//std::cout << "position: " << position.x << ", " << position.y << ", " << position.z << "\n";
	return position;
}
