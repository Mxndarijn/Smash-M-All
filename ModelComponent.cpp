#include "ModelComponent.h"
ModelComponent::ModelComponent(ObjModel* model) : model(model)
{

}

ModelComponent::~ModelComponent()
{

}

void ModelComponent::draw()
{
	tigl::shader->enableTexture(true);
	model->draw();
	tigl::shader->enableTexture(false);
}