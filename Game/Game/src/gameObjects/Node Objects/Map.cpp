#include "Map.h"
#include "../../core/SDLApplication.h"
#include "../../data/json/JSON.h"

Map::Map() : nodeMap(HEIGHT, vector<Node*>(MAX_NODES, nullptr)), initialNodes(vector<Node*>()), unlockedNodes(initialNodes), currentNode(nullptr), nodesPerHeight(HEIGHT, 0) {
	//createMap();
}

void Map::createMap() {
	// Crear el mapa de nodos
	// Crear los nodos (con unos iniciales desbloqueados)
	nodeTextureKeys[NodeType::Battle] = BATTLE_NODE_TEXTURE_KEY;
	nodeTextureKeys[NodeType::Shop] = SHOP_NODE_TEXTURE_KEY;
	nodeTextureKeys[NodeType::Chest] = CHEST_NODE_TEXTURE_KEY;
	nodeLoads[NodeType::Battle] = [](BattleType t) { SDLApplication::instance()->pushNewScene<BattleScene>(t); };
	nodeLoads[NodeType::Chest] = [](BattleType t) { SDLApplication::instance()->pushNewScene<ChestScene>(); };
	nodeLoads[NodeType::Shop] = [](BattleType t) { SDLApplication::instance()->pushNewScene<ShopScene>(); };

	nodeMap[0][1] = new Node(Needs(Battle, 3, false), nodeTextureKeys[Battle], nodeLoads[Battle], Battle, BattleType(rand() % _NONE));
	initialNodes.push_back(nodeMap[0][1]);
	++nodesPerHeight[0];

	nodeMap[1][1] = new Node(Needs(Chest, 0, false), nodeTextureKeys[Chest], nodeLoads[Chest], Chest);
	++nodesPerHeight[1];
	nodeMap[0][1]->addToNextNodes(nodeMap[1][1], 1);

	nodeMap[2][0] = new Node(Needs(Battle, 3, false), nodeTextureKeys[Battle], nodeLoads[Battle], Battle, BattleType(rand() % _NONE));
	++nodesPerHeight[2];
	nodeMap[1][1]->addToNextNodes(nodeMap[2][0], 0);
	nodeMap[2][2] = new Node(Needs(Battle, 3, false), nodeTextureKeys[Battle], nodeLoads[Battle], Battle, BattleType(rand() % _NONE));
	++nodesPerHeight[2];
	nodeMap[1][1]->addToNextNodes(nodeMap[2][2], 2);

	nodeMap[3][1] = new Node(Needs(Shop, 0, false), nodeTextureKeys[Shop], nodeLoads[Shop], Shop);
	++nodesPerHeight[3];
	nodeMap[2][0]->addToNextNodes(nodeMap[3][1], 1);
	nodeMap[2][2]->addToNextNodes(nodeMap[3][1], 1);

	generateLevel(nodeMap, 4);
	//initMap("../Game/src/data/game.map.json");

	nodeMap[HEIGHT - 2][1] = new Node(Needs(Chest, 0, false), nodeTextureKeys[Chest], nodeLoads[Chest], Chest, BattleType(rand() % _NONE));
	++nodesPerHeight[HEIGHT - 2];
	nodeMap[HEIGHT - 1][1] = new Node(Needs(Battle, 0, false), nodeTextureKeys[Battle], nodeLoads[Battle], Battle, _BOSSBATTLE);
	++nodesPerHeight[HEIGHT - 1];

	for (int i = 0; i < MAX_NODES; ++i) {
		if (nodeMap[HEIGHT - 3][i] != nullptr) nodeMap[HEIGHT - 3][i]->addToNextNodes(nodeMap[HEIGHT - 2][1], i);
	}

	nodeMap[HEIGHT - 2][1]->addToNextNodes(nodeMap[HEIGHT - 1][1], 1);
	// TODO: asignar los siguientes de los iniciales y a�adir los 2 �ltimos, preferblemente desde json


	for (Node* n : unlockedNodes) {
		n->unlock();
	}
}

Map::~Map() {
	clearMap();
}

void Map::clearMap() {
	// Borrar el mapa de nodos
	for (auto& height : nodeMap) {
		for (auto& node : height) {
			if (node != nullptr) delete node;
			node = nullptr;
		}
	}
}

