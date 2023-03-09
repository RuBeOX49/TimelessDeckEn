#pragma once
#ifndef NODEBUTTON_H_
#define NODEBUTTON_H_

#include "../../components/Node Components/NodeButtonComponent.h"

class NodeButton : public GameObject {
public:
	// A�ade los componentes al bot�n y crea sus animaciones
	virtual void initGameObject(vector<Node*>::const_iterator nodeIt, CallBack _cb);
};

#endif // !NODEBUTTON_H_