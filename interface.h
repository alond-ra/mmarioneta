#pragma once

#ifndef INTERFACE_CLASS_H
#define INTERFACE_CLASS_H

#include "Model.h"
#include "Sphere.h"

void interfaz(Model& model);
void modelUndo(Model& model);
void modelRedo(Model& model);
void resetStateStack(std::stack<State> &stck, int n);
void modelReset(Model& marioneta);
//void buttons(Model& marioneta);

#endif