// Hay ciertos nodos que son compatibles bajo unas condiciones, este m�todo tiene una probabilidad de juntar dos nodos que cumplan esas condiciones
void Map::lookForCompatibles(Needs& n1, Needs& n2) {
	// Iguales
	if (n1.type == n2.type && n1.battleCounter == n2.battleCounter && n1.battleOnNext == n2.battleOnNext) {
		if (sdlutils().rand().nextInt(0, 2) == 0) n2 = Needs(NodeType::None, 0, false);
	}
	else if (n1.type == Battle && n2.type == Battle) {
		// B1T + B2F = B2T && B1T + B2T = B2T
		if (n1.battleCounter == 1 || n2.battleCounter == 1) {
			if (abs(n1.battleCounter - n2.battleCounter) == 1) {
				if (sdlutils().rand().nextInt(0, 2) == 0) {
					n1 = Needs(Battle, 2, true);
					n2 = Needs(NodeType::None, 0, false);
				}
			}
		}
		// B2T + B2F = B2T
		else if (n1.battleCounter == 2 && n2.battleCounter == 2) {
			if (sdlutils().rand().nextInt(0, 2) == 0) {
				n1 = Needs(Battle, 2, (n1.battleOnNext || n2.battleOnNext));
				n2 = Needs(NodeType::None, 0, false);
			}
		}
		// B2F + B3F = B3F
		else if (n1.battleCounter == 3 || n2.battleCounter == 3) {
			if (abs(n1.battleCounter - n2.battleCounter) == 1) {
				if (sdlutils().rand().nextInt(0, 2) == 0) {
					n1 = Needs(Battle, 3, false);
					n2 = Needs(NodeType::None, 0, false);
				}
			}
		}
	}
}

// Recibe las condiciones con las que se cre� un nodo y devuelve las condiciones que necesita para su siguiente nodo
Needs Map::getNeed(Needs prevNeed) {
	Needs newNeed;
	// I, 0, F -> B, 1, T
	if (prevNeed.type == Chest || prevNeed.type == Shop) {
		newNeed = Needs(Battle, 1, true);
	}
	else {
		// B, 1, T -> B, 2, F
		if (prevNeed.battleCounter == 1) {
			newNeed = Needs(Battle, 2, false);
		}
		// B, 3, F -> I, 0, F
		else if (prevNeed.battleCounter == 3) {
			NodeType difNode = NodeType(sdlutils().rand().nextInt(1,3));
			newNeed = Needs(difNode, 0, false);
		}
		else {
			// B, 2, T -> B, 3, F
			if (prevNeed.battleOnNext) {
				newNeed = Needs(Battle, 3, false);
			}
			// B, 2, 3 -> (B, 3, F) || (I, 0, F)
			else {
				switch (rand() % 2) {
				case 0:
					newNeed = Needs(Battle, 3, false);
					break;
				case 1:
					NodeType difNode = NodeType(sdlutils().rand().nextInt(1, 3));
					newNeed = Needs(difNode, 0, false);
					break;
				}
			}
		}
	}
	return newNeed;
}

// Recibe un vector de nodos y devuelve un vector con las condiciones para crear su siguiente altura
vector<Needs> Map::getNeeds(vector<Node*> const& nodes) {
	vector<Needs> needs(MAX_NODES, Needs(NodeType::None, 0, false));
	for (int i = 0; i < MAX_NODES; ++i) {
		if (nodes[i] != nullptr) {
			needs[i] = getNeed(nodes[i]->getNeeded());
		}
	}

	lookForCompatibles(needs[0], needs[1]);
	lookForCompatibles(needs[1], needs[2]);
	if (needs[1].type == NodeType::None) lookForCompatibles(needs[0], needs[2]);
	return needs;
}

