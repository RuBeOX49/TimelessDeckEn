#pragma once

#include "../../utils/Singleton.h"
#include "Node.h"
#include <unordered_map>

const int MAX_NODES = 3;
const int MAX_SIG = 2;
const int HEIGHT = 17;

class Map : public Singleton<Map> {
	friend Singleton<Map>;
private:
	// Mapa de todos los nodos
	vector<vector<Node*>> nodeMap;
	vector<Node*> initialNodes;
	vector<Node*>& unlockedNodes;
	Node* currentNode; // Nodo actual

	string nodeTextureKeys[NodeType::None];
	function<void(BattleType)> nodeLoads[NodeType::None];

	// Constructora
	Map();

	// Hay ciertos nodos que son compatibles bajo unas condiciones, este m�todo tiene una probabilidad de juntar dos nodos que cumplan esas condiciones
	void lookForCompatibles(Needs& n1, Needs& n2);
	// Recibe las condiciones con las que se cre� un nodo y devuelve las condiciones que necesita para su siguiente nodo
	Needs getNeed(Needs prevNeed);
	// Recibe un vector de nodos y devuelve un vector con las condiciones para crear su siguiente altura
	vector<Needs> getNeeds(vector<Node*> const& nodes);

	// Evita cruces entre conexiones de nodos
	bool validConection(vector<vector<Node*>> m, int alt, int i, int j);
	// Comprueba si un nodo puede tener a otro como siguiente, recibe sus condiciones de creaci�n
	bool linkableNodes(Needs prev, Needs next);
	// Inicializa enteros que se usar�n para recorrer de izq a der o al reves
	void getRandomWay(int& start, int& end, int& sum);
	// Recorre la altura anterior a la indicada para buscar nodos anteriores a aquel con el �ndice pasado
	bool lookForPrevious(vector<vector<Node*>> m, int alt, int ind);
	// Genera los nodos en la altura indicada, se llama recursivamente hasta llegar al final del arbol
	void generateLevel(vector<vector<Node*>>& m, int k);
public:
	// Destructora
	~Map();
	// Inicializa el mapa de nodos
	void initMap(string filename);
	// Asigna el nodo actual
	void setCurrentNode(Node* node);
	// Completa el nodo actual
	void completeCurrentNode();
	// Devuelve una referencia constante al mapa de nodos
	inline vector<vector<Node*>> const& getNodeMap() { return nodeMap; }
};
// Referencia a la instancia del mapa
inline Map& map() { return *Map::instance(); }