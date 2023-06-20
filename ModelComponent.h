#pragma once
#include "DrawComponent.h"
#include "ObjModel.h"

class ModelComponent : public DrawComponent
{
	ObjModel* model;
public:
	ModelComponent(ObjModel* model);
	~ModelComponent();

	virtual void draw() override;
};