// Evita cruces entre conexiones de nodos
bool Map::validConection(vector<vector<Node*>> m, int alt, int i, int j) {
	// Altura anterior          Altura actual
	//        k                        i
	//        j                        l
	// El enlace ij solo se puede dar si ningun nodo mayor o igual a k se une a ningun nodo menor o igual a l

	// Si j es el primer nodo de la altura anterior compruebo si los siguientes a �l se conectan a alguno anterior a mi
	if (j == 0) {
		for (int k = j + 1; k < MAX_NODES; k++) {
			if (m[alt - 1][k] != nullptr) {
				for (int l = i - 1; l > -1; l--) {
					if (m[alt][l] != nullptr && m[alt - 1][k]->conectsWith(l)) return false;
				}
			}
		}
	}

	// Si j es el nodo del centro de la altura anterior miro si el nodo de la der se conecta a alguno anterior y si el de la izq a uno siguiente
	if (j == 1) {
		if (m[alt - 1][2] != nullptr) {
			for (int l = i - 1; l > -1; l--) {
				if (m[alt][l] != nullptr && m[alt - 1][2]->conectsWith(l)) return false;
			}
		}

		if (m[alt - 1][0] != nullptr) {
			for (int l = i + 1; l < MAX_NODES; l++) {
				if (m[alt][l] != nullptr && m[alt - 1][0]->conectsWith(l)) return false;
			}
		}
	}

	// Si j es el nodo de la derecha miro si algun nodo anterior se conecta a alguno siguiente a mi
	if (j == 2) {
		for (int k = j - 1; k > -1; k--) {
			if (m[alt - 1][k] != nullptr) {
				for (int l = i + 1; l < MAX_NODES; l++) {
					if (m[alt][l] != nullptr && m[alt - 1][k]->conectsWith(l)) return false;
				}
			}
		}
	}

	return true;
}

// Comprueba si un nodo puede tener a otro como siguiente, recibe sus condiciones de creaci�n
bool Map::linkableNodes(Needs prev, Needs next) {
	if ((prev.type == Chest || prev.type == Shop) && next.type == Battle && next.battleOnNext) return true;
	if (prev.type == Battle && prev.battleCounter == 1 && next.type == Battle && next.battleCounter == 2) return true;
	if (prev.type == Battle && prev.battleCounter == 1 && next.type == Battle && next.battleCounter == 3 && !next.battleOnNext) return true;
	if (prev.type == Battle && prev.battleCounter == 3 && (next.type == Shop || next.type == Chest)) return true;
	if (prev.type == Battle && prev.battleCounter == 2 && next.type == Battle && !next.battleOnNext && next.battleCounter == 3) return true;
	if (prev.type == Battle && prev.battleCounter == 2 && !prev.battleOnNext && (next.type == Shop || next.type == Chest)) return true;
	return false;
}

// Inicializa enteros que se usar�n para recorrer de izq a der o al reves
void Map::getRandomWay(int& start, int& end, int& sum) {
	// De izq a derecha
	if (rand() % 2 == 0) {
		sum = 1;
		start = 0;
		end = MAX_NODES;
	}
	// De der a izq
	else {
		sum = -1;
		start = MAX_NODES - 1;
		end = -1;
	}
}

// Recorre la altura anterior a la indicada para buscar nodos anteriores a aquel con el �ndice pasado
bool Map::lookForPrevious(vector<vector<Node*>> m, int alt, int ind) {
	Node* n = m[alt][ind];
	bool enlazado = false;

	int sum, start, end;
	getRandomWay(start, end, sum);
	for (int i = start; i != end; i += sum) {
		if (m[alt - 1][i] != nullptr && m[alt - 1][i]->getNextCount() < 2 && linkableNodes(m[alt - 1][i]->getNeeded(), n->getNeeded())
			&& validConection(m, alt, ind, i)) {
			m[alt - 1][i]->addToNextNodes(n, ind);
			enlazado = true;
		}
	}
	return enlazado;
}


// Genera los nodos en la altura indicada, se llama recursivamente hasta llegar al final del arbol
void Map::generateLevel(vector<vector<Node*>>& m, int k) {
	if (k < HEIGHT - 2) {
		// Contador de nodos generados y vector de la nodos requeridos de la altura anterior
		vector<Needs> ns = getNeeds(m[k - 1]);

		// Se generan el m�nimo n�mero de nodos de un nivel con sus tipos requeridos
		for (int i = 0; i < ns.size(); ++i) {
			if (ns[i].type != NodeType::None) {
				addNode(k, i, ns[i]);
			}
		}

		// Random entre m�nimo y m�ximo y se generan los que falten
		for (int i = 0; i < MAX_NODES; ++i) {
			int copy = i;
			if (m[k][i] == nullptr && rand() % 5 > 0) {
				if (copy == 0) {
					if (m[k][1] == nullptr) copy++;
					copy++;
					addNode(k, i, m[k][copy]->getNeeded());
				}
				else if (copy == 2) {
					if (m[k][1] == nullptr) copy--;
					copy--;
					addNode(k, i, m[k][copy]->getNeeded());
				}
				else {
					if (m[k][0] != nullptr) copy--;
					else copy++;
					addNode(k, i, m[k][copy]->getNeeded());
				}
			}
		}

		// Ajuste para poder buscar los siguientes por la derecha o la izquierda aleatoriamente
		int sum, start, end;
		getRandomWay(start, end, sum);

		// Recorremos los nodos creados enlazandolos con los de la altura anterior
		for (int i = start; i != end; i += sum) {
			// Si son imposibles de enlazar los destruimos
			if (m[k][i] != nullptr && !lookForPrevious(m, k, i)) {
				eraseNode(k, i);
			}
		}

		// Comprobamos si en la altura anterior hay alguno que no se ha enlazado
		bool emptyNext = false;
		for (int i = 0; i < MAX_NODES && !emptyNext; ++i) {
			if (m[k - 1][i] != nullptr && m[k - 1][i]->getNextCount() <= 0) emptyNext = true;
		}

		// Si alg�n nodo ha quedado sin siguientes, se vuelve a hacer la altura
		if (emptyNext) {
			for (int i = 0; i < MAX_NODES; i++) {
				if (m[k][i] != nullptr) {
					eraseNode(k, i);
				}
				if (m[k - 1][i] != nullptr) m[k - 1][i]->clearLinks();
			}
			// Llamada recursiva sin aumentar la altura
			generateLevel(m, k);
		}

		// Llamada recursiva para la proxima altura
		else generateLevel(m, k + 1);
	}
}


// A�ade un nodo al mapa en la posici�n indicada con las condiciones indicadas
void Map::addNode(int height, int pos, Needs n) {
	nodeMap[height][pos] = new Node(n, nodeTextureKeys[n.type], nodeLoads[n.type], n.type, BattleType(rand() % _NONE));
	++nodesPerHeight[height];
}
// Borra el nodo en la posici�n dada
void Map::eraseNode(int height, int pos) {
	delete nodeMap[height][pos];
	nodeMap[height][pos] = nullptr;
	--nodesPerHeight[height];
}

void Map::initMap(string filename) {
	/*// TODO check the correctness of values and issue a corresponding
	// exception. Now we just do some simple checks, and assume input
	// is correct.

	// Load JSON configuration file. We use a unique pointer since we
	// can exit the method in different ways, this way we guarantee that
	// it is always deleted
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
	}

	// we know the root is JSONObject
	JSONObject root = jValueRoot->AsObject();
	JSONValue* jValue = nullptr;

	// TODO improve syntax error checks below, now we do not check
	//      validity of keys with values as sting or integer

	unordered_map<pair<int, int>, JSONArray> nexts;

	// load fonts
	jValue = root["map"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			nodeMap.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					int height = static_cast<int>(vObj["height"]->AsNumber());
					int pos = static_cast<int>(vObj["pos"]->AsNumber());
					std::string type = vObj["height"]->AsNumber();
					JSONArray next = vObj["next"]->AsArray();
#ifdef _DEBUG
					std::cout << "Loading node with id: " << name << std::endl;
#endif
					addNode(Needs(type, 0, false), height, pos);
					nexts[{height, pos}] = next;

				} else {
					throw "'node' array in '" + filename
							+ "' includes and invalid value";
				}
			}

			for (auto nodePos : nexts) {
				for (auto next : next.second) {
					if (next.size() == 0) {
						generateHeight(nodeMap, get<0>(nodePos.first));
						
					}
					else {
						int h = static_cast<int>(next[0]);
						if (h == -1) return;
						int p = static_cast<int>(next[1]);
						nodeMap[get<0>(nodePos.first)][get<1>(nodePos.first)]->addToNextNodes(nodeMap[h][p]);
					}
				}
			}
			
		} else {
			throw "'node' is not an array in '" + filename + "'";
		}
	}*/
}

void Map::setCurrentNode(Node* node) {
	currentNode = node;
}

void Map::completeCurrentNode() {
	currentNode->complete(unlockedNodes);
}

void Map::reloadMap() {
	clearMap();
	createMap();
}